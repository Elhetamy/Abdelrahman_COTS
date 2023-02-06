/**
 *
 * @file DIO_program.c
 * @author Abdelrhaman Elhetamy
 * @brief This is the file that implements the DIO driver in MCAL
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_cfg.h"
#include "DIO_interface.h"
#include "DIO_prv.h"
#include "DIO_reg.h"


/**
 * @brief This function is used to set a required pin direction
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8Pin  this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_u8Direction this parameter is used to choose the required direction among DIO_u8PIN_INPUT , DIO_u8PIN_OUTPUT
 * @return
 */
uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8Direction) {

	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Direction == DIO_u8PIN_INPUT)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	CLR_BIT(DDRA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	CLR_BIT(DDRB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	CLR_BIT(DDRC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	CLR_BIT(DDRD,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;
			}
		}else if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	SET_BIT(DDRA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	SET_BIT(DDRB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	SET_BIT(DDRC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	SET_BIT(DDRD,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;
			}
		}else {
			Local_u8ErrorState = NOK;
		}
	}
	else{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/**
 *
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8Pin this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_u8Value this parameter is used to set the pin value among DIO_u8PIN_Low , DIO_u8PIN_High
 * @return
 */

uint8 DIO_u8SetPinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8Value)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Value == DIO_u8PIN_Low)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	CLR_BIT(PORTA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	CLR_BIT(PORTB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	CLR_BIT(PORTC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	CLR_BIT(PORTD,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;	break;
			}
		}else if(Copy_u8Value == DIO_u8PIN_High)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	SET_BIT(PORTA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	SET_BIT(PORTB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	SET_BIT(PORTC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	SET_BIT(PORTD,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;	break;
			}
		}else {
			Local_u8ErrorState = NOK;
		}
	}
	else{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
/**
 * @brief This function get the pin value
 * @param Copy_u8Port	this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8Pin	this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @param Copy_pu8Value	this pointer refers to the address of the returned value
 * @return
 */
uint8 DIO_u8GetPinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8* Copy_pu8Value)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu8Value != NULL){
		if(Copy_u8Pin <= DIO_u8PIN7)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	*Copy_pu8Value = GET_BIT(PINA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	*Copy_pu8Value = GET_BIT(PINB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	*Copy_pu8Value = GET_BIT(PINC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	*Copy_pu8Value = GET_BIT(PIND,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;	break;
			}
		}
		else {
			Local_u8ErrorState = NOK;
		}
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function is used to set the port direction
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @return
 */
uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port,uint8 Copy_u8Direction) {
	uint8 Local_u8ErrorState = OK;


	switch(Copy_u8Port) {
	case DIO_u8PORTA : DDRA = Copy_u8Direction; break;
	case DIO_u8PORTB : DDRB = Copy_u8Direction; break;
	case DIO_u8PORTC : DDRC = Copy_u8Direction; break;
	case DIO_u8PORTD : DDRD = Copy_u8Direction; break;
	default : Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

/**
 * @brief this function is used to set the port value
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8Value this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @return
 */

uint8 DIO_u8SetPortValue(uint8 Copy_u8Port,uint8 Copy_u8Value) {


	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8Port) {
	case DIO_u8PORTA : PORTA = Copy_u8Value; break;
	case DIO_u8PORTB : PORTB = Copy_u8Value; break;
	case DIO_u8PORTC : PORTC = Copy_u8Value; break;
	case DIO_u8PORTD : PORTD = Copy_u8Value; break;
	default : Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

/**
 * @brief This function is used to toggle the pin value
 * @param Copy_u8Port this parameter is used to choose the required port  among DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * @param Copy_u8Pin  this parameter is used to choose the required pin  among DIO_u8PIN0 , DIO_u8PIN1,DIO_u8PIN2,DIO_u8PIN3,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7
 * @return
 */

uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin) {
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Port == DIO_u8PIN_Low)
		{
			switch(Copy_u8Port) {
			case DIO_u8PORTA :	TOG_BIT(PORTA,Copy_u8Pin);	break;
			case DIO_u8PORTB :	TOG_BIT(PORTB,Copy_u8Pin);	break;
			case DIO_u8PORTC :	TOG_BIT(PORTC,Copy_u8Pin);	break;
			case DIO_u8PORTD :	TOG_BIT(PORTD,Copy_u8Pin);	break;
			default : Local_u8ErrorState = NOK;	break;
			}
		}
	}else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}







