#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define KEY1 0x1FE50AF
#define KEY2 0x1FED827
#define KEY3 0x1FEF807

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//IR variables
long keycode = 0;
int timervalue;
int bitposition = 0;
int var = 0;

//servo variables
int a;
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int c1 = 0;
int c2 = 0;
int c3 = 0;

ISR(TIMER0_OVF_vect)
{
  var++;
  TCNT0 = 125;
}

ISR(INT2_vect)
{
  timervalue = var;
  var = 0;
  bitposition++;
  if (timervalue >= 100) {
    bitposition = -2;
    keycode = 0;
  }
  if ((bitposition >= 0) && (bitposition < 32)) {
    if (timervalue > 3) {
      keycode |= (long)1<<(31 - bitposition);
    }
  }
  else if (bitposition >= 32) {
    bitposition = 0;
    compare();
  }
}

void angle1(int a)
{
  count_angle1 = a + 46;
}

void angle2 (int a)
{
  count_angle2 = a + 46;
}

void angle3 (int a)
{
  count_angle3 = a + 46;
}

ISR (TIMER1_COMPA_vect)
{
  count++;
  if(count <=count_angle1){
    SET_BIT(PORTB, 5);
  }
  else if ((count > count_angle1) && (count < 1818)){
    CLEAR_BIT(PORTB, 5);
  }
  else if(count >= 1818){
    count = 0;
  }
  if (count <= count_angle2){
    SET_BIT(PORTB, 6);
  }
  else if ((count > count_angle2) && (count < 1818)){
    CLEAR_BIT(PORTB, 6);
  }
  else if(count >= 1818){
    count = 0;
  }
  if (count <= count_angle3){
    SET_BIT(PORTB, 7);
  }
  else if ((count > count_angle3) && (count < 1818)){
    CLEAR_BIT(PORTB, 7);
  }
  else if(count >= 1818){
    count = 0;
  }
}

void compare()
{
  Serial.println(keycode, HEX);
  if(keycode == KEY1){
    c1 += 5;
    angle1(c1);
  }
  if(keycode == KEY2){
    c2 += 5;
    angle2(c2);
  }
  if(keycode == KEY3){
    c3 += 5;
    angle3(c3);
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRB = 0x00;
  DDRD = 0xFF;
  TIMSK0 = 0x01;
  EICRA = 0x20;
  EIMSK = 0x04;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x03;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  while (true)
  {
  }
}
