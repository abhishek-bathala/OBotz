#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  DDRD = 0x00;
  DDRB = 0xFF;
  int count = 0;

  while (true){
    if (checkbit(PIND, bit(3))){
      count++;
      _delay_ms(500);
    }

    if (count == 1){
      setbit(PORTB, bit(7));
    }
    else if (count == 2){
      clearbit(PORTB, bit(7));
    }
    else{
      count = 1;
    }
  }
}
