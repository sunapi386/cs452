#include <menu.h>
#include <termio.h>

unsigned int front = 0; /* TODO: This global variable is probably bad */

void cleanbuffer( char *buffer ) {
	int i;
	for( i = 0; i < BUFSIZ; ++i ) {
	    buffer[i] = '\0';
	}
	front = 0;
}

void bufferAdd( char *buffer, char c ) {
	if( front == BUFSIZ ) {
		CLLINE;
		PRINT( "Input buffer full!" );
		cleanbuffer( buffer );
	}
	buffer[front] = c;
	front++;
}

void menuInit( char *buffer ) {
	cleanbuffer( buffer );
	CLS;	/* Clear screen */
	POS( MENU_ROW, MENU_COL ); /* Position cursor */
	PRINT( "****************************" ); /* Note there is no \n */
	POS( MENU_ROW + 1, MENU_COL );	/* Go down next line */
	PRINT( "CS 452 Menu Acceptable Commands" ); /* Align under * */
	POS( MENU_ROW + 2, MENU_COL );  /* Next line */
	PRINT( "1/ tr train_number train_speed");
	POS( MENU_ROW + 3, MENU_COL );  /* Next line */
	PRINT( "2/ rv train_number");
	POS( MENU_ROW + 4, MENU_COL );  /* Next line */
	PRINT( "3/ sw switch_number switch_direction");
	POS( MENU_ROW + 5, MENU_COL ); /* Next line */
	PRINT( "4/ q");
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

void menuHistory( char *buffer ) {
	POS( MENU_INPUT_ROW - 1, 0 );
	PRINT( "=> %s", buffer );
}

void menuParse( char *buffer, char c ) {
	if( c == '\r' ) { /* If the enter key was pressed, we figure out what is in the buffer */
		CLLINE;
		POS( MENU_INPUT_ROW - 1, 0 );
		CLLINE;
		PRINT( "%s", buffer ); /* TODO: Actually tokenize the buffer, for now just print it */
		cleanbuffer( buffer );
		POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
	}

	PRINT( "%c", c );
	bufferAdd( buffer, c );
}

