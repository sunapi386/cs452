#include <trains.h>
#include <termio.h>
#include <screen.h>

void trainsInit() {
    termsetspeed( COM1, 2400 );
    termsetfifo( COM1, OFF );
}

void trainsSet( unsigned int train_num, unsigned int train_speed ) {
    termprintf( COM1, "%c%c", TRAIN_GO );
    screenTrains( "Set train %u speed %u", train_num, train_speed );
}

void trainsReverse( unsigned int train_num ) {
    termprintf( COM1, "%c", TRAIN_GO );
    screenTrains( "Reverse train %u", train_num );
}

void trainsSwitch( unsigned int switch_num, char switch_direction ) {
    termprintf( COM1, "%c", TRAIN_GO );
    screenTrains( "Switch %u direction %c", switch_num, switch_direction );
}


