/*
 * receive_message_from_host.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef RECEIVE_MESSAGE_FROM_HOST_H_
#define RECEIVE_MESSAGE_FROM_HOST_H_

#include "common_definition.h"
#include "main.h"

#define CMD_ERASE_FLASH 0xAA
#define CMD_WRITE_FLASH 0xBB

#define SIZE_OF_COMMAND_CODE 0x01

#define WRITE_FLASH_DATA_SIZE 255

extern UART_HandleTypeDef huart3;
extern struct erase_flash_msg_s erase_flash_msg;
extern struct write_flash_msg_s write_flash_msg;


PUBLIC void bootloader_uart_read_data(void);
PUBLIC void receive_message_from_host_polling(uint8_t * pData, uint16_t size);

struct erase_flash_msg_s
{
	uint8_t command_code;
	uint8_t sector_number;
	uint32_t  crc_val;
}__attribute__((__packed__));

struct write_flash_header_s
{
	uint8_t   command_code;
	uint32_t  write_address;
	uint8_t   data_len;
}__attribute__((__packed__));

struct write_flash_msg_s
{
	struct write_flash_header_s write_flash_header;
	uint8_t   data[WRITE_FLASH_DATA_SIZE];
	uint32_t  crc_val;
}__attribute__((__packed__));


#endif /* RECEIVE_MESSAGE_FROM_HOST_H_ */
