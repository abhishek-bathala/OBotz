#include <obotz_level6_servo_motor.h>
#include <LCD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

const float c1 = 0.001125308852122;
const float c2 = 0.000234711863267;
const float c3 = 0.000000085663516;
double R2, t;
double t_tens, t_decimal;
String t_string;
int count = 0;
int count_angle1 = 0, count_angle2 = 0, count_angle3 = 0;
int main(void)
{
  
  DDRC = 0xFF;
  DDRB = 0xFF;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  Serial.begin(2000000);
  //LCD lcd;
  //lcd.init();
  while (true){
    ADMUX  = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      R2 = (10000/(1023-ADCW))*ADCW;
      R2 = log(R2);
      t = (1.0/(c1+c2*R2+c3*R2*R2*R2));
      t -= 273.15;
      Serial.println(t);
      //lcd.cmd(0x01);
      //lcd.line1(0);
      //lcd.showvalue(t);
      if(t > 27){
        angle3(90);
        PORTC = 0x08;
        //lcd.string("Buzzer On");
      }
      else{
        angle3(0);
        PORTC = 0x00;
        //lcd.string("Buzzer Off");
      }

      _delay_ms(200);
    }
  }
}
