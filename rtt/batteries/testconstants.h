#ifndef RTT_BATTERIES_TESTCONSTANTS_H
#define RTT_BATTERIES_TESTCONSTANTS_H

#include <map>

#include "rtt/constants.h"
#include "rtt/clinterface/batteryarg.h"
#include "rtt/rttexception.h"
#include "rtt/bugexception.h"

namespace rtt {
namespace batteries {

typedef std::tuple<std::string ,    /* Logic test name */
                   std::string ,    /* Path to result directory */
                   bool>            /* Adjustable block length of test */
                   tNistStsData;

typedef std::tuple<std::string>     /* Logic test name */
                   tDieharderData;

typedef std::tuple<std::string,                 /* Logic test name */
                   std::vector<std::string>,    /* Test parameters (settable) */
                   std::vector<std::string>,    /* Test parameters (extractable from log) */
                   std::vector<std::string>>    /* Output statistics names list */
                   tTestU01Data;

/* Used as key in map for TestU01 test constants.
 * Compares given integer to ranges in map. */
class IndexRange {
public:
    IndexRange(int x) : bot(x) , top(x) {}

    IndexRange(int b , int t) : bot(b) , top(t) {
        if(t < b)
            raiseBugException("IndexRange: top is less than bot");
    }

    bool operator<(const IndexRange & cmp) const {
        return cmp.top < this->bot;
    }

private:
    int bot = 0;
    int top = 0;
};

using namespace clinterface;

/**
 * @brief The TestConstants class Storage for test data (index in battery, logical name, etc...).
 * Each test is mapped to its index in given battery and can be
 * accessed based on battery constant and test index.
 */
class TestConstants {
public:

    /**
     * @brief getTestLogicName Return human-readable name of given test
     * @param battery ID of the battery
     * @param testIndex ID if the test
     * @return Human-readable name
     */
    static std::string getTestLogicName(const BatteryArg & battery,
                                        int testIndex);

    /**
     * @brief getNistStsTestData Return structure that represents data of NIST STS tests
     * @param battery ID of the batery, must be NIST STS
     * @param testIndex ID of the test
     * @return Structure with test data
     */
    static tNistStsData getNistStsTestData(const BatteryArg & battery ,
                                           int testIndex);

    /**
     * @brief getDieharderTestData Return structure that represents data of DIEHARDER tests
     * @param battery ID of the batery, must be DIEHARDER
     * @param testIndex ID of the test
     * @return Structure with test data
     */
    static tDieharderData getDieharderTestData(const BatteryArg & battery ,
                                               int testIndex);

