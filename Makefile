CC=gcc
CXX=g++
CFLAGS=-std=c++14 -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -I. -O3

# === Header files ===
# === Source files must be in same dir as corresponding header ===
DEPS = \
	libs/cephes/cephes.cpp \
	rtt/constants.cpp \
	rtt/main.cpp \
	rtt/utils.cpp \
	rtt/batteries/dieharder/battery-dh.cpp \
	rtt/batteries/dieharder/test-dh.cpp \
	rtt/batteries/niststs/battery-sts.cpp \
	rtt/batteries/niststs/test-sts.cpp \
	rtt/batteries/dieharder/setting-dh.cpp \
	rtt/batteries/testu01/battery-tu01.cpp \
	rtt/batteries/testu01/test-tu01.cpp \
	rtt/batteries/ibattery-batt.cpp \
	rtt/batteries/itest-batt.cpp \
	rtt/batteries/testrunner-batt.cpp \
	rtt/clioptions.cpp \
	rtt/toolkitsettings.cpp \
	rtt/batteries/configuration-batt.cpp \
	rtt/batteries/testconstants.cpp \
	rtt/globalcontainer.cpp \
	rtt/logger.cpp \
	rtt/strings.cpp \
	rtt/batteries/batteryoutput.cpp \
	rtt/storage/istorage.cpp \
	rtt/storage/filestorage.cpp \
	rtt/batteries/ivariant-batt.cpp \
	rtt/batteries/niststs/variant-sts.cpp \
	rtt/batteries/dieharder/variant-dh.cpp \
	rtt/batteries/testu01/variant-tu01.cpp \
	rtt/batteries/iresult-batt.cpp \
	rtt/batteries/dieharder/result-dh.cpp \
	rtt/batteries/niststs/result-sts.cpp \
	rtt/batteries/result/pvalueset-res.cpp \
	rtt/batteries/result/subtestresult-res.cpp \
	rtt/batteries/result/variantresult-res.cpp \
	rtt/batteries/testu01/result-tu01.cpp

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
	iresult-batt.o \
	result-dh.o \
	result-sts.o \
	pvalueset-res.o \
	subtestresult-res.o \
	variantresult-res.o \
	result-tu01.o

# === All paths inside project directory ===
# === Ugly but works ===
VPATH = \
	libs:\
	libs/cephes:\
	libs/easylogging:\
	libs/moderncppjson:\
	rtt:\
	rtt/batteries:\
	rtt/batteries/dieharder:\
	rtt/batteries/niststs:\
	rtt/batteries/testu01:\
	rtt/batteries/result:\
	rtt/storage

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
randomness-testing-toolkit: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o 
