/*****************************************************************************
 * File          : BTData.c
 * Created       : Jul 10, 2013
 * 
 * Title         : ---
 * Author        : goepfert
 * Contact       : info@SolderLab.de
 * 
 * Version       : 1.0
 * Last Changed  : Jul 10, 2013 by goepfert
 * Remarks       : ---
 *
 * Description   : ---
 *
 *****************************************************************************/

#include "BTData.h"
#include "uart.h"

#include <string.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

//some defaults
uint8_t bufferIdx = 0;
uint8_t aquire = 0;
uint8_t pwm_status = POWER_OFF;

uint8_t readBTPackage() {

	uint8_t ret = FALSE;

	if (uart_available()) {

		uint8_t indata = uart_getc();

		if (indata == START_BYTE) {
			clearDataBuffer();
			bufferIdx = 0;
			aquire = TRUE;
		} else if (aquire) {
			data_buffer[bufferIdx] = indata;
			bufferIdx++;
		} else {
			//
		}

		if (bufferIdx >= DATA_BUFFER_LENGTH) {
			aquire = FALSE;
			ret = TRUE;
			bufferIdx = 0;
		}
	}

	return ret;
}

void clearDataBuffer() {
	memset(data_buffer, (uint8_t)0, DATA_BUFFER_LENGTH);
}
