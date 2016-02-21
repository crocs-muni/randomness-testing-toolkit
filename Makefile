CC=gcc
CXX=g++
CFLAGS=-std=c++11 -static -I. -I./libs/tinyXML -O2

# === Header files ===
# === Source files must be in same dir as corresponding header ===
DEPS = \
	libs/tinyXML/tinystr.h \
	libs/tinyXML/tinyxml.h \
	libs/tinyXML/xmlproc.h \
	libs/cephes/cephes.h \
	rtt/constants.h \
	rtt/options.h \
	rtt/utils.h \
	rtt/version.h \
	rtt/batteries/dieharder/battery-dh.h \
	rtt/batteries/dieharder/test-dh.h \
	rtt/batteries/niststs/battery-sts.h \
	rtt/batteries/niststs/test-sts.h \
	rtt/batteries/dieharder/setting-dh.h \
	rtt/batteries/testu01/battery-tu01.h \
	rtt/batteries/testu01/test-tu01.h \
	rtt/batteries/interface-batt.h \
	rtt/batteries/interfacefactory-batt.h \
	rtt/output/interface-out.h \
	rtt/output/interfacefactory-out.h \
	rtt/output/storage-file.h \
	rtt/batteries/testutils-batt.h

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
	interface-batt.o \
	testutils-batt.o

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
