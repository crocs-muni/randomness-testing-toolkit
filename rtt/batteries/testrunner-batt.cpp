#include "testrunner-batt.h"

namespace rtt {
namespace batteries {

/************************************************************************/
/* Defined variables and corresponding condition variables and mutexes. */
/************************************************************************/
/* Sets how many test threads will be run at once. */
std::atomic_int threadCount{0};
/* Sets how long can be test running before killing */
std::atomic_int timeout{0};
/* Keeps tracks of how many running threads have not yet
 * spawned their child process. */
uint                    withoutChild = 0;
std::condition_variable withoutChild_cv;
std::mutex              withoutChild_mux;
/* Stores info about how many running threads are still waiting
 * for their child process to end. */
uint                    waitingForChild = 0;
std::condition_variable waitingForChild_cv;
std::mutex              waitingForChild_mux;
/* Stores pid of process that was reaped last.
 * Stores its exit code as well. */
int                     finishedPExitCode = 0;
std::atomic<pid_t>      finishedPid;
std::condition_variable finishedPid_cv;
std::mutex              finishedPid_mux;
/* Used to block thread that reaps finished processes until
 * last finished process is assigned to correct thread for processing. */
bool                    childReceived = false;
std::condition_variable childReceived_cv;
std::mutex              childReceived_mux;
/* Keeps state of threads.
 * PENDING - there are still threads to be created;
 * READY   - single or more threads were spawned but there are more to be created;
 * DONE    - all available threads were created, now we are just waiting for them to end */
int                     threadState = 0;
std::condition_variable threadState_cv;
std::mutex              threadState_mux;

/*************/
/* Functions */
/*************/
void TestRunner::executeTests(Logger * logger,
                              std::vector<IVariant *> & variants,
                              int maxThreads, int testTimeout) {
    threadCount = maxThreads;
    timeout = testTimeout;

    std::thread manager(threadManager , std::ref(variants));
    /* String that will be used in logs */
    std::string objectInfo = "Process reaper";

    /* Thread can proceed only after threadMaker notifies this thread. */
    std::unique_lock<std::mutex> threadsReady_lock(threadState_mux);
    threadState_cv.wait(threadsReady_lock ,
                        []{ return (threadState == THREAD_STATE_DONE) ||
                                   (threadState == THREAD_STATE_READY); });
    if(threadState == THREAD_STATE_READY) {
        /* Flip state if there are any unexecuted tests left */
        threadState = THREAD_STATE_PENDING;
    }
    threadsReady_lock.unlock();

    std::unique_lock<std::mutex> withoutChild_lock(withoutChild_mux , std::defer_lock);
    std::unique_lock<std::mutex> waitingForChild_lock(waitingForChild_mux , std::defer_lock);
    std::unique_lock<std::mutex> childReceived_lock(childReceived_mux , std::defer_lock);

    for(;;) {
        /* Here, I need to lock waitingForChild and withoutChild
         * so no new threads will be created while this thread will wait.
         * Furthermore, this thread will start reaping processes only if all currently
         * active threads are waiting for child through finishedPid */
        std::lock(waitingForChild_lock , withoutChild_lock);
        waitingForChild_cv.wait(waitingForChild_lock ,
                                []{ return waitingForChild == withoutChild; });
        /* I can reap finished process now and annouce his PID. */
        /* finishedPid is atomic variable, I can do this w/o mutex */
        //int status;
        finishedPid = wait(&finishedPExitCode);
        /* I can unlock mutexes now, newly created threads
         * can begin to wait for their process */
        withoutChild_lock.unlock();
        waitingForChild_lock.unlock();
        if(finishedPid > 0) {
            /* Some child process finished, hand it out to corresponding
             * thread for processing */
            /* Notifying all waiting threads that there is new finished process. */
            finishedPid_cv.notify_all();
            /* Thread that owns annouced pid will set childReceived to true.
             * This thread cannot continue without knowing that pid is being processed
             * to avoid rewriting of pid before all of the threads check it. */
            childReceived_lock.lock();
            childReceived_cv.wait(childReceived_lock , []{ return childReceived; });
            /* Set to false for next iteration */
            childReceived = false;
            childReceived_lock.unlock();
        } else {
            /* -1 was returned by wait. That means either that this process has no other
             * child processes (this thread can end), or some other error
             * happened (very unlikely). */
            if(errno == ECHILD) {
                logger->info(objectInfo + ": all tests were executed and finished");
                break;
            } else {
                logger->warn(objectInfo + ": wait() returned invalid value. "
                                          "This thread will continue reaping "
                                          "processes but deadlock or some other "
                                          "errors are possible. Inspect logs.");
            }
        }
    }
    /* Wait for manager to join all running threads, then join him. */
    manager.join();
}

BatteryOutput TestRunner::executeBinary(Logger * logger,
                                        const std::string & objectInfo,
                                        const std::string & binaryPath,
                                        uint expExitCode,
                                        const std::string & arguments,
                                        const std::string & input) {
    int stdin_pipe[2];
    int stdout_pipe[2];
    int stderr_pipe[2];

    pid_t pid = 0;
    posix_spawn_file_actions_t actions;

    if(pipe(stdin_pipe) || pipe(stdout_pipe) || pipe(stderr_pipe)) {
        logger->warn(objectInfo + ": pipe creation failed. Test won't be executed.");
        {
            /* Remove thread from list of threads without child, notify and end */
            std::lock_guard<std::mutex> l (withoutChild_mux);
            --withoutChild;
        }
        withoutChild_cv.notify_one();
        return {};
    }

    /* Pipes will be mapped to I/O after process start */
    /* Unused ends are closed */
    posix_spawn_file_actions_init(&actions);
    /* Standard input */
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[1]);
    posix_spawn_file_actions_adddup2(&actions , stdin_pipe[0] , 0);
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[0]);
    /* Standard output */
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);
    /* Standard error output */
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);

    int argc = 0;
    char ** args = buildArgv(arguments , &argc);

    /* Creating locks but not locking them yet */
    std::unique_lock<std::mutex> finishedPid_lock(finishedPid_mux , std::defer_lock);
    std::unique_lock<std::mutex> withoutChild_lock(withoutChild_mux , std::defer_lock);
    std::unique_lock<std::mutex> waitingForChild_lock(waitingForChild_mux , std::defer_lock);
    std::unique_lock<std::mutex> childReceived_lock(childReceived_mux , std::defer_lock);
    std::unique_lock<std::mutex> threadsReady_lock(threadState_mux , std::defer_lock);

    /* Need both locks, if they cannot be acquired
     * main thread is waiting for process to end */
    std::lock(finishedPid_lock , waitingForChild_lock);

    /* Starting child process of this thread */
    logger->info(objectInfo + ": spawning child process with arguments " + arguments);
    int status = posix_spawn(&pid , binaryPath.c_str() ,
                             &actions , NULL , args , NULL);

    if(status == 0) {
        /* Process was started without problems, proceed */
        logger->info(objectInfo + ": child process has pid " + Utils::itostr(pid));
        /* Closing pipes */
        close(stdin_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        if(!input.empty())
            write(stdin_pipe[1] , input.c_str() , input.length());
        /* Start thread for output reading. Thread will be mostly in blocked wait.
         * Also will be essentially over as soon as the process finishes.
         * With this, pipes won't be filled and won't block underlying process. */
        BatteryOutput output;
        std::thread reader(readOutput , std::ref(output),
                           stdout_pipe , stderr_pipe);

        /* Incrementing number of threads waiting.
         * Only if this variable is same as withoutChild
         * main thread can start reaping child processes. */
        ++waitingForChild;
        waitingForChild_lock.unlock();
        waitingForChild_cv.notify_one();

        /* Waiting for PID. PID is annouced by main thread and thread
         * will work with his associated process only
         * (because the thread owns the pipes to this process) */
        auto now = std::chrono::system_clock::now();

        if(!finishedPid_cv.wait_until(finishedPid_lock ,
                                      now + std::chrono::seconds(timeout) ,
                                      [&] { return finishedPid == pid; })) {
            /* If thread goes into this branch, its process timeouted.
             * Send kill signal to it, main thread will then reap it.
             * That's why this go into wait once more (usually it will instantly return) */
            logger->warn(objectInfo + ": child process with pid " + Utils::itostr(pid) + " timeouted."
                         " Process will be killed now.");
            kill(pid , SIGKILL);
            finishedPid_cv.wait(finishedPid_lock , [&] { return finishedPid == pid; });
        }
        /* Obtaining all possible mutexes, decrementing variables that
         * track waiting and active threads, setting childReceived to true
         * so main thread will be notified */
        std::lock(withoutChild_lock , waitingForChild_lock , childReceived_lock);
        logger->info(objectInfo + ": child process with pid " + Utils::itostr(pid) +
                     " finished. Exit code "
                     + Utils::intToHex(finishedPExitCode, 4) +
                     " (" + Utils::itostr(finishedPExitCode) + ")");
        if(finishedPExitCode != expExitCode) {
            logger->warn(objectInfo + ": received exit code (" +
                         Utils::intToHex(finishedPExitCode, 4) + ") "
                         "differs from the expected exit code (" +
                         Utils::intToHex(expExitCode, 4) +
                         ") of the test process");
        }
        --waitingForChild;
        --withoutChild;
        /* Unlock mutexes, this thread no longer needs them */
        finishedPid_lock.unlock();
        waitingForChild_lock.unlock();
        withoutChild_lock.unlock();
        /* Notify threadCreator that number of active threads changed.
         * He will spawn new threads if there is a need to. */
        withoutChild_cv.notify_one();

        /* This thread need to wait for notification from threadMaker
         * that it is ok to continue and after that, main thread can
         * be notified that child process was received and is being
         * processed.*/
        threadsReady_lock.lock();
        threadState_cv.wait(threadsReady_lock ,
                            []{ return (threadState == THREAD_STATE_DONE) ||
                                       (threadState == THREAD_STATE_READY); });
        if(threadState == THREAD_STATE_READY) {
            /* Flip threadState so next thread must wait too. */
            threadState = THREAD_STATE_PENDING;
        }
        threadsReady_lock.unlock();

        /* Notify main thread that it can continue in reaping processes */
        childReceived = true;
        childReceived_lock.unlock();
        childReceived_cv.notify_one();
        /* This thread now completed all communication with other threads.
         *  DO YOUR WORK SLAVE!!! */
        reader.join();

        return output;
    } else {
        /* Some nasty error happened at execution. Report and end thread */
        logger->warn(objectInfo + ": can't execute child process.");
        {
            /* Remove thread from list of threads without child, notify and end */
            std::lock_guard<std::mutex> l (withoutChild_mux);
            --withoutChild;
        }
        withoutChild_cv.notify_one();
        return {};
    }
    /* All locks go out of scope, so everything will be unlocked here */
}

