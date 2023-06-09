/***************************************************/
/***************************************************/
/******** 	Author : Abdelrahman Mohamed	********/
/******** 	File : SSD_interface.h 		********/
/******** 	Version : 1.00					********/
/***************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define ANODE		0u
#define CATHODE		1u
#define ETA_KIT		2u

typedef struct
{
	uint8 Type;
	uint8 Port;
	uint8 LedApin;
	uint8 EnablePort;
	uint8 EnablePin;

}SSD_t;


uint8 SSD_u8SetNumber(const SSD_t * Object,uint8 Copy_u8Num);

#define ZERO		64u

#endif
