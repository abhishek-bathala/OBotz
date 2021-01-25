#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  int y = 0;
  DDRD = 0xFF;
  
  while(true){
    ADMUX  = 0x46;
    ADCSRA = 0xC7;
    if(checkbit(ADCSRA, bitn(ADSC))){
      y = ADCW;
    }
    
    if(y < 370){
      PORTD = 0x03;
    }
    if(y > 300){
      PORTD = 0x00;
    }
  }
}
