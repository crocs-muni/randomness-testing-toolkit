#include "rtt/batteries/dieharder/battery-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

const std::string Battery::XPATH_LOG_DIRECTORY = "TOOLKIT_SETTINGS/LOGGER/DIEHARDER_DIR";
const std::string Battery::XPATH_DEFAULT_TESTS = "DIEHARDER_SETTINGS/DEFAULT_TESTS";

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());
    battery->creationTime = Utils::getRawTime();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    /* Getting path to log file */
    battery->logFilePath = std::move(
                createLogFilePath(
                    battery->creationTime,
                    getXMLElementValue(cfgRoot , XPATH_LOG_DIRECTORY),
                    options.getBinFilePath()));
    /* Creating storage for results */
    battery->storage = output::InterfaceFactory::createOutput(cfgRoot ,
                                                              options ,
                                                              battery->creationTime);

    /* Getting constants of tests to be executed */
    std::vector<int> testConsts = options.getTestConsts();
    if(testConsts.empty()) /* Read them from config if no tests were entered via CLI */
        testConsts = parseIntValues(getXMLElementValue(cfgRoot , XPATH_DEFAULT_TESTS));
    if(testConsts.empty())
        throw std::runtime_error("no tests for execution were set in options "
                                 "and in config file");

    for(int i : testConsts) {
        Test test = Test::getInstance(i , options , cfgRoot);
        battery->tests.push_back(std::move(test));
    }

    delete cfgRoot;
    return battery;
}

void Battery::runTests() {
    for(auto & i : tests)
        i.execute();

    executed = true;
}

void Battery::processStoredResults() {
    if(!executed)
        throw std::runtime_error("can't process results before execution of battery");

    std::cout << "Storing log and results." << std::endl;

    /* Log storage */
    std::string batteryLog;
    for(auto & i : tests)
        i.appendTestLog(batteryLog);

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFilePath));
    Utils::saveStringToFile(logFilePath , batteryLog);

    /* Result storage */
    for(const Test & test : tests) {
        storage->addNewTest(test.getLogicName());
        storage->setTestOptions(test.getSettings());

        std::vector<tTestPvals> results = test.getResults();
        if(results.size() == 1) { /* Single test */
            storage->addStatisticResult("KS" , kstest(results.at(0)) , 8);
            storage->addPValues(results.at(0) , 8);
        } else { /* Multiple subtests */
            for(const auto & result : results) {
                storage->addSubTest();
                storage->addStatisticResult("KS" , kstest(result) , 8);
                storage->addPValues(result , 8);
                storage->finalizeSubTest();
            }
        }
        storage->finalizeTest();
    }
    storage->finalizeReport();
}

/* Following code is taken from DIEHARDER battery. */
/* Used for calculation of final pvalue of test. */
double Battery::kstest(const std::vector<double> & pvalue) {
    int i;
    double y/*,d*/,d1/*,d2*/,dmax;
    double p;
    int count = pvalue.size();

    if (count < 1)
        throw std::runtime_error("can't calculate KS from 0 p-samples");
    if (count == 1) return pvalue[0];

    dmax = 0.0;
    for(i=1;i<=count;i++) {
        y = (double) i/(count+1.0);
        d1 = pvalue[i-1] - y;
        //d2 = fabs(1.0/(count+1.0) - d1);
        d1 = fabs(d1);
        //d = fmax(d1,d2);

        if(d1 > dmax) dmax = d1;
    }
    p = p_ks_new(count,dmax);
    return p;
}

