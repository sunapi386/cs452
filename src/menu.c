#include <menu.h>
#include <termio.h>


void menuInit() {
	CLS;	/* Clear screen */
	POS( MENU_ROW, MENU_COL ); /* Position cursor */
	PRINT( "************************" ); /* Note there is no \n */
	POS( MENU_ROW + 1, MENU_COL );	/* Go down next line */
	PRINT( "CS 452 Train Control Menu" ); /* Align under * */
	POS( MENU_ROW + 2, MENU_COL );  /* Next line */
	PRINT( "Quit (q)");
	POS( MENU_ROW + 3, MENU_COL ); /* Next line */
	PRINT("************************\n\r");
}

/* Moves cursor to line 4 and prints a prompt */
void menuLine() {
	POS( MENU_INPUT_ROW, MENU_INPUT_COL - 3 ); /* Go back and print the >>> */
	PRINT( ">>>" );
	POS( MENU_INPUT_ROW, MENU_INPUT_COL + 1 ); /* Park the cursor */
}

void menuCls() {
	CLS;
}
