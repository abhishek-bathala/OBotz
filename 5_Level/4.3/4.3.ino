#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
  DDRC = 0b11111111;
  Serial.begin(2000000);
  int var1 = 0b00100000;
  
  while(true){
    int result = ~var1;
    Serial.println(result, BIN);
    _delay_ms(5000);
  }
}
