#include <kernel.h>
#include <ts7200.h>
#include <timer.h>
#include <termio.h>
#include <menu.h>
#include <trains.h>

int main( int argc, char* argv[] ) {
    terminit();
    termsetfifo( COM2, OFF );
    termsetfifo( COM1, OFF );
    termsetspeed( COM1, 2400 );
    initClock();
    menuInit();

    int c;

    for( ;; ) {
        doClock();
        termcheckandsend();
        if( (c = termgetc(COM2)) ) {
            if( c == 'q' ) { break; }
            if( c == 's' ) {
                CLLINE;
                POS( 10, 2 );
                CLLINE;
                PRINT( "start" );
                POS( MENU_INPUT_ROW, MENU_INPUT_COL );
                termprintf( COM1, "%c", 96 );
            }
            if( c == 't' ) {
                CLLINE;
                POS( 10, 2 );
                CLLINE;
                PRINT( "stop" );
                POS( MENU_INPUT_ROW, MENU_INPUT_COL );
                termprintf( COM1, "%c", 97 );
            }
            if( c == 'r' ) {
                CLLINE;
                POS( 10, 2 );
                CLLINE;
                PRINT( "reverse" );
                POS( MENU_INPUT_ROW, MENU_INPUT_COL );
                termprintf( COM1, "S50" );
            }
            menuParse( c );
        }
    }

    termflush(); /* Do not print anything after this! */
    return 0;
}

// start signal is 96
// lower bit baud rate 0xbf
// send on com1 speed and train number
// 10 follwoed by 50
