#include "obotz_level6_ir_remote.h"

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//keycode macros and variables for IR remote
#define KEY1 0x01FE50AF
#define KEY2 0x01FED827
#define KEY3 0x01FEF807
#define KEY4 0x01FE30CF
#define KEY5 0x01FEB04F
#define KEY6 0x01FE708F
#define KEY7 0x01FE00FF
#define KEY8 0x01FEF00F

ISR(TIMER0_OVF_vect)
{
  var++;
  TCNT0 = 125;
}


ISR(INT2_vect)
{
  timervalue = var;
  var = 0;
  bitposition++;
  if (timervalue >= 100) {
    bitposition = -2;
    keycode = 0;
  }
  if ((bitposition >= 0) && (bitposition < 32)) {
    if (timervalue > 3) {
      keycode |= (long)1<<(31 - bitposition);
    }
  }
  else if (bitposition >= 32) {
    bitposition = 0;
    compare();
  }
}
