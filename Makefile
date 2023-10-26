#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Oct 25 22:23:41 2023
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS =	-std=c99 -ggdb -Wall -Wextra -pedantic
CLIBFLAGS =	-lm  -lcurses 


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	bracetopia.c happyMeasure.c initializingGrid.c moves.c processCommandLines.c supportFuncs.c use_getopt.c
PS_FILES =	
S_FILES =	
H_FILES =	happyMeasure.h initializingGrid.h moves.h processCommandLines.h supportFuncs.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	happyMeasure.o initializingGrid.o moves.o processCommandLines.o supportFuncs.o 

#
# Main targets
#

all:	bracetopia use_getopt 

bracetopia:	bracetopia.o $(OBJFILES)
	$(CC) $(CFLAGS) -o bracetopia bracetopia.o $(OBJFILES) $(CLIBFLAGS)

use_getopt:	use_getopt.o $(OBJFILES)
	$(CC) $(CFLAGS) -o use_getopt use_getopt.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

bracetopia.o:	happyMeasure.h initializingGrid.h moves.h processCommandLines.h supportFuncs.h
happyMeasure.o:	happyMeasure.h
initializingGrid.o:	initializingGrid.h supportFuncs.h
moves.o:	happyMeasure.h moves.h
processCommandLines.o:	processCommandLines.h
supportFuncs.o:	supportFuncs.h
use_getopt.o:	

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) bracetopia.o use_getopt.o core

realclean:        clean
	-/bin/rm -f bracetopia use_getopt 
