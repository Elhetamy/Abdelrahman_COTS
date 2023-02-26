/*
 * ADC_reg.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_


#define ADMUX			*((volatile uint8*)0x27)
/*
#define ADMUX_u8MUX0 		0u
#define ADMUX_u8MUX1 		1u
#define ADMUX_u8MUX2 		2u
#define ADMUX_u8MUX3 		3u
#define ADMUX_u8MUX4 		4u
*/
#define ADMUX_u8ADLAR		5u
#define ADMUX_u8REFS0		6u
#define ADMUX_u8REFS1		7u



#define ADCSRA  		*((volatile uint8*)0x26)
#define ADCSRA_u8ADPS0 	0u
#define ADCSRA_u8ADPS1 	1u
#define ADCSRA_u8ADPS2 	2u
#define ADCSRA_u8ADIE 	3u
#define ADCSRA_u8ADIF  	4u
#define ADCSRA_u8ADSC  	6u
#define ADCSRA_u8ADEN  	7u


#define ADCL    		*((volatile uint8*)0x24)
#define ADCH			*((volatile uint8*)0x25)

#define ADC				*((volatile uint16*)0x24)	/*ADC data register*/

#endif /* ADC_REG_H_ */
