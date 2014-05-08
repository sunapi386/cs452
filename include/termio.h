#ifndef __TERMIO_H
#define __TERMIO_H
/*
 * termio.h - like bwio.h but with buffering
 */

#define BUFSIZ 100

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

int termcheckandsend( int channel );

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
