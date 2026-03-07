**流缓冲：**

StreamBufferHandle_t xStreamBufferCreate( size_t xBufferSizeBytes,
size_t xTriggerLevelBytes );

xBufferSizeBytes：流缓冲的大小

xTriggerLevelBytes ：任务进入阻塞后，数据达到xTriggerLevelBytes 时，退出阻塞；前提是任务必须进入阻塞。

```
片段1
for (;;)

 {
​    vTaskDelay(pdMS_TO_TICKS(2000));

​    strlen = sprintf(tx_buf, "I am sunny,now I am in shenzhou %d.", i++);

​    sendlen = xStreamBufferSend(xStreamBuffer, tx_buf, strlen, portMAX_DELAY);

​    printf("str len: %d, send len: %d, send data: %s\n", strlen, sendlen, tx_buf);
  }
  
  片段2
for (;;)

 {
​    strlen = sprintf(tx_buf, "I am sunny,now I am in shenzhou %d.", i++);

​    sendlen = xStreamBufferSend(xStreamBuffer, tx_buf, strlen, portMAX_DELAY);

​    printf("str len: %d, send len: %d, send data: %s\n", strlen, sendlen, tx_buf);

​    vTaskDelay(pdMS_TO_TICKS(2000));
  }
  
```

片段1与片段2的区别在vTaskDelay的位置不同。如果sendtask一开始主发数据，rcvtask还没有进入阻塞状态，就会导致，rcvtask第一次接收数据时，打印出sendtask发的数据。

如果sendtask不发数据，让度CPU，让rcvtask进入阻塞状态，rcvtask，只会等sendtask发的数据不少于xTriggerLevelBytes ，rcvtask两次调度时，才会解除阻塞，接受到数据。
