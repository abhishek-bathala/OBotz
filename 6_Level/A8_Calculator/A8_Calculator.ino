#include <LCD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int i = 0, digit;
long result, average;
String num1, num2;
int numOfNums = 0;
char operatorCalc = 'a';
char operation = 'a';
boolean numEntered = false;
boolean operatorEntered = false;

void compare()
{
  if(average >= 585 && average <= 595){
    PORTC = num[0];
    if(operatorEntered == true){
      num2 += "0";
    }
    else{
      num1 += "0";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 512 && average <= 522){
    PORTC = num[1];
    if(operatorEntered == true){
      num2 += "1";
    }
    else{
      num1 += "1";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 683 && average <= 693){
    PORTC = num[2];
    if(operatorEntered == true){
      num2 += "2";
    }
    else{
      num1 += "2";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 763 && average <= 773){
    PORTC = num[3];
    if(operatorEntered == true){
      num2 += "3";
    }
    else{
      num1 += "3";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 481 && average <= 491){
    PORTC = num[4];
    if(operatorEntered == true){
      num2 += "4";
    }
    else{
      num1 += "4";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 631 && average <= 641){
    PORTC = num[5];
    if(operatorEntered == true){
      num2 += "5";
    }
    else{
      num1 += "5";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 700 && average <= 710){
    PORTC = num[6];
    if(operatorEntered == true){
      num2 += "6";
    }
    else{
      num1 += "6";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 466 && average <= 476){
    PORTC = num[7];
    if(operatorEntered == true){
      num2 += "7";
    }
    else{
      num1 += "7";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 605 && average <= 615){
    PORTC = num[8];
    if(operatorEntered == true){
      num2 += "8";
    }
    else{
      num1 += "8";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 668 && average <= 678){
    PORTC = num[9];
    if(operatorEntered == true){
      num2 += "9";
    }
    else{
      num1 += "9";
    }
    numEntered = true;
    operatorEntered = false;
  }
  if(average >= 1001 && average <= 1011){
    PORTC = num[10];
    operation = '+';
    numEntered = false;
    operatorEntered = true;
  }
  if(average >= 895 && average <= 905){
    PORTC = num[11];
    operation = '-';
    numEntered = false;
    operatorEntered = true;
  }
  if(average >= 844 && average <= 854){
    PORTC = num[12];
    operation = '*';
    numEntered = false;
    operatorEntered = true;
  }
  if(average >= 806 && average <= 816){
    PORTC = num[13];
    operation = '/';
    numEntered = false;
    operatorEntered = true;
  }
  if(average >= 643 && average <= 653){
    PORTC = num[14];
    operatorCalc = 'c';
    numEntered = false;
    operatorEntered = true;
    resetCalc();
    numOfNums = 0;
  }
  if(average >= 454 && average <= 464){
    PORTC = num[15];
    operatorCalc = 'e';
    numEntered = false;
    operatorEntered = true;
  }

  Serial.print(num1);
  Serial.print(operation);
  Serial.print(num2);
  Serial.println(operatorCalc);

  if(operatorCalc == 'e'){
    float answer;
    int int1 = num1.toInt();
    int int2 = num2.toInt();
    if(operation == '+'){
      answer = int1 + int2;
    }
    else if(operation == '-'){
      answer = int1 - int2;
    }
    else if(operation == '*'){
      answer = int1*int2;
    }
    else if(operation == '/'){
      answer = int1/int2;
    }
    Serial.print("Answer is");
    Serial.println(answer);
  }
  _delay_ms(250);
}

void resetCalc()
{
  num1 = "";
  num2 = "";
  numEntered = false;
  operatorEntered = false;
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
  resetCalc();
  LCD lcd;
  lcd.init();
  lcd.cmd(0x01);
  lcd.line1(0);
  while(true)
  {
    lcd.string("1");
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
  }
}
