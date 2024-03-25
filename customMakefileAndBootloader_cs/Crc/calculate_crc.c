/*
 * calculate_crc.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Burak
 */

#include "calculate_crc.h"
#include "main.h"

int burak[10];
int burak2[10] = {78,99};
const int burak3[10] = {1,2,4,15,25,66,7058};

PUBLIC uint8_t bootloader_verify_crc(uint8_t *pData, uint32_t len, uint32_t crc_host)
{
  uint32_t uwCRCValue=0xff;

  for (uint32_t i=0 ; i < len ; i++)
	{
    uint32_t i_data = pData[i];
    uwCRCValue = HAL_CRC_Accumulate(&hcrc, &i_data, 1);
	}

  /* Reset CRC Calculation Unit */
  __HAL_CRC_DR_RESET(&hcrc);

	if( uwCRCValue == crc_host)
	{
		return SUCCESS;
	}

	return ERROR;
}
