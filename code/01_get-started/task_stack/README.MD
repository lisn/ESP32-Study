UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask );

1：这个函数可以获取剩余栈空间的大小，返回值的单位是字长(一般为4个字节)，根据平台配置有关。

2：printf/vTaskDelay 这些函数都是要占用任务的栈空间的。

3：app_main的栈定义的宏为CONFIG_ESP_MAIN_TASK_STACK_SIZE=3584

运行idf.py menuconfig

在Component config  ---> ESP System Settings  ---> Main task stack size 中可以进行修改。