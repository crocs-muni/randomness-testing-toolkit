#ifndef RTT_BATTERIES_TESTU01_TEST_H
#define RTT_BATTERIES_TESTU01_TEST_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <tuple>

#include "rtt/batteries/testutils-batt.h"
#include "rtt/options.h"
#include "libs/tinyXML/xmlproc.h"

namespace rtt {
namespace batteries {
namespace testu01 {

/*
 * Defined enums for tests in respective batteries. Each constant
 * represents index in battery on which test occurrs last. E.g. Crush battery
 * has test smarsa_CollisionOver on indices from 3 to 10, therefore constant of
 * smarsa_CollisionOver test will be 10. These constants are used in elseif's
 * to determine which test will be run with certain parameters.
 */
enum class SmallCrushTI {
    smarsa_BirthdaySpacing          = 1,
    sknuth_Collision                = 2,
    sknuth_Gap                      = 3,
    sknuth_SimpPoker                = 4,
    sknuth_CouponCollector          = 5,
    sknuth_MaxOft                   = 6,
    svaria_WeightDistrib            = 7,
    smarsa_MatrixRank               = 8,
    sstring_HammingIndep            = 9,
    swalk_RandomWalk1               = 10
};

enum class CrushTI {
    smarsa_SerialOver               = 2,
    smarsa_CollisionOver            = 10,
    smarsa_BirthdaySpacings         = 17,
    snpair_ClosePairs               = 20,
    snpair_ClosePairsBitMatch       = 22,
    sknuth_SimpPoker                = 26,
    sknuth_CouponCollector          = 30,
    sknuth_Gap                      = 34,
    sknuth_Run                      = 36,
    sknuth_Permutation              = 38,
    sknuth_CollisionPermut          = 40,
    sknuth_MaxOft                   = 44,
    svaria_SampleProd               = 46,
    svaria_SampleMean               = 47,
    svaria_SampleCorr               = 48,
    svaria_AppearanceSpacings       = 50,
    svaria_WeightDistrib            = 54,
    svaria_SumCollector             = 55,
    smarsa_MatrixRank               = 61,
    smarsa_Savir2                   = 62,
    smarsa_GCD                      = 64,
    swalk_RandomWalk1               = 70,
    scomp_LinearComp                = 72,
    scomp_LempelZiv                 = 73,
    sspectral_Fourier3              = 75,
    sstring_LongestHeadRun          = 77,
    sstring_PeriodsInStrings        = 79,
    sstring_HammingWeight2          = 81,
    sstring_HammingCorr             = 84,
    sstring_HammingIndep            = 90,
    sstring_Run                     = 92,
    sstring_AutoCor                 = 96
};

enum class BigCrushTI {
    smarsa_SerialOver               = 2,
    smarsa_CollisionOver            = 12,
    smarsa_BirthdaySpacings         = 21,
    snpair_ClosePairs               = 25,
    sknuth_SimpPoker                = 29,
    sknuth_CouponCollector          = 33,
    sknuth_Gap                      = 37,
    sknuth_Run                      = 39,
    sknuth_Permutation              = 43,
    sknuth_CollisionPermut          = 45,
    sknuth_MaxOft                   = 49,
    svaria_SampleProd               = 52,
    svaria_SampleMean               = 54,
    svaria_SampleCorr               = 56,
    svaria_AppearanceSpacings       = 58,
    svaria_WeightDistrib            = 64,
    svaria_SumCollector             = 65,
    smarsa_MatrixRank               = 71,
    smarsa_Savir2                   = 72,
    smarsa_GCD                      = 73,
    swalk_RandomWalk1               = 79,
    scomp_LinearComp                = 81,
    scomp_LempelZiv                 = 83,
    sspectral_Fourier3              = 85,
    sstring_LongestHeadRun          = 87,
    sstring_PeriodsInStrings        = 89,
    sstring_HammingWeight2          = 91,
    sstring_HammingCorr             = 94,
    sstring_HammingIndep            = 100,
    sstring_Run                     = 102,
    sstring_AutoCor                 = 106
};

enum class RabbitTI {
    smultin_MultinomialBitsOver     = 1,
    snpair_ClosePairsBitMatch       = 3,
    svaria_AppearanceSpacings       = 4,
    scomp_LinearComp                = 5,
    scomp_LempelZiv                 = 6,
    sspectral_Fourier1              = 7,
    sspectral_Fourier3              = 8,
    sstring_LongestHeadRun          = 9,
    sstring_PeriodsInStrings        = 10,
    sstring_HammingWeight           = 11,
    sstring_HammingCorr             = 14,
    sstring_HammingIndep            = 17,
    sstring_AutoCor                 = 19,
    sstring_Run                     = 20,
    smarsa_MatrixRank               = 23,
    swalk_RandomWalk1               = 26
};

enum class AlphabitTI {
    smultin_MultinomialBitsOver     = 4,
    sstring_HammingIndep            = 6,
    sstring_HammingCorr             = 7,
    swalk_RandomWalk1               = 9
};

/* Typedefs for parameter types, test information */
typedef std::pair<std::string , std::string> tParam;
typedef std::vector<std::string> tStringVector;
typedef std::tuple<std::string , tStringVector , tStringVector> tTestInfo;
typedef std::vector<double> tTestPvals;

class Test {
public:
    /* Test info constants */
    static const tTestInfo INFO_SMARSA_SERIALOVER;
    static const tTestInfo INFO_SMARSA_COLLISIONOVER;
    static const tTestInfo INFO_SMARSA_BIRTHDAYSPACINGS;
    static const tTestInfo INFO_SNPAIR_CLOSEPAIRS;
    static const tTestInfo INFO_SNPAIR_CLOSEPAIRSBITMATCH;
    static const tTestInfo INFO_SKNUTH_COLLISION;
    static const tTestInfo INFO_SKNUTH_SIMPPOKER;
    static const tTestInfo INFO_SKNUTH_COUPONCOLLECTOR;
    static const tTestInfo INFO_SKNUTH_GAP;
    static const tTestInfo INFO_SKNUTH_RUN;
    static const tTestInfo INFO_SKNUTH_PERMUTATION;
    static const tTestInfo INFO_SKNUTH_COLLISIONPERMUT;
    static const tTestInfo INFO_SKNUTH_MAXOFT;
    static const tTestInfo INFO_SVARIA_SAMPLEPROD;
    static const tTestInfo INFO_SVARIA_SAMPLEMEAN;
    static const tTestInfo INFO_SVARIA_SAMPLECORR;
    static const tTestInfo INFO_SVARIA_APPEARANCESPACINGS;
    static const tTestInfo INFO_SVARIA_WEIGHTDISTRIB;
    static const tTestInfo INFO_SVARIA_SUMCOLLECTOR;
    static const tTestInfo INFO_SMARSA_MATRIXRANK;
    static const tTestInfo INFO_SMARSA_SAVIR2;
    static const tTestInfo INFO_SMARSA_GDC;
    static const tTestInfo INFO_SWALK_RANDOMWALK1;
    static const tTestInfo INFO_SCOMP_LINEARCOMP;
    static const tTestInfo INFO_SCOMP_LEMPELZIV;
    static const tTestInfo INFO_SSPECRTAL_FOURIER1;
    static const tTestInfo INFO_SSPECRTAL_FOURIER3;
    static const tTestInfo INFO_SSTRING_LONGESTHEADRUN;
    static const tTestInfo INFO_SSTRING_PERIODSINSTRINGS;
    static const tTestInfo INFO_SSTRING_HAMMINGWEIGHT;
    static const tTestInfo INFO_SSTRING_HAMMINGWEIGHT2;
    static const tTestInfo INFO_SSTRING_HAMMINGCORR;
    static const tTestInfo INFO_SSTRING_HAMMINGINDEP;
    static const tTestInfo INFO_SSTRING_RUN;
    static const tTestInfo INFO_SSTRING_AUTOCOR;
    static const tTestInfo INFO_SMULTIN_MULTINOMIALBITSOVER;

