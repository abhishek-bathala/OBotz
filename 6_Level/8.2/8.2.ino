#include <avr/io.h>
#include <util/delay.h>
#define PERIOD 50 //macro period anticlockwise set to 125ms for 50 RPM
#define angle 90 //we want motor to turn 90 degrees
int main(void)
{
  DDRD = 0xF0;  //PD4-PD7 output
  DDRB = 0x00;  //PORTD as input
  int c, d = 0;
  
  while(true){
    void clkstepper()
    {
      if(d==1){PORTD = 0b01110000;}
      if(d==2){PORTD = 0b10110000;}
      if(d==3){PORTD = 0b11010000;}
      if(d==4){PORTD = 0b11100000;}
    }

    void antistepper()
    {
      if(d==1){
        PORTD = 0b11100000;
      }
      if(d==2){
        PORTD = 0b11010000;
      }
      if(d==3){
        PORTD = 0b10110000;
      }
      if(d==4){
        PORTD = 0b11100000;
      }
    }
    }
    
    for(count = 0; count < pulses; count = count+4){
        PORTD = 0b11100000; //anticlockwise one step
        _delay_ms(PERIOD); //wait 500ms
        PORTD = 0b11010000;
        _delay_ms(PERIOD);
        PORTD = 0b10110000;
        _delay_ms(PERIOD);
        PORTD = 0b01110000;
        _delay_ms(PERIOD);
    }
    _delay_ms(500);
  }
}
