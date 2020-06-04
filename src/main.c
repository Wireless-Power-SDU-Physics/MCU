//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <AD5252.h>

uint16_t i;
void setup() {
  AD5252_setup(); //Initialise I2C communication with AD5252

  DDRB |= (1 << DDB1) | (1 << DDB2); //set Pins to output

  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set for 1hz in Fast PWM mode
  ICR1 = 13241;// = (13.56*10^6) / (1*1024) - 1 (must be <65536)
  // Set OCR1A OCR1B
  OCR1A = ICR1/2;
  OCR1B = ICR1/2;
  // turn on Fast PWM mode (ICR1 as TOP)
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  //TCCR1B |= (1 << CS10);
  // OC1A/OC1B on Compare Match
  TCCR1A |= (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1);
  // enable timer compare interrupt
  //TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  i++;
}


void loop() {
}