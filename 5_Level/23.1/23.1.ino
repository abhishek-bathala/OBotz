#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

int main (void)
{
  DDRB = 0x08;
  DDRD = 0x00;
  TCCR0 = 0x6B;
  OCR0 = 0;

  while (true){
    if(CHECK_BIT(PIND, 2)){
      OCR0 += 50;
      _delay_ms(250);
    }
  }
}
