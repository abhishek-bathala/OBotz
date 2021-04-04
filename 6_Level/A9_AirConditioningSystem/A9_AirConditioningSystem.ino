#include <obotz_level6_ir_remote.h>
#include <LCD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define PowerUp 0x1FE48B7
#define tempUp 0x1FE609F
#define tempDown 0x1FEA05F

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

const float c1 = 0.001125308852122;
const float c2 = 0.000234711863267;
const float c3 = 0.000000085663516;
double R2, t;

long keycode = 0;
int timervalue;
int bitposition = 0;
int var = 0;
int currentTemp = 23;
int tempToSet = currentTemp;
boolean powerIsOn = false;
LCD lcd;

void compare()
{
  if(!powerIsOn){
    lcd.cmd(0x01);
    lcd.line1(0);
    lcd.string("AC is OFF");
  }
  
  if (keycode == PowerUp) {
    if (!powerIsOn) {
      Serial.println("Power On");
      powerIsOn = true;
    }
    else {
      Serial.println("Power Off");
      powerIsOn = false;
    }
  }

  if (powerIsOn && keycode == tempUp) {
    tempToSet++;
    changeTemperature();
    Serial.println(tempToSet);
  }
  if (powerIsOn && keycode == tempDown) {
    tempToSet--;
    changeTemperature();
    Serial.println(tempToSet);
  }
}
void changeTemperature()
{
  if (tempToSet < currentTemp) {
    while(tempToSet < currentTemp){
      PORTD = 0x08;
      checkTemperature();
    }
  }
  else{
    PORTD = 0x00;
  }
}

void displayTemp()
{
  lcd.cmd(0x01);
  lcd.line1(0);
  lcd.string("CurrentTemp:");
  checkTemperature();
  lcd.line1(12);
  lcd.showvalue(currentTemp);
  lcd.line2(0);
  lcd.string("SetTemp: ");
  lcd.showvalue(tempToSet);
}

void checkTemperature()
{
  ADMUX  = 0x40;
  ADCSRA = 0xC7;
  while(CHECK_BIT(ADCSRA, ADSC)){
    R2 = (10000/(1023-ADCW))*ADCW;
    R2 = log(R2);
    t = (1.0/(c1+c2*R2+c3*R2*R2*R2));
    t -= 273.15;
    currentTemp = t;
  }
}

int main(void)
{
  Serial.begin(2000000);
  lcd.init();
  DDRB = 0x80;
  DDRD = 0xFF;
  TIMSK0 = 0x01;
  EICRA = 0x20;
  EIMSK = 0x04;
  SREG = 0x80;
  TCCR0A = 0x00;
  TCCR0B = 0x0B;
  while (true)
  {
    PORTD = 0xFF;
    displayTemp();
    _delay_ms(200);
  }
}
