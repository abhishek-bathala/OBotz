#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};
long result;
long average;
int i;

void compare()
{
  if(average > 510 && average < 520)
    PORTC = num[1];
  if(average > 680 && average < 690)
    PORTC = num[2];
  if(average > 760 && average < 770)
    PORTC = num[3];
  if(average > 480 && average < 490)
    PORTC = num[4];
  if(average > 630 && average < 640)
    PORTC = num[5];
}

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  PORTD = 0x00;
  while (true) {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if(i > 99){
      average = result/100;
      compare();
      Serial.println(average);
      result = 0;
      average = 0;
      i = 0;  
    }
  }
}
