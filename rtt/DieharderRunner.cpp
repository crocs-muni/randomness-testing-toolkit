//#include <unistd.h>
//#include <spawn.h>
//#include <sys/wait.h>
//extern char **environ;

/*try {
    loadXMLFile(root, "config_sample.xml");
    char *argv[] = {"dieharder","-d","0","-p","1","-D","511",
                    "-g","201","-f","rand.bin",NULL};
    pid_t pid;
    int status;
    status = posix_spawn(&pid, "/usr/bin/dieharder" , NULL , NULL ,
                         argv , environ);
    if(status == 0) {
        std::cout << "Child pid: " << pid << std::endl;
        if (waitpid(pid , &status , 0) != -1) {
            std::cout << "Child exited with status " << status << std::endl;
        }
        else {
            perror("waitpid");
        }
    }
    else {
        std::cout << "posix_spawn: " << strerror(status) << std::endl;
    }
}
catch (std::runtime_error ex) {
    std::cout << "[ERROR] " << ex.what() << std::endl;
}*/
