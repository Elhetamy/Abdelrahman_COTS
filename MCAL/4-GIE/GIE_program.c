/**
 * @file GIE_program.c
 * @author Abdelrahman Elhetamy
 * @brief Implement the functions of the global interrupt enable
 * @version 1.00
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "GIE_interface.h"
#include "GIE_reg.h"
/**
 * @brief Enable the global interrupt enable
 */
void GIE_voidGlobalInterruptEnable(void)
{
	//SET_BIT(SREG,SREG_I);
	 __asm __volatile ("SEI"); /*Inline Assembly instruction to set I bit*/
}
/**
 * @brief Disable the global interrupt enable
 */
void GIE_voidGlobalInterruptDisable(void)
{
	//CLR_BIT(SREG,SREG_I);
	__asm __volatile ("CLI"); /*Inline Assembly instruction to clear I bit*/
}
