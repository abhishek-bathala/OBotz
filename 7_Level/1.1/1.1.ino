#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//servo motor variables
int count = 0;
int angle = 0;
int count_angle = 0;

void convert()
{
  count_angle = angle + 46;
  _delay_us(5000);
}

ISR(TIMER1_COMPA_vect)
{
  count++;
  if(count <= count_angle){
    SET_BIT(PORTD, 4);
  }
  else if ((count > count_angle) && (count < 1818)){
    CLEAR_BIT(PORTD, 4);
  }
  else if(count >= 1818){
    count = 0;
  }
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
  while(true){
    for(angle = 90; angle <= 150; angle++){
      convert();
    }
    for(angle = 150; angle <= 90; angle--){
      convert();
    }
  }
}
