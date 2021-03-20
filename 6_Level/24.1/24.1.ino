#include <obotz_level6_servo_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int i = 0;
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int finger = 0;
long result, average;

void compare(int average)
{
  if(average >= 515 && average <= 520){
    finger += 15;
    angle3(finger);
    _delay_ms(100);
  }
  if(average >= 685 && average <= 690){
    finger -= 15;
    angle3(finger);
    _delay_ms(100);
  }
  if(finger == 105){
    finger = 0;
    angle3(finger);
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRB = 0xFF;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  SREG = 0x80;    //Enable global interrupt
  while(true)
  {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if(i > 99){
      average = result/100;
      Serial.println(average);
      compare(average);
      result = 0;
      average = 0;
      i = 0;
    }
  }
}
