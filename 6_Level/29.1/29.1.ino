//for ex29, only circuit changes, not program

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main(void)
{
  DDRB = 0xFF;
  while(true){
    PORTB = 0xFF;
    _delay_ms(1000);
    PORTB = 0x00;
    _delay_ms(1000);
  }
}
