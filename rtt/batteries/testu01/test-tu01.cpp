#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const tTestInfo Test::INFO_SMARSA_SERIALOVER            {"smarsa_SerialOver" , {"N","n","r","d","t"}};
const tTestInfo Test::INFO_SMARSA_COLLISIONOVER         {"smarsa_CollisionOver" , {"N","n","r","d","t"}};
const tTestInfo Test::INFO_SMARSA_BIRTHDAYSPACINGS      {"smarsa_BirthdaySpacings" , {"N","n","r","d","t","p"}};
const tTestInfo Test::INFO_SNPAIR_CLOSEPAIRS            {"snpair_ClosePairs" , {"N","n","r","t","p","m"}};
const tTestInfo Test::INFO_SNPAIR_CLOSEPAIRSBITMATCH    {"snpair_ClosePairsBitMatch" , {"N","n","r","t"}};
const tTestInfo Test::INFO_SKNUTH_COLLISION             {"sknuth_Collision" , {"N","n","r","d","t"}};
const tTestInfo Test::INFO_SKNUTH_SIMPPOKER             {"sknuth_SimpPoker" , {"N","n","r","d","k"}};
const tTestInfo Test::INFO_SKNUTH_COUPONCOLLECTOR       {"sknuth_CouponCollector" , {"N","n","r","d"}};
const tTestInfo Test::INFO_SKNUTH_GAP                   {"sknuth_Gap" , {"N","n","r","Alpha","Beta"}};
const tTestInfo Test::INFO_SKNUTH_RUN                   {"sknuth_Run" , {"N","n","r","Up"}};
const tTestInfo Test::INFO_SKNUTH_PERMUTATION           {"sknuth_Permutation" , {"N","n","r","t"}};
const tTestInfo Test::INFO_SKNUTH_COLLISIONPERMUT       {"sknuth_CollisionPermut" , {"N","n","r","t"}};
const tTestInfo Test::INFO_SKNUTH_MAXOFT                {"sknuth_MaxOft" , {"N","n","r","d","t"}};
const tTestInfo Test::INFO_SVARIA_SAMPLEPROD            {"svaria_SampleProd" , {"N","n","r","t"}};
const tTestInfo Test::INFO_SVARIA_SAMPLEMEAN            {"svaria_SampleMean" , {"N","n","r"}};
const tTestInfo Test::INFO_SVARIA_SAMPLECORR            {"svaria_SampleCorr" , {"N","n","r","k"}};
const tTestInfo Test::INFO_SVARIA_APPEARANCESPACINGS    {"svaria_AppearanceSpacings" , {"N","Q","K","r","s","L"}};
const tTestInfo Test::INFO_SVARIA_WEIGHTDISTRIB         {"svaria_WeightDistrib" , {"N","n","r","k","",""}};
const tTestInfo Test::INFO_SVARIA_SUMCOLLECTOR          {"svaria_SumCollector" , {"N","n","r","g"}};
const tTestInfo Test::INFO_SMARSA_MATRIXRANK            {"smarsa_MatrixRank" , {"N","n","r","s","L","k"}};
const tTestInfo Test::INFO_SMARSA_SAVIR2                {"smarsa_Savir2" , {"N","n","r","m","t"}};
const tTestInfo Test::INFO_SMARSA_GDC                   {"smarsa_GCD" , {"N","n","r","s"}};
const tTestInfo Test::INFO_SWALK_RANDOMWALK1            {"swalk_RandomWalk1" , {"N","n","r","s","L0","L1"}};
const tTestInfo Test::INFO_SCOMP_LINEARCOMP             {"scomp_LinearComp" , {"N","n","r","s"}};
const tTestInfo Test::INFO_SCOMP_LEMPELZIV              {"scomp_LempelZiv" , {"N","k","r","s"}};
const tTestInfo Test::INFO_SSPECRTAL_FOURIER1           {"sspectral_Fourier1" , {}};
const tTestInfo Test::INFO_SSPECRTAL_FOURIER3           {"sspectral_Fourier3" , {"N","k","r","s"}};
const tTestInfo Test::INFO_SSTRING_LONGESTHEADRUN       {"sstring_LongestHeadRun" , {"N","n","r","s","L"}};
const tTestInfo Test::INFO_SSTRING_PERIODSINSTRINGS     {"sstring_PeriodsInStrings" , {"N","n","r","s"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGWEIGHT        {"sstring_HammingWeight" , {}};
const tTestInfo Test::INFO_SSTRING_HAMMINGWEIGHT2       {"sstring_HammingWeight2" , {"N","n","r","s","L"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGCORR          {"sstring_HammingCorr" , {"N","n","r","s","L"}};
const tTestInfo Test::INFO_SSTRING_HAMMINGINDEP         {"sstring_HammingIndep" , {"N","n","r","s","L","d"}};
const tTestInfo Test::INFO_SSTRING_RUN                  {"sstring_Run" , {"N","n","r","s"}};
const tTestInfo Test::INFO_SSTRING_AUTOCOR              {"sstring_AutoCor" , {"N","n","r","s","d"}};
const tTestInfo Test::INFO_SMULTIN_MULTINOMIALBITSOVER  {"smultin_MultinomialBitsIver" , {}};

const std::string Test::XPATH_EXECUTABLE_BINARY     = "TESTU01_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_DEFAULT_REPS          = "TESTU01_SETTINGS/DEFAULT_REPETITIONS";
const std::string Test::XPATH_DEFAULT_BIT_NB        = "TESTU01_SETTINGS/DEFAULT_BIT_NB";
const std::string Test::XPATH_DEFAULT_BIT_R         = "TESTU01_SETTINGS/DEFAULT_BIT_R";
const std::string Test::XPATH_DEFAULT_BIT_S         = "TESTU01_SETTINGS/DEFAULT_BIT_S";
const std::string Test::XPATH_SMALL_CRUSH_SETTINGS  = "TESTU01_SETTINGS/SMALL_CRUSH_SETTINGS";
const std::string Test::XPATH_CRUSH_SETTINGS        = "TESTU01_SETTINGS/CRUSH_SETTINGS";
const std::string Test::XPATH_BIG_CRUSH_SETTINGS    = "TESTU01_SETTINGS/BIG_CRUSH_SETTINGS";
const std::string Test::XPATH_RABBIT_SETTINGS       = "TESTU01_SETTINGS/RABBIT_SETTINGS";
const std::string Test::XPATH_ALPHABIT_SETTINGS     = "TESTU01_SETTINGS/ALPHABIT_SETTINGS";
const std::string Test::XPATH_TEST_REPS             = "REPETITIONS";
const std::string Test::XPATH_TEST_PARAMS           = "PARAMS";
const std::string Test::XPATH_TEST_BIT_NB           = "BIT_NB";
const std::string Test::XPATH_TEST_BIT_R            = "BIT_R";
const std::string Test::XPATH_TEST_BIT_S            = "BIT_S";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX  = "test";
const std::string Test::XPATH_ATTRIBUTE_PAR_NAME    = "name";


Test Test::getInstance(int testIndex, const CliOptions & options, TiXmlNode * cfgRoot) {
    if(!cfgRoot)
        throw std::runtime_error("null cfgRoot");
    if(testIndex <= 0)
        throw std::runtime_error("invalid TestU01 test constant: " + Utils::itostr(testIndex));

    Test test;
    std::string batteryXPath;
    tTestInfo tinfo;
    pickTestInfo(testIndex , options.getBattery() , tinfo , batteryXPath);
    TiXmlNode * testSettings = getXMLChildNodeWithAttValue(
                                getXMLElement(cfgRoot , batteryXPath),
                                XPATH_ATTRIBUTE_TEST_INDEX ,
                                Utils::itostr(testIndex)
                               );
    test.battery = options.getBattery();
    test.testIndex = testIndex;
    test.logicName = tinfo.first;

    test.repetitions = getSpecificOrDefaultOpt(cfgRoot , testSettings , XPATH_DEFAULT_REPS ,
                                               XPATH_TEST_REPS);
    if(test.repetitions.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": default or test specific repetitions must be set");
    test.executablePath = getXMLElementValue(cfgRoot , XPATH_EXECUTABLE_BINARY);
    if(test.executablePath.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": path to executable binary can't be empty");
    test.binaryDataPath = options.getBinFilePath();
    if(test.binaryDataPath.empty())
        throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                 ": path to binary data can't be empty");

    /* Getting params - only for Crush batteries */
    if(test.battery == Constants::BATTERY_TU01_SMALLCRUSH ||
            test.battery == Constants::BATTERY_TU01_CRUSH ||
            test.battery == Constants::BATTERY_TU01_BIGCRUSH)
        test.params = checkSetParams(tinfo , getXMLElement(testSettings , XPATH_TEST_PARAMS));

    /* Getting nb - Rabbit and Alphabit */
    if(test.battery == Constants::BATTERY_TU01_RABBIT ||
            test.battery == Constants::BATTERY_TU01_ALPHABIT) {
        test.bit_nb = getSpecificOrDefaultOpt(cfgRoot , testSettings , XPATH_DEFAULT_BIT_NB ,
                                              XPATH_TEST_BIT_NB);
        if(test.bit_nb.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_nb option must be set"
                                     " in Rabbit and Alphabit battery");
    }
    /* Getting r s - Alphabit */
    if(test.battery == Constants::BATTERY_TU01_ALPHABIT) {
        test.bit_r = getSpecificOrDefaultOpt(cfgRoot , testSettings , XPATH_DEFAULT_BIT_R ,
                                              XPATH_TEST_BIT_R);
        if(test.bit_r.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_r option must be set"
                                     " in Alphabit battery");

        test.bit_s = getSpecificOrDefaultOpt(cfgRoot , testSettings , XPATH_DEFAULT_BIT_S ,
                                              XPATH_TEST_BIT_S);
        if(test.bit_s.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific bit_s option must be set"
                                     " in Alphabit battery");
    }
    return std::move(test);
}

void Test::execute() {
    std::cout << "Starting execution of TestU01 test " << testIndex
              << " in battery " << battery << std::endl;

    /* Creating pipes for redirecting battery output */
    int stdout_pipe[2];
    int stderr_pipe[2];
    if(pipe(stdout_pipe) || pipe(stderr_pipe))
            throw std::runtime_error("pipe creation failed");
    /* Setting process actions. At the beginning, stdout and stderr */
    /* are mapped to pipes and unused ends are closed. Then I can */
    /* inspect battery output in this process. */
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);
    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);
    int argc = 0;

    char ** argv = buildArgv(&argc);
    pid_t pid = 0;
    int status = posix_spawn(&pid , executablePath.c_str() ,
                             &actions , NULL , argv , environ);
    if(status == 0) {
        std::cout << "Started TestU01 process with pid: " << pid << std::endl;
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        /* Read and store battery output. */
        /* Later, the pvalues will be extracted */
        readPipes(stdout_pipe , stderr_pipe);
        if(waitpid(pid , &status , 0) != -1)
            std::cout << "TestU01 exited with status: " << status << std::endl;
        else
            throw std::runtime_error("error when running TestU01");
    } else {
        throw std::runtime_error("error occured when starting TestU01: " +
                                             (std::string)strerror(status));
    }
    posix_spawn_file_actions_destroy(&actions);
    destroyArgv(argc , argv);

    /* Battery successfuly finished computation */
    /* Resulting pvalues are extracted from stored battery output */
    extractPvalues();
    std::cout << testLog << std::endl;
    /* Allowing work with results */
    executed = true;
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

void Test::pickTestInfo(int testIndex , int battery ,
                        tTestInfo & tinfo , std::string & batteryXPath) {
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
        if(ti <= CrushTI::snpair_ClosePairsBitMatch)    { tinfo = INFO_SNPAIR_CLOSEPAIRSBITMATCH; } else
        if(ti <= CrushTI::sknuth_SimpPoker)             { tinfo = INFO_SKNUTH_SIMPPOKER; } else
        if(ti <= CrushTI::sknuth_CouponCollector)       { tinfo = INFO_SKNUTH_COUPONCOLLECTOR; } else
        if(ti <= CrushTI::sknuth_Gap)                   { tinfo = INFO_SKNUTH_GAP; } else
        if(ti <= CrushTI::sknuth_Run)                   { tinfo = INFO_SKNUTH_RUN; } else
        if(ti <= CrushTI::sknuth_Permutation)           { tinfo = INFO_SKNUTH_PERMUTATION; } else
        if(ti <= CrushTI::sknuth_CollisionPermut)       { tinfo = INFO_SKNUTH_COLLISIONPERMUT; } else
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
        if(ti <= CrushTI::scomp_LempelZiv)              { tinfo = INFO_SCOMP_LEMPELZIV; } else
        if(ti <= CrushTI::sspectral_Fourier3)           { tinfo = INFO_SSPECRTAL_FOURIER3; } else
        if(ti <= CrushTI::sstring_LongestHeadRun)       { tinfo = INFO_SSTRING_LONGESTHEADRUN; } else
        if(ti <= CrushTI::sstring_PeriodsInStrings)     { tinfo = INFO_SSTRING_PERIODSINSTRINGS; } else
        if(ti <= CrushTI::sstring_HammingWeight2)       { tinfo = INFO_SSTRING_HAMMINGWEIGHT2; } else
        if(ti <= CrushTI::sstring_HammingCorr)          { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= CrushTI::sstring_HammingIndep)         { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= CrushTI::sstring_Run)                  { tinfo = INFO_SSTRING_RUN; } else
        if(ti <= CrushTI::sstring_AutoCor)              { tinfo = INFO_SSTRING_AUTOCOR; } else
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
        if(ti <= BigCrushTI::sknuth_MaxOft)             { tinfo = INFO_SKNUTH_MAXOFT; } else
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
        if(ti <= BigCrushTI::scomp_LempelZiv)           { tinfo = INFO_SCOMP_LEMPELZIV; } else
        if(ti <= BigCrushTI::sspectral_Fourier3)        { tinfo = INFO_SSPECRTAL_FOURIER3; } else
        if(ti <= BigCrushTI::sstring_LongestHeadRun)    { tinfo = INFO_SSTRING_LONGESTHEADRUN; } else
        if(ti <= BigCrushTI::sstring_PeriodsInStrings)  { tinfo = INFO_SSTRING_PERIODSINSTRINGS; } else
        if(ti <= BigCrushTI::sstring_HammingWeight2)    { tinfo = INFO_SSTRING_HAMMINGWEIGHT2; } else
        if(ti <= BigCrushTI::sstring_HammingCorr)       { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= BigCrushTI::sstring_HammingIndep)      { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= BigCrushTI::sstring_Run)               { tinfo = INFO_SSTRING_RUN; } else
        if(ti <= BigCrushTI::sstring_AutoCor)           { tinfo = INFO_SSTRING_AUTOCOR; } else
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
        if(ti <= AlphabitTI::smultin_MultinomialBitsOver)   { tinfo = INFO_SMULTIN_MULTINOMIALBITSOVER; } else
        if(ti <= AlphabitTI::sstring_HammingIndep)          { tinfo = INFO_SSTRING_HAMMINGINDEP; } else
        if(ti <= AlphabitTI::sstring_HammingCorr)           { tinfo = INFO_SSTRING_HAMMINGCORR; } else
        if(ti <= AlphabitTI::swalk_RandomWalk1)             { tinfo = INFO_SWALK_RANDOMWALK1; } else
        {
            throw std::runtime_error("invalid Alphabit test constant: " + Utils::itostr(testIndex));
        }
        break;
    }
    default:
        throw std::runtime_error("unknown TestU01 battery");
    }
}

