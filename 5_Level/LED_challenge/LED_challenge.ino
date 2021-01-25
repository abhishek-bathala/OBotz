#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  DDRD = 0xF3;

  while (true){
    if (checkbit(PIND, bit(2))){
      setbit(PORTD, bit(0));
    }
    if (checkbit(PIND, bit(3))){
      clearbit(PORTD, bit(0));
    }
  }
}
