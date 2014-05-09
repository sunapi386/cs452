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
        PRINT( "Input buffer full!" );
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
    POS( SCREEN_ROW, SCREEN_COL ); /* Position cursor */
    PRINT( "****************************" ); /* Note there is no \n */
    POS( SCREEN_ROW + 1, SCREEN_COL );  /* Go down next line */
    PRINT( "Jason Sun's CS 452 Train Control" ); /* Align under * */
    POS( SCREEN_ROW + 2, SCREEN_COL );  /* Next line */
    PRINT( "(q) quit");
    POS( SCREEN_ROW + 3, SCREEN_COL );  /* Next line */
    PRINT( "(g) trains go");
    POS( SCREEN_ROW + 4, SCREEN_COL );  /* Next line */
    PRINT( "(t) trains stop");
    POS( SCREEN_ROW + 5, SCREEN_COL ); /* Next line */
    PRINT( "");
    POS( SCREEN_ROW + 6, SCREEN_COL ); /* Next line */
    PRINT("****************************");
    POS( SCREEN_ROW + 7, SCREEN_COL ); /* Next line */
    screenLine();
}

/* Moves cursor to line 4 and prints a prompt */
void screenLine() {
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL ); /* Park the cursor */
    CLLINE;
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL ); /* Park the cursor */
}

// void screenHistory() {
//     POS( SCREEN_INPUT_ROW - 1, 0 );
//     PRINT( "=> %s", parsebuffer );
// }

int strcmp( const char* str1, const char* str2 ) { /* Needs to be null terminated */
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) { i++; }
    /* if str1[i] == str2[i], means they all equal to '\0' */
    return (str1[i] == str2[i] ? 0 : (str1[i] > str2[i] ? 1 : -1));
}

void screenParse() {
    POS( SCREEN_INPUT_ROW - 1, 0 );
    CLLINE;
    PRINT( "%s", parsebuffer );
    char cmd = parsebuffer[0];
    switch( cmd ) {
        case 'g': trainsGo(); break;
        case 't': trainsStop(); break;
        default:  screenTrains( "Unknown %c", cmd );
    }
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL ); /* Park the cursor */
    CLLINE;
    cleanbuffer();
}

void screenTrains( char *msg, ... ) {
    SAVECURSOR;
    POS( SCREEN_INPUT_ROW, SCREEN_INPUT_COL );
    CLLINE;
    POS( SCREEN_TRAIN_ACTION_ROW, SCREEN_TRAIN_ACTION_COL );
    CLLINE;
    PRINT( msg );
    LOADCURSOR;
}
