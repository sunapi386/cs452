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
    setTimer( 3, 0 );
    unsigned int msec = 0;
    unsigned int sec = 0;
    unsigned int min = 0;
    unsigned int last_time = 0;
    unsigned int now;

    for( ;; ) {
        now = getTimer(3) / 2;
        if( now != last_time ) {
            last_time = now;
            msec += 1;
        }
        if( msec % 1000 == 0 ) {
            bwprintf( COM2, "Clock %umin, %usec, %umsec.\n\r", min, sec, msec);
            msec = 0;
            sec += 1;
        }
        if( sec % 60 == 0 ) {
            sec = 0;
            min += 1;
        }

    }

    return 0;
}

