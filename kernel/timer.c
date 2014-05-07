#include <ts7200.h>
#include <timer.h>
/* Timer functions. See Cirrus Logic page 427 for timers register map */

// /* Resets timers */
// int resetTimers() {
// 	int *timer1load = (int *)(TIMER1_LOAD);
// }

/* Sets the timer to desired value */
int setTimer( int timer, int desired ) {
	int *timerload;
	switch( timer ) {
		case 1: timerload = (int *)(TIMER1_LOAD);
		case 2: timerload = (int *)(TIMER2_LOAD);
		case 3: timerload = (int *)(TIMER3_LOAD);
		default:  return -1;
	}
	*timerload = desired;
	*(timerload + 0x8) = ENABLE_MASK;
	return 0;
}

/* Get time from timer */
int getTimer( int timer ) {
	int *timerval;
	switch( timer ) {
		case 1: timerval = (int *)(TIMER1_VALUE);
		case 2: timerval = (int *)(TIMER2_VALUE);
		case 3: timerval = (int *)(TIMER3_VALUE);
		default:  return -1;
	}
	return *timerval;
}

/* Get clock time */
int getClock();