#include <avr/io.h>
#include <util/delay.h>
#define PERIOD 62.5  //macro period set to 62.5ms for 20 RPM
int main(void)
{
  DDRD = 0xF0;  //PD4-PD7 output
  int i = 0;
  
  while(true){
    for(i = 0; i < 12; i++){ //looping 12 times
      PORTD = 0b11100000; //anticlockwise one step
      _delay_ms(PERIOD); //wait 500ms
      PORTD = 0b11010000;
      _delay_ms(PERIOD);
      PORTD = 0b10110000;
      _delay_ms(PERIOD);
      PORTD = 0b01110000;
      _delay_ms(PERIOD);
    }

    for(i = 0; i < 12; i++){
      PORTD = 0b01110000;
      _delay_ms(PERIOD);  //clockwise one step
      PORTD = 0b10110000; //wait 500ms
      _delay_ms(PERIOD);
      PORTD = 0b11010000;
      _delay_ms(PERIOD);
      PORTD = 0b11100000;
      _delay_ms(PERIOD);
    }
  }
}
