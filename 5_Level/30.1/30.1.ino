#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
  char var;
  UCSRA = 0x00;
  UCSRB = 0x18;
  UCSRC = 0x06;
  UBRRH = 0x00;
  UBRRL = 103;
  TCCR0 = 0x6B;
  
  while(true){
    
    while(!(CHECK_BIT(UCSRA, RXC)));
    var = UDR;
    if(var == '0'){
      OCR0 += 20;
    }

    if(var == '1'){
      OCR0 -= 20;
    }
  }
}
