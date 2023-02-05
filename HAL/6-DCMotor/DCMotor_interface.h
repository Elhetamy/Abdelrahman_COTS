/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : DCMotor_interface.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef DCMotor_INTERFACE_H_
#define	DCMotor_INTERFACE_H_


void DCMotor_voidClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB);
void DCMotor_voidCounterClockWise(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB);
void DCMotor_voidStop(uint8 Copy_u8Port,uint8 Copy_u8PinA,uint8 Copy_u8PinB);

#endif
