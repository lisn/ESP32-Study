uint32_t ulTaskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait );

xClearCountOnExit：

pdFALSE,不会清除计数，ulTaskNotifyGive调用一次，计数增加一次。

pdTRUE,会清除计数器，

