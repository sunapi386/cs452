#ifndef __TRAINS_H
#define __TRAINS_H
#include <termio.h>

/* Handles controlling of the trains
* https://www.marklin.com/tech/digital1/components/commands.html
*/

    /* Serial communication */
#define TRAIN_COMSPEED  2400
#define TRAIN_SEND( ... )   termprintf( COM1, __VA_ARGS__ )
#define TRAIN_GETC          termgetc( COM1 )
#define TRAIN_SENSOR_BUFSIZ 10

#define TRAIN_GO        96
#define TRAIN_STOP      97
#define TRAIN_REVERSE   15

    /* Switching */
#define TRAIN_NUM_SWITCHES   0x9d
#define TRAIN_SOLENOID_OFF TRAIN_SEND( "%c", 32 )
/* If a number of turnouts are called in sequence, then each command will automatically
* turn off the turnout called previously, which means that only the last one needs to be turned off.
*/
#define TRAIN_SWITCH_STRAIGHT 33
#define TRAIN_SWITCH_CURVED 34
/* Switching take a two byte command, directions and address. Addresses are 1-256.
*/
#define TRAIN_SENSOR_STATUS_COL 2
#define TRAIN_SENSOR_STATUS_ROW 16

void trainsInit();
void trainsQuit();
void trainsSensorPoll();
void trainsSet( unsigned int train_num, unsigned int train_speed );
void trainsReverse( unsigned int train_num );
void trainsSwitch( unsigned int switch_num, char switch_direction );
void trainsSwitchInit();
void trainsDrawSwitches();

#endif // __TRAINS_H
