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
    int i = 0;
    
    for(i = 0; i < 1; i++){
      SET_BIT(PORTD, 0);
      _delay_ms(500);
      CLEAR_BIT(PORTD, 0);
      SET_BIT(PORTD, 1);
      _delay_ms(500);
      CLEAR_BIT(PORTD, 1);
      SET_BIT(PORTD, 2);
      _delay_ms(500);
      CLEAR_BIT(PORTD, 2);
    }
  }
}
