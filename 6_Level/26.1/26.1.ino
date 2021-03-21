#include <obotz_level6_stepper_motor.h>
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
int c, d;
int main(void)
{
  LCD lcd;
  Serial.begin(2000000);
  lcd.init();
  while (true){
    ADMUX  = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      R2 = (10000/(1023-ADCW))*ADCW;
      R2 = log(R2);
      t = (1.0/(c1+c2*R2+c3*R2*R2*R2));
      t -= 273.15;

      //t_tens = (int)t;
      //t_decimal = (int)((t-t_tens)*100);
      t_string = (String)t;
      lcd.cmd(0x01);
      lcd.line1(0);
      lcd.string("Temp:");
      //Serial.print("Temp: ");
      //Serial.println(t);
      //Serial.println("C");
      lcd.showvalue(t);
      _delay_ms(500);
    }
  }
}
