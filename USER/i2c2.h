#ifndef _I2C2_H_
#define _I2C2_H_
#endif

#define I2C2_SCL_PIN  GPIO_Pin_1
#define I2C2_SDA_PIN  GPIO_Pin_0
#define I2C2_SCL_PORT GPIOB
#define I2C2_SDA_PORT GPIOB

#define I2C2_SCL_Set()  GPIO_WriteBit(I2C2_SCL_PORT, I2C2_SCL_PIN, Bit_SET)
#define I2C2_SCL_Clr()  GPIO_WriteBit(I2C2_SCL_PORT, I2C2_SCL_PIN, Bit_RESET)

#define I2C2_SDA_Set()  GPIO_WriteBit(I2C2_SDA_PORT, I2C2_SDA_PIN, Bit_SET)
#define I2C2_SDA_Clr()  GPIO_WriteBit(I2C2_SDA_PORT, I2C2_SDA_PIN, Bit_RESET)

#define I2C2_SDA_Get()  GPIO_ReadInputDataBit(I2C2_SDA_PORT, I2C2_SDA_PIN)

extern void Multiple2_Read_QMC5883(void);
extern void init_i2c2(void);
extern void I2C2_SDAMode(uint8_t Mode);
extern void I2C2_Start(void);
extern void I2C2_Stop(void);
extern bool I2C2_WaitForAck(void);
extern void I2C2_Ack(void);
extern void I2C2_NAck(void);
extern void I2C2_WriteByte(uint8_t Data);
extern bool I2C2_WriteOneByte( uint8_t RegAddr,uint8_t Data);
extern bool I2C2_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
extern uint8_t I2C2_ReadByte(void);
extern bool I2C2_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val);
extern bool I2C2_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
