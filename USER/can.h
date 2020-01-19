#ifndef _CAN_H_
#define _CAN_H_
#endif

extern void init_can(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);
extern u8 CAN1_Send_Msg(u8* msg,u8 len); 
