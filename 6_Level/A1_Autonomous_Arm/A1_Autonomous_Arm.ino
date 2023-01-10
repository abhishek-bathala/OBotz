#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//stepper motor variables
int c = 0;
int d = 0;

//servo variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;

void angle1(int a) //base servo
{
  count_angle1 = a + 46;
}

void angle2 (int a) //elbow servo
{
  count_angle2 = a + 46;
}

void angle3 (int a)//claw servo
{
  count_angle3 = a + 46;
}

ISR (TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle1) {
    SET_BIT(PORTB, 5);
  }
  else if ((count > count_angle1) && (count < 1818)) {
    CLEAR_BIT(PORTB, 5);
  }
  else if (count >= 1818) {
    count = 0;
  }
  if (count <= count_angle2) {
    SET_BIT(PORTB, 6);
  }
  else if ((count > count_angle2) && (count < 1818)) {
    CLEAR_BIT(PORTB, 6);
  }
  else if (count >= 1818) {
    count = 0;
  }
  if (count <= count_angle3) {
    SET_BIT(PORTB, 7);
  }
  else if ((count > count_angle3) && (count < 1818)) {
    CLEAR_BIT(PORTB, 7);
  }
  else if (count >= 1818) {
    count = 0;
  }
}
void clkstepper() //stepper motor clockwise
{
  if (d == 1) {
    PORTD = 0b01110000;
  }
  if (d == 2) {
    PORTD = 0b10110000;
  }
  if (d == 3) {
    PORTD = 0b11010000;
  }
  if (d == 4) {
    PORTD = 0b11100000;
    d = 0;
  }
}

void antistepper()  //stepper motor anticlockwise
{
  if (c == 1) {
    PORTD = 0b11100000;
  }
  if (c == 2) {
    PORTD = 0b11010000;
  }
  if (c == 3) {
    PORTD = 0b10110000;
  }
  if (c == 4) {
    PORTD = 0b11100000;
    c = 0;
  }
}

int main(void)
{
  DDRD = 0xFF;
  DDRB = 0xFF;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  SREG = 0x80;    //Enable global interrupt

  while (true)
  {
    angle1(30);
    _delay_ms(200);
    angle2(10);
    _delay_ms(200);
    angle3(60);
    _delay_ms(200);
    angle3(10);
    _delay_ms(200);
    for (int i = 0; i < 12; i++) {
      c++;
      antistepper();
      _delay_ms(50);
    }
    _delay_ms(200);
    angle1(60);
    _delay_ms(500);
    angle2(10);
    _delay_ms(200);
    angle3(80);
    _delay_ms(50);
    for (int i = 0; i < 12; i++) {
      d++;
      clkstepper();
      _delay_ms(50);
    }
    _delay_ms(200);
  }
}
