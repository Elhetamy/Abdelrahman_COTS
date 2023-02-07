/**
 * @file EXTI_interface.h
 * @author Abdelrahman Elhetamy
 * @brief
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define EXTI_u8LOW_LEVEL		1u
#define EXTI_u8LOGICAL_CHANGE	2u
#define EXTI_u8FALLING_EDGE		3u
#define	EXTI_u8RISING_EDGE		4u


#define EXTI_u8INT0		0u
#define EXTI_u8INT1		1u
#define EXTI_u8INT2		2u


void EXTI_voidInitInt0(void);
void EXTI_voidInitInt1(void);
void EXTI_voidInitInt2(void);
uint8 EXTI_u8InterruptEnable(uint8 Copy_u8Interrupt);
uint8 EXTI_u8InterruptDisable(uint8 Copy_u8Interrupt);
uint8 EXTI_voidSenseCtrl(uint8 Copy_u8Interrupt,uint8 Copy_u8SenseCtrl);


#endif /* EXTI_INTERFACE_H_ */