    /**
     * @brief getTu01TestData Return structure that represents data of TestU01 tests
     * @param battery ID of the batery, must be some battery from TestU01
     * @param testIndex ID of the test
     * @return Structure with test data
     */
    static tTestU01Data getTu01TestData(const BatteryArg & battery ,
                                        int testIndex);

private:
    /* Maps with test indices assigned to test data */
    /* This will be private! */
    static const std::map<int , tNistStsData> nistStsTests;
    static const std::map<int , tDieharderData> dieharderTests;
    static const std::map<IndexRange , tTestU01Data> tu01testsSmallCrush;
    static const std::map<IndexRange , tTestU01Data> tu01testsCrush;
    static const std::map<IndexRange , tTestU01Data> tu01testsBigCrush;
    static const std::map<IndexRange , tTestU01Data> tu01testsRabbit;
    static const std::map<IndexRange , tTestU01Data> tu01testsAlphabit;
    /* Test data declared */
    /*
     __    __  ______   ______  ________         ______  ________   ______
    |  \  |  \|      \ /      \|        \       /      \|        \ /      \
    | $$\ | $$ \$$$$$$|  $$$$$$\\$$$$$$$$      |  $$$$$$\\$$$$$$$$|  $$$$$$\
    | $$$\| $$  | $$  | $$___\$$  | $$         | $$___\$$  | $$   | $$___\$$
    | $$$$\ $$  | $$   \$$    \   | $$          \$$    \   | $$    \$$    \
    | $$\$$ $$  | $$   _\$$$$$$\  | $$          _\$$$$$$\  | $$    _\$$$$$$\
    | $$ \$$$$ _| $$_ |  \__| $$  | $$         |  \__| $$  | $$   |  \__| $$
    | $$  \$$$|   $$ \ \$$    $$  | $$          \$$    $$  | $$    \$$    $$
     \$$   \$$ \$$$$$$  \$$$$$$    \$$           \$$$$$$    \$$     \$$$$$$
    */
    static const std::string NISTSTS_MAIN_RESULT_DIR;
    static const tNistStsData NISTSTS_FREQ;
    static const tNistStsData NISTSTS_BLOCKFREQ;
    static const tNistStsData NISTSTS_CUSUMS;
    static const tNistStsData NISTSTS_RUNS;
    static const tNistStsData NISTSTS_LONGESTRUN;
    static const tNistStsData NISTSTS_RANK;
    static const tNistStsData NISTSTS_FFT;
    static const tNistStsData NISTSTS_NONOVERTEMP;
    static const tNistStsData NISTSTS_OVERTEMP;
    static const tNistStsData NISTSTS_UNIVERSAL;
    static const tNistStsData NISTSTS_APPROXENT;
    static const tNistStsData NISTSTS_RNDEXCURSIONS;
    static const tNistStsData NISTSTS_RNDEXCURSIONSVAR;
    static const tNistStsData NISTSTS_SERIAL;
    static const tNistStsData NISTSTS_LINEARCOMPLEXITY;
    /*
     _______   __            __                                  __
    |       \ |  \          |  \                                |  \
    | $$$$$$$\ \$$  ______  | $$____    ______    ______    ____| $$  ______    ______
    | $$  | $$|  \ /      \ | $$    \  |      \  /      \  /      $$ /      \  /      \
    | $$  | $$| $$|  $$$$$$\| $$$$$$$\  \$$$$$$\|  $$$$$$\|  $$$$$$$|  $$$$$$\|  $$$$$$\
    | $$  | $$| $$| $$    $$| $$  | $$ /      $$| $$   \$$| $$  | $$| $$    $$| $$   \$$
    | $$__/ $$| $$| $$$$$$$$| $$  | $$|  $$$$$$$| $$      | $$__| $$| $$$$$$$$| $$
    | $$    $$| $$ \$$     \| $$  | $$ \$$    $$| $$       \$$    $$ \$$     \| $$
     \$$$$$$$  \$$  \$$$$$$$ \$$   \$$  \$$$$$$$ \$$        \$$$$$$$  \$$$$$$$ \$$
    */
    static const tDieharderData DIEHARDER_BIRTHDAYS;
    static const tDieharderData DIEHARDER_OPERM5;
    static const tDieharderData DIEHARDER_BINARYRANK1;
    static const tDieharderData DIEHARDER_BINARYRANK2;
    static const tDieharderData DIEHARDER_BITSTREAM;
    static const tDieharderData DIEHARDER_OPSO;
    static const tDieharderData DIEHARDER_OQSO;
    static const tDieharderData DIEHARDER_DNA;
    static const tDieharderData DIEHARDER_COUNT1SBYTE;
    static const tDieharderData DIEHARDER_COUNT1SSTREAM;
    static const tDieharderData DIEHARDER_PARKING;
    static const tDieharderData DIEHARDER_MINDISTANCECIRCLE;
    static const tDieharderData DIEHARDER_MINDISTANCESPHERE;
    static const tDieharderData DIEHARDER_SQUEEZE;
    static const tDieharderData DIEHARDER_SUMS;
    static const tDieharderData DIEHARDER_RUNS;
    static const tDieharderData DIEHARDER_CRAPS;
    static const tDieharderData DIEHARDER_GCD;
    static const tDieharderData DIEHARDER_MONOBIT;
    static const tDieharderData DIEHARDER_STSRUNS;
    static const tDieharderData DIEHARDER_SERIAL;
    static const tDieharderData DIEHARDER_BITDIST;
    static const tDieharderData DIEHARDER_MINDISTANCE;
    static const tDieharderData DIEHARDER_PERMUTATIONS;
    static const tDieharderData DIEHARDER_LAGGED;
    static const tDieharderData DIEHARDER_KS;
    static const tDieharderData DIEHARDER_BYTEDIST;
    static const tDieharderData DIEHARDER_DABDCT;
    static const tDieharderData DIEHARDER_DABFILLTREE;
    static const tDieharderData DIEHARDER_DABFILLTREE2;
    static const tDieharderData DIEHARDER_DABMONOBIT;
    /*
     ________                      __       ______     __
    |        \                    |  \     /      \  _/  \
     \$$$$$$$$______    _______  _| $$_   |  $$$$$$\|   $$
       | $$  /      \  /       \|   $$ \  | $$$\| $$ \$$$$
       | $$ |  $$$$$$\|  $$$$$$$ \$$$$$$  | $$$$\ $$  | $$
       | $$ | $$    $$ \$$    \   | $$ __ | $$\$$\$$  | $$
       | $$ | $$$$$$$$ _\$$$$$$\  | $$|  \| $$_\$$$$ _| $$_
       | $$  \$$     \|       $$   \$$  $$ \$$  \$$$|   $$ \
        \$$   \$$$$$$$ \$$$$$$$     \$$$$   \$$$$$$  \$$$$$$
    */
    static const tTestU01Data TESTU01_SMARSA_SERIALOVER;
    static const tTestU01Data TESTU01_SMARSA_COLLISIONOVER;
    static const tTestU01Data TESTU01_SMARSA_BIRTHDAYSPACINGS;
    static const tTestU01Data TESTU01_SNPAIR_CLOSEPAIRS;
    static const tTestU01Data TESTU01_SNPAIR_CLOSEPAIRS_BIGT;
    static const tTestU01Data TESTU01_SNPAIR_CLOSEPAIRSBITMATCH;
    static const tTestU01Data TESTU01_SKNUTH_COLLISION;
    static const tTestU01Data TESTU01_SKNUTH_SIMPPOKER;
    static const tTestU01Data TESTU01_SKNUTH_COUPONCOLLECTOR;
    static const tTestU01Data TESTU01_SKNUTH_GAP;
    static const tTestU01Data TESTU01_SKNUTH_RUN;
    static const tTestU01Data TESTU01_SKNUTH_PERMUTATION;
    static const tTestU01Data TESTU01_SKNUTH_COLLISIONPERMUT;
    static const tTestU01Data TESTU01_SKNUTH_MAXOFT;
    static const tTestU01Data TESTU01_SKNUTH_MAXOFT_BIGN;
    static const tTestU01Data TESTU01_SVARIA_SAMPLEPROD;
    static const tTestU01Data TESTU01_SVARIA_SAMPLEMEAN;
    static const tTestU01Data TESTU01_SVARIA_SAMPLECORR;
    static const tTestU01Data TESTU01_SVARIA_APPEARANCESPACINGS;
    static const tTestU01Data TESTU01_SVARIA_WEIGHTDISTRIB;
    static const tTestU01Data TESTU01_SVARIA_SUMCOLLECTOR;
    static const tTestU01Data TESTU01_SMARSA_MATRIXRANK;
    static const tTestU01Data TESTU01_SMARSA_SAVIR2;
    static const tTestU01Data TESTU01_SMARSA_GDC;
    static const tTestU01Data TESTU01_SWALK_RANDOMWALK1;
    static const tTestU01Data TESTU01_SCOMP_LINEARCOMP;
    static const tTestU01Data TESTU01_SCOMP_LEMPELZIV;
    static const tTestU01Data TESTU01_SCOMP_LEMPELZIV_BIGN;
    static const tTestU01Data TESTU01_SSPECRTAL_FOURIER1;
    static const tTestU01Data TESTU01_SSPECRTAL_FOURIER3;
    static const tTestU01Data TESTU01_SSTRING_LONGESTHEADRUN;
    static const tTestU01Data TESTU01_SSTRING_PERIODSINSTRINGS;
    static const tTestU01Data TESTU01_SSTRING_HAMMINGWEIGHT;
    static const tTestU01Data TESTU01_SSTRING_HAMMINGWEIGHT2;
    static const tTestU01Data TESTU01_SSTRING_HAMMINGCORR;
    static const tTestU01Data TESTU01_SSTRING_HAMMINGINDEP;
    static const tTestU01Data TESTU01_SSTRING_RUN;
    static const tTestU01Data TESTU01_SSTRING_RUN_RABBIT;
    static const tTestU01Data TESTU01_SSTRING_AUTOCOR;
    static const tTestU01Data TESTU01_SSTRING_AUTOCOR_BIGN;
    static const tTestU01Data TESTU01_SMULTIN_MULTINOMIALBITSOVER;
    static const tTestU01Data TESTU01_SMULTIN_MULTBITSOVER_BIGN;
private:
    /* No class instances allowed */
    TestConstants() {}
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTCONSTANTS_H
