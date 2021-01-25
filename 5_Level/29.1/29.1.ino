#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
  char var;
  DDRD = 0xFF;
  UCSRA = 0x00;
  UCSRB = 0x18;
  UCSRC = 0x06;
  UBRRH = 0x00;
  UBRRL = 103;
  
  while(true){
    
    while(!(CHECK_BIT(UCSRA, RXC)));
    var = UDR;
    if(var == '0'){
      SET_BIT(PORTD, 5);
      CLEAR_BIT(PORTD, 4);
    }

    if(var == '1'){
      SET_BIT(PORTD, 4);
      CLEAR_BIT(PORTD, 5);
    }

    if(var == '2'){
      SET_BIT(PORTD, 5);
      SET_BIT(PORTD, 4);
    }
  }
}
