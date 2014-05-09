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
#include <menu.h>
#include <trains.h>

int main( int argc, char* argv[] ) {
    terminit();
    termsetfifo( COM2, OFF );
    initClock();
    menuInit();
    menuLine();
    int c;
    for( ;; ) {
        doClock();
        termcheckandsend();
    }

    termprintf( COM2, "Done!\n\r");
    termflush(); /* Do not print anything after this! */
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
