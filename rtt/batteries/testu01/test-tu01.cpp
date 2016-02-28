#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const tTestInfo Test::INFO_SMARSA_SERIALOVER            {"smarsa_SerialOver" ,
                                                         {"N","n","r","d","t"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SMARSA_COLLISIONOVER         {"smarsa_CollisionOver" ,
                                                         {"N","n","r","d","t"} ,
                                                         {"Collision"}};
const tTestInfo Test::INFO_SMARSA_BIRTHDAYSPACINGS      {"smarsa_BirthdaySpacings" ,
                                                         {"N","n","r","d","t","p"} ,
                                                         {"Collision"}};
const tTestInfo Test::INFO_SNPAIR_CLOSEPAIRS            {"snpair_ClosePairs" ,
                                                         {"N","n","r","t","p","m"} ,
                                                         {"AD (NP)" , "A2 (m-NP)" , "A2 (mNP1)" , "Jumps Y (mN)" , "AD (mNP2)"}};
const tTestInfo Test::INFO_SNPAIR_CLOSEPAIRS_BIGT       {"snpair_ClosePairs" ,
                                                         {"N","n","r","t","p","m"} ,
                                                         {"AD (NP)" , "A2 (m-NP)" , "A2 (mNP1)" , "Jumps Y (mN)" , "AD (mNP2)" ,
                                                            "AD (mNP2-S)"}};
const tTestInfo Test::INFO_SNPAIR_CLOSEPAIRSBITMATCH    {"snpair_ClosePairsBitMatch" ,
                                                         {"N","n","r","t"} ,
                                                         {"Bit distance"}};
const tTestInfo Test::INFO_SKNUTH_COLLISION             {"sknuth_Collision" ,
                                                         {"N","n","r","d","t"} ,
                                                         {"Collision"}};
const tTestInfo Test::INFO_SKNUTH_SIMPPOKER             {"sknuth_SimpPoker" ,
                                                         {"N","n","r","d","k"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SKNUTH_COUPONCOLLECTOR       {"sknuth_CouponCollector" ,
                                                         {"N","n","r","d"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SKNUTH_GAP                   {"sknuth_Gap" ,
                                                         {"N","n","r","Alpha","Beta"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SKNUTH_RUN                   {"sknuth_Run" ,
                                                         {"N","n","r","Up"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SKNUTH_PERMUTATION           {"sknuth_Permutation" ,
                                                         {"N","n","r","t"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SKNUTH_COLLISIONPERMUT       {"sknuth_CollisionPermut" ,
                                                         {"N","n","r","t"} ,
                                                         {"Collision"}};
const tTestInfo Test::INFO_SKNUTH_MAXOFT                {"sknuth_MaxOft" ,
                                                         {"N","n","r","d","t"} ,
                                                         {"Chi-square" , "Anderson-Darling"}};
const tTestInfo Test::INFO_SKNUTH_MAXOFT_BIGN           {"sknuth_MaxOft" ,
                                                         {"N","n","r","d","t"} ,
                                                         {"Chi-square - KS (D+)" , "Chi-square - KS (D-)" , "Chi-square - AD (A2)" ,
                                                            "Observations sums" , "Anderson-Darling - KS (D+)" , "Anderson-Darling - KS (D-)" ,
                                                            "Anderson-Darling - AD (A2)"}};
const tTestInfo Test::INFO_SVARIA_SAMPLEPROD            {"svaria_SampleProd" ,
                                                         {"N","n","r","t"} ,
                                                         {"Anderson-Darling"}};
const tTestInfo Test::INFO_SVARIA_SAMPLEMEAN            {"svaria_SampleMean" ,
                                                         {"N","n","r"} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" , "Anderson-Darling"}};
const tTestInfo Test::INFO_SVARIA_SAMPLECORR            {"svaria_SampleCorr" ,
                                                         {"N","n","r","k"} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SVARIA_APPEARANCESPACINGS    {"svaria_AppearanceSpacings" ,
                                                         {"N","Q","K","r","s","L"} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SVARIA_WEIGHTDISTRIB         {"svaria_WeightDistrib" ,
                                                         {"N","n","r","k","Alpha","Beta"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SVARIA_SUMCOLLECTOR          {"svaria_SumCollector" ,
                                                         {"N","n","r","g"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SMARSA_MATRIXRANK            {"smarsa_MatrixRank" ,
                                                         {"N","n","r","s","L","k"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SMARSA_SAVIR2                {"smarsa_Savir2" ,
                                                         {"N","n","r","m","t"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SMARSA_GDC                   {"smarsa_GCD" ,
                                                         {"N","n","r","s"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SWALK_RANDOMWALK1            {"swalk_RandomWalk1" ,
                                                         {"N","n","r","s","L0","L1"} ,
                                                         {"Chi-square(H)" , "Chi-square(M)" ,"Chi-square(J)" , "Chi-square(R)" , "Chi-square(C)"}};
const tTestInfo Test::INFO_SCOMP_LINEARCOMP             {"scomp_LinearComp" ,
                                                         {"N","n","r","s"} ,
                                                         {"Chi-square" , "Normal"}};
const tTestInfo Test::INFO_SCOMP_LEMPELZIV              {"scomp_LempelZiv" ,
                                                         {} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SCOMP_LEMPELZIV_BIGN         {"scomp_LempelZiv" ,
                                                         {"N","k","r","s"} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" ,
                                                            "Anderson-Darling" , "Normal" , "Sample variance"}};
const tTestInfo Test::INFO_SSPECRTAL_FOURIER1           {"sspectral_Fourier1" ,
                                                         {} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SSPECRTAL_FOURIER3           {"sspectral_Fourier3" ,
                                                         {"N","k","r","s"} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" , "Anderson-Darling"}};
const tTestInfo Test::INFO_SSTRING_LONGESTHEADRUN       {"sstring_LongestHeadRun" ,
                                                         {"N","n","r","s","L"} ,
                                                         {"Chi-square" , "Global longest run of 1"}};
const tTestInfo Test::INFO_SSTRING_PERIODSINSTRINGS     {"sstring_PeriodsInStrings" ,
                                                         {"N","n","r","s"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGWEIGHT        {"sstring_HammingWeight" ,
                                                         {} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGWEIGHT2       {"sstring_HammingWeight2" ,
                                                         {"N","n","r","s","L"} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" ,
                                                            "Anderson-Darling" , "Chi-square"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGCORR          {"sstring_HammingCorr" ,
                                                         {"N","n","r","s","L"} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGINDEP         {"sstring_HammingIndep" ,
                                                         {"N","n","r","s","L","d"} ,
                                                         {"Chi-square"}};
const tTestInfo Test::INFO_SSTRING_RUN                  {"sstring_Run" ,
                                                         {"N","n","r","s"} ,
                                                         {"Chi-square" , "Normal"}};
const tTestInfo Test::INFO_SSTRING_AUTOCOR              {"sstring_AutoCor" ,
                                                         {} ,
                                                         {"Normal"}};
const tTestInfo Test::INFO_SSTRING_AUTOCOR_BIGN         {"sstring_AutoCor" , {"N","n","r","s","d"} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" ,
                                                            "Anderson-Darling" , "Normal" , "Sample variance"}};
const tTestInfo Test::INFO_SMULTIN_MULTINOMIALBITSOVER  {"smultin_MultinomialBitsIver" ,
                                                         {} ,
                                                         {"Collision"}};
const tTestInfo Test::INFO_SMULTIN_MULTBITSOVER_BIGN    {"smultin_MultinomialBitsIver" ,
                                                         {} ,
                                                         {"Kolmogorov-Smirnov (D+)" , "Kolmogorov-Smirnov (D-)" , "Anderson-Darling (A2)" ,
                                                            "Std empirical mean" , "Std empirical correlation"}};

const std::string Test::XPATH_EXECUTABLE_BINARY             = "TESTU01_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_DEFAULT_REPS                  = "TESTU01_SETTINGS/DEFAULT_REPETITIONS";
const std::string Test::XPATH_DEFAULT_BIT_NB                = "TESTU01_SETTINGS/DEFAULT_BIT_NB";
const std::string Test::XPATH_DEFAULT_BIT_R                 = "TESTU01_SETTINGS/DEFAULT_BIT_R";
const std::string Test::XPATH_DEFAULT_BIT_S                 = "TESTU01_SETTINGS/DEFAULT_BIT_S";
const std::string Test::XPATH_SMALL_CRUSH_SETTINGS          = "TESTU01_SETTINGS/SMALL_CRUSH_SETTINGS";
const std::string Test::XPATH_CRUSH_SETTINGS                = "TESTU01_SETTINGS/CRUSH_SETTINGS";
const std::string Test::XPATH_BIG_CRUSH_SETTINGS            = "TESTU01_SETTINGS/BIG_CRUSH_SETTINGS";
const std::string Test::XPATH_RABBIT_SETTINGS               = "TESTU01_SETTINGS/RABBIT_SETTINGS";
const std::string Test::XPATH_ALPHABIT_SETTINGS             = "TESTU01_SETTINGS/ALPHABIT_SETTINGS";
const std::string Test::XPATH_TEST_REPS                     = "REPETITIONS";
const std::string Test::XPATH_TEST_PARAMS                   = "PARAMS";
const std::string Test::XPATH_TEST_BIT_NB                   = "BIT_NB";
const std::string Test::XPATH_TEST_BIT_R                    = "BIT_R";
const std::string Test::XPATH_TEST_BIT_S                    = "BIT_S";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX          = "test";
const std::string Test::XPATH_ATTRIBUTE_PAR_NAME            = "name";


std::unique_ptr<Test> Test::getInstance(int testIndex, const CliOptions & options, TiXmlNode * cfgRoot) {
    if(!cfgRoot)
        throw std::runtime_error("null cfgRoot");
    if(testIndex <= 0)
        throw std::runtime_error("invalid TestU01 test constant: " + Utils::itostr(testIndex));

    std::unique_ptr<Test> test (new Test());
    std::string batteryXPath;

    test->battery = options.getBattery();
    test->testIndex = testIndex;
    std::tie(test->logicName , test->paramNames , test->statisticNames) =
            pickTestInfo(testIndex , options.getBattery() , batteryXPath);

    TiXmlNode * testSettings = getXMLChildNodeWithAttValue(
                                getXMLElement(cfgRoot , batteryXPath),
                                XPATH_ATTRIBUTE_TEST_INDEX ,
                                Utils::itostr(testIndex)
                               );

    std::string strReps = TestUtils::getTestOrDefOpt(cfgRoot , testSettings ,
                                                             XPATH_DEFAULT_REPS ,
                                                             XPATH_TEST_REPS);
    if(strReps.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": default or test specific repetitions must be set");
    test->repetitions = Utils::strtoi(strReps);
    test->executablePath = getXMLElementValue(cfgRoot , XPATH_EXECUTABLE_BINARY);
    if(test->executablePath.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": path to executable binary can't be empty");
    test->binaryDataPath = options.getBinFilePath();
    if(test->binaryDataPath.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": path to binary data can't be empty");

    /* Getting params - only for Crush batteries */
    if(test->battery == Constants::BATTERY_TU01_SMALLCRUSH ||
            test->battery == Constants::BATTERY_TU01_CRUSH ||
            test->battery == Constants::BATTERY_TU01_BIGCRUSH)
        test->checkSetParams(getXMLElement(testSettings , XPATH_TEST_PARAMS));

    /* Getting nb - Rabbit and Alphabit */
    if(test->battery == Constants::BATTERY_TU01_RABBIT ||
            test->battery == Constants::BATTERY_TU01_ALPHABIT) {
        test->bit_nb = TestUtils::getTestOrDefOpt(cfgRoot , testSettings ,
                                                  XPATH_DEFAULT_BIT_NB ,
                                                  XPATH_TEST_BIT_NB);
        if(test->bit_nb.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_nb option must be set"
                                     " in Rabbit and Alphabit battery");
    }
    /* Getting r s - Alphabit */
    if(test->battery == Constants::BATTERY_TU01_ALPHABIT) {
        test->bit_r = TestUtils::getTestOrDefOpt(cfgRoot , testSettings ,
                                                 XPATH_DEFAULT_BIT_R ,
                                                 XPATH_TEST_BIT_R);
        if(test->bit_r.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_r option must be set"
                                     " in Alphabit battery");

        test->bit_s = TestUtils::getTestOrDefOpt(cfgRoot , testSettings ,
                                                 XPATH_DEFAULT_BIT_S ,
                                                 XPATH_TEST_BIT_S);
        if(test->bit_s.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_s option must be set"
                                     " in Alphabit battery");
    }
    return test;
}

void Test::appendTestLog(std::string & batteryLog) const {
    if(!executed)
        throw std::runtime_error("test " + Utils::itostr(testIndex) + " wasn't yet "
                                 "executed, can't provide test log");
    batteryLog.append(testLog);
}

void Test::execute() {
    if(executed)
        throw std::runtime_error("test was already executed");

    std::cout << "Executing test " << testIndex << " in battery "
              << Constants::batteryToString(battery) << std::endl;
    bool timeouted = false;
    testLog = TestUtils::executeBinary(executablePath ,
                                       createArgs(), "" ,
                                       MISC_EXECUTION_TIMEOUT ,
                                       &timeouted);
    if(timeouted) {
        std::cout << "[WARNING] Test " << testIndex << " in battery "
                  << Constants::batteryToString(battery) << " timeouted and was killed. "
                     "Timeout period is set to " << MISC_EXECUTION_TIMEOUT << " seconds." << std::endl;
        return;
    }
    extractPvalues();
    executed = true;
}

std::string Test::getLogicName() const {
    return logicName;
}

std::vector<std::string> Test::getParameters() const {
    std::stringstream rval;
    rval << "Repetitions: " << repetitions << std::endl;
    if(battery == Constants::BATTERY_TU01_RABBIT ||
            battery == Constants::BATTERY_TU01_ALPHABIT)
        rval << "Bit NB: " << bit_nb << std::endl;

    if(battery == Constants::BATTERY_TU01_ALPHABIT) {
        rval << "Bit R: " << bit_r << std::endl;
        rval << "Bit S: " << bit_s << std::endl;
    }

    if(!params.empty() &&
            (battery == Constants::BATTERY_TU01_SMALLCRUSH ||
            battery == Constants::BATTERY_TU01_CRUSH ||
            battery == Constants::BATTERY_TU01_BIGCRUSH)) {
        for(const tParam & par : params)
            rval << par.first << " = " << par.second << std::endl;
    }

    return Utils::split(rval.str() , '\n');
}

std::vector<std::string> Test::getStatistics() const {
    return statisticNames;
}

std::vector<tTestPvals> Test::getResults() const {
    if(!executed)
        throw std::runtime_error("can't return results before execution of test");

    return results;
}
int Test::getTestIndex() const {
    return testIndex;
}


/*
                     __                       __
                    |  \                     |  \
  ______    ______   \$$ __     __  ______  _| $$_     ______
 /      \  /      \ |  \|  \   /  \|      \|   $$ \   /      \
|  $$$$$$\|  $$$$$$\| $$ \$$\ /  $$ \$$$$$$\\$$$$$$  |  $$$$$$\
| $$  | $$| $$   \$$| $$  \$$\  $$ /      $$ | $$ __ | $$    $$
| $$__/ $$| $$      | $$   \$$ $$ |  $$$$$$$ | $$|  \| $$$$$$$$
| $$    $$| $$      | $$    \$$$   \$$    $$  \$$  $$ \$$     \
| $$$$$$$  \$$       \$$     \$     \$$$$$$$   \$$$$   \$$$$$$$
| $$
| $$
 \$$
*/

tTestInfo Test::pickTestInfo(int testIndex , int battery , std::string & batteryXPath) {
    tTestInfo tinfo;
    switch(battery) {
    case Constants::BATTERY_TU01_SMALLCRUSH: {
        batteryXPath = XPATH_SMALL_CRUSH_SETTINGS;
        SmallCrushTI ti = static_cast<SmallCrushTI>(testIndex);
        if(ti <= SmallCrushTI::smarsa_BirthdaySpacing)   { tinfo = INFO_SMARSA_BIRTHDAYSPACINGS; } else
        if(ti <= SmallCrushTI::sknuth_Collision)         { tinfo = INFO_SKNUTH_COLLISION; } else
        if(ti <= SmallCrushTI::sknuth_Gap)               { tinfo = INFO_SKNUTH_GAP; } else
        if(ti <= SmallCrushTI::sknuth_SimpPoker)         { tinfo = INFO_SKNUTH_SIMPPOKER; } else
        if(ti <= SmallCrushTI::sknuth_CouponCollector)   { tinfo = INFO_SKNUTH_COUPONCOLLECTOR; } else
        if(ti <= SmallCrushTI::sknuth_MaxOft)            { tinfo = INFO_SKNUTH_MAXOFT; } else
        if(ti <= SmallCrushTI::svaria_WeightDistrib)     { tinfo = INFO_SVARIA_WEIGHTDISTRIB; } else
        if(ti <= SmallCrushTI::smarsa_MatrixRank)        { tinfo = INFO_SMARSA_MATRIXRANK; } else
        if(ti <= SmallCrushTI::sstring_HammingIndep)     { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= SmallCrushTI::swalk_RandomWalk1)        { tinfo = INFO_SWALK_RANDOMWALK1; } else
        {
            throw std::runtime_error("invalid SmallCrush test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    case Constants::BATTERY_TU01_CRUSH: {
        batteryXPath = XPATH_CRUSH_SETTINGS;
        CrushTI ti = static_cast<CrushTI>(testIndex);
        if(ti <= CrushTI::smarsa_SerialOver)            { tinfo = INFO_SMARSA_SERIALOVER; } else
        if(ti <= CrushTI::smarsa_CollisionOver)         { tinfo = INFO_SMARSA_COLLISIONOVER; } else
        if(ti <= CrushTI::smarsa_BirthdaySpacings)      { tinfo = INFO_SMARSA_BIRTHDAYSPACINGS; } else
        if(ti <= CrushTI::snpair_ClosePairs)            { tinfo = INFO_SNPAIR_CLOSEPAIRS; } else
        if(ti <= CrushTI::snpair_ClosePairs_bigT)       { tinfo = INFO_SNPAIR_CLOSEPAIRS_BIGT; } else
        if(ti <= CrushTI::snpair_ClosePairsBitMatch)    { tinfo = INFO_SNPAIR_CLOSEPAIRSBITMATCH; } else
        if(ti <= CrushTI::sknuth_SimpPoker)             { tinfo = INFO_SKNUTH_SIMPPOKER; } else
        if(ti <= CrushTI::sknuth_CouponCollector)       { tinfo = INFO_SKNUTH_COUPONCOLLECTOR; } else
        if(ti <= CrushTI::sknuth_Gap)                   { tinfo = INFO_SKNUTH_GAP; } else
        if(ti <= CrushTI::sknuth_Run)                   { tinfo = INFO_SKNUTH_RUN; } else
        if(ti <= CrushTI::sknuth_Permutation)           { tinfo = INFO_SKNUTH_PERMUTATION; } else
        if(ti <= CrushTI::sknuth_CollisionPermut)       { tinfo = INFO_SKNUTH_COLLISIONPERMUT; } else
        if(ti <= CrushTI::sknuth_MaxOft_bigN)           { tinfo = INFO_SKNUTH_MAXOFT_BIGN; } else
        if(ti <= CrushTI::sknuth_MaxOft)                { tinfo = INFO_SKNUTH_MAXOFT; } else
        if(ti <= CrushTI::svaria_SampleProd)            { tinfo = INFO_SVARIA_SAMPLEPROD; } else
        if(ti <= CrushTI::svaria_SampleMean)            { tinfo = INFO_SVARIA_SAMPLEMEAN; } else
        if(ti <= CrushTI::svaria_SampleCorr)            { tinfo = INFO_SVARIA_SAMPLECORR; } else
        if(ti <= CrushTI::svaria_AppearanceSpacings)    { tinfo = INFO_SVARIA_APPEARANCESPACINGS; } else
        if(ti <= CrushTI::svaria_WeightDistrib)         { tinfo = INFO_SVARIA_WEIGHTDISTRIB; } else
        if(ti <= CrushTI::svaria_SumCollector)          { tinfo = INFO_SVARIA_SUMCOLLECTOR; } else
        if(ti <= CrushTI::smarsa_MatrixRank)            { tinfo = INFO_SMARSA_MATRIXRANK; } else
        if(ti <= CrushTI::smarsa_Savir2)                { tinfo = INFO_SMARSA_SAVIR2; } else
        if(ti <= CrushTI::smarsa_GCD)                   { tinfo = INFO_SMARSA_GDC; } else
        if(ti <= CrushTI::swalk_RandomWalk1)            { tinfo = INFO_SWALK_RANDOMWALK1; } else
        if(ti <= CrushTI::scomp_LinearComp)             { tinfo = INFO_SCOMP_LINEARCOMP; } else
        if(ti <= CrushTI::scomp_LempelZiv_bigN)         { tinfo = INFO_SCOMP_LEMPELZIV_BIGN; } else
        if(ti <= CrushTI::sspectral_Fourier3)           { tinfo = INFO_SSPECRTAL_FOURIER3; } else
        if(ti <= CrushTI::sstring_LongestHeadRun)       { tinfo = INFO_SSTRING_LONGESTHEADRUN; } else
        if(ti <= CrushTI::sstring_PeriodsInStrings)     { tinfo = INFO_SSTRING_PERIODSINSTRINGS; } else
        if(ti <= CrushTI::sstring_HammingWeight2)       { tinfo = INFO_SSTRING_HAMMINGWEIGHT2; } else
        if(ti <= CrushTI::sstring_HammingCorr)          { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= CrushTI::sstring_HammingIndep)         { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= CrushTI::sstring_Run)                  { tinfo = INFO_SSTRING_RUN; } else
        if(ti <= CrushTI::sstring_AutoCor_bigN)         { tinfo = INFO_SSTRING_AUTOCOR_BIGN; } else
        {
            throw std::runtime_error("invalid BigCrush test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    case Constants::BATTERY_TU01_BIGCRUSH: {
        batteryXPath = XPATH_BIG_CRUSH_SETTINGS;
        BigCrushTI ti = static_cast<BigCrushTI>(testIndex);
        if(ti <= BigCrushTI::smarsa_SerialOver)         { tinfo = INFO_SMARSA_SERIALOVER; } else
        if(ti <= BigCrushTI::smarsa_CollisionOver)      { tinfo = INFO_SMARSA_COLLISIONOVER; } else
        if(ti <= BigCrushTI::smarsa_BirthdaySpacings)   { tinfo = INFO_SMARSA_BIRTHDAYSPACINGS; } else
        if(ti <= BigCrushTI::snpair_ClosePairs)         { tinfo = INFO_SNPAIR_CLOSEPAIRS; } else
        if(ti <= BigCrushTI::sknuth_SimpPoker)          { tinfo = INFO_SKNUTH_SIMPPOKER; } else
        if(ti <= BigCrushTI::sknuth_CouponCollector)    { tinfo = INFO_SKNUTH_COUPONCOLLECTOR; } else
        if(ti <= BigCrushTI::sknuth_Gap)                { tinfo = INFO_SKNUTH_GAP; } else
        if(ti <= BigCrushTI::sknuth_Run)                { tinfo = INFO_SKNUTH_RUN; } else
        if(ti <= BigCrushTI::sknuth_Permutation)        { tinfo = INFO_SKNUTH_PERMUTATION; } else
        if(ti <= BigCrushTI::sknuth_CollisionPermut)    { tinfo = INFO_SKNUTH_COLLISIONPERMUT; } else
        if(ti <= BigCrushTI::sknuth_MaxOft_bigN)        { tinfo = INFO_SKNUTH_MAXOFT_BIGN; } else
        if(ti <= BigCrushTI::svaria_SampleProd)         { tinfo = INFO_SVARIA_SAMPLEPROD; } else
        if(ti <= BigCrushTI::svaria_SampleMean)         { tinfo = INFO_SVARIA_SAMPLEMEAN; } else
        if(ti <= BigCrushTI::svaria_SampleCorr)         { tinfo = INFO_SVARIA_SAMPLECORR; } else
        if(ti <= BigCrushTI::svaria_AppearanceSpacings) { tinfo = INFO_SVARIA_APPEARANCESPACINGS; } else
        if(ti <= BigCrushTI::svaria_WeightDistrib)      { tinfo = INFO_SVARIA_WEIGHTDISTRIB; } else
        if(ti <= BigCrushTI::svaria_SumCollector)       { tinfo = INFO_SVARIA_SUMCOLLECTOR; } else
        if(ti <= BigCrushTI::smarsa_MatrixRank)         { tinfo = INFO_SMARSA_MATRIXRANK; } else
        if(ti <= BigCrushTI::smarsa_Savir2)             { tinfo = INFO_SMARSA_SAVIR2; } else
        if(ti <= BigCrushTI::smarsa_GCD)                { tinfo = INFO_SMARSA_GDC; } else
        if(ti <= BigCrushTI::swalk_RandomWalk1)         { tinfo = INFO_SWALK_RANDOMWALK1; } else
        if(ti <= BigCrushTI::scomp_LinearComp)          { tinfo = INFO_SCOMP_LINEARCOMP; } else
        if(ti <= BigCrushTI::scomp_LempelZiv_bigN)      { tinfo = INFO_SCOMP_LEMPELZIV_BIGN; } else
        if(ti <= BigCrushTI::sspectral_Fourier3)        { tinfo = INFO_SSPECRTAL_FOURIER3; } else
        if(ti <= BigCrushTI::sstring_LongestHeadRun)    { tinfo = INFO_SSTRING_LONGESTHEADRUN; } else
        if(ti <= BigCrushTI::sstring_PeriodsInStrings)  { tinfo = INFO_SSTRING_PERIODSINSTRINGS; } else
        if(ti <= BigCrushTI::sstring_HammingWeight2)    { tinfo = INFO_SSTRING_HAMMINGWEIGHT2; } else
        if(ti <= BigCrushTI::sstring_HammingCorr)       { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= BigCrushTI::sstring_HammingIndep)      { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= BigCrushTI::sstring_Run)               { tinfo = INFO_SSTRING_RUN; } else
        if(ti <= BigCrushTI::sstring_AutoCor_bigN)      { tinfo = INFO_SSTRING_AUTOCOR_BIGN; } else
        {
            throw std::runtime_error("invalid BigCrush test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    case Constants::BATTERY_TU01_RABBIT: {
        batteryXPath = XPATH_RABBIT_SETTINGS;
        RabbitTI ti = static_cast<RabbitTI>(testIndex);
        if(ti <= RabbitTI::smultin_MultinomialBitsOver) { tinfo = INFO_SMULTIN_MULTINOMIALBITSOVER; } else
        if(ti <= RabbitTI::snpair_ClosePairsBitMatch)   { tinfo = INFO_SNPAIR_CLOSEPAIRSBITMATCH; } else
        if(ti <= RabbitTI::svaria_AppearanceSpacings)   { tinfo = INFO_SVARIA_APPEARANCESPACINGS; } else
        if(ti <= RabbitTI::scomp_LinearComp)            { tinfo = INFO_SCOMP_LINEARCOMP; } else
        if(ti <= RabbitTI::scomp_LempelZiv)             { tinfo = INFO_SCOMP_LEMPELZIV; } else
        if(ti <= RabbitTI::sspectral_Fourier1)          { tinfo = INFO_SSPECRTAL_FOURIER1; } else
        if(ti <= RabbitTI::sspectral_Fourier3)          { tinfo = INFO_SSPECRTAL_FOURIER3; } else
        if(ti <= RabbitTI::sstring_LongestHeadRun)      { tinfo = INFO_SSTRING_LONGESTHEADRUN; } else
        if(ti <= RabbitTI::sstring_PeriodsInStrings)    { tinfo = INFO_SSTRING_PERIODSINSTRINGS; } else
        if(ti <= RabbitTI::sstring_HammingWeight)       { tinfo = INFO_SSTRING_HAMMINGWEIGHT; } else
        if(ti <= RabbitTI::sstring_HammingCorr)         { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= RabbitTI::sstring_HammingIndep)        { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= RabbitTI::sstring_AutoCor)             { tinfo = INFO_SSTRING_AUTOCOR; } else
        if(ti <= RabbitTI::sstring_Run)                 { tinfo = INFO_SSTRING_RUN; } else
        if(ti <= RabbitTI::smarsa_MatrixRank)           { tinfo = INFO_SMARSA_MATRIXRANK; } else
        if(ti <= RabbitTI::swalk_RandomWalk1)           { tinfo = INFO_SWALK_RANDOMWALK1; } else
        {
            throw std::runtime_error("invalid Rabbit test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    case Constants::BATTERY_TU01_ALPHABIT: {
        batteryXPath = XPATH_ALPHABIT_SETTINGS;
        AlphabitTI ti = static_cast<AlphabitTI>(testIndex);
        if(ti <= AlphabitTI::smultin_MultinomialBitsOver_bigN)  { tinfo = INFO_SMULTIN_MULTBITSOVER_BIGN; } else
        if(ti <= AlphabitTI::sstring_HammingIndep)              { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= AlphabitTI::sstring_HammingCorr)               { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= AlphabitTI::swalk_RandomWalk1)                 { tinfo = INFO_SWALK_RANDOMWALK1; } else
        {
            throw std::runtime_error("invalid Alphabit test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    default:
        throw std::runtime_error("unknown TestU01 battery");
    }
    return tinfo;
}

void Test::checkSetParams(TiXmlNode * paramsNode) {
    if(!paramsNode || !paramsNode->FirstChild())
        /* Given node has no params, test has no parameters */
        return;

    std::vector<tParam> parameters(paramNames.size());
    tParam emptyPar;
    bool parIsSet;
    const char * parName;
    const char * parValue;

    for(TiXmlElement * parElement = paramsNode->FirstChildElement();
            parElement ;
            parElement = parElement->NextSiblingElement()) {
        parName = parElement->Attribute(XPATH_ATTRIBUTE_PAR_NAME.c_str());
        parValue = parElement->GetText();
        if(!parName || strlen(parName) < 1)
            throw std::runtime_error(logicName + ": "
                                     "PAR node must have non-empty attribute: " +
                                     XPATH_ATTRIBUTE_PAR_NAME);
        if(!parValue || strlen(parValue) < 1)
            throw std::runtime_error(logicName + ": PAR node can't be empty");

        parIsSet = false;
        for(size_t i = 0 ; i < paramNames.size() ; ++i) {
            if(paramNames.at(i) == parName) {
                if(parameters.at(i) != emptyPar)
                    throw std::runtime_error(logicName + ": can't set parameter \"" +
                                             paramNames.at(i) + "\" multiple times");
                parameters.at(i).first = parName;
                parameters.at(i).second = parValue;
                parIsSet = true;
                break;
            }
        }
        if(!parIsSet)
            throw std::runtime_error(logicName + ": unknown parameter name: " +
                                     (std::string)parName);
    }
    for(auto i : parameters)
        if(i == emptyPar)
            throw std::runtime_error(logicName + ": not all test parameters were set");
    params = std::move(parameters);
}

std::string Test::createArgs() const {
    std::stringstream arguments;
    arguments << "testu01 ";
    /* Setting battery mode */
    arguments << "-m ";
    switch(battery) {
    case Constants::BATTERY_TU01_SMALLCRUSH:
        arguments << "small_crush "; break;
    case Constants::BATTERY_TU01_CRUSH:
        arguments << "crush "; break;
    case Constants::BATTERY_TU01_BIGCRUSH:
        arguments << "big_crush "; break;
    case Constants::BATTERY_TU01_RABBIT:
        arguments << "rabbit "; break;
    case Constants::BATTERY_TU01_ALPHABIT:
        arguments << "alphabit "; break;
    default:
        throw std::runtime_error("unknown battery");
    }
    /* Test number option */
    arguments << "-t " << testIndex << " ";
    /* Input file option */
    arguments << "-i " << binaryDataPath << " ";
    /* Repetitions option */
    if(repetitions != 1)
        arguments << "-r " << repetitions << " ";
    /* Custom parameters option */
    if(params.size() > 0) {
        arguments << "--params ";
        for(auto i : params)
            arguments << i.second << " ";
    }
    /* nb */
    if(!bit_nb.empty())
        arguments << "--bit_nb " << bit_nb << " ";
    /* r */
    if(!bit_r.empty())
        arguments << "--bit_r " << bit_r << " ";
    /* s */
    if(!bit_s.empty())
        arguments << "--bit_s " << bit_s;

    return arguments.str();
}

void Test::extractPvalues() {
    static const std::regex RE_PVALUE {
        "p-value of test {23}: *?("
        "eps|"                            /* Just "eps" */
        "1 - eps1|"                       /* Just "1 - eps1" */
        "0\\.\\d{2,4}|"                   /* Decimal rounded from 2 to  digits */
        "(1 -  ?)?\\d\\.\\de-\\d{1,3}"    /* Decimal in scientific notation that can be preceeded by "1 - " */
        ") *?(\\*\\*\\*\\*\\*)?\\n"       /* Capture ending "*****" - pvalue is suspect */
    };

    auto begin = std::sregex_iterator(testLog.begin() , testLog.end() , RE_PVALUE);
    auto end = std::sregex_iterator();

    int pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        std::cout << "[WARNING] No pValues were extracted" << std::endl;
        return;
    }

    if(pValCount % repetitions != 0)
        throw std::runtime_error("can't extract p-values from log: number of"
                                 " p-value is not divisible by repetitions");
    statCount = pValCount / repetitions;
    if(statCount != statisticNames.size()) {
        /* So this normally doesn't happen but(!) some tests have variable
         * output based on their parameters. For example scomp_LempevZiv has
         * different output when executed from Crush battery and Rabbit battery.
         * In that case, say that to user and use unknown statistics names. */
        std::cout << "[WARNING] Number of statistics extracted from log differs from default number."
                     " Inspect the log for correct statistics names." << std::endl;
        std::vector<std::string> newStatNames;
        for(size_t i = 1 ; i <= statCount ; ++i)
            newStatNames.push_back("Unknown " + Utils::itostr(i));
        statisticNames = std::move(newStatNames);
    }

    tTestPvals pValues;

    for(; begin != end ;) {
        for(uint i = 0 ; i < statCount ; ++i) {
            std::smatch match = *begin;
            pValues.push_back(convertStringToDouble(match[1].str() ,
                                                    match[2].str()));
            ++begin;
        }
        results.push_back(std::move(pValues));
        pValues.clear();
    }
}

double Test::convertStringToDouble(const std::string & num,
                                   const std::string & oneMinus) {
    if(num == "eps") {
        return 1.0E-300;
    } else if(num == "1 - eps1") {
        return 1 - 1.0E-15;
    } else if(num.find('e') == std::string::npos) {
        return Utils::strtod(num);
    } else {
        std::string tmp = num;
        tmp.erase(0 , oneMinus.length());
        std::vector<std::string> splitted = Utils::split(tmp , 'e');
        double base = Utils::strtod(splitted.at(0));
        double exp = Utils::strtod(splitted.at(1));
        base *= pow(10.0 , exp);
        if(oneMinus.empty()) {
            return base;
        } else {
            return 1 - base;
        }
    }
}

} // namespace testu01
} // namespace batteries
} // namespace rtt

