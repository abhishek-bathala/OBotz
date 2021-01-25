#include <avr/io.h>
#include <avr/interrupt.h>

int count0 = 0;
int count1 = 0;
int main(void)
{
  DDRD = 0xFF;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x03;
  TIMSK0 = 0x01;
  TCNT0 = 200;
  TCNT2 = 100;
  TCCR2A = 0x00;
  TCCR2B = 0x03;
  TIMSK2 = 0x01;
  
  while(true){
  }
}

ISR(TIMER0_OVF_vect)
{
  count0++;
  if(count0 == 2000){ //200ms/4 is 50
    PORTD ^= 0x01;
    count0 = 0;
  }
  TCNT0 = 200;
}

ISR(TIMER2_OVF_vect){
  count1++;
  if(count1 == 2000){
    PORTD ^= 0x02;
    count1 = 0;
  }
  TCNT2 = 100;
}
