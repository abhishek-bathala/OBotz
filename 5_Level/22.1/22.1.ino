#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

int main (void)
{
  int x = 0;
  Serial.begin(2000000);
  DDRD = 0xFF;
  DDRB = 0xFF;
  
  while (true) {
    ADMUX = 0x45;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }

    if(x > 370){
      PORTD = 0xFF;
      PORTB = 0x00;
    }
    if(x < 320){
      PORTD = 0x00;
      PORTB = 0xFF;
    }
  }
}


