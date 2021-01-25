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

void robot_right()
{
  PORTD = 0x40;
}

void robot_left()
{
  PORTD = 0x20;
}

int main (void)
{
  DDRD = 0x00;
  DDRC = 0xFF;
  
  while (true){
    robot_forward();
    _delay_ms(2000);
    robot_reverse();
    _delay_ms(2000);
    robot_right();
    _delay_ms(2000);
    robot_left();
    _delay_ms(2000);
  }
}
