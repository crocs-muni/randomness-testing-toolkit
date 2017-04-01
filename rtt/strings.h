#ifndef RTT_STRINGS_H
#define RTT_STRINGS_H

#include <string>

namespace rtt {

/**
 * @brief The Strings class Class with hardcoded strings that are used in application
 * to notify about errors, progress, etc
 */
class Strings {
public:
    static const std::string ERR_FILE_OPEN_FAIL;
    static const std::string ERR_INVALID_BATTERY;
    static const std::string ERR_INVALID_TEST_CONST;

    static const std::string BATT_ERR_ALREADY_EXECUTED;
    static const std::string BATT_ERR_NO_TESTS;
    static const std::string BATT_ERR_NO_EXEC_PROC;
    static const std::string BATT_ERR_KS_NO_PSAMPLES;

    static const std::string TEST_ERR_NO_EXEC_RES;
    static const std::string TEST_ERR_NO_EXEC_LOGS;
    static const std::string TEST_ERR_NO_BINARY_DATA;
    static const std::string TEST_ERR_NO_EXECUTABLE;
    static const std::string TEST_ERR_PSAMPLES_NOT_SET;
    static const std::string TEST_ERR_ARGS_BAD_FORMAT_OPT_WO_VAL;
    static const std::string TEST_ERR_NO_PVALS_EXTRACTED;
    static const std::string TEST_ERR_PVALS_BAD_COUNT;
    static const std::string TEST_ERR_STREAM_SIZE_NOT_SET;
    static const std::string TEST_ERR_STREAM_COUNT_NOT_SET;
    static const std::string TEST_ERR_EXCEPTION_DURING_THREAD;
    static const std::string TEST_ERR_PVAL_OUTSIDE_INTERVAL;
    static const std::string TEST_ERR_REPS_NOT_SET;
    static const std::string TEST_ERR_PARAM_INCOMPLETE;
    static const std::string TEST_ERR_BITNB_NOT_SET;
    static const std::string TEST_ERR_BITR_NOT_SET;
    static const std::string TEST_ERR_BITS_NOT_SET;
    static const std::string TEST_ERR_UNKNOWN_STATISTICS;

    static const std::string BATT_INFO_PROCESSING_FILE;
    static const std::string BATT_INFO_PROCESSING_STARTED;
    static const std::string BATT_INFO_PROCESSING_COMPLETE;

private:
    Strings() {}
};

} // namespace rtt

#endif // RTT_STRINGS_H
