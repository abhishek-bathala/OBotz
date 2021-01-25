#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define KEY1 0x1FE50AF
#define KEY2 0x1FED827
#define KEY3 0x1FEF807

long keycode = 0;
int timervalue;
int bitposition = 0;
int var = 0;
int c = 0;
int d = 0;

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

void clkstepper()
{
  if(d==1){
    PORTD = 0b01110000;
    }
  if(d==2){
    PORTD = 0b10110000;
    }
  if(d==3){
    PORTD = 0b11010000;
    }
  if(d==4){
    PORTD = 0b11100000;
    d = 0;
  }
}

void antistepper()
{
  if(c==1){
    PORTD = 0b11100000;
    }
  if(c==2){
    PORTD = 0b11010000;
    }
  if(c==3){
    PORTD = 0b10110000;
    }
  if(c==4){
    PORTD = 0b11100000;
    c = 0;
  }
}

void compare()
{
  Serial.println(keycode, HEX);
  if(keycode == KEY1){
    d++;
    clkstepper();
    _delay_ms(50);
  }
  if(keycode == KEY3){
    c++;
    antistepper();
    _delay_ms(50);
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRB = 0x00;
  DDRD = 0xFF;
  TIMSK0 = 0x01;
  EICRA = 0x20;
  EIMSK = 0x04;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x03;
  while (true)
  {
  }
}
