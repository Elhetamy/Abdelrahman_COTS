/*
 * EXTI_reg.h
 *
 *  Created on: Feb 6, 2023
 *      Author: user
 */

#ifndef EXTI_REG_H_
#define EXTI_REG_H_


#define GICR			*((volatile uint8*)0x5B)             /*@brief Global Interrupt Control Registers*/
#define GICR_INT1		7u		                             /*@brief INT0 CONTROL BIT*/
#define GICR_INT0		6u                                   /*@brief INT1 CONTROL BIT*/
#define GICR_INT2		5u                                   /*@brief INT2 CONTROL BIT*/

#define MCUCR			*((volatile uint8*)0x55)             /*@brief MCU Control Registers*/
#define MCUCR_ISC00		0u                                   /*@brief Interrupt sense control 0 bit 0*/
#define MCUCR_ISC01		1u                                   /*@brief Interrupt sense control 0 bit 1*/
#define MCUCR_ISC10		2u                                   /*@brief Interrupt sense control 1 bit 0*/
#define MCUCR_ISC11		3u                                   /*@brief Interrupt sense control 1 bit 1*/


#define MCUCSR			*((volatile uint8*)0x54)             /*@brief MCU Control and status register*/
#define MCUCSR_ISC2		6u                                   /*@brief Interrupt sense control 2*/


#endif /* EXTI_REG_H_ */
