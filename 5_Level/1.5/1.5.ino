#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRC = 0xFF;
    DDRB = 0xFF;

    while(true){
        PORTC = 0x01;
        PORTB = 0x20;
        _delay_ms(1000);
        PORTC = 0x00;
        PORTB = 0x00;
        _delay_ms(1000);
    }
}
