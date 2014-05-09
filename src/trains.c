#include <trains.h>
#include <termio.h>


void trainsInit() {
	termsetspeed( COM1, 2400 );
	termsetfifo( COM1, OFF );
}

void trainsLight( int on_off ) {
 	termprintf( COM1, "%c", LIGHT_ADDR );
}

