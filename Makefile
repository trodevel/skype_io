# Makefile for libskype_io
# Copyright (C) 2014 Sergey Kolevatov

###################################################################

VER := 0

MODE ?= debug

###################################################################

GDK_LIB=$(shell pkg-config --libs dbus-1)
GDK_INC=$(shell pkg-config --cflags dbus-1)
EXT_LIBS=$(GDK_LIB)

###################################################################

LIBNAME=libskype_io

###################################################################

ifeq "$(MODE)" "debug"
    OBJDIR=./DBG
    BINDIR=./DBG

    CFLAGS := -Wall -std=c++0x -ggdb -g3
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm -g
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. -lm

    TARGET=example
else
    OBJDIR=./OPT
    BINDIR=./OPT

    CFLAGS := -Wall -std=c++0x
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. -lm

    TARGET=example
endif

###################################################################

CC=gcc

LDSHARED=gcc
CPP=gcc -E
INCL = $(GDK_INC) -I.


STATICLIB=$(LIBNAME).a
SHAREDLIB=
SHAREDLIBV=
SHAREDLIBM=
LIBS=$(STATICLIB) $(SHAREDLIBV)

AR=ar rc
RANLIB=ranlib
LDCONFIG=ldconfig
LDSHAREDLIBC=-lc
TAR=tar
SHELL=/bin/sh
EXE=

#vpath %.cpp .

SRCC = dbus.cpp skype_low_io.cpp 
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCC)) $(patsubst %.c,$(OBJDIR)/%.o,$(SRCC))

LIB_NAMES = utils
LIBS = $(patsubst %,$(BINDIR)/lib%.a,$(LIB_NAMES))

all: static

static: $(TARGET)

check: test

test: all teststatic

teststatic: static
	@echo static test is not ready yet, dc10

$(BINDIR)/$(STATICLIB): $(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

$(OBJDIR)/%.o: %.cpp
	@echo compiling $<
	$(CC) $(CFLAGS) $(CDBG) -DPIC -c -o $@ $< $(INCL)

$(OBJDIR)/%.o: %.c
	@echo compiling $<
	$(CC) $(CFLAGS) $(CDBG) -DPIC -c -o $@ $< $(INCL)

$(TARGET): $(BINDIR) $(BINDIR)/$(TARGET) 
	ln -sf $(BINDIR)/$(TARGET) $(TARGET)
	@echo "$@ uptodate - ${MODE}"

$(BINDIR)/$(TARGET): $(LIBS) $(OBJDIR)/$(TARGET).o $(OBJS) $(BINDIR)/$(STATICLIB)
	$(CC) $(CFLAGS) $(CDBG) -o $@ $(OBJDIR)/$(TARGET).o $(BINDIR)/$(LIBNAME).a $(LIBS) $(EXT_LIBS) $(LFLAGS_TEST)

$(BINDIR)/lib%.a: %		# somehow this rule doesn't work
	cd ../$<; make; cd $(project)
	ln -sf ../$</$@ $(BINDIR)

$(BINDIR)/libutils.a:
	cd ../utils; make; cd $(project)
	ln -sf ../../utils/$@ $(BINDIR)

$(BINDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

clean:
	#rm $(OBJDIR)/*.o *~ $(TARGET)
	rm $(OBJDIR)/*.o $(TARGET) $(BINDIR)/$(TARGET) $(BINDIR)/$(STATICLIB)
