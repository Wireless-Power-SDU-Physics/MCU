软件设计
=============
## AD5252.h
AD5252.h文件为我们自主编写的AD5252双通道数字电位器的控制相关库。其提供了设置AD5252电位器特定通道阻值、读取其特定通道阻值的功能。
该头文件定义了AD5252类，该类下包含了5个函数：
|函数|功能|
|------|------|
|AD5252.setR1(int)|设定R1电阻大小（输入范围：0～255）|
|AD5252.setR2(int)|设定R2电阻大小（输入范围：0～255）|
|AD5252.readR1()|读取R1电阻大小（输出范围：0～255）|
|AD5252.readR2()|读取R2电阻大小（输出范围：0～255）|
|AD5252.setup()|初始化与AD5252链接总线，并将电位器拨片置中|

### 实现细节:
AD5252是一款具有256位双通道、I2C、非易失性存储器的数控电位计。可实现与机械电位计、调整器和可变电阻相同的电子调整功能。


我们使用I2C总线与AD5252芯片通信。在Arduino中，有Wire库提供I2C总线通讯的封装，我们利用这一库进行了AD5252相关代码的编写。

### 实现源码:
AD5252阻值设定：
```c/c++
void AD5252::setR(int channel,int R1){ //Set POT
	Wire.beginTransmission(Addr); //Start Transmission
	Wire.write(byte(channel)); //Send instruction for channel
	Wire.write(R1); //send resistance value
	Wire.endTransmission(); //Stop transmission
}
```

AD5252阻值读取：
```C/c++
int AD5252::readR(int channel){ //Read resistance
    Wire.beginTransmission(Addr);
    Wire.write(byte(channel)); //Send instruction for channel
    Wire.endTransmission();
    Wire.requestFrom(Addr,1); //Request 1 byte of data

    int data = -1; //If no return from chip,return -1
    //Read 1 byte if data available 
    if(Wire.available() == 1){
        data = Wire.read();
    }
    return data;
}
```


## main.cpp

为程序的主文件