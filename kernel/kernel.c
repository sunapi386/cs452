 /*
 * digiclock.c
 * a digital clock showing minutes, seconds, and tenths of seconds,
 * which measures time intervals accurately, in the sense that it does not
 * slow down or lose ticks
 */

#include <bwio.h>
#include <ts7200.h>
#include <kernel.h>
#include <timer.h>

int main( int argc, char* argv[] ) {
    bwsetfifo( COM2, OFF );
    setTimer( 1, 255 );

    for( ;; ) {
        // if( *timer1val == 0 ) break;
        bwprintf( COM2, "T11 %d\n\r", getTimer(1) );
    }

    return 0;
}

