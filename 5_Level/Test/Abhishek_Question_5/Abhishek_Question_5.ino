#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  DDRC = 0x08;
  TCCR0 = 0x6B;
  OCR0 = 0;
  
  while(true){
     if(checkbit(PIND, bit(2))){
      OCR0 += 50;
      _delay_ms(200);
     }
  }
}
