**事件组同步（Event Group SYNC）**：

同步的含义是，假如有三个任务，task1,task2,task3;优先级相同

task1,进行了xEventGroupSync等待 ，task1会阻塞，

task2,进行了xEventGroupSync等待 ，task2会阻塞，同时task1,继续阻塞，

task3,行了xEventGroupSync等待 ，task3,不会阻塞，因为其它等待的位，已经置起来了，后面发生任务调度，task1或者task3不不会阻塞。
