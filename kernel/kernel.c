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

// Prints a menu and returns user's choice. Returns -1 if bad choice.
// char getusrcmd( int channel ) {
//     char menu[] = "Menu.\n\r1. Train track state\n\r2. Clock\n\r3. Hello world\n\rEnter a number:\n\r";
//     bwputstr( channel, menu );
//     menu[0] = bwgetc( channel );
//     bwprintf( channel, "You entered '%s'\n\r", menu[0] );
//     return menu[0];
// }

int main( int argc, char* argv[] ) {
    bwsetfifo( COM2, OFF );
    int *timer1load = (int *)(TIMER1_LOAD);
    int *timer1val = (int *)(TIMER1_VALUE);
    int *timer1ctl = (int *)(TIMER1_CONTROL);

    /* Load contains initial values of timer */
    *timer1load = 255;

    /* Timer control: enable timer (p. 430) */
    *timer1ctl = ENABLE_MASK;

    /* Read base + 0x4 */

    for( ;; ) {
        if( *timer1val == 0 ) break;
        bwprintf( COM2, "T1 %u\n\r", *timer1val);
    }

    return 0;
}

