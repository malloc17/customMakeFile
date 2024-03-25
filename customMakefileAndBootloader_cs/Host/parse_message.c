/*
 * parse_message.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#include <send_message_to_host.h>
#include "parse_message.h"
#include "receive_message_from_host.h"
#include "erase_flash_memory.h"
#include "write_flash_memory.h"
#include "main.h"
#include "stdint.h"
#include "calculate_crc.h"

void download_user_app_sector_to_flash()
{
    //execute_mem_write(uint8_t *pBuffer, sector, uint32_t len);  /*Burayı tamamla*/
}

PUBLIC void parse_erase_message(uint8_t bl_received_command)
{
    erase_flash_msg.command_code = bl_received_command;
    receive_message_from_host_polling(&erase_flash_msg.sector_number, (uint16_t) sizeof(struct erase_flash_msg_s) - 1);
    
    uint8_t crc_status = bootloader_verify_crc((uint8_t *) &erase_flash_msg, sizeof(struct erase_flash_msg_s) - sizeof(erase_flash_msg.crc_val), erase_flash_msg.crc_val);
    if(crc_status == SUCCESS)
    {
        bl_erase_flash(&erase_flash_msg);
    }
    else
    {
        send_message_to_host((uint8_t) TX_ERASE_FAILED_CODE);
    }
}

PUBLIC void parse_write_message(uint8_t bl_received_command)
{
    uint8_t addres_arr[4];
    write_flash_msg.write_flash_header.command_code = bl_received_command;

    receive_message_from_host_polling(addres_arr, (uint16_t) sizeof(struct write_flash_header_s) - 2*sizeof(uint8_t));
    write_flash_msg.write_flash_header.write_address = (addres_arr[0] << 3*8) | (addres_arr[1] << 2*8) | (addres_arr[2] << 1*8) | (addres_arr[3]) ;

    receive_message_from_host_polling(&write_flash_msg.write_flash_header.data_len, (uint16_t) sizeof(write_flash_msg.write_flash_header.data_len));
    receive_message_from_host_polling((uint8_t *)write_flash_msg.data, (uint16_t) write_flash_msg.write_flash_header.data_len);
    receive_message_from_host_polling((uint8_t *)&write_flash_msg.crc_val, (uint16_t) sizeof(uint32_t));

    uint8_t crc_status = bootloader_verify_crc((uint8_t *)&write_flash_msg, sizeof(struct write_flash_header_s) + write_flash_msg.write_flash_header.data_len , write_flash_msg.crc_val);

    uint8_t status = execute_mem_write(write_flash_msg.data, write_flash_msg.write_flash_header.write_address, write_flash_msg.write_flash_header.data_len);

    if(status == HAL_OK)
    {
        send_message_to_host((uint8_t) TX_WRITE_SUCCESS_CODE);
        download_user_app_sector_to_flash();
    }
    else
        send_message_to_host((uint8_t) TX_WRITE_FAILED_CODE); 
    
}


