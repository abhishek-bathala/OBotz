#include <avr/io.h>
#include <avr/interrupt.h>

int count0, count1, count2, count3;
int main(void)
{
  DDRD = 0xFF;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x0B;
  TIMSK0 = 0x06;
  OCR0A = 249;
  OCR0B = 249;
  TCCR2A = 0x00;
  TCCR2B = 0x0B;
  TIMSK2 = 0x06;
  OCR2A = 249;
  OCR2B = 249;
  
  while(true){
  }
}

ISR(TIMER0_COMPA_vect)
{
  count0++;
  if(count0 == 200){ 
    PORTD ^= 0x01;
    count0 = 0;
  }
}

ISR(TIMER0_COMPB_vect){
  count1++;
  if(count1 == 400){
    PORTD ^= 0x02;
    count1 = 0;
  }
}

ISR(TIMER2_COMPA_vect)
{
  count2++;
  if(count2 == 600){
    PORTD ^= 0x04;
    count1 = 0;
  }
}

ISR(TIMER2_COMPB_vect)
{
  count3++;
  if(count3 == 100){
    PORTD ^= 0x08;
    count3 = 0;
  }
}
