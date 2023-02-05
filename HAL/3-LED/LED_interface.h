/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : LED_interface.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define ACTIVE_LOW		0u
#define ACTIVE_HIGH		1u

typedef struct {

	uint8 Type;
	uint8 Port;
	uint8 Pin;
}LED_t;

#endif
