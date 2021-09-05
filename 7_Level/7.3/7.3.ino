#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
  Serial.begin(2000000);
  DDRB = 0xFF;
  DDRC = 0xFF;
  PORTB = 0xFF;
  PORTC = 0x00;
  int i = 0;
  int j = 0;
  while(true){
    while(i < 5){
      PORTC = 1 << (i);
      j = 0;
      while(j < 5){
        PORTB = ~(1 << (j));
        _delay_ms(50);
        j++;
      }
      i++;
    }

    if(i == 5){
      i = 0;
    }
    if(j == 5){
      j = 0;
    }
  }
}
