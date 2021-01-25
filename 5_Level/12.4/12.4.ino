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
    if (checkbit(PIND, bitn(3))){
      count++;
      _delay_ms(500);
    }

    if (count == 1){
      setbit(PORTB, bitn(5));
    }
    else if (count == 2){
      setbit(PORTB, bitn(6));
    }
    else if (count == 3){
      clearbit(PORTB, bitn(5));
    }
    else if (count == 4){
      clearbit(PORTB, bitn(6));
    }
    else if (count == 5){
      count = 1;
    }
  }
}
