#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y)(x|=y)
#define clearbit(x,y)(x&=~y)
#define bitn(p)(0x01<<(p))

int main (void)
{
  setbit(DDRD, 0xFF);
  setbit(DDRB, bitn(4));

  while(true)
  {
    setbit(PORTD, bitn(0));
    _delay_ms(1000);
    clearbit(PORTD, bitn(0));
    setbit(PORTD, bitn(1));
    _delay_ms(1000);
    clearbit(PORTD, bitn(1));
    setbit(PORTB, bitn(4));
    _delay_ms(1000);
    clearbit(PORTB, bitn(4));
  }
}
