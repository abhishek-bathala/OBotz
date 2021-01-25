#include "obotz_level6_servo_motor.h"

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
