#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int number[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

long result, average;
int count = 0;

char data;

ISR(USART1_RX_vect)
{
  data = UDR1;
}

int main(void)
{
  DDRC = 0xFF;
  UCSR1B = 0x90;
  UCSR1C = 0x06;
  SREG = 0x80;
  UCSR1A = 0x00;
  UBRR1H = 0x00;
  UBRR1L = 0x67;
  Serial.begin(9600);
  while (true) {
    Serial.println(data);
    if(data == '0')
      PORTC = number[0];
    else if(data == '1')
      PORTC = number[1];
    else if(data == '2')
      PORTC = number[2];
    else if(data == '3')
      PORTC = number[3];
    else if(data == '4')
      PORTC = number[4];
    else if(data == '5')
      PORTC = number[5];
    else if(data == '6')
      PORTC = number[6];
    else if(data == '7')
      PORTC = number[7];
    else if(data == '8')
      PORTC = number[8];
    else if(data == '9')
      PORTC = number[9];
  }
}
