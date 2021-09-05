//Abhishek Question 5
#include <obotz_level6_servo_motor.h> //My own library for servo motor functions
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//bluetooth data
char data;
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int gate_open = 90;
int gate_close = 0;

ISR(USART1_RX_vect) //getting data from bluetooth
{
  data = UDR1;
  compare();
}

void compare() //setting the gate position depending on if up or down arrow key is pressed in bluetooth app
{
  if(data == '1'){
    angle1(gate_open);
    data = '0';
  }
  else if(data == '0'){
    angle1(gate_close);
    data = '0';
  }
}

int main(void)
{
  DDRB = 0xFF;
  DDRD = 0xFF;
  UCSR1B = 0x90;
  UCSR1C = 0x06;
  SREG = 0x80;
  UCSR1A = 0x00;
  UBRR1H = 0x00;
  UBRR1L = 0x67;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  Serial.begin(9600);
  while (true) {
  }
}
