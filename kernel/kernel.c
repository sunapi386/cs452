#include <kernel.h>
#include <ts7200.h>
#include <timer.h>
#include <termio.h>
#include <screen.h>
#include <trains.h>

int main( int argc, char* argv[] ) {
    terminit();
    trainsInit();
    initClock();
    screenInit();

    int c;
    termflush();

    for( ;; ) {
        doClock();
        termcheckandsend();
        if( (c = termgetc(COM2)) ) {
            if( c == 'q' ) {
                break;
            }
            else if( c == '\r' ) {
                screenParse();
            }
            else {
                screenAdd( c );
            }
        } // if
    } // for

    screenQuit(); /* Do not print anything after this! */
    return 0;
} // main

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
