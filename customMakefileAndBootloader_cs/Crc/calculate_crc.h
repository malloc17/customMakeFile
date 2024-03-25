/*
 * calculate_crc.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#ifndef CALCULATE_CRC_H_
#define CALCULATE_CRC_H_

#include "stdint.h"
#include "common_definition.h"
#include "main.h"

extern CRC_HandleTypeDef hcrc;

PUBLIC uint8_t bootloader_verify_crc(uint8_t *pData, uint32_t len, uint32_t crc_host);

#endif /* CALCULATE_CRC_H_ */
