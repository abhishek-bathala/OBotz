#include <avr/io.h>
#include <util/delay.h>
#define PERIOD 50 //macro period anticlockwise set to 125ms for 50 RPM
#define angle 90 //we want motor to turn 90 degrees
int main(void)
{
  DDRD = 0xF0;  //PD4-PD7 output
  int count = 0;
  int pulses = angle/7.5;
  
  while(count < pulses){
      PORTD = 0b11100000; //anticlockwise one step
      _delay_ms(PERIOD); //wait 500ms
      PORTD = 0b11010000;
      _delay_ms(PERIOD);
      PORTD = 0b10110000;
      _delay_ms(PERIOD);
      PORTD = 0b01110000;
      _delay_ms(PERIOD);
      count += 4;
  }
}
