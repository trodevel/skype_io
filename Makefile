# Makefile for libskype_io
# Copyright (C) 2014 Sergey Kolevatov

###################################################################

VER := 0

MODE ?= debug

###################################################################

BOOST_PATH := $(shell echo $$BOOST_PATH)

ifeq (,$(BOOST_PATH))
    $(error 'please define path to boost $$BOOST_PATH')
endif

###################################################################

BOOST_LIB_SYSTEM := libboost_system.a
BOOST_LIB_THREAD := libboost_thread.a


BOOST_INC=$(BOOST_PATH)
BOOST_LIB=$(BOOST_PATH)/stage/lib

###################################################################

LIBNAME=libskype_io

###################################################################

ifeq "$(MODE)" "debug"
    OBJDIR=./DBG
    BINDIR=./DBG

    CFLAGS := -Wall -std=c++0x -ggdb -g3
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm -g
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. $(BINDIR)/$(LIBNAME).a -lm

    TARGET=example
else
    OBJDIR=./OPT
    BINDIR=./OPT

    CFLAGS := -Wall -std=c++0x
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. $(BINDIR)/$(LIBNAME).a -lm

    TARGET=example
endif

###################################################################

WARN = -W -Wall -Wshadow -Wreturn-type -Wcomment -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wuninitialized -O
CDBG = -g $(CWARN) -fno-inline

GDK_LIB=$(shell pkg-config --libs gtk+-2.0 gdk-2.0 gthread-2.0 dbus-1 dbus-glib-1)
GDK_INC=$(shell pkg-config --cflags gtk+-2.0 gdk-2.0 gthread-2.0 dbus-1 dbus-glib-1)

###################################################################

CC=gcc

LDSHARED=gcc
CPP=gcc -E
INCL = -I$(BOOST_INC) -I$(GDK_INC) -I.


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

SRCC = event.cpp event_gen.cpp event_parser.cpp gdk_wrap.cpp parser_types.cpp skype-service.c dbus.cpp dbus_proxy.cpp \
		skype_service_callback.cpp skype_service_c.cpp skype_wrap.cpp skype_io.cpp command_gen.cpp \
		str_helper.cpp
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
	$(CC) $(CFLAGS) $(CDBG) -o $@ $(OBJDIR)/$(TARGET).o $(LFLAGS_TEST) $(LIBS) $(BOOST_LIB)/$(BOOST_LIB_THREAD) $(BOOST_LIB)/$(BOOST_LIB_SYSTEM) \
		$(GDK_LIB)
	

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
