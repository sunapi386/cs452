#include <menu.h>
#include <termio.h>

char parsebuffer[BUFSIZ] = {'\0'};
unsigned int front = 0, back = 0, count = 0;

void cleanbuffer() {
	int i;
	for( i = 0; i < BUFSIZ; ++i ) {
	    parsebuffer[i] = '\0';
	}
	front = 0, back = 0, count = 0;
}

void bufferAdd( char c ) {
	if( count == BUFSIZ ) {
		CLLINE;
		PRINT( "Input buffer full!" );
		cleanbuffer();
	}
	parsebuffer[front] = c;
	front = (front + 1) % BUFSIZ;
	count += 1;
}

void menuInit() {
	cleanbuffer();
	CLS;	/* Clear screen */
	POS( MENU_ROW, MENU_COL ); /* Position cursor */
	PRINT( "****************************" ); /* Note there is no \n */
	POS( MENU_ROW + 1, MENU_COL );	/* Go down next line */
	PRINT( "CS 452 Train Control Menu" ); /* Align under * */
	POS( MENU_ROW + 2, MENU_COL );  /* Next line */
	PRINT( "(q) quit");
	POS( MENU_ROW + 3, MENU_COL );  /* Next line */
	PRINT( "(s) start trains");
	POS( MENU_ROW + 4, MENU_COL );  /* Next line */
	PRINT( "(t) stop trains");
	POS( MENU_ROW + 5, MENU_COL ); /* Next line */
	PRINT( "(r) reverse trains");
	POS( MENU_ROW + 6, MENU_COL ); /* Next line */
	PRINT("****************************");
	POS( MENU_ROW + 7, MENU_COL ); /* Next line */
}

/* Moves cursor to line 4 and prints a prompt */
void menuLine() {
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
	CLLINE;
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

void menuHistory() {
	POS( MENU_INPUT_ROW - 1, 0 );
	PRINT( "=> %s", parsebuffer );
}

void menuParse( char c ) {
	if( c == '\r' ) {
		CLLINE;
		POS( MENU_INPUT_ROW - 1, 0 );
		CLLINE;
		PRINT( "%s", parsebuffer );
		cleanbuffer();
		POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
	}
	PRINT( "%c", c );
	bufferAdd( c );
}

