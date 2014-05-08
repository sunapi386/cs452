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
    volatile unsigned int msec = 0;
    volatile unsigned int sec = 0;
    volatile unsigned int last_time = 0;
    volatile unsigned int now;

    bwprintf( COM2, "%c[2J", 27);
    for( ;; ) {
        now = getTimer(3) / 2;
        if( now != last_time ) {
            last_time = now;
            msec += 1;
        }
        if( msec % 100 == 0 ) {
            bwprintf( COM2, "%c[%d;%dH", 27, 0, 0);
            bwprintf( COM2, "%u:%u.%u\n\r", sec / 60, sec % 60, msec );
            if( msec % 1000 == 0 ) { msec = 0; sec += 1; }
        }

    }

    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
