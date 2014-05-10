#ifndef __TRAINS_H
#define __TRAINS_H
#include <termio.h>

/* Handles controlling of the trains */

#define TRAIN_GO 96
#define TRAIN_STOP 97

void trainsInit();
void trainsSet( unsigned int train_num, unsigned int train_speed );
void trainsReverse( unsigned int train_num );
void trainsSwitch( unsigned int switch_num, char switch_direction );

#endif // __TRAINS_H
