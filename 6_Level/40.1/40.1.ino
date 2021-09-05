#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int x = 0;

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  while(true){
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    x = ADCW;
    Serial.println(x);
    if(x < 75)
        PORTC = num[1];
    else if(x > 200)
        PORTC = num[2];
  }
}
