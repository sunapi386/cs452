#ifndef __TIMER_H
#define __TIMER_H
/* Timer functions. See Cirrus Logic page 427 for timers register map */
#include <ts7200.h>

#define TIMER1_LOAD		TIMER1_BASE			// Initial value of timer (R/W)
#define TIMER1_VALUE 	(TIMER1_BASE + 0x4) // Current value of the timer (R)
#define TIMER1_CONTROL 	(TIMER1_BASE + 0x8) // Configuration modes
#define TIMER1_CLEAR 	(TIMER1_BASE + 0xC) // Writing any value clears an interrupt

#define TIMER2_LOAD		TIMER2_BASE
#define TIMER2_VALUE 	(TIMER2_BASE + 0x4)
#define TIMER2_CONTROL 	(TIMER2_BASE + 0x8)

#define TIMER3_LOAD		TIMER3_BASE
#define TIMER3_VALUE 	(TIMER3_BASE + 0x4)
#define TIMER3_CONTROL 	(TIMER3_BASE + 0x8)

// extern static unsigned int time;

/* Resets timers */
// int resetTimer();

/* Sets the timer to desired */
int setTimer( int timer, int desired );

/* Get time from timer */
int getTimer( int timer );

/* Get clock time */
int getClock();
#endif // __TIMER_H