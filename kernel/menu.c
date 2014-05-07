#include <bwio.h>

// Prints a menu and returns user's choice. Returns -1 if bad choice.
char getusrcmd( int channel ) {
	char menu[] = "Menu.\n\r1. Train track state\n\r2. Clock\n\r3. Hello world\n\rEnter a number:\n\r";
	bwputstr( channel, menu );
	menu[0] = bwgetc( channel );
	bwprintf( channel, "You entered '%s'\n\r", menu[0] );
	return menu[0];
}


// Prints a menu and returns user's choice. Returns -1 if bad choice.
// char getusrcmd( int channel ) {
//     char menu[] = "Menu.\n\r1. Train track state\n\r2. Clock\n\r3. Hello world\n\rEnter a number:\n\r";
//     bwputstr( channel, menu );
//     menu[0] = bwgetc( channel );
//     bwprintf( channel, "You entered '%s'\n\r", menu[0] );
//     return menu[0];
// }