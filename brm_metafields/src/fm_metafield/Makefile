###########
#
# @(#)% full_filespec: Make.user~21 %
#
# Copyright (c) 1996, 2012, Oracle and/or its affiliates. All rights reserved. 
#
#      This material is the confidential property of Oracle
#      Corporation or its licensors and may be used, reproduced,
#      stored or transmitted only in accordance with a valid
#      Oracle license or sublicense agreement.
#
###########

OS=linux
VERSION=7.5

##########

PINDIR=../../..
INCDIR=$(PINDIR)/include
LIBDIR=$(PINDIR)/lib

##########
CC_solaris = cc
CC_hpux = cc
CC_hpux_ia64 = cc
CC_aix = xlc_r
CC_linux = gcc 
CC = $(CC_$(OS))

###########

CFLAGS_solaris= -g -xcg92
CFLAGS_hpux= -g -Ae +Z +DAportable
CFLAGS_hpux_ia64= -g -Ae +Z
CFLAGS_aix= -g -Drs6000 -D__aix -Dunix -D__unix
CFLAGS_linux= -m32 -fPIC
CFLAGS= $(CFLAGS_$(OS)) -DFOR_CM -DFM_CUST_POL_DLL

CPPFLAGS = -I$(INCDIR) -DPCMCPP_CONST_SAFE -DFOR_CM -DFM_CUST_POL_DLL

LDFLAGS_solaris= -G
LDFLAGS_hpux= -b
LDFLAGS_hpux_ia64= -b
LDFLAGS_aix= -G -bnoentry -bexpall -brtl -lc
LDFLAGS_linux= -m elf_i386 -shared -L/usr/lib
LDFLAGS = $(LDFLAGS_$(OS)) -L$(LIBDIR)

SL_EXT_solaris= so
SL_EXT_hpux= sl
SL_EXT_hpux_ia64= so
SL_EXT_aix= a 
SL_EXT_linux= so
SL_EXT= $(SL_EXT_$(OS))

##########

INCFILES= $(INCDIR)/pin_cust.h $(INCDIR)/pcm.h \
	$(INCDIR)/pin_errs.h $(INCDIR)/pinlog.h

#
FILES= fm_metafield_pol_config.c \
	fm_metafield_pol_create_metafield_obj.c


OBJECTS= fm_metafield_pol_config.o \
	fm_metafield_pol_create_metafield_obj.o


#

LIBMETAFIELD=fm_metafield_pol.$(SL_EXT)

###########

all: $(LIBMETAFIELD)

clean:
	rm -f $(OBJECTS) core

clobber: clean
	rm -f $(LIBMETAFIELD)

lint:
	lint $(CPPFLAGS) $(FILES)

tags: FRC

###########

$(LIBMETAFIELD): $(OBJECTS) $(INCFILES) Makefile
	$(LD) -o $(LIBMETAFIELD) $(LDFLAGS) $(OBJECTS) -lpin_cc -lm -lpsiu_for_cm -lregex

$(OBJECTS): $(INCFILES) Makefile
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(FILES)

#

FRC:
