#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
    DDRD = 0xFF;
    while(true){
      int y;

      ADMUX = 0x46;
      ADCSRA = 0xC7;
      while(CHECK_BIT(ADCSRA, ADSC)){
        y = ADCW;
      }

      if(y > 350){
        SET_BIT(PORTD, 0);
        SET_BIT(PORTD, 1);
        SET_BIT(PORTD, 5);
        SET_BIT(PORTD, 6);
      }
      else{
        CLEAR_BIT(PORTD, 0);
        CLEAR_BIT(PORTD, 1);
        CLEAR_BIT(PORTD, 5);
        CLEAR_BIT(PORTD, 6);
      }
  }
}
