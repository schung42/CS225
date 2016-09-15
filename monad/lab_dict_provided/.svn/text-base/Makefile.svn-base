TESTOBJS = anagram_dict.o fib.o pronounce_dict.o cartalk_puzzle.o game.o
CFLAGS += -std=c++11
EWS_MODERN_CPPC =  /software/gcc-4.8.2/bin/g++
ifneq ($(wildcard $(EWS_MODERN_CPPC)),)
    CXX = $(EWS_MODERN_CPPC) 
	LIBS = -static-libstdc++
endif
include Makefile.proxy
