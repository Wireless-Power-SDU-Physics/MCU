//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "AD5252.h"

void setup() {
  //AD5252::setup(); //Initialise I2C communication with AD5252
  //AD5252::setR1(255);
  //AD5252::setR2(255);

  DDRB |= (1 << DDB1) | (1 << DDB2); //set Pins to output

  cli();//stop interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set for Fast PWM mode
  ICR1 = 15;// ICR1 is the Top value for  (must be <65536)
  // Set OCR1A OCR1B
  OCR1A = (ICR1 - 1)/2;
  OCR1B = (ICR1 - 1)/2;
  // turn on Fast PWM mode (ICR1 as TOP)
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  // Set CS10 and CS12 bits for 1024 prescaler
  //TCCR1B |= (1 << CS12) | (1 << CS10);
  TCCR1B |= (1 << CS11); //no prescaler:(CS10); prescaler 8:(CS11)
  // OC1A/OC1B on Compare Match (OC1B in invert mode)
  TCCR1A |= (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1);
  // enable timer compare interrupt
  //TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts

  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt, not used
}


void loop() {
  //Serial.println("Hi");
  //int R1 = AD5252::readR1();
  //int R2 = AD5252::readR2();
  //Serial.println(R1);
  //Serial.println(R2);
  delay(1000);
}