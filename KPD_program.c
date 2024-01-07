/*******************************************************************************/
// Layer : HAL 
// Author : OMAR Sayed 
// Version : 01
// Date : 23/8/2023
//                              *Component KPD*
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

u8 KPD_u8GetPressedKey (void)
{
	u8 Local_u8Col;
	u8 Local_u8Row;
	u8 Local_u8Reading;
	u8 Local_u8Key=0;

	u8 KPD_u8Values [MAX_ROW][MAX_COL] = KPD_VALUES;

	for (Local_u8Col =COL_INIT ; Local_u8Col <COL_FIN ; Local_u8Col++)
	{
		DIO_voidSetPinVal(KPD_PORT,Local_u8Col,PIN_VAL_LOW); // Put GND in each Column

		for (Local_u8Row = ROW_INIT ; Local_u8Row <ROW_FIN ; Local_u8Row++)
		{
			Local_u8Reading = DIO_u8GetPinVal(KPD_PORT,Local_u8Row + MAX_ROW);
			// to get the values of each switch

			if (Local_u8Reading == PIN_VAL_LOW)
			{
				Local_u8Key = KPD_u8Values [Local_u8Row][Local_u8Col];
				_delay_ms(10);
			}
			// read the value of the pressed switch

			while (DIO_u8GetPinVal(KPD_PORT,Local_u8Row +MAX_ROW) == PIN_VAL_LOW)
			{

			}
		}

		DIO_voidSetPinVal(KPD_PORT,Local_u8Col,PIN_VAL_HIGH);
	}
	return Local_u8Key;

}
