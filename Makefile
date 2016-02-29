CC=gcc
CXX=g++
CFLAGS=-std=c++11 -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -I. -I./libs/tinyXML -O2

# === Header files ===
# === Source files must be in same dir as corresponding header ===
DEPS = \
	libs/tinyXML/tinystr.h \
	libs/tinyXML/tinyxml.cpp \
    libs/tinyXML/tinyxmlerror.cpp \
    libs/tinyXML/tinyxmlparser.cpp \
    libs/tinyXML/xmlproc.cpp \
    rtt/constants.cpp \
    rtt/main.cpp \
    rtt/options.cpp \
    rtt/utils.cpp \
    rtt/batteries/dieharder/battery-dh.cpp \
    rtt/batteries/dieharder/test-dh.cpp \
    rtt/batteries/niststs/battery-sts.cpp \
    rtt/batteries/niststs/test-sts.cpp \
    rtt/batteries/dieharder/setting-dh.cpp \
    rtt/batteries/testu01/battery-tu01.cpp \
    rtt/batteries/testu01/test-tu01.cpp \
    rtt/output/storage-file.cpp \
    libs/cephes/cephes.cpp \
    rtt/batteries/ibattery-batt.cpp \
    rtt/batteries/itest-batt.cpp \
    rtt/batteries/testrunner-batt.cpp

# === Target object files ===
OBJ = \
	tinystr.o \
	tinyxml.o \
	tinyxmlerror.o \
	tinyxmlparser.o \
	xmlproc.o \
	constants.o \
	main.o \
	options.o \
	utils.o \
	battery-dh.o \
	test-dh.o \
	battery-sts.o \
	test-sts.o \
	setting-dh.o \
	battery-tu01.o \
	test-tu01.o \
	storage-file.o \
	cephes.o \
	ibattery-batt.o \
	itest-batt.o \
	testrunner-batt.o

# === All paths inside project directory ===
# === Ugly but works ===
VPATH = \
	libs:\
	libs/cephes:\
	libs/tinyXML:\
	rtt:\
	rtt/batteries:\
	rtt/batteries/dieharder:\
	rtt/batteries/niststs:\
	rtt/batteries/testu01:\
	rtt/output

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
randomness-testing-toolkit: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o 
