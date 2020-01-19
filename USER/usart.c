#include "main.h"

void usart1_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure; 
        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);
    
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;   
    USART_InitStructure.USART_HardwareFlowControl=  USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);     
 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE); 
    USART_SendData(USART1, 0xff);
}

void usart2_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);
    
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;   
    USART_InitStructure.USART_HardwareFlowControl=  USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);     
 
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE); 
}

void usart3_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);
    
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;   
    USART_InitStructure.USART_HardwareFlowControl=  USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);     
 
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);
}

void usart1_send(unsigned char data)
{
    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void usart1_send_str(unsigned char *str, unsigned char len)
{
    unsigned char i=0;
    for(i=0;i<len;i++)
    {
        usart1_send(*str);
        str++;
    }
}


