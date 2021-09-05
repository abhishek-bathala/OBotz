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
    PORTC = 0x01;
    PORTB = 0xF9;
    _delay_ms(1);
    PORTC = 0x02;
    PORTB = 0xF6;
    _delay_ms(1);
    PORTC = 0x04;
    PORTB = 0xED;
    _delay_ms(1);
    PORTC = 0x08;
    PORTB = 0xF6;
    _delay_ms(1);
    PORTC = 0x10;
    PORTB = 0xF9;
    _delay_ms(1);
  }
}
