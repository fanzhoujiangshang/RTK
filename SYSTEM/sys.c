#include "main.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;	

void delay_init()   
{ 
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us=SystemCoreClock/8000000;
    fac_ms=(u16)fac_us*1000;
}

void delay_us(u32 nus) 
{    
    u32 temp;
    SysTick->LOAD=nus*fac_us; 
    SysTick->VAL=0x00;        
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          
    do
    {   
        temp=SysTick->CTRL;  
    } 
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;     
    SysTick->VAL =0X00;       
}


//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对168M条件下,nms<=798ms 
void delay_ms(u16 nms) 
{           
    u32 temp;       
    SysTick->LOAD=(u32)nms*fac_ms;
    SysTick->VAL =0x00;           
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          
    do  
    {   
        temp=SysTick->CTRL;  
    }  
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       
    SysTick->VAL =0X00;       
}


