/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmpsystem.h - system specific includes and defines
 *
 * Copyright (c) 2009-2013 Frank Meyer - frank(at)fli4l.de
 *
 * $Id: irmpsystem.h,v 1.8 2013/01/17 07:33:13 fm Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef _IRMPSYSTEM_H_
#define _IRMPSYSTEM_H_

#if !defined(_IRMP_H_) && !defined(_IRSND_H_)
#  error please include only irmp.h or irsnd.h, not irmpsystem.h
#endif

#define ATMEL_AVR                                                                 // ATMEL AVR

#include <string.h>

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define IRSND_OC2   0
#define IRSND_OC2A  1
#define IRSND_OC2B  2
#define IRSND_OC0   3
#define IRSND_OC0A  4
#define IRSND_OC0B  5

#ifndef TRUE
#  define TRUE  1
#  define FALSE 0
#endif

typedef struct
{
  uint8_t   protocol;
  uint16_t  address;
  uint16_t  command;
  uint8_t   flags;
} IRMP_DATA;

#endif // _IRMPSYSTEM_H_
