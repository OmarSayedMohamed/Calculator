#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"

u8 KPD_Value=0;                       //variable to store the pressed button for Keypad
u8 NumberOfDigit=0;                   //variable to calculate the number of digit of password
u8 Pasword[16];						 //array to store the password when set
u8 Check_Pasword[16];			    //array to store the password when check
u8 counter = 0;                    //variable to calculate the number of digit of check password

u8 First_Num[4];                  //Array to store the first number (Assuming the number of digits 4)
u8 Second_Num[4];				//Array to store the Second number (Assuming the number of digits 4)
u8 operation;                   //variable to store the operation

u8 checker;      // variable to store the return of the check function
u8 Check (u8 Password[],u8 Check_Password[],u8 NumberOfDigit);  //Check if Password is correct or not

u16 calc_add(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j); // to add two numbers
u16 calc_sub(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j); // to subtract two numbers
u16 calc_multi(u8 First_Num[],u8 Second_Num[],u8 i,u8 j); // to multiply two numbers
u16 calc_div(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j); // to divide two numbers


void main (void)
{
	DIO_voidSetPortDir(PORTA_REG,PORT_DIR_OUT);
	DIO_voidSetPortDir(PORTC_REG,PORT_DIR_OUT);
	DIO_voidSetPortDir(PORTB_REG,0b00001111);
	DIO_voidSetPortVal(PORTB_REG,PORT_VAL_HIGH);

	CLCD_voidInit();
	CLCD_voidSendString("Set Password");

	//	Set Password
	while (1)
	{


		do {
			KPD_Value=KPD_u8GetPressedKey();
		} while (KPD_Value == '\0');
		NumberOfDigit++;
		if (KPD_Value == '&')break;
		CLCD_voidSetPosition(1,NumberOfDigit-1);
		CLCD_voidSendNum(KPD_Value);
		_delay_ms(200);
		CLCD_voidSetPosition(1,NumberOfDigit-1);
		CLCD_voidSendData('*');
		Pasword[NumberOfDigit] =KPD_Value;


	}

	/*******************************************************************/

	while (1)
	{
		//Get Password To Check It
		CLCD_voidSendCommand(Clear);
		_delay_ms(100);
		CLCD_voidSendString("Check Password");

		KPD_Value='\0';
		counter=0;
		while(KPD_Value != '&')
		{
			do {
				KPD_Value=KPD_u8GetPressedKey();
			} while (KPD_Value == '\0');
			counter++;
			if(KPD_Value == '&') break;
			CLCD_voidSetPosition(1,counter-1);
			CLCD_voidSendNum(KPD_Value);
			_delay_ms(200);
			CLCD_voidSetPosition(1,counter-1);
			CLCD_voidSendData('*');
			Check_Pasword[counter] =KPD_Value;
		}


		//Check if Password is correct or not
		checker= Check(Check_Pasword,Pasword,counter);
		if (checker == NumberOfDigit-1)
		{

			//Loading to Start Calculator
			CLCD_voidSendCommand(Clear);
			CLCD_voidSendString(" Loading");
			for(u8 i=0;i<5;i++)
			{
				CLCD_voidSetPosition(1,i);
				CLCD_voidSendData('.');
				_delay_ms(500);
			}
			_delay_ms(200);
			CLCD_voidSendCommand(Clear);
			CLCD_voidSendString(" Calculator");
			CLCD_voidSetPosition(1,0);
			CLCD_voidSendString(" is Ready");
			_delay_ms(2000);
			CLCD_voidSendCommand(Clear);

			//loop for repeating the calculation

			while(1){
				counter=0;
				operation=0;

			//Getting The First Number

				while(1)
				{
					do{
						KPD_Value = KPD_u8GetPressedKey();
						_delay_ms(200);
					}while(KPD_Value == '\0');
					if(KPD_Value == '+' || KPD_Value == '-' || KPD_Value == '/' || KPD_Value == '*')
					{
						operation = KPD_Value;
						CLCD_voidSetPosition(0,counter+1);
						CLCD_voidSendData(KPD_Value);
						break;
					}
					First_Num[counter]=KPD_Value;
					counter++;
					CLCD_voidSetPosition(0,counter);
					CLCD_voidSendNum(KPD_Value);
				}
				u8 counter2=counter+1;
				u8 counter3=0;

				while (1)
				{
					do{
						KPD_Value = KPD_u8GetPressedKey();
						_delay_ms(200);
					}while(KPD_Value == '\0');
					if(KPD_Value == '=' )
					{
						CLCD_voidSetPosition(0,counter2+1);
						CLCD_voidSendData(KPD_Value);
						break;
					}
					Second_Num[counter3]=KPD_Value;
					counter2++;
					counter3++;
					CLCD_voidSetPosition(0,counter2);
					CLCD_voidSendNum(KPD_Value);
				}
				switch(operation)
				{
				case '+':
					CLCD_voidSetPosition(0,counter2+2);
					CLCD_voidSendNum(calc_add(First_Num,Second_Num,counter,counter3));
					break;
				case '-':
					CLCD_voidSetPosition(0,counter2+2);
					CLCD_voidSendNum(calc_sub(First_Num,Second_Num,counter,counter3));
					break;
				case '*':
					CLCD_voidSetPosition(0,counter2+2);
					CLCD_voidSendNum(calc_multi(First_Num,Second_Num,counter,counter3));
					break;
				case '/':
					CLCD_voidSetPosition(0,counter2+2);
					CLCD_voidSendNum(calc_div(First_Num,Second_Num,counter,counter3));
					break;
				}
				_delay_ms(3000);
				CLCD_voidSendCommand(Clear);
			}
		}
		else {
			CLCD_voidSendCommand(Clear);
			CLCD_voidSendString(" Wrong Password");
			_delay_ms(2000);
		}
	}

}

