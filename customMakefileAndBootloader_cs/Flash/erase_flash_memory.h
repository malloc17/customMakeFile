/*
 * erase_flash_operation.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef ERASE_FLASH_MEMORY_H_
#define ERASE_FLASH_MEMORY_H_

#include "common_definition.h"
#include "receive_message_from_host.h"

PUBLIC int bl_erase_flash(struct erase_flash_msg_s *erase_flash_msg);

#endif /* ERASE_FLASH_MEMORY_H_ */
