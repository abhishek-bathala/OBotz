#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

void robot_forward()
{
  PORTD = 0x60;
}

void robot_reverse()
{
  PORTD = 0x90;
}

void robot_right()
{
  PORTD = 0x40;
}

void robot_left()
{
  PORTD = 0x20;
}

int main (void)
{
  int lir = 0; //left ir
  int rir = 0; //right ir
  DDRD = 0x00;
  
  while(true){
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(checkbit(ADCSRA, bitn(ADSC))){
      lir = ADCW;
    }
    ADMUX = 0x41;
    ADCSRA = 0xC7;
    while(checkbit(ADCSRA, bitn(ADSC))){
      rir = ADCW;
    }

    if(rir < 500 && lir < 500){
      robot_reverse();
    }
    else if(rir > 500 && lir < 500){
      robot_left();
    }
    else if(rir < 500 && lir > 500){
      robot_right();
    }
    else{
      robot_forward();
    }
  }
}
