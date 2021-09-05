#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int x = 0, y = 0;

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  while(true){
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    x = ADCW;
    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    y = ADCW;
    Serial.print("x:");
    Serial.print(x);
    Serial.print("y:");
    Serial.println(y);
    if(x < 100)
        PORTC = num[1];
    else if(x>800)
        PORTC = num[2];
    else if(y<100)
        PORTC = num[3];
    else if(y>800)
        PORTC = num[4];
    else{
      PORTC = num[0];
    }
  }
}
