/*
 * termio.c - non-busy-wait I/O
 *
 * Specific to the TS-7200 ARM evaluation board
 *
 */

#include <ts7200.h>
#include <termio.h>

char bufferCOM1[BUFSIZ], bufferCOM2[BUFSIZ];
int frontCOM1 = 0, backCOM1 = 0, countCOM1 = 0, frontCOM2 = 0, backCOM2 = 0, countCOM2 = 0;

/*
 * The UARTs are initialized by RedBoot to the following state
 * 	115,200 bps
 * 	8 bits
 * 	no parity
 * 	fifos enabled
 */

/* Checks if there are data to send and ready */
int termcheckandsend( int channel ) {
	int *flags, *data;
	switch( channel ) {
	case COM1:
		if( countCOM1 == 0 || ( *flags & TXFF_MASK ) ) {
			return 0;  		/* Can't send right now */
		}
		flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );
		data = (int *)( UART1_BASE + UART_DATA_OFFSET );
		*data = bufferCOM1[frontCOM1];
		frontCOM1 = (frontCOM1 + 1) % BUFSIZ;
		countCOM1 -= 1;
		break;
	case COM2:
		if( countCOM2 == 0 || ( *flags & TXFF_MASK ) ) {
			return 0;  		/* Can't send right now */
		}
		flags = (int *)( UART2_BASE + UART_FLAG_OFFSET );
		data = (int *)( UART2_BASE + UART_DATA_OFFSET );
		*data = bufferCOM2[frontCOM2];
		frontCOM2 = (frontCOM2 + 1) % BUFSIZ;
		countCOM2 -= 1;
		break;
	default:
		return -1;
	}
	return 0;
}

int termsetfifo( int channel, int state ) {
	int *line, buf;
	switch( channel ) {
	case COM1:
		line = (int *)( UART1_BASE + UART_LCRH_OFFSET );
	        break;
	case COM2:
	        line = (int *)( UART2_BASE + UART_LCRH_OFFSET );
	        break;
	default:
	        return -1;
	        break;
	}
	buf = *line;
	buf = state ? buf | FEN_MASK : buf & ~FEN_MASK;
	*line = buf;
	return 0;
}

int termsetspeed( int channel, int speed ) {
	int *high, *low;
	switch( channel ) {
	case COM1:
		high = (int *)( UART1_BASE + UART_LCRM_OFFSET );
		low = (int *)( UART1_BASE + UART_LCRL_OFFSET );
	        break;
	case COM2:
		high = (int *)( UART2_BASE + UART_LCRM_OFFSET );
		low = (int *)( UART2_BASE + UART_LCRL_OFFSET );
	        break;
	default:
	        return -1;
	        break;
	}
	switch( speed ) {
	case 115200:	/* Bug here, need a fix!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		*high = 0x0;
		*low = 0x3;
		return 0;
	case 2400:
		*high = 0x0;
		*low = 0xbf; // should be this 0xbf.
		return 0;
	default:
		return -1;
	}
}

int termputc( int channel, char c ) { /* Adds a character in the buffer for sending */
	switch( channel ) {
		case COM1:
			if( countCOM1 == BUFSIZ ) { /* Sending failed*/
				return -1;
			}
			bufferCOM1[backCOM1] = c;
			backCOM1 = (backCOM1 + 1) % BUFSIZ;
			countCOM1 += 1;
			break;
		case COM2:
			if( countCOM2 == BUFSIZ ) { /* Sending failed*/
				return -1;
			}
			bufferCOM2[backCOM2] = c;
			backCOM2 = (backCOM2 + 1) % BUFSIZ;
			countCOM2 += 1;
		default:
			return -1;
	}
	return 0;
}

char c2x( char ch ) {
	if ( (ch <= 9) ) return '0' + ch;
	return 'a' + ch - 10;
}

int termputx( int channel, char c ) {
	char chh, chl;

	chh = c2x( c / 16 );
	chl = c2x( c % 16 );
	termputc( channel, chh );
	return termputc( channel, chl );
}

int termputr( int channel, unsigned int reg ) {
	int byte;
	char *ch = (char *) &reg;

	for( byte = 3; byte >= 0; byte-- ) termputx( channel, ch[byte] );
	return termputc( channel, ' ' );
}

int termputstr( int channel, char *str ) {
	while( *str ) {
		if( termputc( channel, *str ) < 0 ) return -1;
		str++;
	}
	return 0;
}

void termputw( int channel, int n, char fc, char *bf ) {
	char ch;
	char *p = bf;

	while( *p++ && n > 0 ) n--;
	while( n-- > 0 ) termputc( channel, fc );
	while( ( ch = *bf++ ) ) termputc( channel, ch );
}

int termgetc( int channel ) { /* This still does busy-waiting! */
	int *flags, *data;
	unsigned char c;

	switch( channel ) {
	case COM1:
		flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );
		data = (int *)( UART1_BASE + UART_DATA_OFFSET );
		break;
	case COM2:
		flags = (int *)( UART2_BASE + UART_FLAG_OFFSET );
		data = (int *)( UART2_BASE + UART_DATA_OFFSET );
		break;
	default:
		return -1;
		break;
	}
	while ( !( *flags & RXFF_MASK ) ) ;
	c = *data;
	return c;
}

