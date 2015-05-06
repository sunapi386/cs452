#include <trains.h>
#include <termio.h>
#include <screen.h>


char switchStates[TRAIN_BUFFER_SIZE] = {'\0'};
char sensorbuf[TRAIN_SENSOR_BUFSIZ + 1] = {'\0'}; // Hardcoded 10 bytes
unsigned sensorcount = 0;

void trainsInit() {
    sensorcount = 0;
    termsetfifo( COM1, OFF );
    termsetspeed( COM1, TRAIN_COMSPEED );
    TRAIN_SEND( "%c", TRAIN_GO );
    int i;
    for( i = 0; i < TRAIN_BUFFER_SIZE; ++i ) {
        switchStates[i] = '\0';
    }
    for( i = 0; i < TRAIN_SENSOR_BUFSIZ + 1; ++i ) {
        sensorbuf[i] = '\0';
    }
    /* Hardcoding happens below. I read specific addresses. */
    TRAIN_SEND( "%c", 192 ); // reset memory
}

void trainsQuit() {
    TRAIN_SEND( "%c", TRAIN_STOP );
}

void trainsSet( unsigned int train_num, unsigned int train_speed ) {
    TRAIN_SEND( "%c%c", train_speed, train_num );
    screenTrains( "Set train %u speed %u", train_num, train_speed );
}

void trainsReverse( unsigned int train_num ) {
    TRAIN_SEND( "%c%c", TRAIN_REVERSE, train_num );
    screenTrains( "Reverse train %u. Speed again to move.", train_num );
    /* Give it a speed again to go */
}

void trainsSwitch( unsigned int switch_num, char switch_direction ) {
    char direction;
    if( switch_direction == 'S' || switch_direction == 's' ) {
        direction = TRAIN_SWITCH_STRAIGHT;
        PRINT( "Switch %u direction S", switch_num, direction );
    }
    else if( switch_direction == 'C' || switch_direction == 'c' ) {
        direction = TRAIN_SWITCH_CURVED;
        PRINT( "Switch %u direction C", switch_num, direction );
    }
    else {
        screenTrains( "Invalid direction %c", switch_direction );
    }
    TRAIN_SEND( "%c%c", direction, switch_num );
    PRINT( "Switch %u direction %u", switch_num, direction );
    TRAIN_SOLENOID_OFF;
}

/* Each sensor stores 2 bytes. To read sensor they must be told to dump their memory.
*  Two options for requesting this dump: read one, read many.
*  In read one, send 192 + num_of_unit_to_read
*   Not finished
*  In read many, 128 + num_of_last_unit_to_read
*   the option is get all sensors to dump memor up to a specific unit.
*  The trains lab has 5 modules.
*  The program needs to receive this data.
*/
void trainsSensorPoll() { // Polls until 10 bytes are available and then restarts
    if( sensorcount == TRAIN_SENSOR_BUFSIZ + 1 ) { /* Reinitialize */
        int i;
        for( i = 0; i < TRAIN_SENSOR_BUFSIZ; ++i ) {
            PRINT( "c%c", sensorbuf[i] );
        }
        for( i = 0; i < TRAIN_SENSOR_BUFSIZ + 1; ++i ) {
            sensorbuf[i] = '\0';
        }
        TRAIN_SEND( "%c", 128 + 5 ); // Hardcoded
    }
    char c = TRAIN_GETC;
    if( c != 0 ) { // A valid poll, then add result
        sensorbuf[sensorcount] = c;
        sensorcount += 1;
        PRINT( "g%c", c );
    }
}

void trainsSwitchInit() { /* Hardcoded */
    unsigned int sw;
    char dir = 'C';
    for( sw = 0; sw < 19; ++sw ) {
        TRAIN_SEND( "%c%c", dir, sw );
        PRINT( "Switch %u dir %c", sw, dir );
    }
    // TRAIN_SEND( "%c%c", 0x99, dir );
    // PRINT( "Switch %u dir %c", switch_num, dir );
    // TRAIN_SEND( "%c%c", 0x9a, dir );
    // PRINT( "Switch %u dir %c", switch_num, dir );
    // TRAIN_SEND( "%c%c", 0x9b, dir );
    // PRINT( "Switch %u dir %c", switch_num, dir );
    // TRAIN_SEND( "%c%c", 0x9c, dir );
    // PRINT( "Switch %u dir %c", switch_num, dir );
    TRAIN_SOLENOID_OFF;
}
