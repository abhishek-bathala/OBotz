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
  int x = 0;
  int y = 0;
  int z = 0;
  Serial.begin(2000000);
  DDRD = 0x00;
  
  lcd1.init();
  while(true)
  {
    lcd1.cmd(0x01);
    lcd1.line1(0);
    ADMUX = 0x45;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }

    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    ADMUX = 0x47;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      z = ADCW;
    }

    lcd1.string("x:");
    lcd1.showvalue(x);
    lcd1.line1(7);
    lcd1.string("y:");
    lcd1.showvalue(y);
    lcd1.line2(0);
    lcd1.string("z:");
    lcd1.showvalue(z);
    _delay_ms(300);
  }
}
