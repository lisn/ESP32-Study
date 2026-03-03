#include “FreeRTOS.h”
#include “timers.h”

TimerHandle_t xTimerCreate( const char *pcTimerName,
const TickType_t xTimerPeriod,
const UBaseType_t uxAutoReload,
void * const pvTimerID,
TimerCallbackFunction_t pxCallbackFunction );

pcTimerName：定时器名字，用于调试

xTimerPeriod：周期，单位是系统的tick数，可以通过pdMS_TO_TICKS,把秒转化为tick数。

uxAutoReload：定时器是否重载，为FALSE时，只运行一次。

pvTimerID：给定时器的ID。

pxCallbackFunction ：定时器回调函数。



