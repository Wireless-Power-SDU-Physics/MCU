#ifndef AD5252_h
#define AD5252_h

#include<Wire.h>

class AD5252{
    private:
        static void setR(uint8_t channel,uint8_t R);
        static int readR(uint8_t channel);
    public:
        AD5252();
        static void setR1(uint8_t R1);
        static void setR2(uint8_t R2);
        static int readR1();
        static int readR2();
        static void setup();
};

extern AD5252 TwoAD5252;

#endif