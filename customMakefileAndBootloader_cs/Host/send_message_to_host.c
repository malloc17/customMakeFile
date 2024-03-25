/*
 * send_message_to_host.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */
#include "send_message_to_host.h"
#include "main.h"


PUBLIC void send_message_to_host(uint8_t message_code)
{
	HAL_UART_Transmit(&huart3, &message_code, 1, HAL_MAX_DELAY);
}
