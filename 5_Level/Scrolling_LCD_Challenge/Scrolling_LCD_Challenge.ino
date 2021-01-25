#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

int main (void)
{
  LCD lcd1;
  int i = 0;

  lcd1.init();
  while(true)
  {
    for(i = 0; i < 16; i++)
    {
      lcd1.cmd(0x01);
      lcd1.line1(i);
      lcd1.string("55 Downtown"); 
      lcd1.line2(i);
      lcd1.string("Center-Ville");
      _delay_ms(250);
    }
  }
}
