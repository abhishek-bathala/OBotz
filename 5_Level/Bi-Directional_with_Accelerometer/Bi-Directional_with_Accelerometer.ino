#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

#define ROBOT_FORWARD() ((PORTD) = 0x60)
#define ROBOT_REVERSE() ((PORTD) = 0x90)

int main (void)
{
  int y = 0;
  DDRD = 0xFF;

  while (true) {
    ADMUX = 0x46;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    if(y > 370){
      ROBOT_FORWARD();
    }
    if(y < 320){
      ROBOT_REVERSE();
    }
  }
  
}
