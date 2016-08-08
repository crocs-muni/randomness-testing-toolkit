#include "strings.h"

namespace rtt {

const std::string Strings::ERR_FILE_OPEN_FAIL                   = "can't open file - ";
const std::string Strings::ERR_INVALID_BATTERY                  = "invalid battery";
const std::string Strings::ERR_INVALID_TEST_CONST               = "unknown test constant - ";

const std::string Strings::BATT_ERR_ALREADY_EXECUTED            = "battery was already executed";
const std::string Strings::BATT_ERR_NO_TESTS                    = "no tests were set for execution";
const std::string Strings::BATT_ERR_NO_EXEC_PROC                = "battery must be executed before result processing";
const std::string Strings::BATT_ERR_KS_NO_PSAMPLES              = "can't calculate Kolmogorov-Smirnov statistic from 0 p-values";

const std::string Strings::TEST_ERR_NO_EXEC_RES                 = "test wasn't executed, can't provide results";
const std::string Strings::TEST_ERR_NO_EXEC_LOGS                = "test wasn't executed, can't provide logs";
const std::string Strings::TEST_ERR_NO_BINARY_DATA              = "empty input binary data path";
const std::string Strings::TEST_ERR_NO_EXECUTABLE               = "empty executable path";
const std::string Strings::TEST_ERR_PSAMPLES_NOT_SET            = "p-sample count option was not set";
const std::string Strings::TEST_ERR_ARGS_BAD_FORMAT_OPT_WO_VAL  = "invalid test arguments - each option must have a value";
const std::string Strings::TEST_ERR_NO_PVALS_EXTRACTED          = ": no p-values were extracted";
const std::string Strings::TEST_ERR_PVALS_BAD_COUNT             = ": p-values couldn't be extracted. Number of found p-values is different from expected number. Inspect test log.";
const std::string Strings::TEST_ERR_STREAM_SIZE_NOT_SET         = "stream size option was not set";
const std::string Strings::TEST_ERR_STREAM_COUNT_NOT_SET        = "stream count option was not set";
const std::string Strings::TEST_ERR_EXCEPTION_DURING_THREAD     = ": exception was caught during execution: ";
const std::string Strings::TEST_ERR_PVAL_OUTSIDE_INTERVAL       = "file contains p-value outside <0,1> interval";
const std::string Strings::TEST_ERR_REPS_NOT_SET                = "repetitions option were not set";
const std::string Strings::TEST_ERR_PARAM_INCOMPLETE            = "incomplete parameter settings";
const std::string Strings::TEST_ERR_BITNB_NOT_SET               = "bit_nb option was not set";
const std::string Strings::TEST_ERR_BITR_NOT_SET                = "bit_r option was not set";
const std::string Strings::TEST_ERR_BITS_NOT_SET                = "bit_s option was not set";
const std::string Strings::TEST_ERR_UNKNOWN_STATISTICS          = ": number of statistics extracted from log differs from default numbers. Inspect the test log for correct statistics names.";

const std::string Strings::BATT_INFO_PROCESSING_FILE            = ": processing file ";
const std::string Strings::BATT_INFO_PROCESSING_STARTED         = ": Processing and storing battery results.";
const std::string Strings::BATT_INFO_PROCESSING_COMPLETE        = ": Result processing finished.";

} // namespace rtt

