#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  DDRD = 0xFB;

  while(true){
    if (checkbit(PIND, bitn(2))){
      PORTD = 0x01;
      _delay_ms(200);
    }

    PORTD = 0x00;
  }
}
