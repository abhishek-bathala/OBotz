#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    int count = 0;
    Serial.begin(2000000);
    while(true){
        Serial.println(count);
        _delay_ms(1000);
        count += 2;
    }
}
