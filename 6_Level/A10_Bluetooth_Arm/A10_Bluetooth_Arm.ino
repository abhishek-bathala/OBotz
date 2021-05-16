#include <obotz_level6_servo_motor.h>
#include <obotz_level6_stepper_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//stepper motor
int c = 0, d = 0;
//bluetooth data
char data;
//servo motor variables
int count = 0;
int count_angle1 = 0;
int count_angle2 = 0;
int count_angle3 = 0;
int base = 60;
int elbow = 60;
int finger = 60;

ISR(USART1_RX_vect)
{
  data = UDR1;
  compare();
}

void compare()
{
  if(data == '1'){
    base++;
    angle1(base);
    data = '0';
  }
  else if(data == '2'){
    base--;
    angle1(base);
    data = '0';
  }
  else if(data == '3'){
    elbow++;
    angle2(elbow);
    data = '0';
  }
  else if(data == '4'){
    elbow--;
    angle2(elbow);
    data = '0';
  }
  else if(data == '5'){
    finger += 10;
    angle3(finger);
    data = '0';
  }
  else if(data == '6'){
    finger -= 10;
    angle3(finger);
    data = '0';
  }
  else if(data == '7'){
    c++;
    antistepper();
    _delay_ms(50);
  }
  else if(data == '8'){
    d++;
    clkstepper();
    _delay_ms(50);
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
  OCR1A = 21;     //0.011ms = 1 count
  TCCR1A = 0x00;  //normal mode
  TCCR1B = 0x0A;  //CTC mode prescaler 8
  TIMSK1 = 0x02;  //interrupt for timer1
  Serial.begin(9600);
  while (true) {
    Serial.println(data);
  }
}
