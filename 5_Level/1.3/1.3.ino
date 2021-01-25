#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRC = 0b11111111;

    while(true){
        PORTC = 0b00000001;
        _delay_ms(1000);
        PORTC = 0b00000000;
        _delay_ms(1000);
    }
}
