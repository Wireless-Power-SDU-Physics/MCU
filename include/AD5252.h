#include<Wire.h>

//AD5252 I2C adress is 0x2C(44)(0101100)
#define Addr 0x2C

void AD5252_setR(int channel,int R1){ //Set POT
    Wire.beginTransmission(Addr); //Start Transmission
    Wire.write(byte(channel)); //Send instruction for channel
    Wire.write(R1); //send resistance value
    Wire.endTransmission(); //Stop transmission
}

void AD5252_setR1(int R1){ //Set POT-1 resistance
    AD5252_setR(0x01,R1);
}

void AD5252_setR2(int R2){ //Set POT-3 resistance
    AD5252_setR(0x03,R2);
}

int AD5252_readR(int channel){ //Read resistance
    Wire.beginTransmission(Addr);
    Wire.write(byte(channel));
    Wire.endTransmission();
    Wire.requestFrom(Addr,1); //Request 1 byte of data

    int data = -256;
    //Read 1 byte if data
    if(Wire.available() == 1){
        data = Wire.read();
    }
    return data;
}

float AD5252_readR1(){ //Read POT-1 resistance
    float R1 = AD5252_readR(0x01);
    return R1;
}

float AD5252_readR2(){ //Read POT-3 resistance
    float R2 = AD5252_readR(0x03);
    return R2;
}

void AD5252_setup(){ //Setup AD5252
    DDRB |= (1 << DDB0);
    PORTB |= (1 << PORTB0);
    Wire.begin();   //Initialise I2C communication as Master
    Wire.setClock(100000);
    AD5252_setR1(0x80);
    AD5252_setR2(0x80);
}
