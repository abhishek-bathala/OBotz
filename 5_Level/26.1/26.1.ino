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
  Serial.begin(2000000);
  int ir = 0;
  
  lcd1.init();
  while(true)
  {
      ADMUX = 0x41;
      ADCSRA = 0xC7;
      while(CHECK_BIT(ADCSRA, ADSC)){
        ir = ADCW;
      }
      
      lcd1.cmd(0x01);
      lcd1.showvalue(ir);
      Serial.println(ir);
      _delay_ms(500);
  }
}
