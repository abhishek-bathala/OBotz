#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3};

int main(void)
{
  DDRC = 0xFF;

  while(true)
  {
    PORTC = num[3];
    _delay_ms(500);
    PORTC = num[4];
    _delay_ms(500);
    PORTC = num[3];
    _delay_ms(500);
    PORTC = 0x01;
    _delay_ms(500);
    PORTC = num[2];
    _delay_ms(500);
    PORTC = num[0];
    _delay_ms(500);
    PORTC = num[2];
    _delay_ms(500);
    PORTC = 0x01;
    _delay_ms(500);
    PORTC = num[5];
    _delay_ms(500);
    PORTC = num[1];
    _delay_ms(500);
    PORTC = 0x00;
    _delay_ms(50);
    PORTC = num[1];
    _delay_ms(500);
    PORTC = num[2];
    _delay_ms(500);
  }
}
