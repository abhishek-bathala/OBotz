#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
int num[] = {0xF6, 0x60, 0xD5, 0xF1, 0x63, 0xB3, 0xB7, 0xE0, 0xF7, 0xF3, 0x3D, 0x37, 0x96, 0x75, 0x66, 0x90};

int main(void)
{
  DDRC = 0xFF;
  while (true) {
    PORTC = num[0];
    _delay_ms(1000);
    PORTC = num[1];
    _delay_ms(1000);    
  }
}
