/*
 * TWI_reg.h
 *
 *  Created on: Mar 15, 2023
 *      Author: user
 */

#ifndef TWI_REG_H_
#define TWI_REG_H_

#define TWI_TWCR		*((volatile uint8*)0x56)		/*TWI Control Register*/
#define TWCR_TWINT	7u								/*Interrupt Flag*/
#define TWCR_TWEA	6u                           	/*Enable Acknowledge*/
#define TWCR_TWSTA	5u                           	/*Start Condition*/
#define TWCR_TWSTO	4u                           	/*Stop Condition*/
#define TWCR_TWWC	3u                           	/*Write Collision*/
#define TWCR_TWEN	2u                           	/*Enable*/
#define TWCR_TWIE	0u                           	/*Interrupt Enable*/

#define TWI_TWDR 		*((volatile uint8*)0x23)       	/*TWI Data Register*/

#define	TWI_TWAR		*((volatile uint8*)0x22)       	/*TWI Address Register*/
#define TWAR_TWGCE	0u								/*General Call recognition Enable*/

#define TWI_TWSR		*((volatile uint8*)0x21)       	/*TWI Status Register*/
#define TWSR_TWPS0	0u								/*Prescaler Bit0*/
#define TWSR_TWPS1	1u								/*Prescaler Bit1*/

#define TWI_TWBR		*((volatile uint8*)0x20)       	/*TWI Bit Rate Register*/

#endif /* TWI_REG_H_ */
