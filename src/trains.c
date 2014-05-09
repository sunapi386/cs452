#include <trains.h>
#include <termio.h>
#include <screen.h>

void trainsInit() {
    termsetspeed( COM1, 2400 );
    termsetfifo( COM1, OFF );
}

void trainsLight( int on_off ) {
    termprintf( COM1, "%c", LIGHT_ADDR );
}

void trainsStop() {
    termprintf( COM1, "%c", 97 );
    screenTrains( "Train stop" );
}

void trainsGo() {
    termprintf( COM1, "%c", 96 );
    screenTrains( "Trains go" );
}

void trainsSendCmd( int cmd, int tid ) {
    termprintf( COM1, "%c%c", cmd, tid );
    screenTrains( "Issued %u to train %u", cmd, tid );
}
