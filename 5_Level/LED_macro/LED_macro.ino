#include <avr/io.h>
#include <util/delay.h>
#define setbit(x,y)(x|=y)
#define clearbit(x,y)(x&=~y)
#define bitn(p)(0x01<<p)
#define blueon (setbit(PORTB, bit(4)));
#define blueoff (clearbit(PORTB, bit(4)));
