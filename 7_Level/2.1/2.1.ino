#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//servo motor variables
int count = 0;
int angle1 = 0;
int angle2 = 0;
int count_angle1 = 0;
int count_angle2 = 0;

void convert()
{
  count_angle1 = angle1 + 46;
  count_angle2 = angle2 + 46;
  _delay_us(5000);
}

ISR(TIMER1_COMPA_vect)
{
  count++;
  if(count <= count_angle1){
    SET_BIT(PORTD, 4);
  }
  else if ((count > count_angle1) && (count < 1818)){
    CLEAR_BIT(PORTD, 4);
  }
  else if(count >= 1818){
    count = 0;
  }
  if(count <= count_angle2){
    SET_BIT(PORTD, 5);
  }
  else if ((count > count_angle2) && (count < 1818)){
    CLEAR_BIT(PORTD, 5);
  }
}

void homeposition()
{
  angle1 = 0;
  angle2 = 0;
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
  while(true){
    for(angle1 = 0; angle1 <= 180; angle1++){
      angle2++;
      convert();
    }
    homeposition();
  }
}
