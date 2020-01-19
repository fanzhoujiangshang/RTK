#ifndef _I2C1_H_
#define _I2C1_H_
#endif

#define I2C_SCL_PIN  GPIO_Pin_6
#define I2C_SDA_PIN  GPIO_Pin_7
#define I2C_SCL_PORT GPIOB
#define I2C_SDA_PORT GPIOB

enum {
    I2C_SDA_IN,
	I2C_SDA_OUT
};

enum {
	I2C_ACK,
	I2C_NACK
};

#define QMC_WRITE		0x1A
#define QMC_READ 		0x1B

#define I2C_SCL_Set()  GPIO_WriteBit(I2C_SCL_PORT, I2C_SCL_PIN, Bit_SET)
#define I2C_SCL_Clr()  GPIO_WriteBit(I2C_SCL_PORT, I2C_SCL_PIN, Bit_RESET)

#define I2C_SDA_Set()  GPIO_WriteBit(I2C_SDA_PORT, I2C_SDA_PIN, Bit_SET)
#define I2C_SDA_Clr()  GPIO_WriteBit(I2C_SDA_PORT, I2C_SDA_PIN, Bit_RESET)

#define I2C_SDA_Get()  GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)

#define  Slave_Address   0x1a  
#define  delay()    delay_us(5);

extern void init_i2c1(void);
extern void I2C_SDAMode(uint8_t Mode);
extern void I2C_Start(void);
extern void I2C_Stop(void);
extern bool I2C_WaitForAck(void);
extern void I2C_Ack(void);
extern void I2C_NAck(void);
extern void I2C_WriteByte(uint8_t Data);
extern bool I2C_WriteOneByte( uint8_t RegAddr,uint8_t Data);
extern bool I2C_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
extern uint8_t I2C_ReadByte(void);
extern bool I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val);
extern bool I2C_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
extern void Multiple_Read_QMC5883(void);

