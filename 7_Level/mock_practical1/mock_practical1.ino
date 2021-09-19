#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//joystick variables
int x = 0, y = 0;

//servo motor variables
int count = 0;
int right_foot = 0;
int left_foot = 0;
int count_angle0 = 0;
int count_angle1 = 0;

void convert()
{
  count_angle0 = right_foot + 46;
  count_angle1 = left_foot + 46;
  _delay_us(100);
}

ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle0)
    SET_BIT(PORTD, 5);
  else if ((count > count_angle0) && (count < 1818))
    CLEAR_BIT(PORTD, 5);
  else if (count >= 1818)
    count = 0;

  if (count <= count_angle1)
    SET_BIT(PORTD, 7);
  else if ((count > count_angle1) && (count < 1818))
    CLEAR_BIT(PORTD, 7);
}

int main(void)
{
  DDRC = 0x00;
  DDRD = 0xFF;
  DDRB = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  while (1) {
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    x = ADCW;

    ADMUX = 0x47;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    y = ADCW;
    
    if (y > 800) { //joystick up
      right_foot = 60;
      left_foot = 120;
      convert();
      _delay_ms(250);
    }
    if (x > 450 && x < 550) {
      right_foot = 90;
      left_foot = 90;
      convert();
    }
  }
}
