#include <avr/io.h>
#include <util/delay.h>
#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BIT_NUM))

int c = 0;
int d = 0;
int main(void)
{
  DDRD = 0xFF;  //PD4-PD7 output
  DDRB = 0x00;  //PORTD as input

  while(true){
    if(CHECK_BIT(PINB, BITN(PB0))){
      d++;
      clkstepper();
      _delay_ms(50);
    }
    if(CHECK_BIT(PINB, BITN(PB1))){
      c++;
      antistepper();
     _delay_ms(50);
    }
  }
}
void clkstepper()
{
  if(d==1){
    PORTD = 0b01110000;
    }
  if(d==2){
    PORTD = 0b10110000;
    }
  if(d==3){
    PORTD = 0b11010000;
    }
  if(d==4){
    PORTD = 0b11100000;
    d = 0;
  }
}

void antistepper()
{
  if(c==1){
    PORTD = 0b11100000;
    }
  if(c==2){
    PORTD = 0b11010000;
    }
  if(c==3){
    PORTD = 0b10110000;
    }
  if(c==4){
    PORTD = 0b11100000;
    c = 0;
  }
}
