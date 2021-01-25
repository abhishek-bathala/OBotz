#ifndef OBOTZ_LEVEL6_STEPPER_MOTOR_H
#define OBOTZ_LEVEL6_STEPPER_MOTOR_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//stepper motor variables
extern int c;
extern int d;

void clkstepper();
void antistepper();

#endif
