#include<Wire.h>
#include "AD5252.h"

//AD5252 I2C adress is 0x2C(44)(0101100)
#define Addr 0x2C

AD5252::AD5252(){
};

void AD5252::setR(uint8_t channel,uint8_t R){ //Set POT
    Wire.beginTransmission(Addr); //Start Transmission
    Wire.write(byte(channel)); //Send instruction for channel
    Wire.write(R); //send resistance value
    Wire.endTransmission(); //Stop transmission
}

void AD5252::setR1(uint8_t R1){ //Set POT-1 resistance
    AD5252::setR(0x01,R1);
}

void AD5252::setR2(uint8_t R2){ //Set POT-3 resistance
    AD5252::setR(0x03,R2);
}

int AD5252::readR(uint8_t channel){ //Read resistance
    Wire.beginTransmission(Addr);
    Wire.write(byte(channel)); //Send instruction for channel
    Wire.endTransmission();
    Wire.requestFrom(Addr,1); //Request 1 byte of data

    int data = -1; //If no return from chip, return -1
    //Read 1 byte if data available
    if(Wire.available() == 1){
        data = Wire.read();
    }
    return data;
}

int AD5252::readR1(){ //Read POT-1 resistance
    int R1 = AD5252::readR(0x01);
    return R1;
}

int AD5252::readR2(){ //Read POT-3 resistance
    int R2 = AD5252::readR(0x03);
    return R2;
}

void AD5252::setup(){ //Setup AD5252
    DDRB |= (1 << DDB0);
    PORTB |= (1 << PORTB0);
    Wire.begin();   //Initialise I2C communication as Master
    Wire.setClock(100000);
    AD5252::setR1(0x80);
    AD5252::setR2(0x80);
}
