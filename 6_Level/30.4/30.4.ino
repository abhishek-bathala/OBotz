#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
long result, average;
int count = 0;

void trigger()
{
  PORTB = 0x00;
  _delay_us(10);
  PORTB = 0x01;
  _delay_us(10);
  PORTB = 0x00;
}


int main(void)
{
  DDRB = 0x21;
  int count, pinstate;
  double distance;
  Serial.begin(2000000);
  while (true) {
    trigger();
    while(CHECK_BIT(PINB, 1)){
      TCCR1A = 0x00;
      TCCR1B = 0x02;
      pinstate = 1;
    }
    while(!(CHECK_BIT(PINB, 1)) && (pinstate == 1)){
      TCCR1B = 0x00;
      count = TCNT1;
      distance = (count * 0.008575);
      Serial.println(distance);
      if(distance < 0)
        distance = 1000;
      if(distance < 10)
        PORTB = 0x30;
      else
        PORTB = 0x00;
      pinstate = 0;
      TCNT1 = 0;
      _delay_ms(100);
    }
  }
}
