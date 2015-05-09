#include <kernel.h>
#include <ts7200.h>
#include <timer.h>
#include <termio.h>
#include <menu.h>
#include <trains.h>

/* TODO: memcpy should be put somewhere more appropriate than in kernel */
static inline void memcpy( char *destaddr, char *srcaddr, int len ) {
    while ( len-- ) *destaddr++ = *srcaddr++;
}

int main( int argc, char* argv[] ) {
    terminit();
    /* COM1
        Baud rate = 2400
        Start bits (if requested by computer) = 1
        Stop bits = 2
        Parity = None
        Word size = 8 bits
    */
    termsetspeed( COM1, 2400 );
    termsetfifo( COM1, OFF );

    /* COM2 */
    termsetfifo( COM2, OFF );
    initClock();
    menuDraw();
    trainsInit();

    // char buffer[BUFSIZ] = {'\0'}; /* buffer for storing and parsing user input */
    // char instruction1[BUFSIZ] = {'\0'};  buffer for instr 1
    // char instruction2[BUFSIZ] = {'\0'}; /* buffer for 2 */
    // char instruction3[BUFSIZ] = {'\0'}; /* buffer for 3 */

    buffer_t buffer0, buffer1, buffer2, buffer3; /* buffer 0 used for entry, 1 2 3 for cmds */
    BufferEmpty(&buffer0);
    BufferEmpty(&buffer1);
    BufferEmpty(&buffer2);
    BufferEmpty(&buffer3);
    int spaces = 0;  /* Track number of spaces pressed */
    int c;

    for( ;; ) {
        doClock();
        termcheckandsend();
        if( (c = termgetc(COM2)) ) { /* If there is input */
            if( c == 'q' ) { break; } /* For some reason this quit can only go here */
            if( c == '\r' ) { /* User pressed enter */
                if( spaces == 0 ) { BufferCopy( &buffer0, &buffer1 ); BufferEmpty( &buffer0 ); }
                if( spaces == 1 ) { BufferCopy( &buffer0, &buffer2 ); BufferEmpty( &buffer0 ); }
                if( spaces == 2 ) { BufferCopy( &buffer0, &buffer3 ); BufferEmpty( &buffer0 ); }
                menuInput( &buffer1, &buffer2, &buffer3 );
                spaces = 0;
                BufferEmpty( &buffer0 ); BufferEmpty( &buffer1 ); BufferEmpty( &buffer2 ); BufferEmpty( &buffer3 );
            } else if( c == ' ' ) { /* User pressed space */
                PRINT( "%c", c ); /* Display user's input */
                if( spaces == 0 ) { BufferCopy( &buffer0, &buffer1 ); BufferEmpty( &buffer0 ); }
                if( spaces == 1 ) { BufferCopy( &buffer0, &buffer2 ); BufferEmpty( &buffer0 ); }
                if( spaces == 2 ) { BufferCopy( &buffer0, &buffer3 ); BufferEmpty( &buffer0 ); }
                spaces++;
            } else if ( c == '\b' ) { /* TODO: User pressed backspace */
            } else { /* User pressed a character */
                PRINT( "%c", c ); /* Display user's input */
                BufferInsert( &buffer0, c );
            }
        } // if
    }
    trainsQuit();
    CLS;
    termflush(); /* Do not print anything after this! */
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
