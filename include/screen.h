#ifndef __SCREEN_H
#define __SCREEN_H

/* Menu is responsible for doing any sorts of output to the terminal
*  and general user interface stuff.
*/

#include <termio.h>

#define SCREEN_ROW    1
#define SCREEN_COL    0
#define SCREEN_INPUT_ROW 12
#define SCREEN_INPUT_COL 0
#define SCREEN_TRAIN_ACTION_ROW 10
#define SCREEN_TRAIN_ACTION_COL 2

void screenInit();
void screenLine();
void screenMenu();
// void screenHistory();
int screenAdd( char c );
void screenParse();
/* Prints the ... variable args to PRINT( ... ) in the desired location */
void screenTrains( char *msg, ... );

/* Train stuff */

#endif // __SCREEN_H
