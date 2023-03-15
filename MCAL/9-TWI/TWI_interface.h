/*
 * TWI_interface.h
 *
 *  Created on: Mar 15, 2023
 *      Author: user
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	NullPtrErr,
	StartCondErr,
	RepStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MstrWriteByteWithAckErr,
	MstrReadByteWithAckErr

}TWI_ErrorStatus_t;


void TWI_voidMasterInit(uint8 Copy_u8Address);

void TWI_voidSlaveInit(uint8 Copy_u8Address);

TWI_ErrorStatus_t TWI_SendStartCondition(void);

TWI_ErrorStatus_t TWI_SendRepeatedStart(void);

TWI_ErrorStatus_t TWI_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress);

TWI_ErrorStatus_t TWI_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress);

TWI_ErrorStatus_t TWI_MasterWriteDataByte(uint8 Copy_u8DataByte);

TWI_ErrorStatus_t TWI_MasterReadDataByte(uint8* Copy_u8DataByte);

void TWI_SendStopCondition(void);

#endif /* TWI_INTERFACE_H_ */
