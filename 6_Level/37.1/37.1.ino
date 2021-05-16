#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int c = 0, d = 0;
int pinstate, count;
double distance;
int dist;

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
  Serial.begin(2000000);
  DDRD = 0xFF;
  DDRB = 0x01;
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
      dist = distance/10;
      if(dist> 9)
        dist = 9;
      if(dist < 0)
        dist = 0;
      PORTC = num[dist];
      Serial.println(dist);
      pinstate = 0;
      TCNT1 = 0;
      _delay_ms(150);
    }
  }
}
