#include <screen.h>
#include <termio.h>
#include <trains.h>

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


int strcmp( const char* str1, const char* str2 ) { /* Needs to be null terminated */
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) { i++; }
    /* if str1[i] == str2[i], means they all equal to '\0' */
    return (str1[i] == str2[i] ? 0 : (str1[i] > str2[i] ? 1 : -1));
}

void screenParse() {
    screenUpdateHistory();
    switch( parsebuffer[0] ) {
        case 't':
        if( parsebuffer[1] == 'r' ) {
            // unsigned int train_num = 48;
            // unsigned int train_speed = 30;
            // trainsSet( train_num, train_speed );
            trainsSet( 48, 30 );
            break;
        }
        case 'r':
        if( parsebuffer[1] == 'v' ) {
            // unsigned int train_num = 48;
            // trainsReverse( train_num );
            trainsReverse( 48 );
            break;
        }
        case 's':
        if( parsebuffer[1] == 'w' ) {
            // unsigned int switch_num = 9;
            // char switch_direction = 'C';
            // trainsSwitch( switch_num, switch_direction );
            trainsSwitch( 9, 'C' );
            break;
        }
        default:  screenTrains( "Unknown command %s", parsebuffer );
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