    /* XPath constants */
    static const std::string XPATH_EXECUTABLE_BINARY;
    static const std::string XPATH_DEFAULT_REPS;
    static const std::string XPATH_DEFAULT_BIT_NB;
    static const std::string XPATH_DEFAULT_BIT_R;
    static const std::string XPATH_DEFAULT_BIT_S;
    static const std::string XPATH_SMALL_CRUSH_SETTINGS;
    static const std::string XPATH_CRUSH_SETTINGS;
    static const std::string XPATH_BIG_CRUSH_SETTINGS;
    static const std::string XPATH_RABBIT_SETTINGS;
    static const std::string XPATH_ALPHABIT_SETTINGS;
    static const std::string XPATH_TEST_REPS;
    static const std::string XPATH_TEST_PARAMS;
    static const std::string XPATH_TEST_BIT_NB;
    static const std::string XPATH_TEST_BIT_R;
    static const std::string XPATH_TEST_BIT_S;
    static const std::string XPATH_ATTRIBUTE_TEST_INDEX;
    static const std::string XPATH_ATTRIBUTE_PAR_NAME;

    /*
    ======================
    *** Public methods ***
    ======================
    */
    static Test getInstance(int testIndex ,
                            const CliOptions & options ,
                            TiXmlNode * cfgRoot);

    void appendTestLog(std::string & batteryLog);

    bool wasExecuted() const { return executed; }

    void execute();

    std::string getLogicName() const;

    std::vector<std::string> getParameters() const;

    std::vector<std::string> getStatistics() const;

    std::vector<tTestPvals> getResults() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    int battery = -1;
    int testIndex = -1;
    std::string logicName;
    tStringVector paramNames;
    tStringVector statisticNames;
    int repetitions;
    std::string executablePath;
    std::string binaryDataPath;
    /* Only used in crush batteres */
    std::vector<tParam> params;
    /* Used in rabbit/alphabit battery */
    std::string bit_nb;
    std::string bit_r;
    std::string bit_s;
    /* Following vars will be set after test execution */
    bool executed = false;
    /* Number of statistics calculated in each test
     * resulting pval count = reps*statCount */
    int statCount;
    std::string testLog;
    /* Each tTestPval holds results of single test and its statistics */
    /* This is in vector - multiple test repetitions are possible */
    std::vector<tTestPvals> results;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test() {}

    static tTestInfo pickTestInfo(int testIndex, int battery, std::string & batteryXPath);

    void checkSetParams(TiXmlNode * paramsNode);

    std::string createArgs() const;

    void extractPvalues();

    void saveTestLogToFile();

    double convertStringToDouble(const std::string & num,
                                 const std::string & oneMinus);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TEST_H
