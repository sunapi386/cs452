#include <ts7200.h>
#include <timer.h>
#include <termio.h>
/* Timer functions. See Cirrus Logic page 427 for timers register map */

// /* Resets timers */
// int resetTimers() {
// 	int *timer1load = (int *)(TIMER1_LOAD);
// }

unsigned int tsec = 0, sec = 0, min = 0, last_time = 0, now = 0;

/* Sets the timer to desired value */
int setTimer( int timer, int desired ) {
	int *timerload, *timerctl;
	switch( timer ) {
		case 1: timerload = (int *)(TIMER1_LOAD); timerctl = (int *)(TIMER1_CONTROL); break;
		case 2: timerload = (int *)(TIMER2_LOAD); timerctl = (int *)(TIMER2_CONTROL); break;
		case 3: timerload = (int *)(TIMER3_LOAD); timerctl = (int *)(TIMER3_CONTROL); break;
		default:  return -1;
	}
	*timerload = desired;
	*timerctl = ENABLE_MASK;
	return 0;
}

/* Get time from timer */
int getTimer( int timer ) {
	int *timerval;
	switch( timer ) {
		case 1: timerval = (int *)(TIMER1_VALUE); break;
		case 2: timerval = (int *)(TIMER2_VALUE); break;
		case 3: timerval = (int *)(TIMER3_VALUE); break;
		default:  return 1337;
	}
	return *timerval;
}

int initClock() {
	setTimer( 3, 0 );
	tsec = sec = min = 0;
	return 0;
}

/* Get clock time */
int doClock() {
	now = getTimer(3) / 200;
    if( now != last_time ) {
        last_time = now;
        tsec += 1;
	    termprintf( COM2, "%c[%d;%dH", 27, 0, 0);
	    termprintf( COM2, "%u:%u.%u\n\r", min, sec % 60, tsec % 10 );
	    termprintf( COM2, "%c[%d;%dH", 27, 3, 0); /* return where curser was */
        if( tsec % 10 == 0 ) {
            sec += 1;
            if( sec % 60 == 0 ) {
            	min += 1;
            }
        }
    }
    return 0;
}
