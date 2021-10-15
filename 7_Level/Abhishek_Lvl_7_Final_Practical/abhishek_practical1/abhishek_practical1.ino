/* Abhishek Bathala
 * Level 7 Final Test
 * Practical Question #1
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//joystick variables
int y = 0;

//servo motor variables
int count = 0;
int angle1 = 0;
int count_angle0 = 0;

ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle0)
    SET_BIT(PORTD, 7);
  else if ((count > count_angle0) && (count < 1818))
    CLEAR_BIT(PORTD, 7);
  else if (count >= 1818)
    count = 0;
}

void convert()
{
  count_angle0 = angle1 + 46;
  _delay_us(100);
}


int main(void)
{
  DDRC = 0x00;
  DDRD = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  //Serial.begin(2000000);
  while (1) {
    //getting y axis value from joystick
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    y = ADCW;

    //Serial.println(y);
    if (y > 800) { //joystick up
      angle1 = 140; //move arm up
      convert();
    }
    if (y > 450 && y < 550) { //joystick center/released
      angle1 = 90; //move arm back down
      convert();
    }
  }
}
