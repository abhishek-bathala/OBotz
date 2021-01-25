#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

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
  int count;
  double distance;
  Serial.begin(9600);
  DDRB = 0x01;
  int pinstate;

  while(true){
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
      pinstate = 0;
      TCNT1 = 0;
    }
  }
}
