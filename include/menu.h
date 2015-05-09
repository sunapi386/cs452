#ifndef __MENU_H
#define __MENU_H
#include <termio.h>
#include <buffer.h>
#define MENU_ROW    2
#define MENU_COL    0
#define MENU_INPUT_ROW 10
#define MENU_INPUT_COL 0

void menuDraw();
void menuLine();
// void menuParse( char *buffer, char c );
void menuInput( buffer_t *b1, buffer_t *b2, buffer_t *b3 );

#endif // __MENU_H
