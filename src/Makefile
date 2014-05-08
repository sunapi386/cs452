#
# Makefile for non-busy-wait IO library
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

all:  termio.a timer.a
	cp termio.a ../lib/libtermio.a
	cp timer.a ../lib/libtimer.a

termio.s: termio.c
	$(XCC) -S $(CFLAGS) termio.c

termio.o: termio.s
	$(AS) $(ASFLAGS) -o termio.o termio.s

termio.a: termio.o
	$(AR) $(ARFLAGS) $@ termio.o

timer.s: timer.c
	$(XCC) -S $(CFLAGS) timer.c

timer.o: timer.s
	$(AS) $(ASFLAGS) -o timer.o timer.s

timer.a: timer.o
	$(AR) $(ARFLAGS) $@ timer.o

clean:
	-rm -f *.s *.a *.o
