#ifndef _SPI_H_
#define _SPI_H_
#endif

#define LSP_CS_PORT GPIOB
#define LSP_CS_PIN  GPIO_Pin_13

#define LPS_CS_HIGH GPIO_SetBits(LSP_CS_PORT,GPIO_Pin_12)
//#define LPS_CS_HIGH GPIO_ResetBits(LSP_CS_PORT,GPIO_Pin_12)
#define LPS_CS_LOW  GPIO_ResetBits(LSP_CS_PORT,GPIO_Pin_12)

#define LPS22HB_SPI_READ  0x80
#define LPS22HB_SPI_WRITE 0x00

extern void init_spi2(void);
extern u8 SPI2_ReadWriteByte(u8 TxData);
extern u8 LPS22HB_SPIx_Read(u8 reg_addr);
extern int LPS22HB_SPIx_Reads(u8 reg_addr, u8 len, u8* data);
extern int LPS22HB_SPIx_Write(u8 reg_addr,u8 data);
extern int LPS22HB_SPIx_Writes(u8 reg_addr, u8 len, u8* data);
