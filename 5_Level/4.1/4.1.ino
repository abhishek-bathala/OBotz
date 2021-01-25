#include <avr/io.h>
#include <util/delay.h>

int main (void){
    DDRC = 0b11111111;
    Serial.begin(2000000);
    int var = 0b11110000;
    PORTC = 0b10101010;
    
    while(true){
        int result1 = var | PORTC;
        Serial.println(result1, BIN);
        _delay_ms(2500);

        int result2 = var & PORTC;
        Serial.println(result2, BIN);
        _delay_ms(2500);

        int result3 = ~(PORTC);
        Serial.println(result3, BIN);
        _delay_ms(2500);

        int result4 = var ^ PORTC;
        Serial.println(result4, BIN);
        _delay_ms(2500);

        
    }
}
