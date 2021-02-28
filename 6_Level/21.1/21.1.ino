#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3};
int data = 0;

void compare()
{
  if(data > 0 && data < 10){
    PORTC = num[0];
  }
  if(data > 10 && data < 20){
    PORTC = num[0];
  }
  if(data > 20 && data < 30){
    PORTC = num[0];
  }
  if(data > 30 && data < 40){
    PORTC = num[0];
  }
  if(data > 40 && data < 50){
    PORTC = num[0];
  }
  if(data > 50 && data < 60){
    PORTC = num[0];
  }
  if(data > 60 && data < 70){
    PORTC = num[0];
  }
  if(data > 70 && data < 80){
    PORTC = num[0];
  }
  if(data > 80 && data < 90){
    PORTC = num[0];
  }
  if(data > 100){
    PORTC = num[0];
  }
}

ISR(ADC_vect)
{
  data = ADCW;
  compare();
}

int main(void)
{
  DDRC = 0xFF;
  SREG = 0x80;

  while(true)
  {
    ADMUX = 0x41;
    ADCSRA = 0xCF;
    _delay_ms(500);
    
  }
}
