#include "main.h"

u32 runtimes = 0;
u32 SysTickms = 0;

void NVIC_Configuration(void) 
{ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
} 

void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}


void Init_Devices()
{
    SystemInit();
//    SysTick_Config(72);
    delay_init();
    Led_Init();
    usart1_init(38400);
    usart2_init(38400);
    init_i2c1();
    init_i2c2();
    init_spi2();
    init_can(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_13tq, 9,CAN_Mode_Normal);//1 8 7 5 0
    delay_ms(100);
    init_UBLOX();
    init_QMC5883();
    init_LPS22HB();
    NVIC_Configuration();
    
}