int terma2d( char ch ) {
	if( ch >= '0' && ch <= '9' ) return ch - '0';
	if( ch >= 'a' && ch <= 'f' ) return ch - 'a' + 10;
	if( ch >= 'A' && ch <= 'F' ) return ch - 'A' + 10;
	return -1;
}

char terma2i( char ch, char **src, int base, int *nump ) {
	int num, digit;
	char *p;

	p = *src; num = 0;
	while( ( digit = terma2d( ch ) ) >= 0 ) {
		if ( digit > base ) break;
		num = num*base + digit;
		ch = *p++;
	}
	*src = p; *nump = num;
	return ch;
}

void termui2a( unsigned int num, unsigned int base, char *bf ) {
	int n = 0;
	int dgt;
	unsigned int d = 1;

	while( (num / d) >= base ) d *= base;
	while( d != 0 ) {
		dgt = num / d;
		num %= d;
		d /= base;
		if( n || dgt > 0 || d == 0 ) {
			*bf++ = dgt + ( dgt < 10 ? '0' : 'a' - 10 );
			++n;
		}
	}
	*bf = 0;
}

void termi2a( int num, char *bf ) {
	if( num < 0 ) {
		num = -num;
		*bf++ = '-';
	}
	termui2a( num, 10, bf );
}

void termformat ( int channel, char *fmt, va_list va ) {
	char bf[12];
	char ch, lz;
	int w;


	while ( ( ch = *(fmt++) ) ) {
		if ( ch != '%' )
			termputc( channel, ch );
		else {
			lz = 0; w = 0;
			ch = *(fmt++);
			switch ( ch ) {
			case '0':
				lz = 1; ch = *(fmt++);
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ch = terma2i( ch, &fmt, 10, &w );
				break;
			}
			switch( ch ) {
			case 0: return;
			case 'c':
				termputc( channel, va_arg( va, char ) );
				break;
			case 's':
				termputw( channel, w, 0, va_arg( va, char* ) );
				break;
			case 'u':
				termui2a( va_arg( va, unsigned int ), 10, bf );
				termputw( channel, w, lz, bf );
				break;
			case 'd':
				termi2a( va_arg( va, int ), bf );
				termputw( channel, w, lz, bf );
				break;
			case 'x':
				termui2a( va_arg( va, unsigned int ), 16, bf );
				termputw( channel, w, lz, bf );
				break;
			case '%':
				termputc( channel, ch );
				break;
			}
		}
	}
}

void termprintf( int channel, char *fmt, ... ) {
        va_list va;

        va_start(va,fmt);
        termformat( channel, fmt, va );
        va_end(va);
}
