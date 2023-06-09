/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : SSD_program.c 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"


#include "SSD_interface.h"
#include "SSD_cfg.h"
#include "SSD_prv.h"

static const uint8 ssd[10] = {(0b0111111),(0b0000110),(0b1011011),(0b1001111),(0b1100110),(0b1101101),(0b1111101),(0b0000111),(0b1111111),(0b1101111)};


uint8 SSD_u8SetNumber(const SSD_t * Object,uint8 Copy_u8Num)
{
	uint8 Local_u8ErrorState= OK;
	uint8 Local_u8Counter;
	uint8 Local_u8NumIndex = ssd[Copy_u8Num];
	if(Object != NULL)
	{
		switch(Object->Type)
		{
		case ANODE:
			DIO_u8SetPinValue(Object->EnablePort,Object->EnablePin,DIO_u8PIN_High);
			if(Object->LedApin == DIO_u8PIN0)
			{
				for(int Local_u8Counter = 0; Local_u8Counter < 7;Local_u8Counter++)
				{
					DIO_u8SetPinValue(Object->Port,Local_u8Counter,GET_BIT(Local_u8NumIndex,(Local_u8Counter-1))^ 1);
				}
			}
			else if(Object->LedApin == DIO_u8PIN1)
			{
				for(int Local_u8Counter = 1; Local_u8Counter < 8;Local_u8Counter++)
				{
					DIO_u8SetPinValue(Object->Port,Local_u8Counter,GET_BIT(Local_u8NumIndex,(Local_u8Counter-1)) ^ 1);
				}

			}
			break;


		case CATHODE:
			DIO_u8SetPinValue(Object->EnablePort,Object->EnablePin,DIO_u8PIN_Low);
			if(Object->LedApin == DIO_u8PIN0)
			{
				for(int Local_u8Counter = 0; Local_u8Counter < 7;Local_u8Counter++)
				{
					DIO_u8SetPinValue(Object->Port,Local_u8Counter,GET_BIT(Local_u8NumIndex,(Local_u8Counter)));
				}
			}
			else if(Object->LedApin == DIO_u8PIN1)
			{
				for(int Local_u8Counter = 1; Local_u8Counter < 8;Local_u8Counter++)
				{
					DIO_u8SetPinValue(Object->Port,Local_u8Counter,GET_BIT(Local_u8NumIndex,(Local_u8Counter-1)));
				}

			}
			break;

		case ETA_KIT:
			DIO_u8SetPinValue(Object->EnablePort,Object->EnablePin,DIO_u8PIN_High);

			for(int Local_u8Counter = 1; Local_u8Counter < 8;Local_u8Counter++)
			{
				DIO_u8SetPinValue(Object->Port,Local_u8Counter,GET_BIT(Local_u8NumIndex,(Local_u8Counter-1)));
			}
			break;

		default:
			break;
		}

	}
	else
	{
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

