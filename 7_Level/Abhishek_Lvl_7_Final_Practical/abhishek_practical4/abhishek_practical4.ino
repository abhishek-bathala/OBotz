/* Abhishek Bathala
 * Level 7 Final Test
 * Practical Question #4
 */
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

//default position of the robot
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

void dance1() //when joystick moved is up, dance 1 will be performed
{
  for (int i = 0; i <= 90; i++) {
    right_hand++;
    convert();
  }
  for (right_foot = 90; right_foot <= 110; right_foot++) {
    neck--;
    right_hip++;
    convert();
  }
  _delay_ms(10);
  for (int i = 0; i <= 2; i++) {
    right_hand = 130;
    convert();
    _delay_ms(5);
    right_hand = 110;
    convert();
    _delay_ms(5);
  }
  _delay_ms(10);
  for (int i = 0; i <= 90; i++) {
    right_hand--;
    convert();
  }
  for (right_foot = 110; right_foot >= 90; right_foot--) {
    neck++;
    right_hip--;
    convert();
  }
  _delay_ms(10);
  homeposition();
  convert();
  for (int i = 0; i <= 90; i++) {
    left_hand--;
    convert();
  }
  for (left_foot = 90; left_foot >= 70; left_foot--) {
    neck++;
    left_hip--;
    convert();
  }
  _delay_ms(10);
  for (int i = 0; i <= 2; i++) {
    left_hand = 50;
    convert();
    _delay_ms(5);
    left_hand = 70;
    convert();
    _delay_ms(5);
  }
  _delay_ms(10);
  for (int i = 0; i <= 90; i++) {
    left_hand++;
    convert();
  }
  for (left_foot = 70; left_foot <= 90; left_foot++) {
    neck--;
    left_hip++;
    convert();
  }
  homeposition();
  convert();
}

void dance2() //when joystick moved is right, dance 2 will be performed
{
  for (right_foot = 90; right_foot <= 130; right_foot++) {
    convert();
  }
  for (left_foot = 90; left_foot <= 100; left_foot++) {
    convert();
  }
  for (right_hip = 90; right_hip <= 120; right_hip++) {
    left_hip++;
    right_hand++;
    left_hand--;
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
    left_hand++;
    convert();
  }

  for (right_foot = 90; right_foot >= 80; right_foot--) {
    convert();
  }
  for (left_foot = 90; left_foot >= 50; left_foot--) {
    convert();
  }
  for (right_hip = 90; right_hip >= 60; right_hip--) {
    left_hip--;
    right_hand++;
    left_hand--;
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
    left_hand++;
    convert();
  }

  homeposition();
  convert();

}

void dance3() //when joystick moved is left, dance 3 will be performed
{
  for (right_foot = 90; right_foot <= 110; right_foot++) {
    neck--;
    right_hand++;
    convert();
  }
  _delay_ms(10);
  for (left_foot = 90; left_foot >= 70; left_foot--) {
    neck--;
    left_hand--;
    convert();
  }
  _delay_ms(10);
  for (left_foot = 70; left_foot <= 90; left_foot++) {
    neck--;
    right_hand--;
    convert();
  }
  _delay_ms(10);
  for (right_foot = 110; right_foot >= 90; right_foot--) {
    neck--;
    left_hand++;
    convert();
  }
  _delay_ms(10);


}

void dance4() //when joystick moved is down, dance 4 will be performed
{
  for (right_hand = 90; right_hand <= 160; right_hand++) {
    left_hand--;
    convert();
  }

  for (right_foot = 90; right_foot <= 110; right_foot++) {
    convert();
  }
  for (left_foot = 90; left_foot <= 130; left_foot++) {
    convert();
  }
  for (left_foot = 130; left_foot >= 90; left_foot--) {
    convert();
  }
  for (right_foot = 110; right_foot >= 90; right_foot--) {
    convert();
  }

  for (left_hand = 20; left_hand <= 90; left_hand++) {
    right_hand--;
    convert();
  }
  
  for (left_foot = 90; left_foot >= 70; left_foot--) {
    convert();
  }
  for (right_foot = 90; right_foot >= 50; right_foot--) {
    convert();
  }
  for (right_foot = 50; right_foot <= 90; right_foot++) {
    convert();
  }
  for (left_foot = 70; left_foot <= 90; left_foot++) {
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
  //Serial.begin(2000000);
  while (1) {
    //getting the x axis value from joystick
    ADMUX = 0x47;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    x = ADCW;

    //getting the y axis value from joystick
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while ((ADCSRA & (1 << ADSC)));
    y = ADCW;

    /*Serial.print("x: ");
      Serial.println(x);
      Serial.print("y: ");
      Serial.println(y);*/

    if (y > 800) { //joystick up
      //Serial.println("up");
      dance1();
    }
    if (x < 100) { //joystick to right
      //Serial.println("right");
      dance2();
    }
    if (x > 800) { //joystick to left
      //Serial.println("left");
      dance3();
    }
    if (y < 100) { //joystick down
      //Serial.println("down");
      dance4();
    }
    if (x > 450 && x < 550 && y > 450 && y < 550) { //if the joystick is in the middle/home position, the robot will also go to home position
      //Serial.println("none");
      homeposition();
    }
  }
}
