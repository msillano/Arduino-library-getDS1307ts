# Arduino-library-getDS1307ts
This library defines only one function: getDS1307timeStamp(). 

getDS1307timeStamp() gets from the RTC a timestamp string like "YYYY-MM-DD hh:mm:ss".

The function is fast, it takes only 1.132 ms (1.128 - 1.142).
Using Process to get Linux time (in an Arduini Yùn) take more than 1 sec (see PollingTest
example, here: https://github.com/msillano/Arduino-library-Polling/tree/master/examples/PollingTest).
