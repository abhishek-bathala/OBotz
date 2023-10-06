#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  TCCR0 = 0x6B;
  OCR0 = 0; 
  while(true){
    if(checkbit(PIND, bitn(2))) {
      OCR0 = OCR0 + 25;
    }
  }
}
