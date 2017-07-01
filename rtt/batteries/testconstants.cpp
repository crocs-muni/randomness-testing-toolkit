#include "testconstants.h"

namespace rtt {
namespace batteries {

const std::string TestConstants::NISTSTS_MAIN_RESULT_DIR       = "experiments/AlgorithmTesting/";
const tNistStsData TestConstants::NISTSTS_FREQ {
    "Frequency (monobits) test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "Frequency/",
    false
};
const tNistStsData TestConstants::NISTSTS_BLOCKFREQ {
    "Test For Frequency Within A Block" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "BlockFrequency/",
    true
};
const tNistStsData TestConstants::NISTSTS_CUSUMS {
    "Cumulative Sum (Cusum) Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "CumulativeSums/",
    false
};
const tNistStsData TestConstants::NISTSTS_RUNS {
    "Runs Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "Runs/",
    false
};
const tNistStsData TestConstants::NISTSTS_LONGESTRUN {
    "Test for the Longest Run of Ones in a Block" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "LongestRun/",
    false
};
const tNistStsData TestConstants::NISTSTS_RANK {
    "Random Binary Matrix Rank Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "Rank/",
    false
};
const tNistStsData TestConstants::NISTSTS_FFT {
    "Discrete Fourier Transform (Spectral) Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "FFT/",
    false
};
const tNistStsData TestConstants::NISTSTS_NONOVERTEMP {
    "Non-overlapping (Aperiodic) Template Matching Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "NonOverlappingTemplate/",
    true
};
const tNistStsData TestConstants::NISTSTS_OVERTEMP {
    "Overlapping (Periodic) Template Matching Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "OverlappingTemplate/",
    true
};
const tNistStsData TestConstants::NISTSTS_UNIVERSAL            {
    "Maurer's Universal Statistical Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "Universal/",
    false
};
const tNistStsData TestConstants::NISTSTS_APPROXENT            {
    "Approximate Entropy Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "ApproximateEntropy/",
    true
};
const tNistStsData TestConstants::NISTSTS_RNDEXCURSIONS        {
    "Random Excursions Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "RandomExcursions/",
    false
};
const tNistStsData TestConstants::NISTSTS_RNDEXCURSIONSVAR     {
    "Random Excursions Variant Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "RandomExcursionsVariant/",
    false
};
const tNistStsData TestConstants::NISTSTS_SERIAL               {
    "Serial Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "Serial/",
    true
};
const tNistStsData TestConstants::NISTSTS_LINEARCOMPLEXITY     {
    "Linear Complexity Test" ,
    TestConstants::NISTSTS_MAIN_RESULT_DIR + "LinearComplexity/",
    true
};

const tDieharderData TestConstants::DIEHARDER_BIRTHDAYS            {"Diehard Birthdays Test"};
const tDieharderData TestConstants::DIEHARDER_OPERM5               {"Diehard OPERM5 Test"};
const tDieharderData TestConstants::DIEHARDER_BINARYRANK1          {"Diehard 32x32 Binary Rank Test"};
const tDieharderData TestConstants::DIEHARDER_BINARYRANK2          {"Diehard 6x8 Binary Rank Test"};
const tDieharderData TestConstants::DIEHARDER_BITSTREAM            {"Diehard Bitstream Test"};
const tDieharderData TestConstants::DIEHARDER_OPSO                 {"Diehard OPSO"};
const tDieharderData TestConstants::DIEHARDER_OQSO                 {"Diehard OQSO Test"};
const tDieharderData TestConstants::DIEHARDER_DNA                  {"Diehard DNA Test"};
const tDieharderData TestConstants::DIEHARDER_COUNT1SBYTE          {"Diehard Count the 1s (stream) Test"};
const tDieharderData TestConstants::DIEHARDER_COUNT1SSTREAM        {"Diehard Count the 1s Test (byte)"};
const tDieharderData TestConstants::DIEHARDER_PARKING              {"Diehard Parking Lot Test"};
const tDieharderData TestConstants::DIEHARDER_MINDISTANCECIRCLE    {"Diehard Minimum Distance (2d Circle) Test"};
const tDieharderData TestConstants::DIEHARDER_MINDISTANCESPHERE    {"Diehard 3d Sphere (Minimum Distance) Test"};
const tDieharderData TestConstants::DIEHARDER_SQUEEZE              {"Diehard Squeeze Test"};
const tDieharderData TestConstants::DIEHARDER_SUMS                 {"Diehard Sums Test"};
const tDieharderData TestConstants::DIEHARDER_RUNS                 {"Diehard Runs Test"};
const tDieharderData TestConstants::DIEHARDER_CRAPS                {"Diehard Craps Test"};
const tDieharderData TestConstants::DIEHARDER_GCD                  {"Marsaglia and Tsang GCD Test"};
const tDieharderData TestConstants::DIEHARDER_MONOBIT              {"STS Monobit Test"};
const tDieharderData TestConstants::DIEHARDER_STSRUNS              {"STS Runs Test"};
const tDieharderData TestConstants::DIEHARDER_SERIAL               {"STS Serial Test (Generalized)"};
const tDieharderData TestConstants::DIEHARDER_BITDIST              {"RGB Bit Distribution Test"};
const tDieharderData TestConstants::DIEHARDER_MINDISTANCE          {"RGB Generalized Minimum Distance Test"};
const tDieharderData TestConstants::DIEHARDER_PERMUTATIONS         {"RGB Permutations Test"};
const tDieharderData TestConstants::DIEHARDER_LAGGED               {"RGB Lagged Sum Test"};
const tDieharderData TestConstants::DIEHARDER_KS                   {"RGB Kolmogorov-Smirnov Test"};
const tDieharderData TestConstants::DIEHARDER_BYTEDIST             {"Byte Distribution"};
const tDieharderData TestConstants::DIEHARDER_DABDCT               {"DAB DCT"};
const tDieharderData TestConstants::DIEHARDER_DABFILLTREE          {"DAB Fill Tree Test"};
const tDieharderData TestConstants::DIEHARDER_DABFILLTREE2         {"DAB Fill Tree Test 2"};
const tDieharderData TestConstants::DIEHARDER_DABMONOBIT           {"DAB Monobit 2 Test"};

const tTestU01Data TestConstants::TESTU01_SMARSA_SERIALOVER {
    "smarsa_SerialOver" ,
    {"N","n","r","d","t"} ,
    {"N","n","r","d","t","Sparse"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SMARSA_COLLISIONOVER {
    "smarsa_CollisionOver" ,
    {"N","n","r","d","t"} ,
    {"N","n","r","d","t","Sparse"} ,
    {
        "Collision"
    }
};
const tTestU01Data TestConstants::TESTU01_SMARSA_BIRTHDAYSPACINGS {
    "smarsa_BirthdaySpacings" ,
    {"N","n","r","d","t","p"} ,
    {"N","n","r","d","t","p"} ,
    {
        "Collision"
    }
};
const tTestU01Data TestConstants::TESTU01_SNPAIR_CLOSEPAIRS {
    "snpair_ClosePairs" ,
    {"N","n","r","t","p","m"} ,
    {"N","n","r","t","p","m","Torus"} ,
    {
        "AD (NP)" ,
        "A2 (m-NP)" ,
        "A2 (mNP1)" ,
        "Jumps Y (mN)" ,
        "AD (mNP2)"
    }
};
const tTestU01Data TestConstants::TESTU01_SNPAIR_CLOSEPAIRS_BIGT {
    "snpair_ClosePairs" ,
    {"N","n","r","t","p","m"} ,
    {"N","n","r","t","p","m","Torus"} ,
    {
        "AD (NP)" ,
        "A2 (m-NP)" ,
        "A2 (mNP1)" ,
        "Jumps Y (mN)" ,
        "AD (mNP2)" ,
        "AD (mNP2-S)"
    }
};
const tTestU01Data TestConstants::TESTU01_SNPAIR_CLOSEPAIRSBITMATCH {
    "snpair_ClosePairsBitMatch" ,
    {"N","n","r","t"} ,
    {"N","n","r","t"} ,
    {
        "Bit distance"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_COLLISION {
    "sknuth_Collision" ,
    {"N","n","r","d","t"} ,
    {"N","n","r","d","t","Sparse"} ,
    {
        "Collision"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_SIMPPOKER {
    "sknuth_SimpPoker" ,
    {"N","n","r","d","k"} ,
    {"N","n","r","d","k"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_COUPONCOLLECTOR {
    "sknuth_CouponCollector" ,
    {"N","n","r","d"} ,
    {"N","n","r","d"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_GAP {
    "sknuth_Gap" ,
    {"N","n","r","Alpha","Beta"} ,
    {"N","n","r","Alpha","Beta"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_RUN {
    "sknuth_Run" ,
    {"N","n","r","Up"} ,
    {"N","n","r","Up"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_PERMUTATION {
    "sknuth_Permutation" ,
    {"N","n","r","t"} ,
    {"N","n","r","t","Sparse"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_COLLISIONPERMUT {
    "sknuth_CollisionPermut" ,
    {"N","n","r","t"} ,
    {"N","n","r","t","Sparse"} ,
    {
        "Collision"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_MAXOFT {
    "sknuth_MaxOft" ,
    {"N","n","r","d","t"} ,
    {"N","n","r","d","t"} ,
    {
        "Chi-square" ,
        "Anderson-Darling"
    }
};
const tTestU01Data TestConstants::TESTU01_SKNUTH_MAXOFT_BIGN {
    "sknuth_MaxOft" ,
    {"N","n","r","d","t"} ,
    {"N","n","r","d","t"} ,
    {
        "Chi-square - KS (D+)" ,
        "Chi-square - KS (D-)" ,
        "Chi-square - AD (A2)" ,
        "Observations sums" ,
        "Anderson-Darling - KS (D+)" ,
        "Anderson-Darling - KS (D-)",
        "Anderson-Darling - AD (A2)"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_SAMPLEPROD {
    "svaria_SampleProd" ,
    {"N","n","r","t"} ,
    {"N","n","r","t"} ,
    {
        "Anderson-Darling"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_SAMPLEMEAN {
    "svaria_SampleMean" ,
    {"N","n","r"} ,
    {"N","n","r"} ,
    {
        "Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_SAMPLECORR {
    "svaria_SampleCorr" ,
    {"N","n","r","k"} ,
    {"N","n","r","k"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_APPEARANCESPACINGS {
    "svaria_AppearanceSpacings" ,
    {"N","Q","K","r","s","L"} ,
    {"N","Q","K","r","s","L"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_WEIGHTDISTRIB {
    "svaria_WeightDistrib" ,
    {"N","n","r","k","Alpha","Beta"} ,
    {"N","n","r","k","Alpha","Beta"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SVARIA_SUMCOLLECTOR {
    "svaria_SumCollector" ,
    {"N","n","r","g"} ,
    {"N","n","r","g"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SMARSA_MATRIXRANK {
    "smarsa_MatrixRank" ,
    {"N","n","r","s","L","k"} ,
    {"N","n","r","s","L","k"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SMARSA_SAVIR2 {
    "smarsa_Savir2" ,
    {"N","n","r","m","t"} ,
    {"N","n","r","m","t"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SMARSA_GDC {
    "smarsa_GCD" ,
    {"N","n","r","s"} ,
    {"N","n","r","s"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SWALK_RANDOMWALK1 {
    "swalk_RandomWalk1" ,
    {"N","n","r","s","L0","L1"} ,
    {"N","n","r","s","L0","L1"} ,
    {
        "Chi-square(H)" ,
        "Chi-square(M)" ,
        "Chi-square(J)" ,
        "Chi-square(R)" ,
        "Chi-square(C)"
    }
};
const tTestU01Data TestConstants::TESTU01_SCOMP_LINEARCOMP {
    "scomp_LinearComp" ,
    {"N","n","r","s"} ,
    {"N","n","r","s"} ,
    {
        "Chi-square" ,
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SCOMP_LEMPELZIV {
    "scomp_LempelZiv" ,
    {"N","k","r","s"} ,
    {"N","n","r","s","k"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SCOMP_LEMPELZIV_BIGN {
    "scomp_LempelZiv" ,
    {"N","k","r","s"} ,
    {"N","n","r","s","k"} ,
    {
        "Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling" ,
        "Normal" ,
        "Sample variance"
    }
};
const tTestU01Data TestConstants::TESTU01_SSPECRTAL_FOURIER1 {
    "sspectral_Fourier1" ,
    {"N","k","r","s"} ,
    {"N","n","r","s","k"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SSPECRTAL_FOURIER3 {
    "sspectral_Fourier3" ,
    {"N","k","r","s"} ,
    {"N","n","r","s","k"} ,
    {
        "Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_LONGESTHEADRUN {
    "sstring_LongestHeadRun" ,
    {"N","n","r","s","L"} ,
    {"N","n","r","s","L"} ,
    {
        "Chi-square" ,
        "Global longest run of 1"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_PERIODSINSTRINGS {
    "sstring_PeriodsInStrings" ,
    {"N","n","r","s"} ,
    {"N","n","r","s"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_HAMMINGWEIGHT {
    "sstring_HammingWeight" ,
    {"N","n","r","s","L"} ,
    {"N","n","r","s","L"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_HAMMINGWEIGHT2 {
    "sstring_HammingWeight2" ,
    {"N","n","r","s","L"} ,
    {"N","n","r","s","L"} ,
    {
        "Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling" , "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_HAMMINGCORR {
    "sstring_HammingCorr" ,
    {"N","n","r","s","L"} ,
    {"N","n","r","s","L"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_HAMMINGINDEP {
    "sstring_HammingIndep" ,
    {"N","n","r","s","L","d"} ,
    {"N","n","r","s","L","d"} ,
    {
        "Chi-square"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_RUN {
    "sstring_Run" ,
    {"N","n","r","s"} ,
    {"N","n","r","s"} ,
    {
        "Chi-square" ,
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_RUN_RABBIT {
    "sstring_Run" ,
    {"N","n","r","s"} ,
    {"N","n","r","s"} ,
    {
        "Kolmogorov-Smirnov (D+) (runs)" ,
        "Kolmogorov-Smirnov (D-) (runs)" ,
        "Anderson-Darling (A2) (runs)" ,
        "Chi-square (runs)" ,
        "Kolmogorov-Smirnov (D+) (bits)" ,
        "Kolmogorov-Smirnov (D-) (bits)" ,
        "Anderson-Darling (A2) (bits)" ,
        "Normal (bits)" ,
        "Sample variance (bits)"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_AUTOCOR {
    "sstring_AutoCor" ,
    {"N","n","r","s","d"} ,
    {"N","n","r","s","d"} ,
    {
        "Normal"
    }
};
const tTestU01Data TestConstants::TESTU01_SSTRING_AUTOCOR_BIGN {
    "sstring_AutoCor" ,
    {"N","n","r","s","d"} ,
    {"N","n","r","s","d"} ,
    {
        "Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling" ,
        "Normal" ,
        "Sample variance"
    }
};
const tTestU01Data TestConstants::TESTU01_SMULTIN_MULTINOMIALBITSOVER {
    "smultin_MultinomialBitsOver" ,
    {"N","n","r","s","L","Sparse"} ,
    {"N","n","r","s","L","Sparse"} ,
    {
        "Collision"
    }
};
const tTestU01Data TestConstants::TESTU01_SMULTIN_MULTBITSOVER_BIGN {
    "smultin_MultinomialBitsOver" ,
    {"N","n","r","s","L","Sparse"} ,
    {"N","n","r","s","L","Sparse"} ,
    {"Kolmogorov-Smirnov (D+)" ,
        "Kolmogorov-Smirnov (D-)" ,
        "Anderson-Darling (A2)" ,
        "Std empirical mean" ,
        "Std empirical corr"
    }
};

const std::map<int , tNistStsData> TestConstants::nistStsTests {
    { 1, TestConstants::NISTSTS_FREQ},
    { 2, TestConstants::NISTSTS_BLOCKFREQ},
    { 3, TestConstants::NISTSTS_CUSUMS},
    { 4, TestConstants::NISTSTS_RUNS},
    { 5, TestConstants::NISTSTS_LONGESTRUN},
    { 6, TestConstants::NISTSTS_RANK},
    { 7, TestConstants::NISTSTS_FFT},
    { 8, TestConstants::NISTSTS_NONOVERTEMP},
    { 9, TestConstants::NISTSTS_OVERTEMP},
    {10, TestConstants::NISTSTS_UNIVERSAL},
    {11, TestConstants::NISTSTS_APPROXENT},
    {12, TestConstants::NISTSTS_RNDEXCURSIONS},
    {13, TestConstants::NISTSTS_RNDEXCURSIONSVAR},
    {14, TestConstants::NISTSTS_SERIAL},
    {15, TestConstants::NISTSTS_LINEARCOMPLEXITY}
};

const std::map<int , tDieharderData> TestConstants::dieharderTests = {
    {  0, TestConstants::DIEHARDER_BIRTHDAYS},
    {  1, TestConstants::DIEHARDER_OPERM5},
    {  2, TestConstants::DIEHARDER_BINARYRANK1},
    {  3, TestConstants::DIEHARDER_BINARYRANK2},
    {  4, TestConstants::DIEHARDER_BITSTREAM},
    {  5, TestConstants::DIEHARDER_OPSO},
    {  6, TestConstants::DIEHARDER_OQSO},
    {  7, TestConstants::DIEHARDER_DNA},
    {  8, TestConstants::DIEHARDER_COUNT1SBYTE},
    {  9, TestConstants::DIEHARDER_COUNT1SSTREAM},
    { 10, TestConstants::DIEHARDER_PARKING},
    { 11, TestConstants::DIEHARDER_MINDISTANCECIRCLE},
    { 12, TestConstants::DIEHARDER_MINDISTANCESPHERE},
    { 13, TestConstants::DIEHARDER_SQUEEZE},
    { 14, TestConstants::DIEHARDER_SUMS},
    { 15, TestConstants::DIEHARDER_RUNS},
    { 16, TestConstants::DIEHARDER_CRAPS},
    { 17, TestConstants::DIEHARDER_GCD},
    {100, TestConstants::DIEHARDER_MONOBIT},
    {101, TestConstants::DIEHARDER_STSRUNS},
    {102, TestConstants::DIEHARDER_SERIAL},
    {200, TestConstants::DIEHARDER_BITDIST},
    {201, TestConstants::DIEHARDER_MINDISTANCE},
    {202, TestConstants::DIEHARDER_PERMUTATIONS},
    {203, TestConstants::DIEHARDER_LAGGED},
    {204, TestConstants::DIEHARDER_KS},
    {205, TestConstants::DIEHARDER_BYTEDIST},
    {206, TestConstants::DIEHARDER_DABDCT},
    {207, TestConstants::DIEHARDER_DABFILLTREE},
    {208, TestConstants::DIEHARDER_DABFILLTREE2},
    {209, TestConstants::DIEHARDER_DABMONOBIT}
};

const std::map<IndexRange , tTestU01Data> TestConstants::tu01testsSmallCrush = {
    { IndexRange(1)  , TestConstants::TESTU01_SMARSA_BIRTHDAYSPACINGS},
    { IndexRange(2)  , TestConstants::TESTU01_SKNUTH_COLLISION},
    { IndexRange(3)  , TestConstants::TESTU01_SKNUTH_GAP},
    { IndexRange(4)  , TestConstants::TESTU01_SKNUTH_SIMPPOKER},
    { IndexRange(5)  , TestConstants::TESTU01_SKNUTH_COUPONCOLLECTOR},
    { IndexRange(6)  , TestConstants::TESTU01_SKNUTH_MAXOFT},
    { IndexRange(7)  , TestConstants::TESTU01_SVARIA_WEIGHTDISTRIB},
    { IndexRange(8)  , TestConstants::TESTU01_SMARSA_MATRIXRANK},
    { IndexRange(9)  , TestConstants::TESTU01_SSTRING_HAMMINGINDEP},
    { IndexRange(10) , TestConstants::TESTU01_SWALK_RANDOMWALK1}
};

const std::map<IndexRange , tTestU01Data> TestConstants::tu01testsCrush = {
    { IndexRange(1,2)   , TestConstants::TESTU01_SMARSA_SERIALOVER},
    { IndexRange(3,10)  , TestConstants::TESTU01_SMARSA_COLLISIONOVER},
    { IndexRange(11,17) , TestConstants::TESTU01_SMARSA_BIRTHDAYSPACINGS},
    { IndexRange(18,18) , TestConstants::TESTU01_SNPAIR_CLOSEPAIRS},
    { IndexRange(19,20) , TestConstants::TESTU01_SNPAIR_CLOSEPAIRS_BIGT},
    { IndexRange(21,22) , TestConstants::TESTU01_SNPAIR_CLOSEPAIRSBITMATCH},
    { IndexRange(23,26) , TestConstants::TESTU01_SKNUTH_SIMPPOKER},
    { IndexRange(27,30) , TestConstants::TESTU01_SKNUTH_COUPONCOLLECTOR},
    { IndexRange(31,34) , TestConstants::TESTU01_SKNUTH_GAP},
    { IndexRange(35,36) , TestConstants::TESTU01_SKNUTH_RUN},
    { IndexRange(37,38) , TestConstants::TESTU01_SKNUTH_PERMUTATION},
    { IndexRange(39,40) , TestConstants::TESTU01_SKNUTH_COLLISIONPERMUT},
    { IndexRange(41,42) , TestConstants::TESTU01_SKNUTH_MAXOFT_BIGN},
    { IndexRange(43,44) , TestConstants::TESTU01_SKNUTH_MAXOFT},
    { IndexRange(45,46) , TestConstants::TESTU01_SVARIA_SAMPLEPROD},
    { IndexRange(47,47) , TestConstants::TESTU01_SVARIA_SAMPLEMEAN},
    { IndexRange(48,48) , TestConstants::TESTU01_SVARIA_SAMPLECORR},
    { IndexRange(49,50) , TestConstants::TESTU01_SVARIA_APPEARANCESPACINGS},
    { IndexRange(51,54) , TestConstants::TESTU01_SVARIA_WEIGHTDISTRIB},
    { IndexRange(55,55) , TestConstants::TESTU01_SVARIA_SUMCOLLECTOR},
    { IndexRange(56,61) , TestConstants::TESTU01_SMARSA_MATRIXRANK},
    { IndexRange(62,62) , TestConstants::TESTU01_SMARSA_SAVIR2},
    { IndexRange(63,64) , TestConstants::TESTU01_SMARSA_GDC},
    { IndexRange(65,70) , TestConstants::TESTU01_SWALK_RANDOMWALK1},
    { IndexRange(71,72) , TestConstants::TESTU01_SCOMP_LINEARCOMP},
    { IndexRange(73,73) , TestConstants::TESTU01_SCOMP_LEMPELZIV_BIGN},
    { IndexRange(74,75) , TestConstants::TESTU01_SSPECRTAL_FOURIER3},
    { IndexRange(76,77) , TestConstants::TESTU01_SSTRING_LONGESTHEADRUN},
    { IndexRange(78,79) , TestConstants::TESTU01_SSTRING_PERIODSINSTRINGS},
    { IndexRange(80,81) , TestConstants::TESTU01_SSTRING_HAMMINGWEIGHT2},
    { IndexRange(82,84) , TestConstants::TESTU01_SSTRING_HAMMINGCORR},
    { IndexRange(85,90) , TestConstants::TESTU01_SSTRING_HAMMINGINDEP},
    { IndexRange(91,92) , TestConstants::TESTU01_SSTRING_RUN},
    { IndexRange(93,96) , TestConstants::TESTU01_SSTRING_AUTOCOR_BIGN}
};

const std::map<IndexRange , tTestU01Data> TestConstants::tu01testsBigCrush = {
    { IndexRange(1,2)     , TestConstants::TESTU01_SMARSA_SERIALOVER},
    { IndexRange(3,12)    , TestConstants::TESTU01_SMARSA_COLLISIONOVER},
    { IndexRange(13,21)   , TestConstants::TESTU01_SMARSA_BIRTHDAYSPACINGS},
    { IndexRange(22,25)   , TestConstants::TESTU01_SNPAIR_CLOSEPAIRS},
    { IndexRange(26,29)   , TestConstants::TESTU01_SKNUTH_SIMPPOKER},
    { IndexRange(30,33)   , TestConstants::TESTU01_SKNUTH_COUPONCOLLECTOR},
    { IndexRange(34,37)   , TestConstants::TESTU01_SKNUTH_GAP},
    { IndexRange(38,39)   , TestConstants::TESTU01_SKNUTH_RUN},
    { IndexRange(40,43)   , TestConstants::TESTU01_SKNUTH_PERMUTATION},
    { IndexRange(44,45)   , TestConstants::TESTU01_SKNUTH_COLLISIONPERMUT},
    { IndexRange(46,49)   , TestConstants::TESTU01_SKNUTH_MAXOFT_BIGN},
    { IndexRange(50,52)   , TestConstants::TESTU01_SVARIA_SAMPLEPROD},
    { IndexRange(53,54)   , TestConstants::TESTU01_SVARIA_SAMPLEMEAN},
    { IndexRange(55,56)   , TestConstants::TESTU01_SVARIA_SAMPLECORR},
    { IndexRange(57,58)   , TestConstants::TESTU01_SVARIA_APPEARANCESPACINGS},
    { IndexRange(59,64)   , TestConstants::TESTU01_SVARIA_WEIGHTDISTRIB},
    { IndexRange(65,65)   , TestConstants::TESTU01_SVARIA_SUMCOLLECTOR},
    { IndexRange(66,71)   , TestConstants::TESTU01_SMARSA_MATRIXRANK},
    { IndexRange(72,72)   , TestConstants::TESTU01_SMARSA_SAVIR2},
    { IndexRange(73,73)   , TestConstants::TESTU01_SMARSA_GDC},
    { IndexRange(74,79)   , TestConstants::TESTU01_SWALK_RANDOMWALK1},
    { IndexRange(80,81)   , TestConstants::TESTU01_SCOMP_LINEARCOMP},
    { IndexRange(82,83)   , TestConstants::TESTU01_SCOMP_LEMPELZIV_BIGN},
    { IndexRange(84,85)   , TestConstants::TESTU01_SSPECRTAL_FOURIER3},
    { IndexRange(86,87)   , TestConstants::TESTU01_SSTRING_LONGESTHEADRUN},
    { IndexRange(88,89)   , TestConstants::TESTU01_SSTRING_PERIODSINSTRINGS},
    { IndexRange(90,91)   , TestConstants::TESTU01_SSTRING_HAMMINGWEIGHT2},
    { IndexRange(92,94)   , TestConstants::TESTU01_SSTRING_HAMMINGCORR},
    { IndexRange(95,100)  , TestConstants::TESTU01_SSTRING_HAMMINGINDEP},
    { IndexRange(101,102) , TestConstants::TESTU01_SSTRING_RUN},
    { IndexRange(103,106) , TestConstants::TESTU01_SSTRING_AUTOCOR_BIGN}
};

const std::map<IndexRange , tTestU01Data> TestConstants::tu01testsRabbit = {
    { IndexRange(1,1)   , TestConstants::TESTU01_SMULTIN_MULTINOMIALBITSOVER},
    { IndexRange(2,3)   , TestConstants::TESTU01_SNPAIR_CLOSEPAIRSBITMATCH},
    { IndexRange(4,4)   , TestConstants::TESTU01_SVARIA_APPEARANCESPACINGS},
    { IndexRange(5,5)   , TestConstants::TESTU01_SCOMP_LINEARCOMP},
    { IndexRange(6,6)   , TestConstants::TESTU01_SCOMP_LEMPELZIV},
    { IndexRange(7,7)   , TestConstants::TESTU01_SSPECRTAL_FOURIER1},
    { IndexRange(8,8)   , TestConstants::TESTU01_SSPECRTAL_FOURIER3},
    { IndexRange(9,9)   , TestConstants::TESTU01_SSTRING_LONGESTHEADRUN},
    { IndexRange(10,10) , TestConstants::TESTU01_SSTRING_PERIODSINSTRINGS},
    { IndexRange(11,11) , TestConstants::TESTU01_SSTRING_HAMMINGWEIGHT},
    { IndexRange(12,14) , TestConstants::TESTU01_SSTRING_HAMMINGCORR},
    { IndexRange(15,17) , TestConstants::TESTU01_SSTRING_HAMMINGINDEP},
    { IndexRange(18,19) , TestConstants::TESTU01_SSTRING_AUTOCOR_BIGN},
    { IndexRange(20,20) , TestConstants::TESTU01_SSTRING_RUN_RABBIT},
    { IndexRange(21,23) , TestConstants::TESTU01_SMARSA_MATRIXRANK},
    { IndexRange(24,26) , TestConstants::TESTU01_SWALK_RANDOMWALK1}
};

const std::map<IndexRange , tTestU01Data> TestConstants::tu01testsAlphabit = {
    { IndexRange(1,4) , TestConstants::TESTU01_SMULTIN_MULTBITSOVER_BIGN},
    { IndexRange(5,6) , TestConstants::TESTU01_SSTRING_HAMMINGINDEP},
    { IndexRange(7,7) , TestConstants::TESTU01_SSTRING_HAMMINGCORR},
    { IndexRange(8,9) , TestConstants::TESTU01_SWALK_RANDOMWALK1}
};

std::string TestConstants::getTestLogicName(const BatteryArg & battery,
                                            int testIndex) {
    try {
        switch (battery.getBatteryId()) {
            case Constants::BatteryID::NIST_STS:
                return std::get<0>(nistStsTests.at(testIndex));
            case Constants::BatteryID::DIEHARDER:
                return std::get<0>(dieharderTests.at(testIndex));
            case Constants::BatteryID::TU01_SMALLCRUSH:
                return std::get<0>(tu01testsSmallCrush.at(testIndex));
            case Constants::BatteryID::TU01_CRUSH:
                return std::get<0>(tu01testsCrush.at(testIndex));
            case Constants::BatteryID::TU01_BIGCRUSH:
                return std::get<0>(tu01testsBigCrush.at(testIndex));
            case Constants::BatteryID::TU01_RABBIT:
                return std::get<0>(tu01testsRabbit.at(testIndex));
            case Constants::BatteryID::TU01_ALPHABIT:
                return std::get<0>(tu01testsAlphabit.at(testIndex));
            case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
                /* Block Alphabit has same tests as Alphabit. */
                return std::get<0>(tu01testsAlphabit.at(testIndex));
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
        }
    } catch (std::out_of_range) {
        throw RTTException(battery.getName() ,
                           Strings::ERR_INVALID_TEST_CONST + Utils::itostr(testIndex));
    }
}

tNistStsData TestConstants::getNistStsTestData(const BatteryArg & battery,
                                               int testIndex) {
    try {
        switch(battery.getBatteryId()) {
            case Constants::BatteryID::NIST_STS :
                return nistStsTests.at(testIndex);
            default:
                raiseBugException(Strings::ERR_INVALID_BATTERY);
        }
    } catch (std::out_of_range) {
        throw RTTException(battery.getName() ,
                           Strings::ERR_INVALID_TEST_CONST + Utils::itostr(testIndex));
    }
}

tDieharderData TestConstants::getDieharderTestData(const BatteryArg & battery,
                                                   int testIndex) {
    try {
        switch(battery.getBatteryId()) {
            case Constants::BatteryID::DIEHARDER :
                return dieharderTests.at(testIndex);
            default:
                raiseBugException(Strings::ERR_INVALID_BATTERY);
        }
    } catch (std::out_of_range) {
        throw RTTException(battery.getName() ,
                           Strings::ERR_INVALID_TEST_CONST + Utils::itostr(testIndex));
    }
}

tTestU01Data TestConstants::getTu01TestData(const BatteryArg & battery,
                                            int testIndex) {
    try {
        switch(battery.getBatteryId()) {
            case Constants::BatteryID::TU01_SMALLCRUSH:
                return tu01testsSmallCrush.at(testIndex);
            case Constants::BatteryID::TU01_CRUSH:
                return tu01testsCrush.at(testIndex);
            case Constants::BatteryID::TU01_BIGCRUSH:
                return tu01testsBigCrush.at(testIndex);
            case Constants::BatteryID::TU01_RABBIT:
                return tu01testsRabbit.at(testIndex);
            case Constants::BatteryID::TU01_ALPHABIT:
                return tu01testsAlphabit.at(testIndex);
            case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
                /* Block Alphabit has same tests as Alphabit. */
                return tu01testsAlphabit.at(testIndex);
            default:
                raiseBugException(Strings::ERR_INVALID_BATTERY);
        }
    } catch (std::out_of_range) {
        throw RTTException(battery.getName() ,
                           Strings::ERR_INVALID_TEST_CONST + Utils::itostr(testIndex));
    }
}

} // namespace batteries
} // namespace rtt
