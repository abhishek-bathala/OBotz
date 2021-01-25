#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  //using timer/counter 1
  int count = 0;
  DDRD = 0x01;
  TCCR1A = 0x00;
  TCCR1B = 0x05; //0x05 means we are using prescaler 1024

  while(true){
    if(TCNT1 == 249){
      count++;
      TCNT1 = 0;
    }
    if (count == 62){ //this value is 62 because 1000/16 prescaler 1024 is 16 times slower
      PORTD ^= 0x01;
      count = 0;
    }
  }
}
