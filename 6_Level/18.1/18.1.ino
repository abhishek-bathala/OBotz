#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//servo variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;

int c = 0;
int d = 0;

void compare(int x, int y)
{
  //if(x == 506 || y == 506 || x == 498 || y == 498){
  //  PORTD = 0x00;
  //}
  if(y > 800){ //up
    d++;
    clkstepper();
  }
  else if(y < 100){ //down
    c++;
    antistepper();
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
