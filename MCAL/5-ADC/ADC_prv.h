/*
 * ADC_prv.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

#define PRESCALER_MASK			0b11111000
#define CHANNEL_MASK			0b11100000

#define AREF_REF				1u
#define AVCC_REF				2u
#define INTERNAL_2560MV_REF		3u

#define EIGHT_BITS 				1u
#define TEN_BITS				2u


#define DIVISION_BY_0			0u
#define DIVISION_BY_2			1u
#define DIVISION_BY_4			2u
#define DIVISION_BY_8			3u
#define DIVISION_BY_16			4u
#define DIVISION_BY_32			5u
#define DIVISION_BY_64			6u
#define DIVISION_BY_128			7u

#endif /* ADC_PRV_H_ */
