#ifndef OBOTZ_LEVEL6_SERVO_MOTOR_H
#define OBOTZ_LEVEL6_SERVO_MOTOR_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//servo variables
extern int count;
extern int count_angle1;
extern int count_angle2;
extern int count_angle3;

void angle1 (int a);
void angle2 (int a);
void angle3 (int a);

ISR (TIMER1_COMPA_vect);

#endif