void TestRunner::threadManager(std::vector<IVariant *> & variants) {
    /* Incrementing variable withoutChild with each new thread */
    std::unique_lock<std::mutex> withoutChild_lock(withoutChild_mux);
    std::unique_lock<std::mutex> threadState_lock(threadState_mux , std::defer_lock);
    std::vector<std::thread> threads;
    /* Initial threads are activated. Only MAX_THREADS are running at a time. */
    for(size_t i = 0 ; (i < threadCount) && i < variants.size() ; ++i) {
        threads.push_back(std::thread(&IVariant::execute , variants.at(i)));
        ++withoutChild;
    }
    /* Unlock so we won't block anyone */
    withoutChild_lock.unlock();

    /* Setting threadState to READY - more threads will be created */
    threadState_lock.lock();
    threadState = THREAD_STATE_READY;
    threadState_lock.unlock();
    /* Notify main thread that it can proceed */
    threadState_cv.notify_one();

    for(size_t i = threadCount ; i < variants.size() ; ++i) {
        /* Each thread, after finishing its ITC, will notify this thread that
         * withoutChild has changed. If there are less active threads than MAX_THREADS
         * and there are some unexecuted tests left, this thread will add them. */
        withoutChild_lock.lock();
        withoutChild_cv.wait(withoutChild_lock , []{ return withoutChild < threadCount; });
        threadState_lock.lock();
        threads.push_back(std::thread(&IVariant::execute , variants.at(i)));
        ++withoutChild;
        /* More threads can be created and one was created.
         * Let's share that with world */
        threadState = THREAD_STATE_READY;

        /* Unlock mutexes and notify other thread that might be waiting for this. */
        threadState_lock.unlock();
        withoutChild_lock.unlock();
        threadState_cv.notify_one();
    }

    /* No more threads will be created, set threadState to DONE. */
    threadState_lock.lock();
    threadState = THREAD_STATE_DONE;
    threadState_lock.unlock();
    /* I don't think there will be ever thread that will wait for this.
     * But better be safe than sorry. */
    threadState_cv.notify_all();

    /* Now there are no more threads to spawn. Thread will just
     * wait here and join finishing threads when they are ready. */
    for(std::thread & t : threads)
        t.join();
    /* Joining complete, end. */
}

