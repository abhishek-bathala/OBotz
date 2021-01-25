#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM)))

int main (void)
{
  int brightness = 0;
  DDRB = 0x08;
  TCCR0 = 0x6B;
  OCR0 = 0;
  
  Serial.begin(2000000);
  
  while (true){
    ADMUX = 0x41;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      brightness = ADCW;
    }
    
    OCR0 = (brightness/4);
    Serial.println(OCR0);
  }
}
