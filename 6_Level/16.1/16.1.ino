#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))


void compare(int x, int y)
{
  if(x == 506 || y == 506 || x == 498 || y == 498){
    PORTD = 0x00;
  }
  else if((450<x && x<550) && (950<y && y<1023)){ //up
    PORTD = 0x01;
  }
  else if((15<x && x<105) && (15<x && x<105)){ //down
    PORTD = 0x02;
  }
  else if((1000<x && x<1023) && (1000<x && x<1023)){ //left
    PORTD = 0x04;
  }
  else if((450<x && x<550) && (450<x && x<550)){ //right
    PORTD = 0x08;
  }
  else{
    PORTD = 0x00;
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRA = 0x00;
  DDRD = 0xFF;
  int x = 0;
  int y = 0;
  
  while(true)
  {
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }
    
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);
    compare(x, y);
    _delay_ms(250);
  }
}
