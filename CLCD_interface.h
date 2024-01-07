/*******************************************************************************/
// Layer : HAL 
// Author : OMAR Sayed 
// Version : 01
// Date : 21/8/2023
//                              *Component CLCD*
/*******************************************************************************/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define Clear  0b00000001

void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidInit(void);
void CLCD_voidSendString(char *Copy_pcString);
void CLCD_voidSendNum (u16 Copy_u16Num);
void CLCD_voidSetPosition (u8 Copy_u8X, u8 Copy_u8Y);
void CLCD_voidDrawSpecialChar (u8 *Copy_pu8Pattern, u8 Copy_u8Loc,u8 Copy_u8X,u8 Copy_u8Y);











#endif
