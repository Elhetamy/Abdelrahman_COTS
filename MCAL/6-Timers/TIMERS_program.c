/**
 * @file TIMERS_program.c
 * @author Abdelrahman Elhetamy
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TIMERS_cfg.h"
#include "TIMERS_interface.h"
#include "TIMERS_prv.h"
#include "TIMERS_reg.h"

/*Global Array of pointers to functions*/
static void(*TIMERS_pvCallBackFuncArr[8])(void)={NULL};

/**
 * TIMER0 Functions
 */

uint8 TIMER0_u8Init(TIMER0_2_Cfg_t* Copy_psTimer0)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_psTimer0 != NULL && (Copy_psTimer0->WFGMode != NULL) && (Copy_psTimer0->Normal_OC != NULL) && (Copy_psTimer0->PHPWM_OC != NULL) && (Copy_psTimer0->FPWM_OC != NULL) && (Copy_psTimer0->Clock_PreScaler != NULL))
	{

	}

	return Local_u8ErrorState;
}
void TIMER0_voidInit(void)
{

	/*Make the TIMER0 works on FAST PWM mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Set The PreScaler to 64*/

	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

	/*Set on top clear on compare operation*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

}


void TIMER0_voidSetCompValue(uint8 Copy_u8Val)
{
	OCR0 = Copy_u8Val;
}


/**
 * TIMER1 Functions
 */
void TIMER1_voidInit(void)
{
	/*Make Timer1 Works on Normal mode*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	/*Compare Output Mode : Normal*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Set PreScaler to 64*/
	SET_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);

}


void TIMER1_voidSetCompValue(uint16 Copy_u8Val)
{
	OCR1A = Copy_u8Val;
}


void TIMER1_voidSetTimerValue(uint16 Copy_u8Val)
{
	TCNT1 = Copy_u8Val;
}

uint16 TIMER1_voidGetTimerValue(void)
{
	return TCNT1;
}


/**
 * ICU Functions
 */
void ICU_voidInit(void)
{
#if ICU_SENSE_CTRL == ICU_FALLING
	/*Initiate Trigger source (FALLING EDGE)*/
	CLR_BIT(TCCR1B,TCCR1B_ICES1);
#elif ICU_SENSE_CTRL == ICU_RISING
	SET_BIT(TCCR1B,TCCR1B_ICES1);
#else
#error Wrong ICU configuration option
#endif
#if ICU_INT_INIT_STATE == ENABLED
	/*Enable the Interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
#elif ICU_INT_INIT_STATE == DISABLED
	CLR_BIT(TIMSK,TIMSK_TICIE1);
#else
#error Wrong ICU interrupt configuration option
#endif
}

void ICU_voidIntEnable(void)
{
	/*Enable the Interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidIntDisable(void)
{
	/*Disable the Interrupt*/
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

uint8 ICU_voidTriggerSource(uint8 Copy_u8Trigger)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Trigger == ICU_FALLING)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Trigger == ICU_RISING)	/*Trigger Source is Rising Edge*/
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint16 ICU_voidGetValue(void)
{
	return ICR1;
}



/**
 * @brief Function designed to make a call back function to invoke that the timer had done it's work
 * @param Copy_u8TmrIntSource
 * @param Copy_pvCallBackFunc
 * @return Error state
 */

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TmrIntSource,void (*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFuncArr[Copy_u8TmrIntSource] = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void __vector_10(void)		__attribute__((signal));
void __vector_10(void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP]!=NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
}

void __vector_6(void)		__attribute__((signal));
void __vector_6(void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER1_ICU]!=NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_ICU]();
	}
}
