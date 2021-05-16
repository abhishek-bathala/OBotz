#include <LCD.h>
#include <obotz_level6_stepper_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int c = 0, d = 0;
int pinstate, count;
double distance;

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
  LCD lcd;
  lcd.init();
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
      distance = distance;
      lcd.cmd(0x01);
      lcd.line1(8);
      lcd.showvalue(distance);
      lcd.string(".");
      distance /= 100;
      distance *= 100;
      lcd.showvalue(distance);
      lcd.string("cm");
      lcd.line1(0);
      lcd.string("distance:");
      Serial.println(distance);
      pinstate = 0;
      TCNT1 = 0;
      _delay_ms(200);
    }
  }
}