u8 Check (u8 Password[],u8 Check_Password[],u8 NumberOfDigit)
{

	u8 checker=0;
	for(u8 i=0; i<NumberOfDigit-1;i++)
	{
		if(Password[NumberOfDigit] == Check_Pasword[counter])
		{
			checker++;
		}
	}
	return checker;

}

u16 calc_add(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j)
{
	u16 num1=First_Num[0];
	u16 num2=Second_Num[0];


	for(u8 counter=1;counter<i;counter++)
	{

		num1 = num1*10 +First_Num[counter];
	}

	for(u8 counter=1;counter<j;counter++)
	{
		num2= num2*10 +Second_Num[counter];
	}

	return (num1+num2);
}
u16 calc_sub(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j)
{

	u16 num1=First_Num[0];
	u16 num2=Second_Num[0];
	for(u8 counter=1;counter<i;counter++)
	{

		num1 = num1*10 +First_Num[counter];
	}

	for(u8 counter=1;counter<j;counter++)
	{
		num2= num2*10 +Second_Num[counter];
	}

	return (num1-num2);

}
u16 calc_multi(u8 First_Num[],u8 Second_Num[],u8 i,u8 j)
{
	u16 num1=First_Num[0];
	u16 num2=Second_Num[0];
	for(u8 counter=1;counter<i;counter++)
	{

		num1 = num1*10 +First_Num[counter];
	}

	for(u8 counter=1;counter<j;counter++)
	{
		num2= num2*10 +Second_Num[counter];
	}

	return (num1*num2);
}


u16 calc_div(  u8 First_Num[],u8 Second_Num[],u8 i,u8 j)

{
	u16 num1=First_Num[0];
	u16 num2=Second_Num[0];
	for(u8 counter=1;counter<i;counter++)
	{

		num1 = num1*10 +First_Num[counter];
	}

	for(u8 counter=1;counter<j;counter++)
	{
		num2= num2*10 +Second_Num[counter];
	}

	return (num1/num2);
}

