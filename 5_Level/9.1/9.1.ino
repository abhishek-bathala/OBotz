#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  DDRD = 0xFB;

  while(true){
    if (PIND & 0x04){
      setbit(PORTD, bit(0));
      _delay_ms(200);
    }

    clearbit(PORTD, bit(0));
  }
}
