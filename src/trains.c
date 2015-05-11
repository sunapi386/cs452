#include <trains.h>
#include <termio.h>
#include <bool.h>
char switches[TRAIN_NUM_SWITCHES] = {'*'};
char sensorbuf[TRAIN_SENSOR_BUFSIZ + 1] = {'*'}; // Hardcoded 10 bytes
unsigned sensorcount = 0, last_poll_time = 0;
bool pollbusy = false, switch_changed = true;

void trainsInit() {
    sensorcount = 0;
    last_poll_time = 0;
    TRAIN_SEND( "%c", TRAIN_GO );
    int i;
    for( i = 0; i < TRAIN_NUM_SWITCHES; ++i ) {
        switches[i] = '.';
    }
    for( i = 0; i < TRAIN_SENSOR_BUFSIZ + 1; ++i ) {
        sensorbuf[i] = '.';
    }
    SAVECURSOR;
    POS( TRAIN_SENSOR_STATUS_ROW - 2, TRAIN_SENSOR_STATUS_COL );
    PRINT( ".......SWITCHES......." );
    POS( TRAIN_SENSOR_STATUS_ROW - 1, TRAIN_SENSOR_STATUS_COL );
    LOADCURSOR;
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
    switches[switch_num] = switch_direction;
    switch_changed = true;
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
    else if( pollbusy && last_poll_time > 1500 ) {
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
    // PRINT( "switches: [%c]", switches );
    // POS( TRAIN_SENSOR_STATUS_ROW + 1, TRAIN_SENSOR_STATUS_COL );
    // PRINT( "sensorbuf: [%c]", sensorbuf );
    // LOADCURSOR;
}

void trainsSwitchInit() { /* Hardcoded */
    unsigned int i;
    for( i = 0; i < 19; ++i ) {
        trainsSwitch( i, 'S' );
        trainsSwitch( i, 'C' );
        switches[i] = 'C';
    }
    /* Special handling of middle tracks to avoid CC position: x99 x9a x9b x9c */
    trainsSwitch( 0x99, 'C' );
    switches[0x99] = 'C';
    trainsSwitch( 0x9c, 'C' );
    switches[0x9c] = 'C';

    trainsSwitch( 0x9a, 'S' );
    switches[0x9a] = 'S';
    trainsSwitch( 0x9b, 'S' );
    switches[0x9b] = 'S';

    TRAIN_SOLENOID_OFF;
}

static inline void drawSwitches() {
    SAVECURSOR;
    int i;
    for(i = 0; i < 10; i++ ) {
        POS( TRAIN_SENSOR_STATUS_ROW + i, TRAIN_SENSOR_STATUS_COL );
        PRINT( "[%d %c]", i, switches[i] );
    }

    for(i = 11; i < 19; i++ ) {
        POS( TRAIN_SENSOR_STATUS_ROW + i - 11, TRAIN_SENSOR_STATUS_COL + 6 );
        PRINT( "[%d %c]", i, switches[i] );
    }

    POS( TRAIN_SENSOR_STATUS_ROW + 0, TRAIN_SENSOR_STATUS_COL + 13 );
    PRINT( "[%d %c]", 0x99, switches[0x99] );
    POS( TRAIN_SENSOR_STATUS_ROW + 1, TRAIN_SENSOR_STATUS_COL + 13 );
    PRINT( "[%d %c]", 0x9a, switches[0x9a] );
    POS( TRAIN_SENSOR_STATUS_ROW + 2, TRAIN_SENSOR_STATUS_COL + 13 );
    PRINT( "[%d %c]", 0x9b, switches[0x9b] );
    POS( TRAIN_SENSOR_STATUS_ROW + 3, TRAIN_SENSOR_STATUS_COL + 13 );
    PRINT( "[%d %c]", 0x9c, switches[0x9c] );
    LOADCURSOR;
}

void trainsDrawSwitches() {
    if(switch_changed) { /* Only redraw when there is a change */
        /* Display the poll data */
        drawSwitches();
        switch_changed = false;
    }
}
