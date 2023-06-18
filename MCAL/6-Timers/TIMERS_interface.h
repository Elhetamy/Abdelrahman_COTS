/**
 * @file TIMERS_interface.h
 * @author Abdelrahman Elhetamy
 * @version 1.00
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

typedef enum
{
	TIMER0_OVF=0,
	TIMER0_COMP,
	TIMER1_ICU
}TIMERS_Int_Src_t;

typedef enum
{
	NORMAL=0,
	PWM,
	CTC,
	FAST_PWM
}TIMER0_2WFG_Mode_t;

typedef enum
{
	NORMAL=0,
	TOGGLE,
	CLEAR,
	SET
}TIMER0_2NORMAL_OC_t;

typedef enum
{
	NORMAL=0,
	RESERVED,
	CLEAR,
	SET
}TIMER0_2FPWM_OC_t;

typedef enum
{
	NORMAL=0,
	RESERVED,
	CLEARONUP_SETONDOWN,
	SETONUP_CLEARONDOWN
}TIMER0_2PHPWM_OC_t;

typedef enum
{
	NO_CLOCK=0,
	NO_PRESCALE,
	PRE_8,
	PRE_64,
	PRE_256,
	PRE_1024,
	EXT_FALLING,
	EXT_RISING
}TIMER0_2CLOCK_t;

typedef enum
{
	NORMAL=0,
	PHASE_CO_PWM_8,
	PHASE_CO_PWM_9,
	PHASE_CO_PWM_10,
	CTC,
	FAST_PWM_8,
	FAST_PWM_9,
	FAST_PWM_10,
	PHASE_FREQ_CO_PWM_ICR1,
	PHASE_FREQ_CO_PWM_OCR1A,
	PHASE_CO_PWM_ICR1,
	PHASE_CO_PWM_OCR1A,
	CTC_ICR1,
	RESERVED,
	FAST_PWM_ICR1,
	FAST_PWM_OCR1A
}TIMER1_WFG_Mode_t;

typedef enum
{
	NORMAL=0,
	TOGGLE,
	CLEAR,
	SET
}TIMER1_NORMAL_OC_t;

typedef enum
{
	NORMAL=0,
	TOGGLE,
	CLEAR,
	SET
}TIMER1_FPWM_OC_t;

typedef enum
{
	NORMAL=0,
	TOGGLE_ON_CMP_MATCH,
	CLEARONUP_SETONDOWN,
	SETONUP_CLEARONDOWN
}TIMER1_PHPWM_OC_t;

typedef enum
{
	NO_CLOCK=0,
	NO_PRESCALE,
	PRE_8,
	PRE_64,
	PRE_256,
	PRE_1024,
	EXT_FALLING,
	EXT_RISING
}TIMER1_CLOCK_t;

typedef struct
{
	TIMER0_2WFG_Mode_t WFGMode;
	TIMER0_2CLOCK_t	Clock_PreScaler;
	TIMER0_2NORMAL_OC_t Normal_OC;
	TIMER0_2FPWM_OC_t FPWM_OC;
	TIMER0_2PHPWM_OC_t PHPWM_OC;
}TIMER0_2_Cfg_t;

typedef struct
{
	TIMER1_WFG_Mode_t WFGMode;
	TIMER1_CLOCK_t Clock_PreScaler;
	TIMER1_NORMAL_OC_t Normal_OC;
	TIMER1_FPWM_OC_t FPWM_OC;
	TIMER1_PHPWM_OC_t PHPWM_OC;
}TIMER1_Cfg_t;

#define ICU_FALLING			1u
#define ICU_RISING			2u

uint8 TIMER0_u8Init(TIMER0_2_Cfg_t* Copy_psTimer0);
uint8 TIMER1_u8Init(TIMER1_Cfg_t* Copy_psTimer1);
uint8 TIMER2_u8Init(TIMER0_2_Cfg_t* Copy_psTimer2);

void TIMER0_voidInit(void);
void TIMER1_voidInit(void);
uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TmrIntSource,void (*Copy_pvCallBackFunc)(void));
void TIMER0_voidSetCompValue(uint8 Copy_u8Val);
void TIMER1_voidSetCompValue(uint16 Copy_u8Val);
void TIMER1_voidSetTimerValue(uint16 Copy_u8Val);
uint16 TIMER1_voidGetTimerValue(void);

void ICU_voidInit(void);
uint8 ICU_voidTriggerSource(uint8 Copy_u8Trigger);
void ICU_voidIntEnable(void);
void ICU_voidIntDisable(void);
uint16 ICU_voidGetValue(void);

#endif /* TIMERS_INTERFACE_H_ */
