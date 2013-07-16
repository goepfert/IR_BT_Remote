/*****************************************************************************
* File          : uart.h
* Created       : 23.03.2013
*
* Title         : ---
* Author        : Thomas Goepfert
* Contact       : info@SolderLab.de
*
* Version       : 1.0
* Last Changed  : 23.03.2013 by goepfert
* Remarks       : Based on Peter Fleury's uart lib
*
* Description   : uart with circular buffers
*****************************************************************************/

#ifndef UART_H
#define UART_H

#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef UART_RX_BUFFER_SIZE
	#define UART_RX_BUFFER_SIZE 32
#endif

#ifndef UART_TX_BUFFER_SIZE
	#define UART_TX_BUFFER_SIZE 32
#endif

// error return code: high byte of uart_getc()
#define UART_FRAME_ERROR      0x0800 	// Framing Error by UART - FE=4
#define UART_OVERRUN_ERROR    0x0400 	// Overrun condition by UART - DOR=3
												// A character already present in the UART UDR register was
 	 	 	 	 	 	 	 	 	 	 	 	// not read by the interrupt handler before the next character arrived,
									 	 	 	// one or more received characters have been dropped.
#define UART_BUFFER_OVERFLOW  0x0200 	// receive circular buffer overflow
 	 	 	 	 	 	 	 	 	 	 	 	// We are not reading the receive buffer fast enough,
 	 	 	 	 	 	 	 	 	 	 	 	// one or more received character have been dropped.
#define UART_NO_DATA          0x0100 	// no receive data available


// function prototypes
extern void uart_init(uint32_t baudrate);
extern unsigned int uart_getc(void); 	   	// low byte: received character, high byte: last receive error
extern void uart_putc(char data);

#endif // UART_H
