#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)


int main (void)
{
  char var;
  DDRD = 0xFF;
  UCSRA = 0x00;
  UCSRB = 0x18;
  UCSRC = 0x06;
  UBRRH = 0x00;
  UBRRL = 103;
  
  while(true){
     while(!(checkbit(UCSRA, bit(RXC))));
     var = UDR;
     if(var == '0'){
      //setting motor to clockwise, red led off, green led on
      setbit(PORTD, bit(4));
      clearbit(PORTD, bit(5));
      setbit(PORTD, bit(0));
      clearbit(PORTD, bit(1));
     }
     if(var == '1'){
      //setting motor to anticlockwise, red led on, green led off
      clearbit(PORTD, bit(4));
      setbit(PORTD, bit(5));
      clearbit(PORTD, bit(0));
      setbit(PORTD, bit(1));
     }
  }
}
