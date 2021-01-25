#include "obotz_level6.h"

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))


void angle1(int a) //base servo
{
  count_angle1 = a + 46;
}

void angle2 (int a) //elbow servo
{
  count_angle2 = a + 46;
}

void angle3 (int a)//claw servo
{
  count_angle3 = a + 46;
}

ISR (TIMER1_COMPA_vect)
{
  count++;
  if(count <=count_angle1){
    SET_BIT(PORTB, 5);
  }
  else if ((count > count_angle1) && (count < 1818)){
    CLEAR_BIT(PORTB, 5);
  }
  else if(count >= 1818){
    count = 0;
  }
  if (count <= count_angle2){
    SET_BIT(PORTB, 6);
  }
  else if ((count > count_angle2) && (count < 1818)){
    CLEAR_BIT(PORTB, 6);
  }
  else if(count >= 1818){
    count = 0;
  }
  if (count <= count_angle3){
    SET_BIT(PORTB, 7);
  }
  else if ((count > count_angle3) && (count < 1818)){
    CLEAR_BIT(PORTB, 7);
  }
  else if(count >= 1818){
    count = 0;
  }
}

ISR(TIMER0_OVF_vect)
{
  var++;
  TCNT0 = 125;
}


ISR(INT2_vect)
{
  timervalue = var;
  var = 0;
  bitposition++;
  if (timervalue >= 100) {
    bitposition = -2;
    keycode = 0;
  }
  if ((bitposition >= 0) && (bitposition < 32)) {
    if (timervalue > 3) {
      keycode |= (long)1<<(31 - bitposition);
    }
  }
  else if (bitposition >= 32) {
    bitposition = 0;
    compare();
  }
}

void clkstepper() //stepper motor clockwise
{
  if(d==1){
    PORTD = 0b01110000;
    }
  if(d==2){
    PORTD = 0b10110000;
    }
  if(d==3){
    PORTD = 0b11010000;
    }
  if(d==4){
    PORTD = 0b11100000;
    d = 0;
  }
}

void antistepper()  //stepper motor anticlockwise
{
  if(c==1){
    PORTD = 0b11100000;
    }
  if(c==2){
    PORTD = 0b11010000;
    }
  if(c==3){
    PORTD = 0b10110000;
    }
  if(c==4){
    PORTD = 0b11100000;
    c = 0;
  }
}