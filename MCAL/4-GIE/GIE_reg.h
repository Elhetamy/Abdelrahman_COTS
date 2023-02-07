/**
 * @file GIE_reg.h
 * @author Abdelrahman Elhetamy
 * @brief define The registers of the global interrupt enable
 * @version 1.00
 */
#ifndef GIE_REG_H_
#define GIE_REG_H_

#define SREG		*((volatile uint8*)0x5F)	/*Status Register*/
#define SREG_I		7u							/*Interrupt bit*/

#endif /* GIE_REG_H_ */
