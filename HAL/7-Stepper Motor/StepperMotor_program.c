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
/**
 * @brief This Function is used to rotate the stepper motor (Clock Wise or Counter Clock Wise)
 * @param Object	This parameter is used to access the struct
 * @param Copy_u16Angle	This parameter is the angle the user want the motor to rotate
 * @param Copy_u8Direction This Parameter is used to get the direction of rotating the motor
 */
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
/**
 * @brief This function is used to stop the Motor
 * @param Object
 */
void StepperMotor_voidStop(const SM_t * Object)
{
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8OrangePin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8BluePin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8PinkPin,DIO_u8PIN_High);
	DIO_u8SetPinValue(Object->Local_u8Port,Object->Local_u8YellowPin,DIO_u8PIN_High);
}
