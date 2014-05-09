#ifndef __MENU_H
#define __MENU_H
#include <termio.h>
#define MENU_ROW    3
#define MENU_COL    0
#define MENU_INPUT_ROW 8
#define MENU_INPUT_COL 3

void menuInit();
void menuLine();
void menuCls();

#endif // __MENU_H
