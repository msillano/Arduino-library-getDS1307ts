/*
  getDS1307ts.h - Library for DS1307 local timestamp.
  Copyright (c) 2014 Marco Sillano.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef getDS1307timeStamp_h
#define getDS1307timeStamp_h

#define USE_I2C
// #define USE_I2CW
#include "Arduino.h"

#if defined(USE_I2C) || defined( USE_I2CW)
#ifdef USE_I2C
  #include <I2Ctunnel.h>
#else
  #include <I2CtunnelW.h>
#endif
#else
  #include <Wire.h>
  #define  I2C_ADD8   'B'
  #define  I2C_ADD16  'W'
#endif

#define   DS1307_ADDRESS  0x68

// defines only one function
uint8_t getDS1307timeStamp(char* buffer);
/*
char* getDS1307timeStamp();
*/

#endif