message buffer 与 stream buffer 高度相似
区别：

1：message 只能是发一次，接收一次数据，收发的次数一一对应，

​		stream 可以是多次发，一次或者几次接收完，发的次数大于等于接的次数。

2：message 与 stream 接收函数的区别

``````

size_t xMessageBufferReceive( MessageBufferHandle_t xMessageBuffer,
void *pvRxData,
size_t xBufferLengthBytes,
TickType_t xTicksToWait );

与

size_t xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
void *pvRxData,
size_t xBufferLengthBytes,
TickType_t xTicksToWait );
``````

当xBufferLengthBytes的长度小于发送数据长度时，message,将接收不到数据，而stream是可以接收到数据。

详见代码的例子。
