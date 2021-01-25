#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

void robot_forward()
{
  PORTD = 0x60;
}

void robot_reverse()
{
  PORTD = 0x90;
}

int main (void)
{
  Serial.begin(2000000);
  int ir = 0;
  DDRD = 0x00;
  
  while(true){
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(checkbit(ADCSRA, bitn(ADSC))){
      ir = ADCW;
      Serial.println(ir);
      if(ir > 650){
        robot_forward();
      }
      else{
        robot_reverse();
      }
    }
  }
}
