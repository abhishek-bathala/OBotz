#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int i = 0, c = 0, d = 0;
long result, average;

void compare()
{
  if(average == 517){
    c++;
    antistepper();
    _delay_ms(50);
  }
  if(average == 688){
    d++;
    clkstepper();
    _delay_ms(50);
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  DDRD = 0xF0;
  while(true)
  {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if(i > 99){
      average = result/100;
      Serial.println(average);
      compare();
      result = 0;
      average = 0;
      i = 0;
    }
  }
}
