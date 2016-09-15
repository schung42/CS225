TESTOBJS = 
CFLAGS += -std=c++11
EWS_MODERN_CXX = /software/gcc-4.8.2/bin/g++
ifneq ($(wildcard $(EWS_MODERN_CXX)),)
    CXX = $(EWS_MODERN_CXX) 
	LIBS = -static-libstdc++
endif
include Makefile.proxy
