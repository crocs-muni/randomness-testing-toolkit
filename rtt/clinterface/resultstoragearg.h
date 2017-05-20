#ifndef RTT_CLINTERFACE_RESULTSTORAGEARG_H
#define RTT_CLINTERFACE_RESULTSTORAGEARG_H

#include <string>
#include <istream>
#include <ostream>

#include "rtt/constants.h"
#include "rtt/bugexception.h"

namespace rtt {
namespace clinterface {

/**
 * @brief The ResultStorageArg class Stores information about the chosen storage.
 * Stored information: ID, name, short name (cli)
 */
class ResultStorageArg {
public:
    ResultStorageArg();

    ResultStorageArg(const std::string & resultStorage);

    static std::string getName(Constants::ResultStorageID rsId);

    static std::string getShortName(Constants::ResultStorageID rsId);

    static std::string getDefaultShortName();

    Constants::ResultStorageID getResultStorageId() const;

    std::string getName();

    std::string getShortName();

    friend std::istream & operator>> (std::istream & is, ResultStorageArg & rs) {
        std::string resultStorage;
        is >> resultStorage;
        if(!is.eof() || is.fail())
            return is;

        rs.init(resultStorage);
        return is;
    }

    friend std::ostream & operator<< (std::ostream & os, const ResultStorageArg & rs) {
        rs.initCheck();

        os << rs.name;
        return os;
    }

private:
    bool initialized = false;
    Constants::ResultStorageID resultStorageId;
    std::string name;
    std::string shortName;

    static Constants::ResultStorageID getResultStorageIdFromShortName(
            const std::string & shortName);

    void init(const std::string & shortName);

    void initCheck() const;
};

} // namespace clinterface
} // namespace rtt

#endif // RTT_CLINTERFACE_RESULTSTORAGEARG_H
