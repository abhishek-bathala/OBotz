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
int right_hip = 0;
int left_hip = 0;
int right_foot = 0;
int left_foot = 0;
int right_hand = 0;
int left_hand = 0;
int neck = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int count_angle4 = 0;
int count_angle5 = 0;
int count_angle6 = 0;
int count_angle7 = 0;

void convert()
{
  count_angle1 = right_hip + 46;
  count_angle2 = right_foot + 46;
  count_angle3 = left_hip + 46;
  count_angle4 = left_foot + 46;
  count_angle5 = left_hand + 46;
  count_angle6 = right_hand + 46;
  count_angle7 = neck + 46;
  _delay_us(100);
}

ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle1)
    SET_BIT(PORTD, 4);
  else if ((count > count_angle1) && (count < 1818))
    CLEAR_BIT(PORTD, 4);
  else if (count >= 1818)
    count = 0;

  if (count <= count_angle2)
    SET_BIT(PORTD, 5);
  else if ((count > count_angle2) && (count < 1818))
    CLEAR_BIT(PORTD, 5);

  if (count <= count_angle3)
    SET_BIT(PORTD, 6);
  else if ((count > count_angle3) && (count < 1818))
    CLEAR_BIT(PORTD, 6);

  if (count <= count_angle4)
    SET_BIT(PORTD, 7);
  else if ((count > count_angle4) && (count < 1818))
    CLEAR_BIT(PORTD, 7);

  if (count <= count_angle5)
    SET_BIT(PORTD, 3);
  else if ((count > count_angle5) && (count < 1818))
    CLEAR_BIT(PORTD, 3);

  if (count <= count_angle6)
    SET_BIT(PORTD, 2);
  else if ((count > count_angle6) && (count < 1818))
    CLEAR_BIT(PORTD, 2);

  if (count <= count_angle7)
    SET_BIT(PORTD, 0);
  else if ((count > count_angle7) && (count < 1818))
    CLEAR_BIT(PORTD, 0);
}

void homeposition()
{
  right_hip = 90;
  left_hip = 90;
  right_foot = 90;
  left_foot = 90;
  right_hand = 40;
  left_hand = 140;
  neck = 90;
}

void dribbling_ball() //when joystick is up
{
  //left side
  for (right_foot = 90; right_foot <= 130; right_foot++) {
    convert();
  }
  for (left_foot = 90; left_foot <= 100; left_foot++) {
    convert();
  }
  for (right_hip = 90; right_hip <= 120; right_hip++) {
    left_hip++;
    right_hand++;
    convert();
  }

  for (left_foot = 100; left_foot >= 90; left_foot--) {
    convert();
  }
  for (right_foot = 130; right_foot >= 80; right_foot--) {
    convert();
  }
  for (right_hip = 120; right_hip >= 90; right_hip--) {
    left_hip--;
    right_hand--;
    convert();
  }

  //right side
  for (right_foot = 90; right_foot >= 80; right_foot--) {
    convert();
  }
  for (left_foot = 90; left_foot >= 50; left_foot--) {
    convert();
  }
  for (right_hip = 90; right_hip >= 60; right_hip--) {
    left_hip--;
    right_hand++;
    convert();
  }

  for (left_foot = 50; left_foot <= 90; left_foot++) {
    convert();
  }
  for (right_foot = 80; right_foot <= 90; right_foot++) {
    convert();
  }
  for (right_hip = 60; right_hip <= 90; right_hip++) {
    left_hip++;
    right_hand--;
    convert();
  }

  homeposition();
  convert();

}

void right_concentration_curl() //when joystick is right
{
  for (right_hand = 40; right_hand <= 140; right_hand++) {
    neck++;
    convert();
  }
  _delay_ms(10);
  for (right_hand = 140; right_hand >= 40; right_hand--) {
    neck--;
    convert();
  }
  _delay_ms(10);
  homeposition();
  convert();
}

void left_concentration_curl() //when joystick is left
{
  for (left_hand = 140; left_hand >= 40; left_hand--) {
    neck++;
    convert();
  }
  _delay_ms(10);
  for (left_hand = 40; left_hand <= 140; left_hand++) {
    neck--;
    convert();
  }
  _delay_ms(10);
  homeposition();
  convert();
}

void soccer_ball_exercise() //when joystick is down
{
  for (right_hip = 90; right_hip <= 120; right_hip++) {
    left_hip++;
    convert();
  }

  for (right_foot = 90; right_foot <= 120; right_foot++) {
    convert();
  }

  for (right_hip = 120; right_hip >= 90; right_hip--) {
    left_hip--;
    convert();
  }

  for (right_foot = 120; right_foot >= 90; right_foot--) {
    convert();
  }
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
  homeposition();
  convert();
  Serial.begin(2000000);
  while (1) {

    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    x = ADCW;
    ADMUX = 0x41;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    y = ADCW;

    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);

    if (x < 100) { //joystick to right
      Serial.println("right");
      right_concentration_curl();
    }
    if (x > 800) { //joystick to left
      Serial.println("left");
      left_concentration_curl();
    }
    if (y < 100) { //joystick down
      Serial.println("down");
      soccer_ball_exercise();
    }
    if (y > 800) { //joystick up
      Serial.println("up");
      dribbling_ball();
    }
    if (x > 450 && x < 550 && y > 450 && y < 550) {
      Serial.println("none");
      homeposition();
    }
  }
}
