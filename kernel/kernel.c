 /*
 * digiclock.c
 * a digital clock showing minutes, seconds, and tenths of seconds,
 * which measures time intervals accurately, in the sense that it does not
 * slow down or lose ticks
 */

#include <bwio.h>
#include <ts7200.h>

// Prints a menu and returns user's choice. Returns -1 if bad choice.
int getusrcmd( int channel ) {
	char menu[] = "Menu.
	1. Train track state
	2. Clock
	3. Hello world
	Enter a number:\n\r";
	bwputstr( channel, menu );
	menu[0] = bwgetc( channel );
	// bwprintf( channel, "You entered '%s'\n\r", menu[0] );
	int ret = atoi( menu[0] );
	return (ret > 0 && ret < 4)? ret : -1;
}

int main( int argc, char* argv[] ) {
	char str[] = "Jason Train Menu.\n\r";
	bwsetfifo( COM2, OFF );
	bwputstr( COM2, str );
	int choice = getusrcmd( COM2 );
	// bwprintf( COM2, "%s", str );
	bwprintf( COM2, "You entered '%s'\n\r", menu[0] );
	return 0;
}

