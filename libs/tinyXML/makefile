#****************************************************************************
#
# Makefile for TinyXml.
# Lee Thomason
# www.grinninglizard.com
#
# This is a GNU make (gmake) makefile
#****************************************************************************

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := NO

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

# TINYXML_USE_STL can be used to turn on STL support. NO, then STL
# will not be used. YES will include the STL files.
TINYXML_USE_STL := NO

#****************************************************************************

# unix
RM     := rm -f
# windows-equivalent
# RM     := del /f /q
# leave CC, GCC, LD settings from system
#CC     := gcc
#CXX    := g++
#LD     := g++
AR     := ar rv
RANLIB := ranlib
LIB    := libtinyXML.a

DEBUG_CFLAGS     := -Wall -Wno-format -g -DDEBUG
RELEASE_CFLAGS   := -Wall -Wno-unknown-pragmas -Wno-format -O3

LIBS		 :=

DEBUG_CXXFLAGS   := ${DEBUG_CFLAGS} 
RELEASE_CXXFLAGS := ${RELEASE_CFLAGS}

DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  :=

ifeq (YES, ${DEBUG})
   CFLAGS       := ${DEBUG_CFLAGS}
   CXXFLAGS     := ${DEBUG_CXXFLAGS}
   LDFLAGS      := ${DEBUG_LDFLAGS}
else
   CFLAGS       := ${RELEASE_CFLAGS}
   CXXFLAGS     := ${RELEASE_CXXFLAGS}
   LDFLAGS      := ${RELEASE_LDFLAGS}
endif

ifeq (YES, ${PROFILE})
   CFLAGS   := ${CFLAGS} -pg -O3
   CXXFLAGS := ${CXXFLAGS} -pg -O3
   LDFLAGS  := ${LDFLAGS} -pg
endif

#****************************************************************************
# Preprocessor directives
#****************************************************************************

ifeq (YES, ${TINYXML_USE_STL})
  DEFS := -DTIXML_USE_STL
else
  DEFS :=
endif


CFLAGS   := ${CFLAGS}   ${DEFS}
CXXFLAGS := ${CXXFLAGS} ${DEFS}

HDRS = tinyxml.h tinyxmlparser.h tinyxmlerror.h tinystr.h
SRCS = tinyxml.cpp tinyxmlparser.cpp tinyxmlerror.cpp tinystr.cpp
OBJS = tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o
INC_DIRS= -I..

.SUFFIXES: .cpp
.cpp.o: 
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $<
 
$(LIB): $(OBJS)
	$(PRELINK)
	$(AR) $(LIB) $?
	$(RANLIB) $(LIB)
.cpp.a:;

clean:
	-$(RM) core $(OBJS) $(LIB)

# DO NOT DELETE THIS LINE -- make depend depends on it. 
