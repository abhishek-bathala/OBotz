#include <avr/io.h>
#include <avr/interrupt.h>

int count0 = 0;
int count2 = 0;
int main(void)
{
  DDRD = 0x0F;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x0C; //prescaler 256
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
  if(count0 == 50){ //200ms/4 is 50
    PORTD ^= 0x0C;
    count0 = 0;
  }
}

ISR(TIMER0_COMPB_vect)
{
  count2++;
  if(count2 == 250){ //1000/4 = 250 because prescaler 256 is 4 times slower than p64
    PORTD ^= 0x03;
    count2 = 0;
  }
}
