#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
  DDRC = 0b11111111;
  Serial.begin(2000000);
  
  while(true){
    int var = 0b11110000;
    int var1 = 0b00000000;
    PORTC = 0b10101010;

    int result1 = var || PORTC;
    Serial.println(result1);
    _delay_ms(2500);

    int result2 = var && PORTC;
    Serial.println(result2);
    _delay_ms(2500);

    int result3 = var1 && PORTC;
    Serial.println(result3);
    _delay_ms(2500);

    int result4 = !(PORTC);
    Serial.println(result4);
    _delay_ms(2500);

    int result5 = !(var1);
    Serial.println(result5);
    _delay_ms(2500);
  }
}
