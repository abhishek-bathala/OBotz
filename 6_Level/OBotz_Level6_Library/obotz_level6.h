#ifndef OBOTZ_LEVEL6_H
#define OBOTZ_LEVEL6_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//ir variables
extern long keycode;
extern int pressed;

//stepper motor variables
extern int c;
extern int d;
extern int base;
extern int elbow;
extern int finger;

//servo variables
extern int count;
extern int count_angle1;
extern int count_angle2;
extern int count_angle3;

//timer variables
extern int timervalue;
extern int bitposition;
extern int var;


void angle1 (int a);
void angle2 (int a);
void angle3 (int a);

ISR (TIMER1_COMPA_vect);

ISR (TIMER0_OVF_vect);

ISR (INT2_vect);
extern void compare();

void clkstepper();
void antistepper();

#endif
