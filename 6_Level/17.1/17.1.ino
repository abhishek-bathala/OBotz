#include <obotz_level6_servo_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//servo variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int a = 0;

void compare(int x, int y)
{
  //if(x == 506 || y == 506 || x == 498 || y == 498){
  //  PORTD = 0x00;
  //}
  if(y > 800){ //up
    a += 20;
  }
  else if(y < 100){ //down
    a -= 20;
  }
  else{
    PORTD = 0x00;
  }
  Serial.println("Servo angle:");
  Serial.println(a);
  angle3(a);

  if(a == 180){
    a = 0;
  }
}

int main(void)
{
  Serial.begin(2000000);
  DDRA = 0x00;
  DDRB = 0xFF;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  SREG = 0x80;    //Enable global interrupt
  int x = 0;
  int y = 0;
  
  while(true)
  {
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }

    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }
    
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);
    compare(x, y);
    _delay_ms(250);
  }
}
