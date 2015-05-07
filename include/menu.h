#ifndef __MENU_H
#define __MENU_H
#include <termio.h>
#define MENU_ROW    2
#define MENU_COL    0
#define MENU_INPUT_ROW 10
#define MENU_INPUT_COL 0

void menuInit();
void menuLine();
void menuHistory();
void menuParse( char *buffer, char c );

#endif // __MENU_H
