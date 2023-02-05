/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : CLCD_cfg.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef CLCD_CFG_H_
#define CLCD_CFG_H_


/*Please Choose which PORT to connect control pins:RS , RW , E*/
/*Configure the operation mode : 1 -> EIGHT_BIT_MODE
 * 								 2 -> FOUR_BIT_MODE */
#define CLCD_OP_MODE		FOUR_BIT_MODE

/*Configure if the RW pin is controlled or not , options : 1- Enabled
											   	   	   	   2- DISABLED*/

#define CLCD_RW_CTRL_EN		DISABLED

#define CLCD_CTRL_PORT		DIO_u8PORTA


#define CLCD_RS_PIN			DIO_u8PIN1
#define CLCD_E_PIN			DIO_u8PIN2

#if	CLCD_RW_CTRL_EN == ENABLED
#define CLCD_RW_PIN			DIO_u8PIN0
#endif



#define CLCD_DATA_PORT		DIO_u8PORTA

#if CLCD_OP_MODE == FOUR_BIT_MODE

#define CLCD_D4_PIN		DIO_u8PIN3
#define CLCD_D5_PIN		DIO_u8PIN4
#define CLCD_D6_PIN		DIO_u8PIN5
#define CLCD_D7_PIN		DIO_u8PIN6
#endif


#endif
