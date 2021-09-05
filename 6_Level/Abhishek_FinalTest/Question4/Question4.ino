//Abhishek Question 4
//LCD is not working properly, so I am using serial monitor to display output. The code for LCD is still present, but it is commented out.
#include <avr/io.h>
#include <util/delay.h>
#include <LCD.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int x, y;

int main(void)
{
  //LCD lcd; //constructing lcd object
  //lcd.init(); //initializing lcd
  Serial.begin(2000000);
  DDRA = 0x00; //setting joystick pins to input
  while (true) {
    //clearing LCD
    //lcd.cmd(0x01);
    //getting y axis value for joystick
    ADMUX = 0x42;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      y = ADCW;
    }
    //getting x axis value for joystick
    ADMUX = 0x43;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      x = ADCW;
    }

    
    if(y > 700){ //if joystick is up
      //lcd.string("up"); //display up on LCD
      Serial.println("up");
    }
    else if(y < 100){ //if joystick is down
      //lcd.string("down"); //display down on LCD
      Serial.println("down");
    }
    else if(x > 700)
    {
      //lcd.string("left"); //display left on LCD
      Serial.println("left");
    }
    else if(x < 100)
    {
      //lcd.string("right"); //display right on LCD
      Serial.println("right");
    }
    
    /*Serial.print("x: ");  
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);*/
    _delay_ms(100);
  }
}
