#
# Makefile for libraries
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

all:  termio.a timer.a screen.a trains.a
	cp termio.a ../lib/libtermio.a
	cp timer.a ../lib/libtimer.a
	cp screen.a ../lib/libscreen.a
	cp trains.a ../lib/libtrains.a

###################################
# bwio
#

bwio.s: bwio.c
	$(XCC) -S $(CFLAGS) bwio.c

bwio.o: bwio.s
	$(AS) $(ASFLAGS) -o bwio.o bwio.s

bwio.a: bwio.o
	$(AR) $(ARFLAGS) $@ bwio.o

###################################
# termio
#

termio.s: termio.c
	$(XCC) -S $(CFLAGS) termio.c

termio.o: termio.s
	$(AS) $(ASFLAGS) -o termio.o termio.s

termio.a: termio.o
	$(AR) $(ARFLAGS) $@ termio.o

###################################
# timer
#

timer.s: timer.c
	$(XCC) -S $(CFLAGS) timer.c

timer.o: timer.s
	$(AS) $(ASFLAGS) -o timer.o timer.s

timer.a: timer.o
	$(AR) $(ARFLAGS) $@ timer.o

###################################
# screen
#

screen.s: screen.c
	$(XCC) -S $(CFLAGS) screen.c

screen.o: screen.s
	$(AS) $(ASFLAGS) -o screen.o screen.s

screen.a: screen.o
	$(AR) $(ARFLAGS) $@ screen.o

###################################
# trains
#

trains.s: trains.c
	$(XCC) -S $(CFLAGS) trains.c

trains.o: trains.s
	$(AS) $(ASFLAGS) -o trains.o trains.s

trains.a: trains.o
	$(AR) $(ARFLAGS) $@ trains.o


###################################
# clean
#

clean:
	-rm -f *.s *.a *.o
