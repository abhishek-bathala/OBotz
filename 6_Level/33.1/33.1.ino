#include <LCD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int c = 0, d = 0;
char data;
LCD lcd;

ISR(USART1_RX_vect)
{
  data = UDR1;
}

int main(void)
{
  DDRB = 0xFF;
  UCSR1B = 0x90;
  UCSR1C = 0x06;
  SREG = 0x80;
  UCSR1A = 0x00;
  UBRR1H = 0x00;
  UBRR1L = 0x67;
  Serial.begin(9600);
  lcd.init();
  lcd.cmd(0x0C);
  while (true) {
    Serial.println(data);
    if(data == '1'){
      lcd.cmd(0x00);
      lcd.line1(0);
      lcd.string("bluetooth data:");
      lcd.dispchar(data);
      lcd.line2(0);
      PORTB = 0xFF;
      lcd.string("Relay On");
    }
    if(data == '2'){
      lcd.cmd(0x00);
      lcd.line1(0);
      lcd.string("bluetooth data:");
      lcd.dispchar(data);
      lcd.line2(0);
      PORTB = 0x00;
      lcd.string("Relay Off");
    }
  }
}
