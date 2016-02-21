# (C)2004-2010 Metamod:Source Development Team
# Makefile written by David "BAILOPAN" Anderson

###########################################
### EDIT THESE PATHS FOR YOUR OWN SETUP ###
###########################################

MMSOURCE = ..

#####################################
### EDIT BELOW FOR OTHER PROJECTS ###
#####################################

PROJECT = autogain_mm
OBJECTS = autogain_mm.cpp voice.cpp voice_silk.cpp voice_speex.cpp asm/asm.c CDetour/detours.cpp util/MemoryUtils.cpp

##############################################
### CONFIGURE ANY OTHER FLAGS/OPTIONS HERE ###
##############################################

OPT_FLAGS = -O3 -funroll-loops -s -pipe
GCC4_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden
DEBUG_FLAGS = -g -ggdb3 -D_DEBUG
CPP = gcc

##########################
### SDK CONFIGURATIONS ###
##########################

METAMOD = $(MMSOURCE)/core

OS := $(shell uname -s)

ifeq "$(OS)" "Darwin"
	LIB_EXT = dylib
else
	LIB_EXT = so
endif

# if ENGINE is original or OB
LIB_PREFIX = lib
LIB_SUFFIX = .$(LIB_EXT)

CFLAGS += -DMETA_NO_HL2SDK

LINK += silk/libSKP_SILK_SDK.a speex/libspeex.a -static-libgcc

INCLUDE += -I. -I.. -I$(METAMOD) -I$(METAMOD)/sourcehook -I./silk -I./speex -I./util

################################################
### DO NOT EDIT BELOW HERE FOR MOST PROJECTS ###
################################################

BINARY = $(PROJECT).$(LIB_EXT)

ifeq "$(DEBUG)" "true"
	BIN_DIR = Debug
	CFLAGS += $(DEBUG_FLAGS)
else
	BIN_DIR = Release
	CFLAGS += $(OPT_FLAGS)
endif

GCC_VERSION := $(shell $(CPP) -dumpversion >&1 | cut -b1)

ifeq "$(OS)" "Darwin"
	LIB_EXT = dylib
	CFLAGS += -isysroot /Developer/SDKs/MacOSX10.5.sdk
	LINK += -dynamiclib -lstdc++ -mmacosx-version-min=10.5
else
	LIB_EXT = so
	CFLAGS += -D_LINUX
	LINK += -shared
endif

CFLAGS += -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp \
	-Dstrnicmp=strncasecmp -D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca \
	-Dstrcmpi=strcasecmp -Wall -Wno-non-virtual-dtor -w -fPIC -fno-exceptions \
	-fno-rtti -msse -m32 -fno-strict-aliasing

ifeq "$(GCC_VERSION)" "4"
	CFLAGS += $(GCC4_FLAGS)
endif

OBJ_BIN := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all: check
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/CDetour
	mkdir -p $(BIN_DIR)/util
	$(MAKE) -f Makefile autogain_mm
	
check:
	

autogain_mm: check $(OBJ_BIN)
	$(CPP) $(INCLUDE) -m32 $(OBJ_BIN) $(LINK) -ldl -lm -o $(BIN_DIR)/$(BINARY)

default: all

clean: check
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/CDetour/*.o
	rm -rf $(BIN_DIR)/util/*.o
	rm -rf $(BIN_DIR)/$(BINARY)

