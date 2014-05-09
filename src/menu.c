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
	PRINT( "Quit (q)");
	POS( MENU_INPUT_ROW - 2, MENU_INPUT_COL ); /* Next line */
	PRINT("****************************");
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

/* Moves cursor to line 4 and prints a prompt */
void menuLine() {
	CLLINE;
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

void menuHistory() {
	POS( MENU_INPUT_ROW - 1, 0 );
	PRINT( "%s", parsebuffer );
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
