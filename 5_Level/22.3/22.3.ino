#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

int main (void)
{
  int y = 0;
  Serial.begin(2000000);
  DDRC = 0xFF;
  DDRB = 0xFF;
  
  while (true) {
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    if(y > 370){
      PORTC = 0xFF;
      PORTB = 0x00;
    }
    if(y < 320){
      PORTC = 0x00;
      PORTB = 0xFF;
    }
  }
}


