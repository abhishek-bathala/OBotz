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
    PORTB = 0xFD;
    _delay_ms(10);
    PORTC = 0x10;
    PORTB = 0xFB;
    _delay_ms(10);
    
  }
}
