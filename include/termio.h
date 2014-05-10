#ifndef __TERMIO_H
#define __TERMIO_H
/*
 * termio.h - like bwio.h but with buffering. Handles communication.
 */


#define BUFSIZ 		2048
#define ESC         27
#define CLS             termprintf( COM2, "%c[2J", ESC )
#define CLLINE			termprintf( COM2, "%c[2K", ESC )
#define CLTOEND			termprintf( COM2, "%c[0K", ESC )
#define POS(row,col)    termprintf( COM2, "%c[%d;%dH", ESC, row, col )
#define PRINT( ... )    termprintf( COM2, __VA_ARGS__ )
#define SAVECURSOR		termprintf( COM2, "%c7", ESC )
#define LOADCURSOR		termprintf( COM2, "%c8", ESC )
#define STATUS_X	10
#define STATUS_Y	1

typedef char *va_list;

#define __va_argsiz(t)	\
		(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(ap, pN) ((ap) = ((va_list) __builtin_next_arg(pN)))

#define va_end(ap)	((void)0)

#define va_arg(ap, t)	\
		 (((ap) = (ap) + __va_argsiz(t)), *((t*) (void*) ((ap) - __va_argsiz(t))))

#define COM1	0
#define COM2	1

#define ON	1
#define	OFF	0

void terminit();

int termcheckandsend();

void termflush(); /* Finishes sending buffers */

int termatoi( char* str ); /* A simple atoi() function */

int termsetfifo( int channel, int state );

int termsetspeed( int channel, int speed );

int termputc( int channel, char c );

int termgetc( int channel );

int termputx( int channel, char c );

int termputstr( int channel, char *str );

int termputr( int channel, unsigned int reg );

void termputw( int channel, int n, char fc, char *bf );

void termprintf( int channel, char *format, ... );


#endif
