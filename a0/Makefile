# Author j53sun May 5 2014
# Program that uses the busy wait functions to put output on the terminal 
# attached to the TS-7200. 
#
XCC     = gcc
AS	= as
AR	= ar
CFLAGS  = -c -fPIC -Wall -I. -I../include -mcpu=arm920t -msoft-float
# -g: include hooks for gdb
# -c: only compile
# -mcpu=arm920t: generate code for the 920t architecture
# -fpic: emit position-independent code
# -Wall: report all warnings
# -msoft-float: use software for floating point

ASFLAGS	= -mcpu=arm920t -mapcs-32
# -mapcs-32: always create a complete stack frame

ARFLAGS = rcs

all:  j53sunmain.a 
# for lack of a better name at the moment, I'll call it j53sunmain.a

j53sunmain.s: j53sunmain.c 
	$(XCC) -S $(CFLAGS) j53sunmain.c

j53sunmain.o: j53sunmain.s
	$(AS) $(ASFLAGS) -o j53sunmain.o j53sunmain.s

j53sunmain.a: j53sunmain.o
	$(AR) $(ARFLAGS) $@ j53sunmain.o


clean:
	-rm -f *.s *.a *.o
