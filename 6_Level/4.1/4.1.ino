#include <avr/io.h>
#include <avr/interrupt.h>

int count0 = 0;
int count2 = 0;
int main(void)
{
  DDRD = 0x0F;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x0B;
  TIMSK0 = 0x06;
  OCR0A = 249;
  OCR0B = 249;
  PORTD = 0x09;
  
  while(true){
  }
}

ISR(TIMER0_COMPA_vect)
{
  count0++;
  if(count0 == 250){
    PORTD ^= 0x0C;
    count0 = 0;
  }
}

ISR(TIMER0_COMPB_vect)
{
  count2++;
  if(count2 == 1000){
    PORTD ^= 0x03;
    count2 = 0;
  }
}
