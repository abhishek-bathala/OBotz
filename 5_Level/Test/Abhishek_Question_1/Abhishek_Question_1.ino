#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  DDRD = 0xFF;
  DDRB = 0xFF;

  while(true){
    PORTB = 0x60;
    _delay_ms(200);
    _delay_ms(200);
    PORTB = 0x00;
    _delay_ms(200);
    _delay_ms(200);
  }
}
