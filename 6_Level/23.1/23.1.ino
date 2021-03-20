#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int i = 0;
long result, average;

void compare()
{
  if(average == 590){
    PORTC = num[0];
  }
  if(average == 517){
    PORTC = num[1];
  }
  if(average == 688){
    PORTC = num[2];
  }
  if(average == 768){
    PORTC = num[3];
  }
  if(average == 486 || average == 487){
    PORTC = num[4];
  }
  if(average == 636){
    PORTC = num[5];
  }
  if(average == 705){
    PORTC = num[6];
  }
  if(average == 471 || average == 472){
    PORTC = num[7];
  }
  if(average == 610){
    PORTC = num[8];
  }
  if(average == 672 || average == 673){
    PORTC = num[9];
  }
  if(average == 1006){
    PORTC = num[10];
  }
  if(average == 900){
    PORTC = num[11];
  }
  if(average == 849){
    PORTC = num[12];
  }
  if(average == 811){
    PORTC = num[13];
  }
  if(average == 648 || average == 649){
    PORTC = num[14];
  }
  if(average == 459 || average == 460){
    PORTC = num[15];
  }
  
}

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  PORTD = 0x00;
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
