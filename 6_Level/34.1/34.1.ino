#include <obotz_level6_stepper_motor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int c = 0, d = 0;
char data;

ISR(USART1_RX_vect)
{
  data = UDR1;
}

int main(void)
{
  DDRD = 0xFF;
  UCSR1B = 0x90;
  UCSR1C = 0x06;
  SREG = 0x80;
  UCSR1A = 0x00;
  UBRR1H = 0x00;
  UBRR1L = 0x67;
  Serial.begin(9600);
  while (true) {
    Serial.println(data);
    if(data == '1'){
      c++;
      antistepper();
      _delay_ms(50);
    }
    if(data == '2'){
      d++;
      clkstepper();
      _delay_ms(50);
    }
    if(data == '3')
      PORTD = 0x00;     
  }
}
