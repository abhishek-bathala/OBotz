#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main(void)
{
  int x, y = 0;
  DDRB = 0xFF;
  Serial.begin(2000000);
  while(true){
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    x = ADCW;

    ADMUX = 0x41;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    y = ADCW;

    Serial.println(x);
    Serial.println(y);

    if(x < 100)
      PORTB = 0x00;
    if(y < 100)
      PORTB = 0xFF;
    _delay_ms(250);
  }
}
