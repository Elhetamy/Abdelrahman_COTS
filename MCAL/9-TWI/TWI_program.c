/*
 * TWI_program.c
 *
 *  Created on: Mar 15, 2023
 *      Author: user
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include  "defines.h"

#include "TWI_interface.h"
#include "TWI_cfg.h"
#include "TWI_private.h"
#include "TWI_reg.h"

/*In case of the master won't being addressed, pass the address parameter as zero*/
void TWI_voidMasterInit(uint8 Copy_u8Address)
{
	/*Set node address*/
	if(Copy_u8Address != 0u)
	{
		TWI_TWAR = Copy_u8Address << 1u;
	}

	/*CPU frequency = 16MHz , preScaler =0 , Communication frequency = 400KHz*/
	CLR_BIT(TWI_TWSR,TWSR_TWPS0);
	CLR_BIT(TWI_TWSR,TWSR_TWPS1);
	TWI_TWBR = 12u;

	/*TWI Enable*/
	SET_BIT(TWI_TWCR,TWCR_TWEN);

}

void TWI_voidSlaveInit(uint8 Copy_u8Address)
{
	/*Set node address*/

	TWI_TWAR = Copy_u8Address << 1u;


	/*Enable ACK bit*/
	SET_BIT(TWI_TWCR,TWCR_TWEA);


	/*TWI Enable*/
	SET_BIT(TWI_TWCR,TWCR_TWEN);


}

TWI_ErrorStatus_t TWI_SendStartCondition(void)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set Start condition bit*/
	SET_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous action finishes and the interrupt flag is raised again*/
	while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

	/*Check the status of the bus*/
	if((TWI_TWSR & STATUS_BITS_MASK) != START_ACK)
	{
		Local_Error = StartCondErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrorStatus_t TWI_SendRepeatedStart(void)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set Start condition bit*/
	SET_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous action finishes and the interrupt flag is raised again*/
	while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

	/*Check the status of the bus*/
	if((TWI_TWSR & STATUS_BITS_MASK) != REP_START_ACK)
	{
		Local_Error = RepStartErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrorStatus_t TWI_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t LocalError = NoError;

	/*Set the slave address into the data register*/
	TWI_TWDR = Copy_u8SlaveAddress << 1;

	/*Clear bit 0 for write request*/
	CLR_BIT(TWI_TWDR , 0);

	/*Clear start condition bit*/
	CLR_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous action finishes and the interrupt flag is raised again*/
	while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

	/*Check the status of the bus*/
	if((TWI_TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		LocalError = SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return LocalError;
}

TWI_ErrorStatus_t TWI_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress)
{

	TWI_ErrorStatus_t LocalError = NoError;

	/*Set the slave address into the data register*/
	TWI_TWDR = Copy_u8SlaveAddress << 1;

	/*set bit 0 for Read request*/
	SET_BIT(TWI_TWDR , 0);

	/*Clear start condition bit*/
	CLR_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous action finishes and the interrupt flag is raised again*/
	while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

	/*Check the status of the bus*/
	if((TWI_TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		LocalError = SlaveAddressWithReadErr;
	}
	else
	{
		/*Do nothing*/
	}

	return LocalError;
}

TWI_ErrorStatus_t TWI_MasterWriteDataByte(uint8 Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Put the data type on the bus*/
	TWI_TWDR = Copy_u8DataByte;

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous action finishes and the interrupt flag is raised again*/
	while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

	/*Check the status of the bus*/
	if((TWI_TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_Error = MstrWriteByteWithAckErr;
	}
	else
	{
		/*Do nothing*/
	}



	return Local_Error;
}

TWI_ErrorStatus_t TWI_MasterReadDataByte(uint8* Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	if(Copy_u8DataByte != NULL)
	{
		/*Clear interrupt flag to enable SLAVE to send data*/
		SET_BIT(TWI_TWCR,TWCR_TWINT);
		/*Wait until the slave writing finishes and the interrupt flag is raised again*/
		while(GET_BIT(TWI_TWCR,TWCR_TWINT) == 0);

		/*Check the status of the bus*/
		if((TWI_TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_Error = MstrReadByteWithAckErr;
		}
		else
		{
			/*Read the data sent from slave*/
			*Copy_u8DataByte = TWI_TWDR;
		}

	}
	else
	{
		Local_Error = NullPtrErr;
	}


	return Local_Error;
}

void TWI_SendStopCondition(void)
{
	/*Set the stop condition bit */
	SET_BIT(TWI_TWCR,TWCR_TWSTO);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

}
