/*******************************************************************************/
// Layer : HAL 
// Author : OMAR Sayed 
// Version : 01
// Date : 21/8/2023
//                              *Component CLCD*
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	// Set RS ->0 , Set RW ->0   for send command
	DIO_voidSetPinVal(CLCD_CTRL_PORT,RS,PIN_VAL_LOW);
	DIO_voidSetPinVal(CLCD_CTRL_PORT,RW,PIN_VAL_LOW);
	DIO_voidSetPortVal(CLCD_DATA_PORT,Copy_u8Command);

	// Set enable pulse
	DIO_voidSetPinVal(CLCD_CTRL_PORT,EN,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CLCD_CTRL_PORT,EN,PIN_VAL_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data) // Send Character
{
	// Set RS ->1 , Set RW ->0   for send data

	DIO_voidSetPinVal(CLCD_CTRL_PORT,RS,PIN_VAL_HIGH);
	DIO_voidSetPinVal(CLCD_CTRL_PORT,RW,PIN_VAL_LOW);
	DIO_voidSetPortVal(CLCD_DATA_PORT,Copy_u8Data);

	// Set enable pulse
	DIO_voidSetPinVal(CLCD_CTRL_PORT,EN,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CLCD_CTRL_PORT,EN,PIN_VAL_LOW);
}


void CLCD_voidInit(void)
{
	_delay_ms(40);
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	CLCD_voidSendCommand(1);
	_delay_ms(2);
}

// Send String
void CLCD_voidSendString(char *Copy_pcString)
{
	u8 Local_u8Iterator = 0;
	while (Copy_pcString[Local_u8Iterator]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Iterator]);
		Local_u8Iterator ++;
	}
}

//Send Number
void CLCD_voidSendNum (u16 Copy_u16Num)
{
	u8 Local_u8arr [10];
	u8 Local_u8Iterator=0;
	u8 Local_u8Iterator2=0;

	if (Copy_u16Num == 0)
		CLCD_voidSendData('0');
	while (Copy_u16Num)
	{
		Local_u8arr[Local_u8Iterator] = Copy_u16Num%10 + '0'; // Casting to ASCII Code
		Copy_u16Num /=10; // Remove the last digit
		Local_u8Iterator++;
	}

	for (Local_u8Iterator2=Local_u8Iterator;Local_u8Iterator2>0;Local_u8Iterator2--)
	{
		CLCD_voidSendData(Local_u8arr[(Local_u8Iterator2)-1]);
	}
}


void CLCD_voidSetPosition (u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 Local_u8Position = 0;
	if (Copy_u8X ==0)
	{
		Local_u8Position=Copy_u8Y;
	}
	else if (Copy_u8X ==1)
	{
		Local_u8Position = Copy_u8Y +0x40;
	}

	CLCD_voidSendCommand(Local_u8Position+128); // Set DDRAM Address
}

void CLCD_voidDrawSpecialChar (u8 *Copy_pu8Pattern, u8 Copy_u8Loc,u8 Copy_u8X,u8 Copy_u8Y)
{
	// Calculate the CGRAM Address
	u8 Local_u8CgramAdd = Copy_u8Loc * 8;
	// Command to write on CGRAM
	CLCD_voidSendCommand(Local_u8CgramAdd+64);


	for (u8 Local_u8Counter=0 ; Local_u8Counter <8 ; Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	CLCD_voidSetPosition(Copy_u8X,Copy_u8Y);
	//CLCD_voidSendCommand(Local_u8CgramAdd+128);

}

