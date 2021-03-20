#include <obotz_level6_stepper_motor.h>
#include <obotz_level6_servo_motor.h>
#include <obotz_level6_ir_remote.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
int pressed = 0;
long keycode = 0;

//stepper motor variables
int c = 0;
int d = 0;

//servo variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int base = 60;
int elbow = 60;
int finger = 60;

//timer variables
int timervalue = 0;
int bitposition = 0;
int var = 0;

void compare()
{
  //Serial.println(keycode, HEX);
  if(keycode == KEY1){
    base += 5;
    angle1(base);
  }
  if(keycode == KEY2){
    base -= 5;
    angle1(base);
  }
  if(keycode == KEY3){
    elbow += 5;
    angle2(elbow);
  }
  if(keycode == KEY4){
    elbow -= 5;
    angle2(elbow);
  }
  if(keycode == KEY5){
    finger += 10;
    angle3(finger);
  }
  if(keycode == KEY6){
    finger -= 10;
    angle3(finger);
  }
  if(keycode == KEY7){
    c++;
    antistepper();
    _delay_ms(50);
  }
  if(keycode == KEY8){
    d++;
    clkstepper();
    _delay_ms(50);
  }  
}

int main(void)
{
  //Serial.begin(2000000);
  DDRD = 0xFF;
  DDRB = 0x00;
  TIMSK0 = 0x01; //enable timer 0 interrupt
  EICRA = 0x20;
  EIMSK = 0x04;
  SREG = 0x80;    //Enable global interrupt
  TCCR0A = 0x00;
  TCCR0B = 0x03;
  TCNT1 = 0x00;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1

  while(true)
  {
  }
}
