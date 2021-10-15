#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//servo motor variables
int count = 0;
int right_fore = 0;
int left_fore = 0;
int right_hind = 0;
int left_hind = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int count_angle4 = 0;

void convert()
{
  count_angle1 = right_fore+ 46;
  count_angle2 = right_hind + 46;
  count_angle3 = left_fore + 46;
  count_angle4 = left_hind + 46;
  _delay_us(500);
}

ISR(TIMER1_COMPA_vect)
{
  count++;      
  if(count <= count_angle1)
    SET_BIT(PORTD, 4);
  else if ((count > count_angle1) && (count < 1818))
    CLEAR_BIT(PORTD, 4);
  else if(count >= 1818)
    count = 0;
  
  if(count <= count_angle2)
    SET_BIT(PORTD, 5);
  else if ((count > count_angle2) && (count < 1818))
    CLEAR_BIT(PORTD, 5);
    
  if(count <= count_angle3)
    SET_BIT(PORTD, 6);
  else if ((count > count_angle3) && (count < 1818))
    CLEAR_BIT(PORTD, 6);
    
  if(count <= count_angle4)
    SET_BIT(PORTD, 7);
  else if ((count > count_angle4) && (count < 1818))
    CLEAR_BIT(PORTD, 7);

  /*if(count <= count_angle5)
    SET_BIT(PORTD, 3);
  else if ((count > count_angle5) && (count < 1818))
    CLEAR_BIT(PORTD, 3);
  
  if(count <= count_angle6)
    SET_BIT(PORTD, 2);
  else if ((count > count_angle6) && (count < 1818))
    CLEAR_BIT(PORTD, 2);*/
}

void homeposition()
{
right_fore = 90;
left_fore = 90;
right_hind = 90;
left_hind = 90;
  //right_hand = 40;
  //left_hand = 140;
}

int main(void)
{
  DDRD = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  homeposition();
  convert();
  while(true){
    homeposition();
    for(int i = 0; i < 20; i++)
    {
      right_fore++;
      left_hind--;
      convert();
    }
    for(int i = 0; i < 10; i++)
    {
      right_hind--;
      left_fore++;
      convert();
    }
    for(int i = 0; i < 20; i++)
    {
      right_fore--;
      left_hind++;
      convert();
    }
    for(int i = 0; i < 10; i++)
    {
      right_hind++;
      left_fore--;
      convert();
    }
    for(int i = 0; i < 20; i++)
    {
      right_hind++;
      left_fore--;
      convert();
    }
    for(int i = 0; i < 10; i++)
    {
      right_fore--;
      left_hind++;
      convert();
    }
    for(int i = 0; i < 20; i++)
    {
      right_hind--;
      left_fore++;
      convert();
    }
    for(int i = 0; i < 10; i++)
    {
      right_fore++;
      left_hind--;
      convert();
    }
  }
}
