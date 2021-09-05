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
    for(int i = 0; i < 5; i++){
      PORTC = ~(1 << (i));
      for(int j = 0; j < 5; j++){
        PORTB = 1 << (j);
        _delay_ms(50);
      }
    }
  }
}
