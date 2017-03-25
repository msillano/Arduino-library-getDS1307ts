/*
  RTC_timestamp.ino - Extends I2Ctest.ino testing the getDS1307ts library.
  Copyright (c) 2014 Marco Sillano.  All right reserved.

  getDS1307timeStamp() return a timestamp using RTC and I2C. The timestamp 
  can be used in datalogging applications. 
  The function is fast, it takes about 1.132 ms to get the timestamp.
  (To get the timestamp from linux, using Process and date, is 1000 times 
  slover: see PollingTest.ino, in Polling library).
  See I2Ctest for more informations.
  
  Timestamp format: YYYY-MM-DD hh:mm:ss.
  note: the clock must be in 24H mode, no AM/PM support.
  
USE
  Compile and start this sketch, start Console.

HARDWARE
  This sketch requires a RTC clock (DS1307) 
*/

#include <Bridge.h>
#include <Console.h>
#include <Wire.h>
#include <YunServer.h>
#include <YunClient.h>
// uses I2Ctunnel to do I2C read
#include <I2Ctunnel.h>
#include <getDS1307ts.h>

YunServer server;
//---------------------------------------------------------

void setup() {
  Bridge.begin();
  Console.begin();
  Wire.begin();
  // Wait for the Console port to connect
  while (!Console);
  Console.println("getDS130l7ts  Library TEST");
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
// test getDS1307ts library
  unsigned long ustart = micros();
  String ts = getDS1307timeStamp();
  unsigned long uend = micros();
// output results every 2 secomds 
  Console.print(" timeStamp: ");
  Console.println(ts); 
  Console.print( "  micros:");
  Console.println(uend - ustart);
  
// Get clients coming from server (same as I2Ctest)
  YunClient client = server.accept();
  // There is a new client?
  if (client) {
    // Process request
    doCommand(client);
    // Close connection and free resources.
    client.stop();
  }
  delay(2000);  // 2 sec delay, must add the execution time.
// To do simplest and more precise polling you can use the 
// Polling library.
}

void doCommand(YunClient client) {
  // read the command
  String commandstr = client.readStringUntil('/');
  // is "I2C" command?
  if (commandstr == "I2C") {
    I2Ctunnel.command(client);     // I2Ctunnel does all  work
  // for debug only
#ifdef I2C_DEBUG 
    Console.println(I2Ctunnel.getLastCommand()); 
#endif	
    } else {
	/* more commands here */
	}
}
/*
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
