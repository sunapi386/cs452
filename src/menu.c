#include <menu.h>
#include <trains.h>

unsigned int front = 0; /* TODO: This global variable is probably bad */

void menuDraw() {
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
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

/* Moves cursor to line 4 and prints a prompt */
void menuLine() {
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
	CLLINE;
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

static void menuHistory( char *buffer ) {
	CLLINE;
	POS( MENU_INPUT_ROW - 1, 0 );
	CLLINE;
	PRINT( "%80s", buffer ); /* %80s prevent buffer overflow */
}

static void menuHistory3( buffer_t *b1, buffer_t *b2, buffer_t *b3 ) {
	CLLINE;
	POS( MENU_INPUT_ROW - 1, 0 );
	CLLINE;
	PRINT( "[%s:%s:%s]", b1->elements, b2->elements, b3->elements ); /* %80s prevent buffer overflow */
}

// void menuParse( char *buffer, char c ) {
// 	/* This function is called because the enter key was pressed; we parse the buffer */
// 	menuHistory( buffer );
// 	/* Here we need to parse the buffer */
// 	if( buffer[0] == 't' && buffer[1] == 'r' ) {
// 		int train_number, train_speed;
// 		/* Handles tr train_number train_speed */
// 	    CLLINE;
// 	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
// 	    CLLINE;
// 	    PRINT( "tr %d %d", train_number, train_speed );
// 	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
// 	    termprintf( COM1, "%c", 97 );
// 	}
// 	else
// 	if( buffer[0] == 'r' && buffer[1] == 'v' ) {
// 		int train_number;
// 		/* Handles rv train_number */
// 	    CLLINE;
// 	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
// 	    CLLINE;
// 	    PRINT( "rv %d", train_number );
// 	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
// 	    termprintf( COM1, "S50" );
// 	}
// 	else
// 	if( buffer[0] == 's' && buffer[1] == 'w' ) {
// 		int switch_number, switch_direction;
// 		/* Handles sw switch_number switch_direction */
// 		// a2i( , &buffer );
// 	    CLLINE;
// 	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
// 	    CLLINE;
// 	    PRINT( "sw %d %c", switch_number, switch_direction );
// 	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
// 	    termprintf( COM1, "%c", 96 );
// 	}
// 	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
// }

int c2d( char ch ) {
	if( ch >= '0' && ch <= '9' ) return ch - '0';
	if( ch >= 'a' && ch <= 'f' ) return ch - 'a' + 10;
	if( ch >= 'A' && ch <= 'F' ) return ch - 'A' + 10;
	return -1;
}

int a2i( char *b ) {
	int num, digit;
	num = 0;
	while( ( digit = c2d( *b++ ) ) >= 0 ) {
		if ( digit > 10 ) break;
		num = num*10 + digit;
	}
	return num;
}
/*
void trainsSet( unsigned int train_num, unsigned int train_speed );
void trainsReverse( unsigned int train_num );
void trainsSwitch( unsigned int switch_num, char switch_direction );
void trainsSwitchInit();

*/
void menuInput( buffer_t *b1, buffer_t *b2, buffer_t *b3 ) {
	menuHistory3( b1, b2, b3 );
	int i1, i2, i3;
	i1 = a2i( b1->elements ); i2 = a2i( b2->elements ); i3 = a2i( b3->elements );

	if( b1->elements[0] == 't' && b1->elements[1] == 'r' ) {
		int train_number, train_speed;
		train_number = i2;
		train_speed = i3;
		trainsSet( train_number, train_speed );
		/* Handles tr train_number train_speed */
	    CLLINE;
	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
	    CLLINE;
	    PRINT( "[CMD] tr %d %d", train_number, train_speed );
	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
		termprintf( COM1, "%c", 97 );
	}
	else
	if( b1->elements[0] == 'r' && b1->elements[1] == 'v' ) {
		int train_number;
		train_number = i2;
		trainsReverse( train_number );
		/* Handles rv train_number */
	    CLLINE;
	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
	    CLLINE;
	    PRINT( "[CMD] rv %d", train_number );
	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
	    termprintf( COM1, "S50" );
	}
	else
	if( b1->elements[0] == 's' && b1->elements[1] == 'w' ) {
		int switch_number;
		char switch_direction;
		switch_number = i2;
		switch_direction = (char)*(b3->elements);
		trainsSwitch( switch_number, switch_direction );
		/* Handles sw switch_number switch_direction */
	    CLLINE;
	    POS( MENU_INPUT_ROW - 1, MENU_INPUT_COL );
	    CLLINE;
	    PRINT( "[CMD] sw %d %c", switch_number, switch_direction );
	    POS( MENU_INPUT_ROW, MENU_INPUT_COL );
	    termprintf( COM1, "%c", 96 );
	}
	POS( MENU_INPUT_ROW, MENU_INPUT_COL ); /* Park the cursor */
}

