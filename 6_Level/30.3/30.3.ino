#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
long result, average;
int count = 0;

void compare()
{
  if (average >= 585 && average <= 595) {
    PORTB = 0xFF;
  }
  if(average == 610)
    PORTB = 0x00;
}


int main(void)
{
  int x, y, i = 0;
  DDRB = 0xFF;
  Serial.begin(2000000);
  while (true) {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while (CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if (i > 99) {
      average = result / 100;
      Serial.println(average);
      compare();
      result = 0;
      average = 0;
      i = 0;
    }
  }
}
