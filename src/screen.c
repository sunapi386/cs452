#include <screen.h>
#include <termio.h>
#include <trains.h>
#include <string.h>

char parsebuffer[BUFSIZ] = {'\0'};
unsigned int front = 0, back = 0, count = 0;

void cleanbuffer() {
    int i;
    for( i = 0; i < BUFSIZ; ++i ) {
        parsebuffer[i] = '\0';
    }
    front = 0, back = 0, count = 0;
}

void screenInit() {
    cleanbuffer();
    CLS;    /* Clear screen */
    screenMenu();
}

int screenAdd( char c ) {
    if( count == BUFSIZ ) {
        CLLINE;
        PRINT( "Input buffer full!" ); /* This should signal when its near full  */
        cleanbuffer();
        return -1;
    }
    parsebuffer[front] = c;
    front = (front + 1) % BUFSIZ;
    count += 1;
    PRINT( "%c", c );
    return 0;
}


void screenMenu() {
    int line;
    for( line = 0; line < 25; ++line ) {
        POS( SCREEN_BEGIN_ROW + line, SCREEN_BEGIN_COL );      PRINT( "|" );
        POS( SCREEN_BEGIN_ROW + line, SCREEN_BEGIN_COL + 69 ); PRINT( "|" );
        if( line >= 2 && line <= 17 ) {
            POS( SCREEN_BEGIN_ROW + line, SCREEN_BEGIN_COL + 35 ); PRINT( "|" );
        }
    }
    POS( SCREEN_BEGIN_ROW + 1, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    POS( SCREEN_BEGIN_ROW + 2, SCREEN_BEGIN_COL );
    PRINT( "| Sensor Data                     |  Track Switch States            |" );
    POS( SCREEN_BEGIN_ROW + 3, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    POS( SCREEN_BEGIN_ROW + 16, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    POS( SCREEN_BEGIN_ROW + 17, SCREEN_BEGIN_COL );
    PRINT( "| Jason Sun's CS 452 Controller   | Clock                           |" );
    POS( SCREEN_BEGIN_ROW + 18, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    POS( SCREEN_BEGIN_ROW + 20, SCREEN_BEGIN_COL + 3 );
    PRINT( "$" );
    POS( SCREEN_BEGIN_ROW + 21, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    POS( SCREEN_BEGIN_ROW + 22, SCREEN_BEGIN_COL );
    PRINT( "| Commands: | tr train_num train_speed       | rv train_number      |" );
    POS( SCREEN_BEGIN_ROW + 23, SCREEN_BEGIN_COL );
    PRINT( "|           | sw switch_num switch_direction | q                    |" );
    POS( SCREEN_BEGIN_ROW + 24, SCREEN_BEGIN_COL );
    PRINT( "|---------------------------------+---------------------------------|" );
    screenClearInputLine();
}


void screenUpdateHistory() {
    POS( SCREEN_INPUT_ROW - 1, SCREEN_INPUT_COL );  CLTOEND; /* Erase from cursor to EOL */
    POS( SCREEN_INPUT_ROW - 1, SCREEN_INPUT_COL );  PRINT( "%s", parsebuffer );
    POS( SCREEN_INPUT_ROW - 1, SCREEN_INPUT_COL + 64 ); PRINT( "|" );
}

void screenClearInputLine() {
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL );      CLTOEND; /* Erase from cursor to EOL */
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL + 64 ); PRINT( "|" );
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL );
    cleanbuffer();
}

// TODO: Need to correctly parse because otherwise console doesn't work properly
// currently it is hardcoded to use the specific formats:
//
// 01234567 (hardcoded to use index)
// tr nn ss
// rv nn
// sw nn d
//
// This will utterly break if the format is given incorrectly.
void screenParse() {
    screenUpdateHistory();
    switch( parsebuffer[0] ) {
        case 't':
        if( parsebuffer[1] == 'r' ) {
            unsigned int train_num = char2int(parsebuffer[3]) * 10 + char2int(parsebuffer[4]);
            unsigned int train_speed = char2int(parsebuffer[6]) * 10 + char2int(parsebuffer[7]);
            trainsSet( train_num, train_speed );
            break;
        }
        case 'r':
        if( parsebuffer[1] == 'v' ) {
            unsigned int train_num = char2int(parsebuffer[3]) * 10 + char2int(parsebuffer[4]);
            trainsReverse( train_num );
            break;
        }
        case 's':
        if( parsebuffer[1] == 'w' ) {
            unsigned int switch_num = char2int(parsebuffer[3]) * 10 + char2int(parsebuffer[4]);
            char switch_direction = parsebuffer[6];
            trainsSwitch( switch_num, switch_direction );
            break;
        }
        default:  screenTrains( "Unknown command: %s", parsebuffer );
    }
    screenClearInputLine();
}

void screenPrintClock( int min, int sec, int tsec ) {
    SAVECURSOR;
    POS( SCREEN_CLOCK_ROW, SCREEN_CLOCK_COL );
    PRINT( "%u:%u.%u", min, sec, tsec % 10 );
    LOADCURSOR;
}

void screenTrains( char *msg, ... ) {
    SAVECURSOR;
    POS( SCREEN_TRACK_ROW, SCREEN_TRACK_COL );
    CLTOEND;
    PRINT( msg );
    POS( SCREEN_TRACK_ROW, SCREEN_BEGIN_COL + 69 );
    PRINT( "|" );
    LOADCURSOR;
}

void screenQuit() {
    PRINT( "Goodbye\n\r" );
    termflush();
}
