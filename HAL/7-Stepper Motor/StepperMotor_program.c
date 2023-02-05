/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : StepperMotor_program.c 		********/
/******** 	Version : 1.00					********/
/***************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "StepperMotor_interface.h"
#include "StepperMotor_cfg.h"
#include "StepperMotor_prv.h"
#include "KPD_interface.h"
#include <util/delay.h>

void StepperMotor_voidRotate(const SM_t * Object,uint16 Copy_u16Angle,uint8 Copy_u8Direction)
{
	uint16 Local_u16Stepps=(uint16)((uint32)Copy_u16Angle * 2048UL / 360UL);
	uint16 Local_u16FSCounter;
	if(Copy_u8Direction== ROTATECLOCKWISE)
	{
	for(Local_u16FSCounter = 0;Local_u16FSCounter<Local_u16Stepps;Local_u16FSCounter++)
	{
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		_delay_ms(2);
	}
	}
	if(Copy_u8Direction== ROTATECOUNTERCLOCKWISE)
	{
	for(Local_u16FSCounter = 0;Local_u16FSCounter<Local_u16Stepps;Local_u16FSCounter++)
		{

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);

		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_Low);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
		DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
		_delay_ms(2);
		}
	}
}

void StepperMotor_voidStop(const SM_t * Object)
{
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
}
