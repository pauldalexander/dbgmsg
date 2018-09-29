################################################################################
#
#	Makefile for test-dbgmsg test program
#
#	Note: The following environment variables should be set prior to
#	invoking this Makefile: 
#
#	${PREFIX}          - Path to installation folder.
#
#	${PKG_CONFIG_PATH} - Search path for .pc files.
#
################################################################################

SRC_DIR=.

PROGRAM_NAME=test-dbgmsg

OUT_FILE=$(PROGRAM_NAME)

SRC_FILES=$(SRC_DIR)/$(PROGRAM_NAME).cpp

CXX=g++

CFLAGS=-g -O0 -Wall -std=gnu++0x

CFLAGS+=$(shell pkg-config --cflags libdbgmsg)

LDFLAGS=-Wl,-L$(PREFIX)/lib

LDFLAGS+=-Wl,--as-needed -Wl,-rpath=$(PREFIX)/lib

LIBS=
LIBS+=$(shell pkg-config --libs libdbgmsg)

$(OUT_FILE): $(SRC_FILES)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(SRC_FILES) $(LIBS) -o $(OUT_FILE)
	
clean:
	$(RM) $(OUT_FILE) *.o
	
install:
	
.PHONY: install clean

