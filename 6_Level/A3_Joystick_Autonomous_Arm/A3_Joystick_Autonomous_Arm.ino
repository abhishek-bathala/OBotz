#include <obotz_level6_servo_motor.h>
#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//base servo - up down joystick
//stepper motor - left right joystick
//pick up drop - joystick press

//servo variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int base1 = 0;
int base2 = 0;

int c = 0;
int d = 0;
int pressed = 0;

void compare(int x, int y)
{
  if(y > 800){ //up
    base1 += 5;
    angle1(base1);
    base2 -= 5;
    angle2(base2);
  }
  else if(y < 100){ //down
    base1 -= 5;
    angle1(base1);
    base2 += 5;
    angle2(base2);
  }
  if(x > 800){ //left
    c++;
    antistepper();
  }
  else if(x < 100){ //right
    d++;
    clkstepper();
  }
  if(PINB & 0x01){
    pressed++;
  }
  if(pressed == 1){
    angle3(0);
  }
  else if (pressed == 2){
    angle3(60);
    pressed = 0;
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRA = 0x00;
  DDRD = 0xFF;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  int x = 0;
  int y = 0;
  
  while(true)
  {
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }
    
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);
    compare(x, y);
    _delay_ms(100);
  }
}
