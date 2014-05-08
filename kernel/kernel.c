 /*
 * digiclock.c
 * a digital clock showing minutes, seconds, and tenths of seconds,
 * which measures time intervals accurately, in the sense that it does not
 * slow down or lose ticks
 */

#include <termio.h>
#include <ts7200.h>
#include <kernel.h>
#include <timer.h>

int main( int argc, char* argv[] ) {
    termsetfifo( COM2, OFF );

    for( ;; ) {
        termcheckandsend( COM1 );
        termcheckandsend( COM2 );
    }

    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
