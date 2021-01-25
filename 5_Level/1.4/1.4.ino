#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRC = 0b11111111;
    DDRB = 0b11111111;

    while(true){
        PORTC = 0b00000001;
        PORTB = 0b00100000;
        _delay_ms(1000);
        PORTC = 0b00000000;
        PORTB = 0b00000000;
        _delay_ms(1000);
    }
}
