#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
  LCD lcd1;
  lcd1.init();
  char var;
  DDRB = 0xFF;
  UCSRA = 0x00;
  UCSRB = 0x18;
  UCSRC = 0x06;
  UBRRH = 0x00;
  UBRRL = 103;
  
  while(true){
    
    while(!(CHECK_BIT(UCSRA, RXC)));
    var = UDR;
    if(var == '0'){
      CLEAR_BIT(PORTB, 4);
    }

    if(var == '1'){
      SET_BIT(PORTB, 4);
    }
    lcd1.cmd(0x01);
    lcd1.showvalue(var);
    _delay_ms(500);
  }
}
