#ifndef __MENU_H
#define __MENU_H
#include <termio.h>
#define MENU_ROW    2
#define MENU_COL    0
#define MENU_INPUT_ROW 10
#define MENU_INPUT_COL 5

void menuInit();
void menuLine();
void menuCls();

#endif // __MENU_H