void TestRunner::readOutput(BatteryOutput & output ,
                            int * stdout_pipe, int * stderr_pipe) {
    std::string buffer(1024 , ' ');
    std::string tmpStr;
    size_t bytes_read;

    std::vector<pollfd> pollVector {{stdout_pipe[0] , POLLIN , 0},
                                    {stderr_pipe[0] , POLLIN , 0}};
    for(; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if(pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            tmpStr = buffer.substr(0, bytes_read);
            output.appendStdOut(tmpStr);
        }
        else if(pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            tmpStr = buffer.substr(0, bytes_read);
            output.appendStdErr(tmpStr);
        }
        else break; /* Nothing else to read */
    }
}

char ** TestRunner::buildArgv(const std::string & arguments, int * argc) {
    std::vector<std::string> vecArg = Utils::split(arguments , ' ');
    char ** argv = new char * [vecArg.size() + 1];
    for(size_t i = 0 ; i < vecArg.size() ; ++i) {
        argv[i] = new char [vecArg.at(i).length() + 1];
        strcpy(argv[i] , vecArg.at(i).c_str());
    }
    argv[vecArg.size()] = NULL;
    *argc = vecArg.size() + 1;
    return argv;
}

void TestRunner::destroyArgv(int argc, char **argv) {
    for(int i = 0 ; i < argc ; ++i) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

} // namespace batteries
} // namespace rtt
