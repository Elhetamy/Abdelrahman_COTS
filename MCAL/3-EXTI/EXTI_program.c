/**
 *
 * @file EXTI_program.c
 * @author Abdelrahman Elhetamy
 * @brief This file implements the EXTI module functions
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"


#include "EXTI_interface.h"
#include "EXTI_cfg.h"
#include "EXTI_reg.h"
#include "GIE_interface.h"
#include "DIO_interface.h"

static void (*EXTI_pfINTFuncPtr[3])(void) ={NULL}/*Array of pointers to functions to hold ISR CallBacks*/;

/**
 * @brief This Function Enable the desired interrupt
 * @param Copy_u8Interrupt	This parameter is the interrupt you want to enable
 * @return
 */
uint8 EXTI_u8InterruptEnable(uint8 Copy_u8Interrupt)
{
	uint8 Local_u8ErrorState = NOK;
	if (Copy_u8Interrupt == EXTI_u8INT0) {
		Local_u8ErrorState = OK;
		SET_BIT(GICR,DIO_u8PIN6);
	}
	else if (Copy_u8Interrupt == EXTI_u8INT1) {
		Local_u8ErrorState = OK;
		SET_BIT(GICR,DIO_u8PIN7);
	}
	else if (Copy_u8Interrupt == EXTI_u8INT2) {
		Local_u8ErrorState = OK;
		SET_BIT(GICR,DIO_u8PIN5);
	}
	return Local_u8ErrorState;
}

/**
 * @brief This Function Disable the desired interrupt
 * @param Copy_u8Interrupt	This parameter is the interrupt you want to Disable
 * @return
 */
uint8 EXTI_u8InterruptDisable(uint8 Copy_u8Interrupt)
{
	uint8 Local_u8ErrorState = NOK;
	if (Copy_u8Interrupt == EXTI_u8INT0) {
		Local_u8ErrorState = OK;
		CLR_BIT(GICR,GICR_INT0);
	}
	else if (Copy_u8Interrupt == EXTI_u8INT1) {
		Local_u8ErrorState = OK;
		CLR_BIT(GICR,GICR_INT1);
	}
	else if (Copy_u8Interrupt == EXTI_u8INT2) {
		Local_u8ErrorState = OK;
		CLR_BIT(GICR,GICR_INT2);
	}
	return Local_u8ErrorState;
}


/**
 * @brief This Function Operates with the interrupt depends on the Sense Control you want options 1- Rising Edge	2-Falling Edge	3-Logical Change	4-Low Level
 * @param Copy_u8Interrupt This parameter is the interrupt you want to use
 * @param Copy_u8SenseCtrl	This parameter is the Sense control you want options 1- Rising Edge	2-Falling Edge	3-Logical Change	4-Low Level
 * @return
 */
uint8 EXTI_voidSenseCtrl(uint8 Copy_u8Interrupt,uint8 Copy_u8SenseCtrl)
{
	uint8 Local_u8ErrorState = NOK;
	/**
	 * EXTI_u8INT0
	 */
	if(Copy_u8Interrupt==EXTI_u8INT0)
	{
		switch(Copy_u8SenseCtrl)
		{
		case EXTI_u8FALLING_EDGE : 			CLR_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		case EXTI_u8RISING_EDGE  :			SET_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		case EXTI_u8LOGICAL_CHANGE : 		CLR_BIT(MCUCR,MCUCR_ISC01);	SET_BIT(MCUCR,MCUCR_ISC00); break;
		case EXTI_u8LOW_LEVEL : 			CLR_BIT(MCUCR,MCUCR_ISC01); CLR_BIT(MCUCR,MCUCR_ISC00); break;
		default :							Local_u8ErrorState = NOK; break;
		}
	}


	/**
	 * EXTI_u8INT1
	 */
	else if(Copy_u8Interrupt==EXTI_u8INT1)
	{
		switch(Copy_u8SenseCtrl)
		{
		case EXTI_u8FALLING_EDGE : 			CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11); break;
		case EXTI_u8RISING_EDGE  :			SET_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11); break;
		case EXTI_u8LOGICAL_CHANGE :		CLR_BIT(MCUCR,MCUCR_ISC11);SET_BIT(MCUCR,MCUCR_ISC10); break;
		case EXTI_u8LOW_LEVEL : 			CLR_BIT(MCUCR,MCUCR_ISC11);CLR_BIT(MCUCR,MCUCR_ISC10); break;
		default : 							Local_u8ErrorState = NOK; break;
		}
	}

	/**
	 * EXTI_u8INT2
	 */
	else if(Copy_u8Interrupt==EXTI_u8INT2)
	{
		switch(Copy_u8SenseCtrl)
		{
		case EXTI_u8FALLING_EDGE : 			CLR_BIT(MCUCSR,MCUCSR_ISC2); break;
		case EXTI_u8RISING_EDGE  :			SET_BIT(MCUCSR,MCUCSR_ISC2); break;
		default :							Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief This Function initialize the Interrupts with initial values
 */
void EXTI_voidInitInt0(void)
{
	/**
	 * Initial values for EXTI_u8INT0
	 */
#if INT0_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8LOGICAL_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);

#elif INT0_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);
#else
#error Wrong INT0_SENSE_CTRL configuration option
#endif

	/**
	 * Implement INT0 initial state configuration
	 */
#if INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#elif INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#else
#error Wrong INT0_INITIAL_STATE configuration option
#endif
}

void EXTI_voidInitInt1(void)
{
	/**
	 * Initial values for EXTI_u8INT1
	 */

#if INT1_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE_CTRL == EXTI_u8LOGICAL_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
#else
#error Wrong INT1_SENSE_CTRL configuration option
#endif
	/**
	 * Implement INT1 initial state configuration
	 */
#if INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#elif INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#else
#error Wrong INT1_INITIAL_STATE configuration option
#endif
}
void EXTI_voidInitInt2(void)
{

	/**
	 * Initial values for EXTI_u8INT2
	 */
#if INT2_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL configuration option
#endif
	/**
	 * Implement INT2 initial state configuration
	 */
#if INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#elif INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#else
#error Wrong INT2_INITIAL_STATE configuration option
#endif
}

uint8 EXTI_u8SetCallBack(uint8 Copy_u8Interrupt,void (*Copy_pfFuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pfFuncPtr != NULL)
	{
		EXTI_pfINTFuncPtr[Copy_u8Interrupt] = Copy_pfFuncPtr;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief INT0 ISR
 */
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pfINTFuncPtr[EXTI_u8INT0] != NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT0]();
	}
}

/**
 * @brief INT1 ISR
 */
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pfINTFuncPtr[EXTI_u8INT1] != NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT1]();
	}
}

/**
 * @brief INT2 ISR
 */
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pfINTFuncPtr[EXTI_u8INT2] != NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT2]();
	}
}
