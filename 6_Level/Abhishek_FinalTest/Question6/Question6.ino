//Abhishek Question 6
#include <obotz_level6_servo_motor.h> //My own library for servo motor functions
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//bluetooth data
char data;
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int servo2 = 90;
int servo1 = 90;
int x, y;

int main(void)
{
  DDRA = 0x00; //setting joystick pins to input
  DDRD = 0xFF; 
  DDRB = 0xFF;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  Serial.begin(2000000);
  while (true) {
    //getting y axis value for joystick
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }
    //getting x axis value for joystick
    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }

    if(y > 700){ //if joystick is up
      Serial.println("up");
      angle1(180);
      angle2(0);
    }
    else if(x < 100)
    {
      Serial.println("right");
      angle1(0);
      angle2(180);
    }

    /*Serial.print("x: ");
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);*/
    _delay_ms(100);
  }
}
