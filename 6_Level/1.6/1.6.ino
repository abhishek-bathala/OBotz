#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

  int count = 0;
  DDRD = 0x01;
  TCCR1A = 0x00;
  TCCR1B = 0x04; //0x04 means we are using prescaler 256

  while(true){
    if(TCNT1 == 62){ //this value is ~62 because 249/4 since the prescaler is 4 times slower
      count++;
      TCNT1 = 0;
    }
    if (count == 1000){
      PORTD ^= 0x01;
      count = 0;
    }
  }
}
