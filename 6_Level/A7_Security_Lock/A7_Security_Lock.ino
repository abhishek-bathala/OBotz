#include <obotz_level6_servo_motor.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};
int passcode[4] = {10, 11, 12, 13};
int userenter[4] = {0, 0, 0, 0};
int digitsnum = -1;
boolean correct = false;
boolean gateIsOpen = false;

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
#define GATE_OPEN 90
#define GATE_CLOSE 0
int i = 0, digit;
long result, average;
int count = 0, count_angle1 = 0, count_angle2 = 0, count_angle3 = 0;

void compare()
{
  if(average >= 585 && average <= 595){
    PORTC = num[0];
    digit = 0;
  }
  if(average >= 512 && average <= 522){
    PORTC = num[1];
    digit = 1;
  }
  if(average >= 683 && average <= 693){
    PORTC = num[2];
    digit = 2;
  }
  if(average >= 763 && average <= 773){
    PORTC = num[3];
    digit = 3;
  }
  if(average >= 481 && average <= 491){
    PORTC = num[4];
    digit = 4;
  }
  if(average >= 631 && average <= 641){
    PORTC = num[5];
    digit = 5;
  }
  if(average >= 700 && average <= 710){
    PORTC = num[6];
    digit = 6;
  }
  if(average >= 466 && average <= 476){
    PORTC = num[7];
    digit = 7;
  }
  if(average >= 605 && average <= 615){
    PORTC = num[8];
    digit = 8;
  }
  if(average >= 668 && average <= 678){
    PORTC = num[9];
    digit = 9;
  }
  if(average >= 1001 && average <= 1011){
    PORTC = num[10];
    digit = 10;
  }
  if(average >= 895 && average <= 905){
    PORTC = num[11];
    digit = 11;
  }
  if(average >= 844 && average <= 854){
    PORTC = num[12];
    digit = 12;
  }
  if(average >= 806 && average <= 816){
    PORTC = num[13];
    digit = 13;
  }
  if(average >= 643 && average <= 653){
    PORTC = num[14];
    digit = 14;
  }
  if(average >= 454 && average <= 464){
    PORTC = num[15];
    digit = 15;
  }
  if(average >= 0 && average <= 3){
    PORTC = 0x00;
    digit = -1;
  }

  if(digit != -1){
    digitsnum += 1;
    userenter[digitsnum] = digit;
    if(digitsnum == 3){
      digitsnum = -1;
    }
  }

  for(int i = 0; i < 4; i++){
    if(userenter[i] == passcode[i]){
      correct = true;
    }
    else{
      correct = false;
      break;
    }
  }

  if(correct == true){
    angle2(GATE_OPEN);
    Serial.println("Gate open");
    gateIsOpen = true;
    
  }
  if(gateIsOpen == true){
    do{
      Serial.println("Gate is still open");
      _delay_ms(100);
      ADMUX = 0x44;
      ADCSRA = 0xC7;
      while(CHECK_BIT(ADCSRA, ADSC));
      result += ADCW;
      i++;
      if(i > 99){
        average = result/100;
        //Serial.println(average);
        compare();
        result = 0;
        average = 0;
        i = 0;
      }
    }while(average <=3);
    angle2(GATE_CLOSE);
    Serial.println("Gate close");
    gateIsOpen = false;
    userenter[0] = 0;
    userenter[1] = 0;
    userenter[2] = 0;
    userenter[3] = 0;
  }
  
  /*if(gateIsOpen == true && digit == 15){
    angle2(GATE_CLOSE);
    Serial.println("Gate is close");
    digitsnum = 3;
    correct = false;
    userenter[0] = 15;
    userenter[1] = 15;
    userenter[2] = 15;
    userenter[3] = 15;
  }*/
  _delay_ms(250);
}

int main(void)
{
  Serial.begin(2000000);
  DDRC = 0xFF;
  PORTD = 0x00;
  DDRB = 0xFF;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  SREG = 0x80;    //Enable global interrupt
  while(true)
  {
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if(i > 99){
      average = result/100;
      //Serial.println(average);
      compare();
      result = 0;
      average = 0;
      i = 0;
      Serial.print("User entered: ");
      for(int i = 0; i < 4; i++){
        Serial.print(userenter[i]);
        Serial.print(" ");
      }
      Serial.println("");
    }
  }
}
