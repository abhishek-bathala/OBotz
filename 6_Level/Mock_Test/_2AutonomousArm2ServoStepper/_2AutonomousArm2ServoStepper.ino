#include <obotz_level6_stepper_motor.h>
#include <obotz_level6_servo_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;

//stepper motor variables
int c = 0, d = 0;

int main(void)
{
  Serial.begin(2000000);
  DDRD = 0xFF;
  DDRC = 0xFF;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  while (true) {
    angle1(10);
    _delay_ms(100);
    angle1(70);
    _delay_ms(100);
    angle2(10);
    _delay_ms(100);
    angle2(70);
    _delay_ms(100);
    for(int i = 0; i < 6; i++){
      c++;
      antistepper();
      _delay_ms(50);
    }
    for(int i = 0; i < 6; i++){
      d++;
      clkstepper();
      _delay_ms(50);
    }
    _delay_ms(200);
  }
}
