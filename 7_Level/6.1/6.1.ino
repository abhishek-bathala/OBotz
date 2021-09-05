#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
  Serial.begin(2000000);
  DDRB = 0xFF;
  DDRC = 0xFF;
  PORTB = 0xFF;
  PORTC = 0x00;
  while(true){
    PORTC = 0x01;
    PORTB = 0xFE;
    _delay_ms(1);
    for(int i = 0; i < 5; i++){
      //Serial.println(PORTC, BIN);
      PORTC = PORTC << 1;
      //Serial.println(PORTB, BIN);
      PORTB = ~(PORTC);
      _delay_ms(1);
    }
  }
}
