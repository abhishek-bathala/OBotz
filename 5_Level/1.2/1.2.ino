#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRD = 0b11111111;

    while(true){
        PORTD = 0b00000010;
        _delay_ms(1000);
        PORTD = 0b00000000;
        _delay_ms(300);
    }
}
