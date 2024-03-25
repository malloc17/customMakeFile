/*
 * send_message_to_host.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef SEND_MESSAGE_TO_HOST_H_
#define SEND_MESSAGE_TO_HOST_H_

#include "common_definition.h"
#include "stdint.h"
#include "main.h"

#define TX_BL_IS_READY        0x01
#define TX_WRITE_SUCCESS_CODE 0x02
#define TX_ERASE_SUCCESS_CODE 0x03
#define TX_WRITE_FAILED_CODE  0x04
#define TX_ERASE_FAILED_CODE  0x05
#define TX_USER_APP_RUNNING   0x06

extern UART_HandleTypeDef huart3;

PUBLIC void send_message_to_host(uint8_t message_code);

#endif /* SEND_MESSAGE_TO_HOST_H_ */
