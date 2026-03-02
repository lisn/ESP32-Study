队列消息邮箱，

xMailbox = xQueueCreate(1, sizeof(int));

创建时，长度为1.

xQueueOverwrite 函数，会覆盖之前的数据，也不会产生满的情况。

只要xQueueOverwrite 写过一次，xQueuePeek就可以读到数据。