std::string Test::getSpecificOrDefaultOpt(TiXmlNode * cfgRoot , TiXmlNode * testNode ,
                                    const std::string & defaultPath ,
                                    const std::string & testPath) {
    if(!cfgRoot)
        throw std::runtime_error("null root");

    std::string nodeValue;
    if(!testNode) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    }

    nodeValue = getXMLElementValue(testNode , testPath);
    if(nodeValue.empty()) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    } else {
        return nodeValue;
    }
}

std::vector<tParam> Test::checkSetParams(const tTestInfo & testInfo ,
                                         TiXmlNode * paramsNode) {
    if(testInfo.first.empty() || testInfo.second.empty())
        /* This won't happen without bug in code */
        throw std::runtime_error("invalid testinfo");

    if(!paramsNode || !paramsNode->FirstChild())
        /* Given node has no params, test has no parameters */
        return {};

    const std::string & logicName = testInfo.first;
    const tParNameList & paramNames = testInfo.second;

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
    return std::move(parameters);
}

char ** Test::buildArgv(int * argc) const {
    std::stringstream tmpss;
    tmpss << "testu01 ";
    /* Setting battery mode */
    tmpss << "-m ";
    switch(battery) {
    case Constants::BATTERY_TU01_SMALLCRUSH:
        tmpss << "small_crush "; break;
    case Constants::BATTERY_TU01_CRUSH:
        tmpss << "crush "; break;
    case Constants::BATTERY_TU01_BIGCRUSH:
        tmpss << "big_crush "; break;
    case Constants::BATTERY_TU01_RABBIT:
        tmpss << "rabbit "; break;
    case Constants::BATTERY_TU01_ALPHABIT:
        tmpss << "alphabit "; break;
    default:
        throw std::runtime_error("unknown battery");
    }
    /* Test number option */
    tmpss << "-t " << testIndex << " ";
    /* Input file option */
    tmpss << "-i " << binaryDataPath << " ";
    /* Repetitions option */
    tmpss << "-r " << repetitions << " ";
    /* Custom parameters option */
    if(params.size() > 0) {
        tmpss << "--params ";
        for(auto i : params)
            tmpss << i.second << " ";
    }
    /* nb */
    if(!bit_nb.empty())
        tmpss << "--bit_nb " << bit_nb << " ";
    /* r */
    if(!bit_r.empty())
        tmpss << "--bit_r " << bit_r << " ";
    /* s */
    if(!bit_s.empty())
        tmpss << "--bit_s " << bit_s;
    std::vector<std::string> vecArg = Utils::split(tmpss.str() , ' ');

    char ** argv = new char * [vecArg.size() + 1];
    for(size_t i = 0 ; i < vecArg.size() ; ++i) {
        argv[i] = new char [vecArg[i].length() + 1];
        strcpy(argv[i] , vecArg[i].c_str());
    }
    argv[vecArg.size()] = NULL;
    *argc = vecArg.size() + 1;
    return argv;
}

void Test::destroyArgv(int argc, char ** argv) const {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

void Test::readPipes(int * stdout_pipe, int * stderr_pipe) {
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::vector<pollfd> pollVector = {{stdout_pipe[0] , POLLIN},
                                      {stderr_pipe[0] , POLLIN}};
    for( ; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if (pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            testLog.append(buffer , 0 , bytes_read);
        }
        else if (pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            testLog.append(buffer , 0 , bytes_read);
        }
        else break; /* Reading done */
    }
}

void Test::extractPvalues() {
    // In time...
}

} // namespace testu01
} // namespace batteries
} // namespace rtt

