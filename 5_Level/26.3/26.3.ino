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
  int ir1 = 0;
  int ir2 = 0;
  
  lcd1.init();
  while(true)
  {
      ADMUX = 0x41;
      ADCSRA = 0xC7;
      while(CHECK_BIT(ADCSRA, ADSC)){
        ir1 = ADCW;
      }

      ADMUX = 0x42;
      ADCSRA = 0xC7;
      while(CHECK_BIT(ADCSRA, ADSC)){
        ir2 = ADCW;
      }
      
      lcd1.cmd(0x01);
      lcd1.line1(0);
      lcd1.showvalue(ir1);
      lcd1.line2(0);
      lcd1.showvalue(ir2);
      Serial.print(ir1);
      Serial.print("\t");
      Serial.println(ir2);
      _delay_ms(500);
  }
}
