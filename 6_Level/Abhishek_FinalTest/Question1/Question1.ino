//Abhishek Question 1
//Including libraries
#include <avr/io.h>
#include <util/delay.h>

//Array for SSD Values
int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

int main(void)
{
  //Setting pins for SSD as output
  DDRC = 0xFF;
  while (true) {
    //Setting SSD to show number 0
    PORTC = num[0];
    //wait 500 milliseconds
    _delay_ms(500);
    //Setting SSD to show number 1
    PORTC = num[1];
    //wait 500 milliseconds
    _delay_ms(500);    
  }
}
