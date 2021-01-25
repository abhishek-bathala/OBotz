#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main(void)
{
  int val = 0;
  Serial.begin(2000000);

  while(true){
    ADMUX = 0x45;
    ADCSRA = 0xC7;
    while(checkbit(ADCSRA, bitn(ADSC))){
      val = ADCW;
      Serial.println(val);
    }
  }
}
