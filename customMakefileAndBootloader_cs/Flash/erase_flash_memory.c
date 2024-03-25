/*
 * erase_flash_operation.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */
#include <send_message_to_host.h>
#include "erase_flash_memory.h"
#include "main.h"
#include "stdint.h"
#include "receive_message_from_host.h"

int bl_erase_flash(struct erase_flash_msg_s *erase_flash_msg)
{
	FLASH_EraseInitTypeDef flash_erase_init;
	uint32_t sector_err;
	HAL_StatusTypeDef status;

	if(erase_flash_msg->sector_number == 0xFF)
	{
		flash_erase_init.TypeErase = FLASH_TYPEERASE_MASSERASE;
	}
	else
	{
		flash_erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
		flash_erase_init.Sector = erase_flash_msg->sector_number;
	}

	flash_erase_init.Banks = FLASH_BANK_1;
	flash_erase_init.NbSectors = 1;
	flash_erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	HAL_FLASH_Unlock();
	status = HAL_FLASHEx_Erase(&flash_erase_init, &sector_err);
	HAL_FLASH_Lock();

	if(status != HAL_OK)
	{
		send_message_to_host((uint8_t) TX_ERASE_FAILED_CODE);
		return ERROR;
	}
	send_message_to_host((uint8_t) TX_ERASE_SUCCESS_CODE);
	return SUCCESS;
}
