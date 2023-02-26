/*
 * ADC_cfg.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/**
 * @details Configure the reference voltage options : 1-AREF_REF	2-AVCC_REF	3-INTERNAL_2560MV_REF
 */
#define ADC_u8REF_VOLT		AVCC_REF

/**
 * @details configure the required ADC resolution options : 1-EIGHT_BITS	2-TEN_BITS
 */
#define ADC_u8RESOLUTION	EIGHT_BITS

/**
 * @details configure the required ADC Interrupt Enable options : 1-ENABLED	2-DISABLED
 */
#define ADC_u8INT_ENABLE	DISABLED


#define ADC_u8PRESCALER_VAL	DIVISION_BY_128

#define ADC_u32TIMEOUT		50000u

#endif /* ADC_CFG_H_ */
