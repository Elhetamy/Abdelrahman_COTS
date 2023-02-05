/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : CLCD_program.c 		********/
/******** 	Version : 1.00					********/
/***************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

static void	voidSendEnablePulse(void)
{

	/*Send Enable Pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_High);
	_delay_ms(2);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_Low);

}

#if CLCD_OP_MODE == FOUR_BIT_MODE
static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple)
{
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Nipple,0));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Nipple,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Nipple,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Nipple,3));

}
#endif
void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set RS pin to low for command*/
	
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_Low);

	/*Set RW pin to low for write operation*/
#if CLCD_RW_CTRL_EN == ENABLED
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_Low);
#endif
	/*Send the Command on Data Pins*/
#if CLCD_OP_MODE == EIGHT_BIT_MODE
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Cmd);
	/*Send Enable Pulse*/
	voidSendEnablePulse();
#elif CLCD_OP_MODE == FOUR_BIT_MODE

	voidSetLCDHalfDataPort(Copy_u8Cmd>>4);		//Shift Right to get the most 4 pins
	voidSendEnablePulse();

	voidSetLCDHalfDataPort(Copy_u8Cmd);			//Send The Least 4 bits to the LCD
	voidSendEnablePulse();


#endif
	}

void CLCD_voidSendData(uint8 Copy_u8Data)
{
	
	/*Set RS to high for data*/

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_High);

	/*Set RW pin to low for write operation*/
#if CLCD_RW_CTRL_EN == ENABLED
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_Low);
#endif

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/* Set the data on the port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	voidSendEnablePulse();
#elif CLCD_OP_MODE == FOUR_BIT_MODE

	voidSetLCDHalfDataPort(Copy_u8Data>>4);		//Shift Right to get the most 4 pins
	voidSendEnablePulse();

	voidSetLCDHalfDataPort(Copy_u8Data);			//Send The Least 4 bits to the LCD
	voidSendEnablePulse();


#endif
	}

uint8 CLCD_u8SendString(const char* Copy_chString)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_chString != NULL)
	{
		uint8 Local_u8Counter = 0u;
		while(Copy_chString[Local_u8Counter]!='\0')
		{
			CLCD_voidSendData(Copy_chString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;
}

void CLCD_voidSendNumber(sint32 Copy_s32Number)

{
	char Local_chNumberArr[10];
	uint8 Local_u8RightDigit;
	uint8 Local_u8Counter=0;
	sint8 Local_s8Counter2;

	if (Copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
		return ;
	}
	else if(Copy_s32Number < 0)
	{
		CLCD_voidSendData('-');
		Copy_s32Number *= -1;
	}
	while(Copy_s32Number!=0)
	{
		Local_u8RightDigit = Copy_s32Number%10;
		Copy_s32Number /=10;	//Eliminate the right digit
		Local_chNumberArr[Local_u8Counter] = Local_u8RightDigit + '0';	//The +'0' To convert it to ascii value
		Local_u8Counter++;
	}
	for(Local_s8Counter2= Local_u8Counter-1; Local_s8Counter2>=0; Local_s8Counter2--)
	{
		CLCD_voidSendData(Local_chNumberArr[Local_s8Counter2]);
	}

}

void CLCD_voidGetBinary(sint32 Copy_s32Decimal)
{
	char Local_chBinaryArr[10];
	uint8 Local_u8Counter=0;
	sint8 Local_s8Counter2;

	while(Copy_s32Decimal != 0)
	{
		Local_chBinaryArr[Local_u8Counter] = (Copy_s32Decimal % 2)+ '0';
		Copy_s32Decimal /=2;
		Local_u8Counter++;
	}
	CLCD_u8SendString("0b");
	for(Local_s8Counter2= Local_u8Counter-1; Local_s8Counter2>=0; Local_s8Counter2--)
	{
		CLCD_voidSendData(Local_chBinaryArr[Local_s8Counter2]);
	}

}

void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos )
{

	uint8 Local_u8DDRamAdd;

	if(Copy_u8YPos == 0u)
	{
		/*Start To Write from the first Line*/
		Local_u8DDRamAdd = Copy_u8XPos;
	}else if(Copy_u8YPos == 1u)
	{
		/*Start To Write from the second Line*/
		Local_u8DDRamAdd = 0x40 + Copy_u8XPos;
	}

	/*Set bit 7 to set DDRAM Address Command*/
	Local_u8DDRamAdd |= 1 << 7;
	CLCD_voidSendCmd(Local_u8DDRamAdd);



}

void CLCD_voidSendSpecialCharacter(uint8 *Copy_pu8Pattern,uint8 Copy_u8PatternNum,uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8CGRamAdd = Copy_u8PatternNum * 8u;

	uint8 Local_u8LoopCounter;

	/*Set bit 6 for set CGRAM Command*/
	Local_u8CGRamAdd |= 1 << 6u;
	CLCD_voidSendCmd(Local_u8CGRamAdd);

	/*Write The Pattern In the CGRAM*/
	for(Local_u8LoopCounter = 0;Local_u8LoopCounter <8u;Local_u8LoopCounter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8LoopCounter]);
	}
	/*Go To DDRAM To Display The Pattern*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Display The Pattern Written inside CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNum);


}

void CLCD_voidInit(void)
{


	/*Wait for 40ms after power on*/
	_delay_ms(40);


	/*Function set command : 2line,5*7 font size*/
#if CLCD_OP_MODE == EIGHT_BIT_MODE
	CLCD_voidSendCmd(0b00111000);

#elif CLCD_OP_MODE == FOUR_BIT_MODE

	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b1000);
	voidSendEnablePulse();

#endif
	/*Display Enable, Cursor Disable,Blink Disable*/
	CLCD_voidSendCmd(0b00001100);

	/*Display Clear*/
	CLCD_voidSendCmd(1);


}
