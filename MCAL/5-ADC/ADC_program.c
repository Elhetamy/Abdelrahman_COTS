/**
 * @file ADC_program.c
 * @author Abdelrahman Elhetamy
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"
#include "ADC_reg.h"

static uint16* ADC_pu16ConversionResult = NULL;
static void(*ADC_pvNotificationFunc)(void) = NULL;
static uint8 ADC_u8BusyFlag = IDLE;
static uint8 ADC_u8ChannelCounter;
static ADC_ChainConv_t ADC_pstChainData= NULL;
static uint8 ADC_u8IntReason;
/**
 * @brief This Function initialize the basics configurations for ADC
 */
void ADC_Init(void)
{
#if ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX,ADMUX_u8REFS0);
	CLR_BIT(ADMUX,ADMUX_u8REFS1);

#elif ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX,ADMUX_u8REFS0);
	CLR_BIT(ADMUX,ADMUX_u8REFS1);
#elif ADC_u8REF_VOLT == INTERNAL_2560MV_REF
	SET_BIT(ADMUX,ADMUX_u8REFS0);
	SET_BIT(ADMUX,ADMUX_u8REFS1);
#else
#error Wrong ADC_u8REF_VOLT configuration option

#endif

#if ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_u8ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX,ADMUX_u8ADLAR);
#else
#error Wrong ADC_u8RESOLUTION configuration option
#endif

#if ADC_u8INT_ENABLE == DISABLED
	CLR_BIT(ADCSRA,ADCSRA_u8ADIE);
#elif ADC_u8INT_ENABLE == ENABLED
	SET_BIT(ADCSRA,ADCSRA_u8ADIE);
#else
#error Wrong ADC_u8INT_ENABLE configuration option
#endif

	/*Configure PreScaler bit*/
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_u8PRESCALER_VAL;

	/*ADC Enable */
	SET_BIT(ADCSRA,ADCSRA_u8ADEN);
}

uint16 ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu16Result != NULL)
	{
		/*Check if ADC is not busy*/
		if(ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32TimeOutCounter = 0u;

			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Configure the analog channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_u8ADSC);

			/*Wait until the conversion is complete (POLLING) or the timeout is passed*/
			while(GET_BIT(ADCSRA,ADCSRA_u8ADIF)==0 && (Local_u32TimeOutCounter < ADC_u32TIMEOUT))
			{
				Local_u32TimeOutCounter++;
			}
			if(Local_u32TimeOutCounter == ADC_u32TIMEOUT)
			{
				/*Loop is broken because flag isn't raised until the timeout is passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Loop is broken because flag isn't raised before the timeout is passed*/
				/*We Must CLEAR THE CONVERSION COMPLETE FLAG AFTER POLLING*/
				SET_BIT(ADCSRA,ADCSRA_u8ADIF);

#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result = ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result = ADC;
#endif
				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;
			}
		}
		else
		{
			/*ADC was busy , assign the error state*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;
}


uint8 ADC_u16StartSingleConversionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result, void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		/*Check if ADC is not busy*/
		if(ADC_u8BusyFlag == IDLE)
		{

			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			ADC_u8IntReason = SINGLE_CONV_ASYNCH;

			/*Initialize The result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize The Notification Function globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Configure the analog channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_u8ADSC);

			/*Enable The ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_u8ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t* Copy_pstChain)
{
	uint8 Local_u8ErrorState = OK;
	if((Copy_pstChain != NULL) && (Copy_pstChain->ChainArr != NULL) && (Copy_pstChain->NotificationFunc != NULL) && (Copy_pstChain->ResultArr != NULL))
	{
		/*Check if adc is busy*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Initialize the global chain data*/
			ADC_pstChainData = Copy_pstChain;
			ADC_u8ChannelCounter = 0u;

			/*Set the first channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];

			/*Start the first conversion*/
			SET_BIT(ADCSRA,ADCSRA_u8ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_u8ADIE);



		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/**
 * @brief ADC Conversion Complete ISR
 */
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	if(ADC_u8IntReason == SINGLE_CONV_ASYNCH)
	{
		if(ADC_pu16ConversionResult != NULL)
		{
#if ADC_u8RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult = ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult = ADC;
#endif
			/*Disable The ADC Conversion Complete Interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_u8ADIE);

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;

			/*Invoke the application Notification function*/
			if(ADC_pvNotificationFunc != NULL)
			{
				ADC_pvNotificationFunc();
			}
			else
			{
				/*Notification Function pointer is NULL*/
			}
		}
		else
		{
			/*Conversion Pointer is NULL*/
		}
	}
	else	/*Interrupt reason is due to chain conversion*/
	{
#if ADC_u8RESOLUTION == EIGHT_BITS
			ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] = ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
			ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] = ADC;
#endif

			/*Channel Counter increment*/
			ADC_u8ChannelCounter++;

			if(ADC_u8ChannelCounter < ADC_pstChainData -> ChainSize)
			{
				/*Chain is not finished yet*/
				/*Start the next conversion*/
				ADMUX &= CHANNEL_MASK;
				ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];

				/*Start the first conversion*/
				SET_BIT(ADCSRA,ADCSRA_u8ADSC);
			}
			else
			{
				/*Chain is finished*/
				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;

				/*Disable Interrupt*/
				CLR_BIT(ADCSRA,ADCSRA_u8ADIE);
				/*Invoke the notification function*/
				if(ADC_pstChainData->NotificationFunc != NULL)
				{
					ADC_pstChainData->NotificationFunc();
				}
				else
				{
				 /*Do nothing*/
				}
			}
	}
}
