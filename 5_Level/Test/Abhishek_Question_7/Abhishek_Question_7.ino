#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define setbit(x,y) (x|=y)
#define checkbit(x,y)((x) & (y))
#define clearbit(x,y)(x&=~y)
#define bitn(p) (0x01<<p)

int main (void)
{
  LCD lcd1;
  int left_ir = 0;
  int right_ir = 0;
  DDRD = 0xFF;
  DDRA = 0x00;
  Serial.begin(2000000);

  lcd1.init();
  while (true) {
    //checking and storing right ir sensor
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(checkbit(ADCSRA, bit(ADSC))){
      left_ir = ADCW;
    }

    //checking and storing left ir sensor
    ADMUX = 0x41;
    ADCSRA = 0xC7;
    
    while(checkbit(ADCSRA, bit(ADSC))){
      right_ir = ADCW;
    }

    lcd1.cmd(0x01);
    lcd1.line1(0);
    lcd1.string("left:");
    lcd1.showvalue(left_ir);
    lcd1.line2(0);
    lcd1.string("right:");
    lcd1.showvalue(right_ir);

    if((right_ir > 500) && (left_ir > 500)){
      PORTD = 0x00;
    }
    else if((right_ir > 500) && (left_ir < 500)) {
      PORTD = 0x40;
    }
    else if((right_ir < 500) && (left_ir > 500)){
      PORTD = 0x20;
    }
    else {
      PORTD = 0x60;
    }
    _delay_ms(200);
  }
}
