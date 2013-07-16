/*****************************************************************************
 * File          : BTData.h
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

#ifndef BTDATA_H_
#define BTDATA_H_

#include <inttypes.h>

#define START_BYTE 0xFF

#define TYPE_POS 0x00
#define DATA 0x01
#define RA 0x02
#define AW 0x03

#define STATUS_POS 0x01
#define POWER_ON 0x01
#define POWER_OFF 0x02

#define DATA_POS 0x02

#define DATA_BUFFER_LENGTH 6
#define DATA_LENGTH DATA_BUFFER_LENGTH-DATA_POS

extern uint8_t bufferIdx;
uint8_t data_buffer[DATA_BUFFER_LENGTH];

extern uint8_t aquire;

typedef struct data_buffer{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t white;
} data_t;

uint8_t data_type;
extern uint8_t pwm_status;

extern uint8_t readBTPackage();
extern void clearDataBuffer();

#endif /* BTDATA_H_ */

