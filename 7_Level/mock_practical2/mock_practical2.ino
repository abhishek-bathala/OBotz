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
  DDRC = 0xFF;
  DDRD = 0xFF;
  DDRB = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  Serial.begin(2000000);
  while (1) {
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    x = ADCW;

    ADMUX = 0x47;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    y = ADCW;

    Serial.print(x);
    Serial.println(y);
    if (y > 900) { //joystick up
      PORTC = 0x04; //1
      PORTB = 0xE0;
      _delay_ms(1000);
      for(int i = 0; i < 200; i++){ //2
        PORTC = 0x0E;
        PORTB = 0xFE;
        _delay_ms(1);
        PORTC = 0x08;
        PORTB = 0xF9;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xFB;
        _delay_ms(1);
        PORTC = 0x02;
        PORTB = 0xF7;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xEF;
        _delay_ms(1);
      }
      for(int i = 0; i < 200; i++){ //3
        PORTC = 0x0E;
        PORTB = 0xFE;
        _delay_ms(1);
        PORTC = 0x08;
        PORTB = 0xF9;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xFB;
        _delay_ms(1);
        PORTC = 0x08;
        PORTB = 0xF7;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xEF;
        _delay_ms(1);
      }
      for(int i = 0; i < 333; i++){ //4
        PORTC = 0x02;
        PORTB = 0xFC;
        _delay_ms(1);
        PORTC = 0x06;
        PORTB = 0xFB;
        _delay_ms(1);
        PORTC = 0x08;
        PORTB = 0xE0;
        _delay_ms(1);
      }
      for(int i = 0; i < 200; i++){ //5
        PORTC = 0x0E;
        PORTB = 0xFE;
        _delay_ms(1);
        PORTC = 0x08;
        PORTB = 0xF7;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xFB;
        _delay_ms(1);
        PORTC = 0x02;
        PORTB = 0xF9;
        _delay_ms(1);
        PORTC = 0x0E;
        PORTB = 0xEF;
        _delay_ms(1);
      }
    }
    if (x > 450 && x < 550) {
      PORTC = 0x00;
      PORTD = 0x00;
    }
  }
}
