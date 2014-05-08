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
    setTimer( 3, 0 );
    volatile unsigned int tsec = 0;
    volatile unsigned int sec = 0;
    volatile unsigned int last_time = 0;
    volatile unsigned int now;
    termprintf( COM2, "%c[2J", 27);
    termprintf( COM2, ">>>\n\r");

    for( ;; ) {
        termcheckandsend();
        now = getTimer(3) / 200;
        if( now != last_time ) {
            last_time = now;
            tsec += 1;
            if( tsec % 10 == 0 ) {
                tsec = 0; sec += 1;
            }
            termprintf( COM2, "%c[%d;%dH", 27, 0, 0);
            termprintf( COM2, "%u:%u.%u\n\r", sec / 60, sec % 60, tsec );
            termprintf( COM2, "%c[%d;%dH", 27, 3, 0);
        }
    }

    // termprintf( COM2, "%c[2J", 27);
    // termprintf( COM2, "Done!\n\r");
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
