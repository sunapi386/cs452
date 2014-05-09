#ifndef __TRAINS_H
#define __TRAINS_H
#include <termio.h>

/* Handles controlling of the trains */

#define LIGHT_ADDR 96

void trainsInit();

void trainsLight( int on_off );

void trainsStop();

void trainsGo();

void trainsSendCmd( int cmd, int tid );

#endif // __TRAINS_H
