#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int a;
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int c1 = 0;
int c2 = 0;
int c3 = 0;


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

int main(void)
{
  DDRB = 0xFF;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  SREG = 0x80;    //Enable global interrupt

  while(true)
  {
    angle1(0);
    _delay_ms(500);
    angle2(30);
    _delay_ms(500);
    angle3(60);
    _delay_ms(500);
    angle1(90);
    _delay_ms(500);
    angle2(120);
    _delay_ms(500);
    angle3(180);
    _delay_ms(500);
  }
}
