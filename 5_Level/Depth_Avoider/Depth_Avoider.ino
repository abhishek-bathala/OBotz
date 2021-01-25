#include <avr/io.h>
#include <util/delay.h>

#define LEFT_IR_THRESHOLD    500
#define RIGHT_IR_THRESHOLD   500

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))


#define ROBOT_FORWARD() ((PORTD) = 0x60)
#define ROBOT_REVERSE() ((PORTD) = 0x90)
#define ROBOT_RIGHT()   ((PORTD) = 0x40)
#define ROBOT_LEFT()    ((PORTD) = 0x20)


int main (void)
{
  int left_ir = 0;
  int right_ir = 0;
  DDRD = 0x00;
  
  while (true) {
    //checking and storing right ir sensor
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      left_ir = ADCW;
    }

    //checking and storing left ir sensor
    ADMUX = 0x41;
    ADCSRA = 0xC7;
    
    while(CHECK_BIT(ADCSRA, ADSC)){
      right_ir = ADCW;
    }

    if((right_ir > RIGHT_IR_THRESHOLD) && (left_ir > LEFT_IR_THRESHOLD)){
      ROBOT_REVERSE();
    }
    else if((right_ir > RIGHT_IR_THRESHOLD) && (left_ir < LEFT_IR_THRESHOLD)) {
      ROBOT_RIGHT();
    }
    else if((right_ir < RIGHT_IR_THRESHOLD) && (left_ir > LEFT_IR_THRESHOLD)){
      ROBOT_LEFT();
    }
    else {
      ROBOT_FORWARD();
    }
  }
}


