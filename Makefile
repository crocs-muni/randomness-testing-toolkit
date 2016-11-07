CC=gcc
CXX=g++
CXXFLAGS = \
	-std=c++14 -I. \
	-L/usr/lib \
	-lmysqlcppconn \
	-lpthread -O3

# === Header files ===
# === Source files must be in same dir as corresponding header ===
DEPS = \
	libs/cephes/cephes.h \
	rtt/constants.h \
	rtt/utils.h \
	rtt/version.h \
	rtt/batteries/dieharder/battery-dh.h \
	rtt/batteries/dieharder/test-dh.h \
	rtt/batteries/niststs/battery-sts.h \
	rtt/batteries/niststs/test-sts.h \
	rtt/batteries/dieharder/setting-dh.h \
	rtt/batteries/testu01/battery-tu01.h \
	rtt/batteries/testu01/test-tu01.h \
	rtt/batteries/ibattery-batt.h \
	rtt/batteries/itest-batt.h \
	rtt/batteries/testrunner-batt.h \
	rtt/rttexception.h \
	rtt/clioptions.h \
	rtt/toolkitsettings.h \
	rtt/bugexception.h \
	rtt/batteries/configuration-batt.h \
	rtt/batteries/testconstants.h \
	rtt/globalcontainer.h \
	libs/easylogging/easylogging++.h \
	rtt/logger.h \
	rtt/strings.h \
	rtt/batteries/batteryoutput.h \
	libs/moderncppjson/json.hpp \
	rtt/storage/istorage.h \
	rtt/storage/filestorage.h \
	rtt/batteries/ivariant-batt.h \
	rtt/batteries/niststs/variant-sts.h \
	rtt/batteries/dieharder/variant-dh.h \
	rtt/batteries/testu01/variant-tu01.h \
	rtt/batteries/result/pvalueset-res.h \
	rtt/batteries/result/subtestresult-res.h \
	rtt/batteries/result/variantresult-res.h \
	rtt/storage/mysqlstorage.h \
	rtt/batteries/itestresult-batt.h \
	rtt/batteries/testu01/testresult-tu01.h \
	rtt/batteries/niststs/testresult-sts.h \
	rtt/batteries/dieharder/testresult-dh.h \
	rtt/batteries/result/statistic-res.h

# === Target object files ===
OBJ = \
	cephes.o \
	constants.o \
	main.o \
	utils.o \
	battery-dh.o \
	test-dh.o \
	battery-sts.o \
	test-sts.o \
	setting-dh.o \
	battery-tu01.o \
	test-tu01.o \
	ibattery-batt.o \
	itest-batt.o \
	testrunner-batt.o \
	clioptions.o \
	toolkitsettings.o \
	configuration-batt.o \
	testconstants.o \
	globalcontainer.o \
	logger.o \
	strings.o \
	batteryoutput.o \
	istorage.o \
	filestorage.o \
	ivariant-batt.o \
	variant-sts.o \
	variant-dh.o \
	variant-tu01.o \
	subtestresult-res.o \
	variantresult-res.o \
	mysqlstorage.o \
	itestresult-batt.o \
	testresult-dh.o \
	testresult-sts.o \
	testresult-tu01.o \
	statistic-res.o

# === All paths inside project directory ===
# === Ugly but works ===
VPATH = \
	rtt:\
	rtt/batteries:\
	rtt/batteries/dieharder:\
	rtt/batteries/niststs:\
	rtt/batteries/testu01:\
	rtt/batteries/result:\
	rtt/storage:\
	libs:\
	libs/cephes:\
	libs/easylogging:\
	libs/moderncppjson

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	
randomness-testing-toolkit: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o 
