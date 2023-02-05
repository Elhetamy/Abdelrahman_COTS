/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : StepperMotor_interface.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef StepperMotor_INTERFACE_H_
#define	StepperMotor_INTERFACE_H_



typedef struct StepperMotor
{
	uint8 Local_u8Port;
	uint8 Local_u8BluePin;
	uint8 Local_u8PinkPin;
	uint8 Local_u8YellowPin;
	uint8 Local_u8OrangePin;

} SM_t;

void StepperMotor_voidRotate(const SM_t *Object,uint16 Copy_u16Angle,uint8 Copy_u8Direction);
void StepperMotor_voidStop(const SM_t * Object);



#endif
