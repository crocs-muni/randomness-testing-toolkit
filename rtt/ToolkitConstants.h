#ifndef TOOLKITCONSTANTS_H
#define TOOLKITCONSTANTS_H

///////////////////////////////////////////////
/*************Toolkit constants***************/
///////////////////////////////////////////////

// Statistical batteries constants
#define BATTERY_DIEHARDER           1
#define BATTERY_NIST_STS            2
#define BATTERY_TU01_SMALLCRUSH     3
#define BATTERY_TU01_CRUSH          4
#define BATTERY_TU01_BIGCRUSH       5
#define BATTERY_EACIRC              6

// Default files locations
#define FILE_DEFAULT_CFG_PATH       "./config.xml"

// Default XPaths in configuration file
// XPaths in Dieharder section
#define XPATH_DIEHARDER_BINARY_PATH     "DIEHARDER_SETTINGS/BINARY_PATH"
#define XPATH_DIEHARDER_OUTPUT_FILE     "DIEHARDER_SETTINGS/DEFAULT_OUTPUT_FILE"
#define XPATH_DIEHARDER_ADDITIONAL_ARGS "DIEHARDER_SETTINGS/ADDITIONAL_ARGUMENTS"

// XPaths in NIST STS section
#define XPATH_NIST_STS_BINARY_PATH      "NIST_STS_SETTINGS/BINARY_PATH"
#define XPATH_NIST_STS_OUTPUT_FILE      "NIST_STS_SETTINGS/DEFAULT_OUTPUT_FILE"
#define XPATH_NIST_STS_STREAM_SIZE      "NIST_STS_SETTINGS/STREAM_SIZE"
#define XPATH_NIST_STS_STREAM_COUNT     "NIST_STS_SETTINGS/STREAM_COUNT"
#define XPATH_NIST_STS_PAR_ADJUST       "NIST_STS_SETTINGS/PARAMETER_ADJUSTMENTS"
#define XPATH_NIST_STS_PAR_ADJUST_ATT   "test"

// XPaths in TestU01 section

// XPaths in EACirc section

#endif // TOOLKITCONSTANTS_H

