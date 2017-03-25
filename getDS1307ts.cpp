/*
  getDS1307timeStamp.cpp - Library for DS1007.
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
/* 
This library defines only one function: getDS1307timeStamp().
This function gets from the RTC a timestamp string like
"YYYY-MM-DD hh:mm:ss".

The function is fast, it takes only 1.132 ms (1.128 - 1.142).
Using Process to get Linux time take more than 1 sec (see PollingTest
example).
For small footprint, this library can be used alone (undefine USE_I2C, USE_I2CW in 
getDS1307ts.h) or, if the I2Ctunnel is used, define USE_I2C or USE_I2CW. 

HARDWARE
  Requires real time clock DS13007 
*/

#include <getDS1307ts.h>


#ifndef USE_I2C
#ifndef USE_I2CW

// low level read I2C, can be used in arduino sketch to do local I2C tasks (see I2Ctunnel)
void readi2c(const byte dev_id, const char size_add,
               const unsigned int data_add, byte data[], const byte ndata) {
  Wire.beginTransmission(dev_id);
  if (size_add == I2C_ADD16) {
    Wire.write(highByte(data_add));
  }
  Wire.write(lowByte(data_add));
  Wire.endTransmission();
  Wire.requestFrom(dev_id, ndata);
  for (uint8_t  i = 0; i < ndata; i++) {
    data[i] = Wire.read();
  }
}
#endif
#endif
/*
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}
*/

const byte _tspos[7] = {17,14,11,0,8,5,2};
char _ts[20] = "20YY-MM-DD hh:mm:ss";  // 19 char plus \0
//              0123456789012345678
byte _i2cData[7];


char* _DS1307buffer2timeStamp(byte data[]) {
  // packedBCD to Ascii String
   for (byte i = 0; i<7; i++){
    if (i !=3) {
      _ts[_tspos[i]] = (data[i] >> 4) + '0';
      _ts[_tspos[i]+1] = (data[i] & 0x0F) + '0';
      }
    }
 return _ts;
  }

 
 
uint8_t getDS1307timeStamp(char* buffer){
#if defined(USE_I2C) || defined( USE_I2CW)

#ifdef USE_I2C
uint8_t error =  I2c.read(DS1307_ADDRESS, I2C_ADD8, 0, _i2cData, 7);
if (error) return error;
 _i2cData[0] &= 0x7F;        // clear bit 8
_DS1307buffer2timeStamp(_i2cData);
strcpy(buffer, _ts);
return(0);
#endif
#ifdef USE_I2CW
 I2Ctunnel.read(DS1307_ADDRESS, I2C_ADD8, 0, _i2cData, 7);
_DS1307buffer2timeStamp(_i2cData);
strcpy(buffer, _ts);
#endif
#else 
  readi2c(DS1307_ADDRESS, I2C_ADD8, 0, _i2cData, 7);
_DS1307buffer2timeStamp(_i2cData);
strcpy(buffer, _ts);

#endif
}
/*
char* getDS1307timeStamp(){
#ifndef USE_I2C
    readi2c(DS1307_ADDRESS, I2C_ADD8, 0, _i2cData, 7);
#else
    I2c.read(DS1307_ADDRESS, I2C_ADD8, 0, _i2cData, 7);
#endif
  _i2cData[0] &= 0x7F;        // clear bit 8
  return ( _DS1307buffer2timeStamp(_i2cData));
}
*/

/*
extra (maybe) useful functions

void _timeStamp2bufferDS1307(String tStamp, char tbuffer[]) {
  int n[7];
  // text to int array
  sscanf(tStamp.c_str(), "%u-%u-%u %u:%u:%u", &n[6],  &n[5],  &n[4],  &n[2],  &n[1],  &n[0] );
  n[3] = 0;
  n[6] -= 2000;
  // int to packedBCD
  for (int i = 0; i < 7; i++) {
    tbuffer[i] = n[i] + 6 * (n[i] / 10);
  }
}

void setDS1307clock(String timeStamp) {
  char i2cData[7];
  _timeStamp2bufferDS1307(timeStamp, i2cData);
  writeI2C(DS1307_ADDRESS, I2C_ADD8, 0, i2cData, 7);
}

*/
