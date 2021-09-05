//Abhishek Question 2
//Stepper Motor Library is used in this program
#include <obotz_level6_stepper_motor.h>

#include <avr/io.h>
#include <util/delay.h>

#define BITN(BIT_NUM)               (0x01 << (BIT_NUM))
#define SET_BIT(PORT, BIT_NUM)      ((PORT) |= (BITN(BIT_NUM)))
#define CHECK_BIT(PORT, BIT_NUM)    ((PORT) & (BITN(BIT_NUM)))
#define CLEAR_BIT(PORT, BIT_NUM)    ((PORT) &= (~(BITN(BIT_NUM))))
//Stepper motor variables
int c, d; 
int main(void)
{
  //Stepper motor is not working, so getting the output with serial monitor
  Serial.begin(2000000); //Serial being for serial monitor
  DDRB = 0x00; //to make pins for input from switch
  DDRC = 0xFF; //to make pins for stepper motor as output
  while (true) {
    if(CHECK_BIT(PINB, 1)){ //if onboard tact switch is pressed
      d += 4; //d += 4 because ++ increases angle by 7.5, so 30 degrees means times 4
      clkstepper(); //calling clkstepper function to spin stepper motor
      Serial.println("Pressed, stepper motor should spin 30 degrees"); //using this because stepper motor is not working
      _delay_ms(200);
    }
  }
}
