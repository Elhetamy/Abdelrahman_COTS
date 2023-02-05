/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : LED_program.c 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"


#include "LED_interface.h"
#include "LED_cfg.h"
#include "LED_prv.h"

void LED_voidON(const LED_t * Object)
{
	DIO_u8SetPinDirection(Object->Port,Object->Pin,DIO_u8PIN_OUTPUT);


	if(Object->Type==ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_High);
	}else if(Object->Type==ACTIVE_LOW)
	{
		DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_Low);
	}
}

void LED_voidOFF(const LED_t * Object)
{
	DIO_u8SetPinDirection(Object->Port,Object->Pin,DIO_u8PIN_OUTPUT);

	if(Object->Type==ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_Low);
	}else if(Object->Type==ACTIVE_LOW)
	{
		DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_High);
	}
}

void LED_voidToggle(const LED_t * Object)
{
	DIO_u8SetPinDirection(Object->Port,Object->Pin,DIO_u8PIN_OUTPUT);

	/*The Type will not make a difference here because it will also switch every 500ms*/

	DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_High);
	_delay_ms(500);
	DIO_u8SetPinValue(Object->Port,Object->Pin,DIO_u8PIN_Low);
	_delay_ms(500);
}
