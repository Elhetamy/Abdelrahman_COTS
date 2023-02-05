/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : DCMotor_program.c 		********/
/******** 	Version : 1.00					********/
/***************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DCMotor_interface.h"
#include "DCMotor_cfg.h"
#include "DCMotor_prv.h"

void DCMotor_voidClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_High);
}

void DCMotor_voidCounterClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_High);
}

void DCMotor_voidStop(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_Low);
}
