/*
 * parse_message.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef PARSE_MESSAGE_H_
#define PARSE_MESSAGE_H_

#include "common_definition.h"
#include "stdint.h"

PUBLIC void parse_erase_message(uint8_t bl_received_command);
PUBLIC void parse_write_message(uint8_t bl_received_command);

#endif /* PARSE_MESSAGE_H_ */
