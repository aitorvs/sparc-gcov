#############################################################################
# Makefile for building: libosal_rtems.a
# Generated by qmake (2.01a) (Qt 4.3.2) on: mar ago 12 17:25:14 2008
# Project:  osal.pro
# Template: lib
# Command: /usr/bin/qmake-qt4 -unix CONFIG\ +=\ sparc\ rtems -o Makefile.rtems osal.pro
#############################################################################

####### Compiler, tools and options

CROSS		  = /opt/rtems-4.10/bin/sparc-rtems
CROSS		  = /opt/rtems-4.6/bin/sparc-rtems
CROSS		  = /opt/rtems-4.8/bin/sparc-rtems

CC            = $(CROSS)-gcc
CXX           = $(CROSS)-g++
AR            = $(CROSS)-ar r

DEFINES_LEON3 = 
DEFINES_LEON2 = -qleon2
CFLAGS        = -O2 -g -Wall -W 
CXXFLAGS      = -pipe -g -fPIC -D_REENTRANT -Wall -W 
INCPATH       = -I. -Iinclude
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
TOPDIR  := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
VERSION_DIR := ./tools/version

####### Output directory

OBJECTS_DIR   = $(DESTDIR)/

####### Files

COMMON_OBJS   = $(DESTDIR)/wrapper_rtems.o \
				$(DESTDIR)/libgcov.o \
				$(DESTDIR)/interface.o \
				$(DESTDIR)/gcov-io.o \

LEON2_OBJS    = $(DESTDIR)/if_serial_leon2.o 

LEON3_OBJS    = 

OBJECTS       = $(COMMON_OBJS) $(LEON3_OBJS) $(LEON2_OBJS)

DESTDIR       = build
TARGET_LEON2  = libgcov_rtems_leon2.a
TARGET_LEON3  = libgcov_rtems_leon3.a

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile dest_dir gcov_dir

dest_dir:
	@$(CHK_DIR_EXISTS) $(DESTDIR)/ || $(MKDIR) $(DESTDIR)/ 
	@make -C tools/version
	@$(VERSION_DIR)/gcov-iov 4.2 '*' > include/gcov-iov.h

gcov_dir:  $(OBJECTS) $(OBJCOMP) 
	@$(CHK_DIR_EXISTS) $(DESTDIR)/ || $(MKDIR) $(DESTDIR)/ 
	-$(DEL_FILE) $(TARGET_LEON3)
	$(AR) $(TARGET_LEON2) $(COMMON_OBJS) $(LEON2_OBJS)
	$(AR) $(TARGET_LEON3) $(COMMON_OBJS) $(LEON3_OBJS)
	-$(DEL_FILE) $(DESTDIR)/$(TARGET_LEON3) $(DESTDIR)/$(TARGET_LEON2)
	-$(MOVE) $(TARGET_LEON2) $(TARGET_LEON3) $(DESTDIR)/


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(DESTDIR)/$(TARGET_LEON3) $(DESTDIR)/$(TARGET_LEON2)
	-$(DEL_FILE) *~ core *.core

compiler_clean:

####### Sub-libraries

distclean: clean

########################## COMPILATION ###########################

#====== LEON3 Architecture =======


#====== LEON2 Architecture =======

$(DESTDIR)/if_serial_leon2.o: arch/sparc/leon2/if_serial.c arch/sparc/leon2/if_serial.h
	$(CC) -c $(CFLAGS) $(DEFINES_LEON2) $(INCPATH) -o $@ arch/sparc/leon2/if_serial.c

#====== Architecture Independent =======

$(DESTDIR)/wrapper_rtems.o: os/rtems/wrapper.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ os/rtems/wrapper.c

$(DESTDIR)/libgcov.o: lib/libgcov.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ lib/libgcov.c

$(DESTDIR)/gcov-io.o: arch/sparc/gcov-io.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@  arch/sparc/gcov-io.c

$(DESTDIR)/interface.o: arch/sparc/interface.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@  arch/sparc/interface.c


########################## INSTALATION ###########################

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/osal/libosal/ || $(MKDIR) $(INSTALL_ROOT)/osal/libosal/ 
	-$(INSTALL_FILE) "$(DESTDIR)/$(TARGET_LEON2)" "$(INSTALL_ROOT)/osal/libosal/$(TARGET_LEON2)"
	-$(INSTALL_FILE) "$(DESTDIR)/$(TARGET_LEON3)" "$(INSTALL_ROOT)/osal/libosal/$(TARGET_LEON3)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/osal/libosal/$(TARGET_LEON2)"
	-$(DEL_FILE) "$(INSTALL_ROOT)/osal/libosal/$(TARGET_LEON3)"
	-$(DEL_DIR) $(INSTALL_ROOT)/osal/libosal/ 


install_headerfiles: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/osal/include/ || $(MKDIR) $(INSTALL_ROOT)/osal/include/ 
	-$(INSTALL_FILE) $(TOPDIR)/include/autoconf.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/common_types.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi-compiler-switches.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi-debug.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi-hw-core.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi-os-core.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi-os-filesys.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osapi.h $(INSTALL_ROOT)/osal/include/
	-$(INSTALL_FILE) $(TOPDIR)/include/osconfig.h $(INSTALL_ROOT)/osal/include/


uninstall_headerfiles:  FORCE
	-$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/autoconf.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/common_types.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi-compiler-switches.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi-debug.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi-hw-core.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi-os-core.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi-os-filesys.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osapi.h 
	 -$(DEL_FILE) -r $(INSTALL_ROOT)/osal/include/osconfig.h
	-$(DEL_DIR) $(INSTALL_ROOT)/osal/include/ 


install:  install_target install_headerfiles  FORCE

uninstall: uninstall_target uninstall_headerfiles   FORCE

FORCE:

