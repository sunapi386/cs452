#
# Makefile for busy-wait IO tests
#
XCC     = gcc
AS		= as
LD      = ld
CFLAGS  = -c -fPIC -Wall -I. -I../include -mcpu=arm920t -msoft-float
# -g: include hooks for gdb
# -c: only compile
# -mcpu=arm920t: generate code for the 920t architecture
# -fpic: emit position-independent code
# -Wall: report all warnings

ASFLAGS	= -mcpu=arm920t -mapcs-32
# -mapcs: always generate a complete stack frame

LDFLAGS = -init main -Map kernel.map -N  -T orex.ld -L/u/wbcowan/gnuarm-4.0.2/lib/gcc/arm-elf/4.0.2 -L../lib

# Kernel

install: all
	cp kernel.elf /u/cs452/tftp/ARM/j53sun

all:  kernel.s kernel.elf

kernel.s: kernel.c kernel.h
	$(XCC) -S $(CFLAGS) kernel.c

kernel.o: kernel.s
	$(AS) $(ASFLAGS) -o kernel.o kernel.s

kernel.elf: kernel.o
	$(LD) $(LDFLAGS) -o $@ kernel.o -ltermio -ltimer -lgcc

# Libraries
libs:
	cd ../src && $(MAKE) clean && sleep 0.5 && $(MAKE)

clean:
	-rm -f kernel.elf *.s *.o kernel.map

