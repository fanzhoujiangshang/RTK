#ifndef _BAROMETER_H_
#define _BAROMETER_H_
#endif

#define LPS22HB_INTERRUPT_CFG (0x0B)
#define LPS22HB_THS_P_L       (0x0C)
#define LPS22HB_THS_P_H       (0x0D)
#define LPS22HB_WHO_AM_I      (0x0F)
#define LPS22HB_CTRL_REG1     (0x10)
#define LPS22HB_CTRL_REG2     (0x11)
#define LPS22HB_CTRL_REG3     (0x12)
#define LPS22HB_FIFO_CTRL     (0x14)
#define LPS22HB_REF_P_XL      (0x15)
#define LPS22HB_REF_P_L       (0x16)
#define LPS22HB_REF_P_H       (0x17)
#define LPS22HB_RPDS_L        (0x18)
#define LPS22HB_RPDS_H        (0x19)
#define LPS22HB_RES_CONF      (0x1A)
#define LPS22HB_INT_SOURCE    (0x25)
#define LPS22HB_FIFO_STATUS   (0x26)
#define LPS22HB_STATUS        (0x27)
#define LPS22HB_PRESS_OUT_XL  (0x28)
#define LPS22HB_PRESS_OUT_L   (0x29)
#define LPS22HB_PRESS_OUT_H   (0x2A)
#define LPS22HB_TEMP_OUT_L    (0x2B)
#define LPS22HB_TEMP_OUT_H    (0x2C)
#define LPS22HB_LPFP_RES      (0x33)

typedef struct
{
    u8 id;
    u8 press_out[3];
    u8 temp_out[2];
}_LPS22HB_str_t;

typedef struct
{
    float press;
    float temperature;
    int height;
}_barometer_str_t;

extern void init_LPS22HB(void);
extern void BAROMETER_Handle(void);
