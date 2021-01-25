#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))


int main(void)
{
  Serial.begin(2000000);
  DDRA = 0x00;
  DDRD = 0xFF;
  int x = 0;
  int y = 0;
  
  while(true)
  {
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }

    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);
  }
}
