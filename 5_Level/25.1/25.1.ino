#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>


#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

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
      lcd1.string("Hello"); 
      lcd1.line2(3);
      lcd1.string("world");
      _delay_ms(500);
    }
  }
}
