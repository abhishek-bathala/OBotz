#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
  DDRD = 0x00;
  DDRB = 0xFF;
  int count = 0;

  while (true){
    if (PIND & 0x04){
      count++;
      _delay_ms(500);
    }

    if (count == 1){
      PORTB = 0x10;
    }
    else if (count == 2){
      PORTB = 0x00;
    }
    else{
      count = 1;
    }
  }
}
