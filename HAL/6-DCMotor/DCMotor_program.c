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

/**
 * @brief This function is used to rotate the DCMotor clockwise
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8PinA this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_u8PinB this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 */
void DCMotor_voidClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_High);
}

/**
 * @brief This function is used to rotate the DCMotor Counter clockwise
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8PinA this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_u8PinB this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 */
void DCMotor_voidCounterClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_High);
}

/**
 * @brief This function is used to stop the DCMotor Counter clockwise
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8PinA this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_u8PinB this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 */
void DCMotor_voidStop(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinB,DIO_u8PIN_Low);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8PinA,DIO_u8PIN_Low);
}
