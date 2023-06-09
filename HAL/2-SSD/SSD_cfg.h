/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : SSD_reg.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef SSD_CFG_H_
#define SSD_CFG_H_

/*Please Choose What type of SSD you use : 1-ANODE -> common anode
 * 										   2-CATHODE -> common cathode
 * 										   3-ETA -> ETA KIT*/

#define SSD_OP_MODE		ETA

/*7segment display is common cathode, so a high on a segment turns it ON while low turns it OFF : 1- ON
 * 																								  2- OFF*/

#define SSD_STATE	OFF

#define SSD_ENABLE_PORT		DIO_u8PORTC
#define SSD_ENABLE_PIN		DIO_u8PIN6

#define SSD_CTRL_PORT	DIO_u8PORTA
/*
#define SSD_A_PIN		DIO_u8PIN1
#define SSD_B_PIN		DIO_u8PIN2
#define SSD_C_PIN		DIO_u8PIN3
#define SSD_D_PIN		DIO_u8PIN4
#define SSD_E_PIN		DIO_u8PIN5
#define SSD_F_PIN		DIO_u8PIN6
#define SSD_G_PIN		DIO_u8PIN7
*/
/*The dot pin is the first pin in PORTB*/
#define SSD_DT_PIN		DIO_u8PIN0



#endif
