/*
 * receive_message_from_host.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */
#include "receive_message_from_host.h"
#include "main.h"
#include "stdint.h"
#include "parse_message.h"

struct erase_flash_msg_s erase_flash_msg;
struct write_flash_msg_s write_flash_msg;

PUBLIC void receive_message_from_host_polling(uint8_t * pData, uint16_t size)
{
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart3, pData, size, HAL_MAX_DELAY);
    while(status != HAL_OK)
    {
        status = HAL_UART_Receive(&huart3, pData, size, HAL_MAX_DELAY);
    }
}

PUBLIC void bootloader_uart_read_data(void)
{
    uint8_t bl_received_command;
	while(1)
	{
        receive_message_from_host_polling(&bl_received_command, (uint16_t) SIZE_OF_COMMAND_CODE);

		if(bl_received_command == CMD_ERASE_FLASH)
		{
            parse_erase_message(bl_received_command);
		}
		else if(bl_received_command == CMD_WRITE_FLASH)
		{
            parse_write_message(bl_received_command);
		}
	}
}

