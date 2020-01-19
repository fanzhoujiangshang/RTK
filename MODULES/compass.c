#include "main.h"

_compass_str_t compass_str1;
_compass_str_t compass_str2;

void init_QMC1()
{
    I2C_WriteOneByte(0x09,0x0d);
    I2C_WriteOneByte(0x0b,0x01);
    I2C_WriteOneByte(0x20,0x40);
    I2C_WriteOneByte(0x21,0x01);
    
}

void init_QMC2()
{
    I2C2_WriteOneByte(0x09,0x0d);
    I2C2_WriteOneByte(0x0b,0x01);
    I2C2_WriteOneByte(0x20,0x40);
    I2C2_WriteOneByte(0x21,0x01);
}

void init_QMC5883(void)
{
    init_QMC1();
    init_QMC2();
}


void QMC_Handle(void)
{
    Multiple_Read_QMC5883();
    compass_str1.X = compass_str1.data_out[1]<<8|compass_str1.data_out[0];
    compass_str1.Y = compass_str1.data_out[3]<<8|compass_str1.data_out[2];
    compass_str1.Z = compass_str1.data_out[5]<<8|compass_str1.data_out[4];
    
    if(compass_str1.X>0x7fff) compass_str1.X-=0xffff;      
    if(compass_str1.Y>0x7fff) compass_str1.Y-=0xffff;   
    if(compass_str1.Z>0x7fff) compass_str1.Z-=0xffff;
    
    Multiple2_Read_QMC5883();
    compass_str2.X = compass_str2.data_out[1]<<8|compass_str2.data_out[0];
    compass_str2.Y = compass_str2.data_out[3]<<8|compass_str2.data_out[2];
    compass_str2.Z = compass_str2.data_out[5]<<8|compass_str2.data_out[4];
    
    if(compass_str2.X>0x7fff) compass_str2.X-=0xffff;      
    if(compass_str2.Y>0x7fff) compass_str2.Y-=0xffff;   
    if(compass_str2.Z>0x7fff) compass_str2.Z-=0xffff;
    
}
