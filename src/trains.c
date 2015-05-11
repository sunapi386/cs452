#include <trains.h>
#include <termio.h>
#include <bool.h>
char switchStates[TRAIN_BUFFER_SIZE] = {'*'};
char sensorbuf[TRAIN_SENSOR_BUFSIZ + 1] = {'*'}; // Hardcoded 10 bytes
unsigned sensorcount = 0, last_poll_time = 0;
bool pollbusy = false;

void trainsInit() {
    sensorcount = 0;
    last_poll_time = 0;
    TRAIN_SEND( "%c", TRAIN_GO );
    int i;
    for( i = 0; i < TRAIN_BUFFER_SIZE; ++i ) {
        switchStates[i] = '.';
    }
    for( i = 0; i < TRAIN_SENSOR_BUFSIZ + 1; ++i ) {
        sensorbuf[i] = '.';
    }
}

void trainsQuit() {
    TRAIN_SEND( "%c", TRAIN_STOP );
}

void trainsSet( unsigned int train_num, unsigned int train_speed ) {
    // TRAIN_SEND( "%c%c", train_speed, train_num );
    termprintf( COM1, "%c%c", (char)train_speed, (char)train_num );
}

void trainsReverse( unsigned int train_num ) {
    TRAIN_SEND( "%c%c", TRAIN_REVERSE, train_num );
    /* Give it a speed again to go */
}

void trainsSwitch( unsigned int switch_num, char switch_direction ) {
    char direction;
    if( switch_direction == 'S' || switch_direction == 's' ) {
        direction = TRAIN_SWITCH_STRAIGHT;
        // PRINT( "Switch %u direction S", switch_num, direction );
    }
    else if( switch_direction == 'C' || switch_direction == 'c' ) {
        direction = TRAIN_SWITCH_CURVED;
        // PRINT( "Switch %u direction C", switch_num, direction );
    }
    else {
    }
    TRAIN_SEND( "%c%c", direction, switch_num );
    // PRINT( "Switch %u direction %u", switch_num, direction );
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
    TRAIN_SEND( "%c", 192 ); // reset memory

*/
void trainsSensorPoll() { // Polls until 10 bytes are available and then restarts
    if( ! pollbusy && sensorcount == TRAIN_SENSOR_BUFSIZ + 1 ) {
        int i;
        /* Reinitialize */
        for( i = 0; i < TRAIN_SENSOR_BUFSIZ; ++i ) {
            PRINT( "c%c", sensorbuf[i] );
        }
        for( i = 0; i < TRAIN_SENSOR_BUFSIZ + 1; ++i ) {
            sensorbuf[i] = '\0';
        }
        TRAIN_SEND( "%c", 128 + 5 ); // Hardcoded
        pollbusy = true;
        last_poll_time = 0;
    }
    else if( pollbusy && last_poll_time > 5000 ) {
        char c = TRAIN_GETC; // this is probably too soon for the train to respond to
        if( c != 0 ) { // A valid poll, then add result
            // sensorbuf[sensorcount] = c;
            // sensorcount += 1;
            // PRINT( "g%c", c );
            pollbusy = false;
            last_poll_time = 0;
        }
    }

    /* Display the poll data */
    // SAVECURSOR;
    // POS( TRAIN_SENSOR_STATUS_ROW, TRAIN_SENSOR_STATUS_COL );
    // PRINT( "switchStates: [%c]", switchStates );
    // POS( TRAIN_SENSOR_STATUS_ROW + 1, TRAIN_SENSOR_STATUS_COL );
    // PRINT( "sensorbuf: [%c]", sensorbuf );
    // LOADCURSOR;
}

void trainsSwitchInit() { /* Hardcoded */
    unsigned int i;
    for( i = 0; i < 19; ++i ) {
        trainsSwitch( i, 'S' );
    }
    for( i = 0; i < 19; ++i ) {
        trainsSwitch( i, 'C' );
    }
    /* Special handling of middle tracks to avoid CC position */

    // TRAIN_SEND( "%c%c", 0x99, dir );
    // PRINT( "Switch %x dir %c", 0x99, dir );
    // TRAIN_SEND( "%c%c", 0x9c, dir );
    // PRINT( "Switch %x dir %c", 0x9c, dir );
    // dir = 'S';
    // TRAIN_SEND( "%c%c", 0x9a, dir );
    // PRINT( "Switch %x dir %c", 0x9a, dir );
    // TRAIN_SEND( "%c%c", 0x9b, dir );
    // PRINT( "Switch %x dir %c", 0x9b, dir );
    TRAIN_SOLENOID_OFF;
}
