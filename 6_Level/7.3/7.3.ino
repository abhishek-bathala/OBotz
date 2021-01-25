#include <avr/io.h>
#include <util/delay.h>
#define PERIODAC 125  //macro period anticlockwise set to 125ms for 50 RPM
#define PERIODC 25 //macro period clockwise set to 25ms for 10 RPM
int main(void)
{
  DDRD = 0xF0;  //PD4-PD7 output
  int i = 0;
  
  while(true){
    for(i = 0; i < 12; i++){ //looping 12 times
      PORTD = 0b11100000; //anticlockwise one step
      _delay_ms(PERIODC); //wait 500ms
      PORTD = 0b11010000;
      _delay_ms(PERIODC);
      PORTD = 0b10110000;
      _delay_ms(PERIODC);
      PORTD = 0b01110000;
      _delay_ms(PERIODC);
    }

    for(i = 0; i < 12; i++){
      PORTD = 0b01110000;
      _delay_ms(PERIODAC);  //clockwise one step
      PORTD = 0b10110000; //wait 500ms
      _delay_ms(PERIODAC);
      PORTD = 0b11010000;
      _delay_ms(PERIODAC);
      PORTD = 0b11100000;
      _delay_ms(PERIODAC);
    }
  }
}
