#ifndef RTT_BATTERIES_TESTUTILS_H
#define RTT_BATTERIES_TESTUTILS_H

#include <iostream>
#include <string>
#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <stdexcept>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "libs/tinyXML/xmlproc.h"
#include "rtt/utils.h"

extern char ** environ;

namespace rtt {
namespace batteries {

/* Class with methods that are used by all tests. */
class TestUtils {
public:
    static std::string executeBinary(const std::string & binaryPath,
                                     const std::string & arguments,
                                     const std::string & input = "",
                                     int timeout = 0,
                                     bool * timeouted = NULL);

    static std::string getTestOrDefOpt(TiXmlNode * cfgRoot,
                                       TiXmlNode * testNode,
                                       const std::string & defaultPath,
                                       const std::string & testPath);
private:
    static char ** buildArgv(const std::string & arguments , int * argc);

    static void destroyArgv(int argc , char ** argv);

    static std::string readOutput(int * stdout_pipe , int * stderr_pipe);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTUTILS_H
