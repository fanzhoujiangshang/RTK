#include "main.h"

void init_i2c1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //     GPIO_Mode_Out_PP
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //     GPIO_Mode_Out_PP
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 
}


void I2C_SDAMode(uint8_t Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	if (Mode)
    {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_PP
    }
	else
    {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void I2C_Start(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	I2C_SDA_Set();
	I2C_SCL_Set();
	delay();
	I2C_SDA_Clr();
	delay();
	I2C_SCL_Clr();
}

void I2C_Stop(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	I2C_SDA_Clr();
	I2C_SCL_Set();
    delay();
	I2C_SDA_Set();
    delay();
}

bool I2C_WaitForAck(void)
{
    u8 data;
	I2C_SDAMode(I2C_SDA_IN);
    I2C_SCL_Set();
	delay();
	if(I2C_SDA_Get())
	{
		data = 1;
	}
	else 
	{
		data = 0;
	}
	I2C_SCL_Clr();
	delay();
	return data;
}

void I2C_Ack(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
    I2C_SCL_Clr();
    delay();
    I2C_SDA_Clr();
    delay();
    I2C_SCL_Set();
    delay();
    I2C_SCL_Clr();
}

void I2C_NAck(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
    I2C_SCL_Clr();
    I2C_SDA_Set();
    delay();
    I2C_SCL_Set();
    delay();
    I2C_SCL_Clr();
}

void I2C_WriteByte(uint8_t Data)
{
	uint8_t i;
	I2C_SDAMode(I2C_SDA_OUT);
	for (i = 0; i < 8; i ++)
	{   
		if (Data & 0x80)
        {
			I2C_SDA_Set();
        }
		else
        {
			I2C_SDA_Clr();
        }
		delay();
		I2C_SCL_Set();
		delay();
		I2C_SCL_Clr();
		if(i == 7)
		{
			I2C_SDA_Set();
		}
		Data <<= 1;
		delay();
	}
    I2C_WaitForAck();
}

bool I2C_WriteOneByte( uint8_t RegAddr,uint8_t Data)
{
	I2C_Start();
	I2C_WriteByte(QMC_WRITE);
//	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
//	I2C_WaitForAck();
	I2C_WriteByte(Data);
//	I2C_WaitForAck();
	I2C_Stop();	
	return true;
}

bool I2C_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff)
{
	uint8_t i;	
	I2C_Start();
	I2C_WriteByte(QMC_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	for(i = 0;i < Num;i++)
	{
		I2C_WriteByte(*(pBuff + i));
		I2C_WaitForAck();
	}
	I2C_Stop();	
	
	return true;
}


uint8_t I2C_ReadByte(void)
{
	uint8_t i, RecDat = 0;
    I2C_SDA_Set();
	I2C_SDAMode(I2C_SDA_IN);
	delay();
	for(i = 0; i < 8; i ++)
	{
        I2C_SCL_Clr();
        delay();
		I2C_SCL_Set();
		delay();
        RecDat <<= 1;
		if(I2C_SDA_Get())
		{
			RecDat |= 0x01;
		}
		else
		{
			RecDat &= ~0x01;
		}
		I2C_SCL_Clr();
		delay();
	}
	return RecDat;
}

bool I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val)
{
	uint8_t TempVal = 0;
	I2C_Start();
	I2C_WriteByte(QMC_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	I2C_Start();
	I2C_WriteByte(QMC_READ);
	TempVal = I2C_ReadByte();
	I2C_NAck();
	I2C_Stop();	
	*Val = TempVal;
	return true;
}

bool I2C_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff)
{
	uint8_t i;
	I2C_Start();
	I2C_WriteByte(QMC_WRITE);
//	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
//	I2C_WaitForAck();
	I2C_Start();
	I2C_WriteByte(QMC_READ);
	for(i = 0;i<Num;i++)
	{
		if(i == Num - 1)
		{
			*(pBuff + i) = I2C_ReadByte();
			I2C_Ack();
		}
		else 
		{
			*(pBuff + i) = I2C_ReadByte();
			I2C_NAck();
		}
	}
	I2C_Stop();	
	return true;
}

u8 buf[6];
void Multiple_Read_QMC5883(void)
{
    u8 i;
    I2C_Start();
    I2C_WriteByte(Slave_Address);
    I2C_WriteByte(0x00);
    I2C_Start();
    I2C_WriteByte(Slave_Address+1);
    for(i=0;i<6;i++)
    {
        compass_str1.data_out[i] = I2C_ReadByte();
        if(i==5)
        {
            I2C_NAck();
        }
        else
        {
            I2C_Ack();
        }
     }
    I2C_Stop();
    delay();
}

