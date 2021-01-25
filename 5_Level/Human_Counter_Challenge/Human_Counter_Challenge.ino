#include <avr/io.h>
#include <util/delay.h>

#define IR_THRESHOLD 500

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))

int main (void)
{
  int ir = 0;
  int person = 0; //if person is in front of ir sensor, value is 1, if no person is infront of sensor, value is 0
  int count = 0;
  Serial.begin(2000000);
  DDRB = 0xFF;
  DDRA = 0x00;

  while (true) {
    //checking and storing right ir sensor
    ADMUX = 0x40;
    ADCSRA = 0xC7;
    while(CHECK_BIT(ADCSRA, ADSC)){
      ir = ADCW;
    }

    if(ir < IR_THRESHOLD){
      person = 1;
    }

    if(ir > IR_THRESHOLD && person == 1 && count < 10){
      count += 1;
      Serial.println(count);
      person = 0;
      _delay_ms(500);
    }

    if(count == 10){
      PORTB = 0xFF;
    }

    if(CHECK_BIT(PIND, 2)){
      PORTB = 0x00;
      count = 0;
    }
  }
}
