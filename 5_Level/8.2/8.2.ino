#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y)(x|=y)
#define clearbit(x,y)(x&=~y)
#define bitn(p)(0x01<<p)

int main (void)
{
  setbit(DDRD, 0xFF);
  int i = 0;

  for (i = 0; i < 5; i-=-1){
    setbit(PORTD, bit(0));
    _delay_ms(500);
    clearbit(PORTD, bit(0));
    _delay_ms(500);
  }

  for (i = 5; i > 0; i--){
    setbit(PORTD, bit(1));
    _delay_ms(500);
    clearbit(PORTD, bit(1));
    _delay_ms(500);
  }
}
