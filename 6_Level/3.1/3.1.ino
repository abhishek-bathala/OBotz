#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRD = 0x01;
  while(true){
    PORTD = 0x00;
    waitms(500);
    PORTD = 0x01;
    waitms(200);
  }
}

void waitms(int a)
{
  int count = 0;
  TCCR0A = 0x00;
  TCCR0B = 0x03;
  while(count != a){
    if(TCNT0 == 249){
      count++;
      TCNT0 = 0;
    }
  }
}
