#include <obotz_level6_servo_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int base = 0;

boolean num1 = false;
boolean num2 = false;
boolean num3 = false;
boolean num4 = false;
char digit;
long result, average;

void compare()
{
  if(average >= 585 && average <= 595){
    PORTC = num[0];
    digit = '0';
  }
  if(average >= 512 && average <= 522){
    PORTC = num[1];
    digit = '1';
    if(num2 == false && num3 == false && num4 == false){
      num1 = true;
    }
  }
  if(average >= 683 && average <= 693){
    PORTC = num[2];
    digit = '2';
    if(num1 == true){
      num2 = true;
    }
    else{
      num2 = false;
    }
  }
  if(average >= 763 && average <= 773){
    PORTC = num[3];
    digit = '3';
    if(num2 == true){
      num3 = true;
    }
    else{
      num3 = false;
    }
  }
  if(average >= 481 && average <= 491){
    PORTC = num[4];
    digit = '4';
    if(num3 == true){
      num4 = true;
    }
    else{
      num4 = false;
    }
  }
  if(average >= 631 && average <= 641){
    PORTC = num[5];
    digit = '5';
  }
  if(average >= 700 && average <= 710){
    PORTC = num[6];
    digit = '6';
  }
  if(average >= 466 && average <= 476){
    PORTC = num[7];
    digit = '7';
  }
  if(average >= 605 && average <= 615){
    PORTC = num[8];
    digit = '8';
  }
  if(average >= 668 && average <= 678){
    PORTC = num[9];
    digit = '9';
  }
  if(average >= 0 && average <= 3){
    PORTC = 0x00;
    digit = ' ';
  }

  if(num1 == true && num2 == true && num3 == true && num4 == true){
    base = 90;
    _delay_ms(500);
    base = 0;
    num1 = false;
    num2 = false;
    num3 = false;
    num4 = false;
  }
}

int main(void)
{
  Serial.begin(2000000);
  PORTD = 0x00;
  DDRB = 0xFF;
  DDRC = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  while (true) {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    
  }
}
