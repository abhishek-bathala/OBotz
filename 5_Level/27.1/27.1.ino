#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
  LCD lcd1;
  int var = 0;
  DDRD = 0x00;
  
  lcd1.init();
  while(true)
  {

      if(CHECK_BIT(PIND, 2) && var < 9999){
        var++;
        lcd1.cmd(0x01);
        lcd1.showvalue(var);
        _delay_ms(300);
      }
      else if(CHECK_BIT(PIND, 3) && var > 0){
        var--;
        lcd1.cmd(0x01);
        lcd1.showvalue(var);
        _delay_ms(300);
      }
      
  }
}
