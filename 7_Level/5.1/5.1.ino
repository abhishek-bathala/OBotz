#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
  DDRB = 0xFF;
  DDRC = 0xFF;
  PORTB = 0xFF;
  PORTC = 0x00;
  while(true){
    PORTC = 0x01;
    PORTB = 0xFE;
    _delay_ms(1000);
    PORTB = 0xFD;
    _delay_ms(1000);
    PORTB = 0xFB;
    _delay_ms(1000);
    PORTB = 0xF7;
    _delay_ms(1000);
    PORTB = 0xEF;
    _delay_ms(1000);
  }
}
