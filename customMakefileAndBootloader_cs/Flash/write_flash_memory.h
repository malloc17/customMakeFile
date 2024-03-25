/*
 * write_flash_operation.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef WRITE_FLASH_MEMORY_H_
#define WRITE_FLASH_MEMORY_H_

#include "common_definition.h"
#include "stdint.h"

PUBLIC uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len);

#endif /* WRITE_FLASH_MEMORY_H_ */
