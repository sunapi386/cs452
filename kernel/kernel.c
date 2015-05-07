#include <kernel.h>
#include <ts7200.h>
#include <timer.h>
#include <termio.h>
#include <menu.h>
#include <trains.h>

/* TODO: memcpy should be put somewhere more appropriate than in kernel */
void memcpy( char *destaddr, char *srcaddr, int len ) {
    while ( len-- ) *destaddr++ = *srcaddr++;
}

int main( int argc, char* argv[] ) {
    terminit();
    termsetfifo( COM2, OFF );
    termsetfifo( COM1, OFF );
    termsetspeed( COM1, 2400 );
    initClock();

    char parsebuffer[BUFSIZ] = {'\0'}; /* buffer for storing and parsing user input */
    menuInit(parsebuffer);

    int c;

    for( ;; ) {
        doClock();
        termcheckandsend();
        if( (c = termgetc(COM2)) ) {
            if( c == 'q' ) {
                break;
            }
            menuParse( parsebuffer, c );
        } // if
    }

    CLS;
    termflush(); /* Do not print anything after this! */
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
