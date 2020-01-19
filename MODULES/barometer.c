#include "main.h"

_barometer_str_t barometer_str;
_LPS22HB_str_t   LPS22HB_str;

u8 spi_temp[6];

void init_LPS22HB(void)
{
    LPS22HB_SPIx_Reads(LPS22HB_WHO_AM_I, 1, (u8*)&LPS22HB_str);
    if(LPS22HB_str.id != 0xB1)
        return;
    LPS22HB_SPIx_Write(LPS22HB_CTRL_REG2,1<<2);
    LPS22HB_SPIx_Reads(LPS22HB_CTRL_REG2,1,spi_temp);
    LPS22HB_SPIx_Write(LPS22HB_CTRL_REG1,1<<6);
    
}

void BAROMETER_Handle()
{
    float temp;
    LPS22HB_SPIx_Reads(LPS22HB_PRESS_OUT_XL, 3, (u8 *)&LPS22HB_str.press_out);
    temp = LPS22HB_str.press_out[2]<<16 | LPS22HB_str.press_out[1]<<8 \
    | LPS22HB_str.press_out[0];
    barometer_str.press = temp / 4096.00f;
    
    LPS22HB_SPIx_Reads(LPS22HB_TEMP_OUT_L, 2, (u8 *)&LPS22HB_str.temp_out);
    temp = LPS22HB_str.temp_out[1]<<8 | LPS22HB_str.temp_out[0];
    barometer_str.temperature = temp / 100;
 // H=44300*(1- (P/P0)^(1/5.256) )   
    barometer_str.height = 44300*(1 - pow((barometer_str.press/1013.25f),1/5.256f));
}
