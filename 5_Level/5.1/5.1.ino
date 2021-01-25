#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
  DDRC = 0b11111111;
  Serial.begin(2000000);
  PORTC = 0b10101010;
  
  while(true){
    int result1 = PORTC<<1;
    Serial.println(result1, BIN);
    _delay_ms(5000);

    int result2 = PORTC<<2;
    Serial.println(result2,BIN);
    _delay_ms(5000);

    int result3 = PORTC>>2;
    Serial.println(result3, BIN);
    _delay_ms(5000);
  }
}
