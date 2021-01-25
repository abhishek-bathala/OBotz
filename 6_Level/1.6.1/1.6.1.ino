#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  //using timer/counter 1
  int count = 0;
  DDRD = 0x01;
  TCCR1A = 0x00;
  TCCR1B = 0x02; //0x02 means we are using prescaler 8

  while(true){
    if(TCNT1 == 1992){ //this value is ~1992 because 249*4 since prescaler is 4 times faster
      count++;
      TCNT1 = 0;
    }
    if (count == 1000){
      PORTD ^= 0x01;
      count = 0;
    }
  }
}
