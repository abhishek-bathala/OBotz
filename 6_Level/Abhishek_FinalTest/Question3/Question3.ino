//Abhishek Question 3
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

//Array for SSD values
int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};
//variables for Keypad
long result;
long average;
int i;

//if certain keypad values are there, respective numbers on SSD are displayed
void compare()
{
  if(average > 510 && average < 520) //if 1 key is pressed
    PORTC = num[1]; //display 1 on SSD
  if(average > 680 && average < 690) //if 2 key is pressed
    PORTC = num[2]; //display 2 on SSD
  if(average > 760 && average < 770) //if 3 key is pressed
    PORTC = num[3]; //display 3 on SSD
  if(average > 480 && average < 490) //if 4 key is pressed
    PORTC = num[4]; //display 4 on SSD
  if(average > 630 && average < 640) //if 5 key is pressed
    PORTC = num[5]; //display 5 on SSD
}

int main(void)
{
  DDRC = 0xFF;
  PORTD = 0x00;
  while (true) {
    //Getting the value from keypad
    ADMUX = 0x44;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC));
    result += ADCW;
    i++;
    if(i > 99){
      average = result/100; //calculating average from keypad values
      compare(); //calling compare function to display respective numbers on SSD
      //resetting variables for next average calculation
      result = 0;
      average = 0;
      i = 0;  
    }
  }
}
