#ifndef __SCREEN_H
#define __SCREEN_H

/* Menu is responsible for doing any sorts of output to the terminal
*  and general user interface stuff.
+-------------------------------------------------------------------+
| Sensor Data                     |  Track Switch States            |
|---------------------------------+---------------------------------|
| 1  :         13 :               |                                 |
| 2  :         14 :               |                                 |
| 3  :         15 :               |                                 |
| 4  :         16 :               |                                 |
| 5  :         17 :               |                                 |
| 6  :         18 :               |                                 |
| 7  :       0x99 :               |                                 |
| 8  :       0x9A :               |                                 |
| 9  :       0x9B :               |                                 |
| 10 :       0x9C :               |                                 |
| 11 :                            |                                 |
|                                 |                                 |
|-------------------------------------------------------------------|
| Jason Sun's CS 452 Controller   | Clock                           |
|-------------------------------------------------------------------|
|                                                                   |
| $                                                                 |
|-------------------------------------------------------------------|
| Commands: tr                                                      |
| q         sw                                                      |
+-------------------------------------------------------------------+
*/

#include <termio.h>


#define SCREEN_BEGIN_ROW  0
#define SCREEN_BEGIN_COL  0

#define SCREEN_SENSR_ROW 4
#define SCREEN_SENSR_COL 3

#define SCREEN_TRACK_ROW 4
#define SCREEN_TRACK_COL 37

#define SCREEN_CLOCK_ROW 17
#define SCREEN_CLOCK_COL 43

#define SCREEN_INPUT_ROW 20
#define SCREEN_INPUT_COL 5

#define SCREEN_PREVC_ROW 19
#define SCREEN_PREVC_COL 5


void screenInit();
void screenClearInputLine();
void screenMenu();
// void screenHistory();
int screenAdd( char c );
void screenParse();
void screenUpdateHistory();
void screenClearInputLine();
void screenPrintClock( int min, int sec, int tsec );
void screenTrains( char *msg, ... );
void screenQuit();

/* Train stuff */

#endif // __SCREEN_H
