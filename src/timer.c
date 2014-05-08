#include <ts7200.h>
#include <timer.h>
/* Timer functions. See Cirrus Logic page 427 for timers register map */

// /* Resets timers */
// int resetTimers() {
// 	int *timer1load = (int *)(TIMER1_LOAD);
// }



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

int checkAndUpdateClock() {
	return 0;
}

/* Get clock time */
int getClock() {
	return 0;
}
