#include <obotz_level6_servo_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
char data;
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;

ISR(USART1_RX_vect)
{
  data = UDR1;
  compare();
}

void compare()
{
  if(data == '1'){
    angle1(0);
    data = '0';
  }
  else if(data == '0'){
    angle1(90);
    data = '0';
  }
}

int main(void)
{
  Serial.begin(9600);
  DDRB = 0xFF;
  DDRD = 0xFF;
  UCSR1B = 0x90;
  UCSR1C = 0x06;
  SREG = 0x80;
  UCSR1A = 0x00;
  UBRR1H = 0x00;
  UBRR1L = 0x67;
  TCNT1 = 0x00;
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  while (true) {
    Serial.println(data);    
  }
}