double Battery::p_ks_new(int n, double d) {
  int k,m,i,j,g,eH,eQ;
  double h,s,*H,*Q;
  /*
     * The next fragment is used if ks_test is not 2.  This is faster
     * than going to convergence, but is still really slow compared to
     * switching to the asymptotic form.
     *
     * If you require >7 digit accuracy in the right tail use ks_test = 2
     * but be prepared for occasional long runtimes.
     */
    s=d*d*n;
    if(/*ks_test != 2 && */ ( s>7.24 || ( s>3.76 && n>99 ))) {
      if(n == 10400) printf("Returning the easy way\n");
      return 2.0*exp(-(2.000071+.331/sqrt(n)+1.409/n)*s);
    }

    /*
     * If ks_test = 2, we always execute the following code and work to
     * convergence.
     */
    k=(int)(n*d)+1;
    m=2*k-1;
    h=k-n*d;
    /* printf("p_ks_new:  n = %d  k = %d  m = %d  h = %f\n",n,k,m,h); */
    H=(double*)malloc((m*m)*sizeof(double));
    Q=(double*)malloc((m*m)*sizeof(double));
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        if(i-j+1<0){
          H[i*m+j]=0;
        } else {
          H[i*m+j]=1;
        }
      }
    }

    for(i=0;i<m;i++){
      H[i*m]-=pow(h,i+1);
      H[(m-1)*m+i]-=pow(h,(m-i));
    }

    H[(m-1)*m]+=(2*h-1>0?pow(2*h-1,m):0);
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        if(i-j+1>0){
          for(g=1;g<=i-j+1;g++){
        H[i*m+j]/=g;
      }
        }
      }
    }

    eH=0;
    mPower(H,eH,Q,&eQ,m,n);
    /* printf("p_ks_new eQ = %d\n",eQ); */
    s=Q[(k-1)*m+k-1];
    /* printf("s = %16.8e\n",s); */
    for(i=1;i<=n;i++){
      s=s*i/n;
      /* printf("i = %d: s = %16.8e\n",i,s); */
      if(s<1e-140){
        /* printf("Oops, starting to have underflow problems: s = %16.8e\n",s); */
        s*=1e140;
        eQ-=140;
      }
    }

    /* printf("I'll bet this is it: s = %16.8e  eQ = %d\n",s,eQ); */
    s*=pow(10.,eQ);
    s = 1.0 - s;
    free(H);
    free(Q);
    return s;
}

void Battery::mMultiply(double *A, double *B, double *C, int m) {
    int i,j,k;
    double s;
    for(i=0; i<m; i++){
      for(j=0; j<m; j++){
        s=0.0;
        for(k=0; k<m; k++){
          s+=A[i*m+k]*B[k*m+j];
      C[i*m+j]=s;
        }
      }
    }
}

void Battery::mPower(double *A, int eA, double *V, int *eV, int m, int n) {
    double *B;
      int eB,i,j;

      /*
       * n == 1: first power just returns A.
       */
      if(n == 1){
        for(i=0;i<m*m;i++){
          V[i]=A[i];*eV=eA;
        }
        return;
      }

      /*
       * This is a recursive call.  Either n/2 will equal 1 (and the line
       * above will return and the recursion will terminate) or it won't
       * and we will cumulate the product.
       */
      mPower(A,eA,V,eV,m,n/2);
      /* printf("n = %d  mP eV = %d\n",n/2,*eV); */
      B=(double*)malloc((m*m)*sizeof(double));
      mMultiply(V,V,B,m);
      eB=2*(*eV);
      if(n%2==0){
        for(i=0;i<m*m;i++){
          V[i]=B[i];
        }
        *eV=eB;
        /* printf("n = %d (even) eV = %d\n",n,*eV); */
      } else {
        mMultiply(A,B,V,m);
        *eV=eA+eB;
        /* printf("n = %d (odd) eV = %d\n",n,*eV); */
      }

      /*
       * Rescale as needed to avoid overflow.  Note that we check
       * EVERY element of V to make sure NONE of them exceed the
       * threshold (and if any do, rescale the whole thing).
       */
      for(i=0;i<m*m;i++) {
        if( V[i] > 1.0e140 ) {
          for(j=0;j<m*m;j++) {
            V[j]=V[j]*1.0e-140;
          }
          *eV+=140;
          /* printf("rescale eV = %d\n",*eV); */
        }
      }

      free(B);
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt

