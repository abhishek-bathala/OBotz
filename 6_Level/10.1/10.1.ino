#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int a;
int count = 0;
int count_angle = 0;

void angle(int a)
{
  count_angle = a + 46;
}

ISR (TIMER1_COMPA_vect)
{
  count++;
  if(count <=count_angle){
    SET_BIT(PORTB, 4);
  }
  else if ((count > count_angle) && (count < 1818)){
    CLEAR_BIT(PORTB, 4);
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
    angle(0);
    _delay_ms(500);
    angle(30);
    _delay_ms(500);
    angle(60);
    _delay_ms(500);
    angle(90);
    _delay_ms(500);
    angle(120);
    _delay_ms(500);
    angle(180);
    _delay_ms(500);
  }
}
