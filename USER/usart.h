#ifndef _USART_H_
#define _USART_H_
#endif

extern void usart1_init(u32 bound);
extern void usart2_init(u32 bound);
extern void usart3_init(u32 bound);
extern void usart1_send(unsigned char data);
extern void usart1_send_str(unsigned char *str, unsigned char len);



