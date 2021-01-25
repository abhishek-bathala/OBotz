#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
  DDRC = 0b11111111;
  Serial.begin(2000000);
  
  while(true){
    int var1 = 0b00100000;
    PORTC = 0b10101010;

    int result = !(var1);
    Serial.println(result);
    _delay_ms(2500);
  }
}
