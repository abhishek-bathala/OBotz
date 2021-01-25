#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  DDRD = 0xF0;
  
  while(true){
    if(checkbit(PIND, bitn(2)) || checkbit(PIND, bitn(3))){
      PORTD = 0x10;
    }
    else{
      PORTD = 0x00;
    }
  }
}
