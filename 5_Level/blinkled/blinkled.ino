#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRD = 0b00000001;
   while(1){
    PORTD = 0b00000001;
   }
}
