 /*
 * digiclock.c
 * a digital clock showing minutes, seconds, and tenths of seconds,
 * which measures time intervals accurately, in the sense that it does not
 * slow down or lose ticks
 */

#include <kernel.h>
#include <ts7200.h>
#include <timer.h>
#include <termio.h>

int main( int argc, char* argv[] ) {

    termsetfifo( COM2, OFF );
    initClock();
    termprintf( COM2, "%c[2J", 27);
    termprintf( COM2, "%c[%d;%dH", 27, 3, 0);
    termprintf( COM2, ">>>\n\r");

    for( ;; ) {
        doClock();
        termcheckandsend();
    }

    // termprintf( COM2, "%c[2J", 27);
    // termprintf( COM2, "Done!\n\r");
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
