# Arduino-library-getDS1307ts
This library defines only one function: getDS1307timeStamp(). 

getDS1307timeStamp() gets from the RTC a timestamp string like "YYYY-MM-DD hh:mm:ss".

The function is fast, it takes only 1.132 ms (1.128 - 1.142).
Using Process to get Linux time (using an Arduino Yùn) take more than 1 sec (see PollingTest
example, here: https://github.com/msillano/Arduino-library-Polling/tree/master/examples/PollingTest).

If one of I2Ctunnel or I2CtunnelW library are used, this library uses low level I2Ctunnel read.
Else it uses local I2C read function whith Wire lib (see USE_I2C  and  USE_I2CW).
