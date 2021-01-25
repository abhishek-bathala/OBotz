#ifndef OBOTZ_LEVEL6_IR_REMOTE_H
#define OBOTZ_LEVEL6_IR_REMOTE_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//ir variables
extern long keycode;
extern int pressed;

//timer variables
extern int timervalue;
extern int bitposition;
extern int var;

ISR (TIMER0_OVF_vect);

ISR (INT2_vect);
extern void compare();

#endif
