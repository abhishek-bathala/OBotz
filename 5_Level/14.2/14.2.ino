#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  DDRD = 0x00;
  DDRC = 0xFF;
  DDRB = 0xFF;
  
  while (true){
    if(checkbit(PIND, bit(2))){
      PORTC = 0x01;
      PORTB = 0x10;
    }
    else if(checkbit(PIND, bit(3))){
      PORTC = 0x02;
      PORTB = 0x00;
    }
    else{
      PORTC = 0x00;
      PORTB = 0x00;
    }
  }
}
