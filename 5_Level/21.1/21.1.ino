#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

int main (void)
{
  int x, y, z = 0;
  Serial.begin(2000000);
  
  while (true) {
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

    Serial.print("x: ");
    Serial.print(x);
    Serial.print("\ty: ");
    Serial.print(y);
    Serial.print("\tz: ");
    Serial.print(z);
    Serial.print("\n");
    _delay_ms(1000);
  }
}


