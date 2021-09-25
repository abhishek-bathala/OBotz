#include <avr/io.h>
#include <util/delay.h>

#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int count = 0;

int main(void)
{
   Serial.begin(2000000);
   DDRD = 0x00;
   while(1){
      if(checkbit(PIND, bit(2))){
        count++;
        Serial.println(count);
      }
      if(checkbit(PIND, bit(3))){
        count--;
        Serial.println(count);
      }
      _delay_ms(1);
   }
}
