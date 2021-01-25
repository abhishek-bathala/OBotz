#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  LCD lcd1;
  DDRD = 0x00;
  int count = 0;
  int number = 0;
  lcd1.init();

  while(true){
    if (checkbit(PIND, bit(2))){
      count++;
    }

    if (count == 1){
      while(!(checkbit(PIND, bit(2)))){
        lcd1.cmd(0x01);
        lcd1.showvalue(number);
        number++;
        _delay_ms(10);

        if (number == 1000){
          number = 0;
        }
      }
    }
    if (count == 2){
      count = 0;
    }
    if(checkbit(PIND, bit(3))){
      number = 0;
      lcd1.cmd(0x01);
      lcd1.showvalue(number);
      count = 0;
    }
  }
}
