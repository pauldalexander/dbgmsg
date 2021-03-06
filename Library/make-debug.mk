################################################################################
#
#	Makefile for libdbgmsg.so - Debug version
#
#	Note: The following environment variables should be set prior to
#	invoking this Makefile: 
#
#	${PREFIX}          - Path to installation folder.
#
#	${PKG_CONFIG_PATH} - Search path for .pc files.
#
################################################################################

INTERFACE_DIR=../Interface/include
INC_DIR=include
SRC_DIR=src

LIB_NAME=libdbgmsg

OUT_FILE=$(LIB_NAME).so

INCLUDES=-I$(INTERFACE_DIR) -I$(INC_DIR)

SRC_FILES=$(SRC_DIR)/dbgmsg.c \

CC = gcc

CFLAGS=-g -O0 -Wall -fPIC -std=gnu99
CFLAGS+=$(INCLUDES)

LDFLAGS=-shared -Wl,--as-needed

LIBS=

all: $(OUT_FILE)

$(OUT_FILE): $(SRC_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC_FILES) $(LIBS) -o $(OUT_FILE)
    	
install:
	make-pc-file "dbgmsg" $(PREFIX) "Logging facility for program debugging" 1.0.0
	mkdir -p $(PREFIX)/libd
	cp $(OUT_FILE) $(PREFIX)/libd
	mkdir -p $(PREFIX)/include
	cp $(INTERFACE_DIR)/*.h $(PREFIX)/include
	mkdir -p $(PREFIX)/libd/pkgconfig
	cp $(LIB_NAME).pc $(PREFIX)/libd/pkgconfig
	
clean:
	$(RM) *.o *.so *.pc *.h
	
uninstall:
	$(RM) $(PREFIX)/libd/$(OUT_FILE)
	$(RM) $(PREFIX)/include/dbgmsg.h
	$(RM) $(PREFIX)/libd/pkgconfig/$(LIB_NAME).pc
	
.PHONY: install clean uninstall

