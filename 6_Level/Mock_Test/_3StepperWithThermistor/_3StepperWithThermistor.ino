#include <obotz_level6_stepper_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;

//stepper motor variables
int c = 0, d = 0;

int main(void)
{
  Serial.begin(2000000);
  DDRD = 0xFF;
  
}
