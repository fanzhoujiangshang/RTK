#include "main.h"

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler) 
{    
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));  
    SPI2->CR1&=0XFFC7;  
    SPI2->CR1|=SPI_BaudRatePrescaler;         
    SPI_Cmd(SPI2,ENABLE);  
}

u8 SPI2_ReadWriteByte(u8 TxData) 
{    
    u8 retry=0;       
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)         
    {   
        retry++;   
        if(retry>200)
            return 0;   
    }       
    SPI_I2S_SendData(SPI2, TxData);           
    retry=0;  
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 
    {   
        retry++;   
        if(retry>200)
            return 0;  
    }    
    return SPI_I2S_ReceiveData(SPI2);         
}

u8 LPS22HB_SPIx_Read(u8 reg_addr)
{
	u8 dummy = 0;
	u8 data = 0;
	LPS_CS_LOW;
	SPI2_ReadWriteByte(LPS22HB_SPI_READ | reg_addr);
	data = SPI2_ReadWriteByte(dummy);
    LPS_CS_HIGH;
	return data;
}

int LPS22HB_SPIx_Reads(u8 reg_addr, u8 len, u8* data){
	u32 i = 0;
	u8 dummy = 0x00;
	LPS_CS_LOW;
	SPI2_ReadWriteByte(LPS22HB_SPI_READ | reg_addr);
	while(i < len){
		data[i++] = SPI2_ReadWriteByte(dummy);
	}
     LPS_CS_HIGH;
	return 0;
}

int LPS22HB_SPIx_Write(u8 reg_addr,u8 data){
	LPS_CS_LOW;
	SPI2_ReadWriteByte(reg_addr);
	SPI2_ReadWriteByte(data);
	LPS_CS_HIGH;
	return 0;
}

int LPS22HB_SPIx_Writes(u8 reg_addr, u8 len, u8* data){
	u32 i = 0;
	LPS_CS_LOW;
	SPI2_ReadWriteByte(reg_addr);
	while(i < len){
		SPI2_ReadWriteByte(data[i++]);
	}
    LPS_CS_HIGH;
	return 0;
}

void init_spi2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;    
    SPI_InitTypeDef  SPI_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE );
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);                       
    GPIO_SetBits(GPIOB,GPIO_Pin_12);   
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13  | GPIO_Pin_15;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);                       
    GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_15); 

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 ;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);                       
    GPIO_SetBits(GPIOB,GPIO_Pin_14); 

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;     
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; 
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
    SPI_InitStructure.SPI_CRCPolynomial = 7;         
    SPI_Init(SPI2, &SPI_InitStructure); 

    SPI_Cmd(SPI2, ENABLE);                    
    SPI2_ReadWriteByte(0xff); 
}

