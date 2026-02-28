1：esp32 有两种看门狗

a:中断看门狗

b:任务看门狗

2：

idf.py menuconfig

使能中断看门狗

Component config  ---> ESP System Settings  ---> Interrupt watchdog 

配置中断看门狗的时间

Component config  ---> ESP System Settings  ---> (300)   Interrupt watchdog timeout (ms)

使能任务看门狗

Component config  ---> ESP System Settings  ---> Enable Task Watchdog Timer 

配置任务看门狗的时间

Component config  ---> ESP System Settings  ---> (5)         Task Watchdog timeout period (seconds)



3：参考网址

[看门狗 - ESP32-C5 - — ESP-IDF 编程指南 v5.5.3 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.5.3/esp32c5/api-reference/system/wdts.html)