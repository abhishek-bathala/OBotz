#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main(void)
{
  DDRB = 0xFF;
  DDRD = 0x00;

  while(true){
    if (checkbit(PIND, bit(2)) || checkbit(PIND, bit(3))){
      PORTB = 0xFF;
    }
    else{
      PORTB = 0x00;
    }
  }
}
