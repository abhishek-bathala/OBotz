#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

long keycode = 0;
int timervalue;
int bitposition = 0;
int var = 0;

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
      keycode |= (long)1 << (31 - bitposition);
    }
  }
  else if (bitposition >= 32) {
    bitposition = 0;
    Serial.println(keycode, HEX);
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRB = 0x00;
  TIMSK0 = 0x01;
  EICRA = 0x20;
  EIMSK = 0x04;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x0B;
  while (true)
  {
  }
}
