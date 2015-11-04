Linux Lab 2015-2016
=====================

Li Yilong 1300012815


LL101 -- 安装配置
---------------------

实战1：安装virtualbox和ubuntu server 14.04（1分）

实战2：Access a Virtualbox guest machine throught ssh（1分）

实战3：成功安装taglist，在vim中呈现函数列表（1分）

实战4：构建开发环境，成功编译运行helloworld程序（1分）


LL102 -- 启动流程
---------------------

实战1：利用git方式获取linux内核（1分）

实战2：开启initcall_debug，获取trace信息（1分）

实战3：采用scripts/bootgraph.pl生成SVG可缩放矢量图形（1分）

实战4：对占据时间较大的前10个initcall，列出其所在文件、initcall level以及功能简要说明（1分）


LL103 -- 内核模块
---------------------

实战1：编译并更新带自己名字缩写的内核（1分）

实战2：完成The Linux Kernel Module Programming Guide中的hello-5.c（1分）
http://tldp.org/LDP/lkmpg/2.6/html/index.html

实战3：总结内核的CodingStyle，并列出要点（1分）<br />
``Documentation/CodingStyle``

实战4：解决hello-5.c中的所有code style问题（1分）<br />
``scripts/checkpatch.pl -f hello-5.c``


LL104 -- 抽象层次
------------------

实战1：修改The Linux Kernel Module Programming Guide 8.1的例子，替换open系统调用（3分）

实战2：解决make headerdep的一个Warning（1分）



LL105 -- 调试之道
------------------

实战1：用`print_hex_dump`打印`boot_command_line`和`saved_command_line`的地址空间内容（1分）

实战2：开启Magic SysRQ，测试各种按键组合（1分）

实战3：学习内核`dump_stack`使用，使用`dump_stack`打印上堂课实战1的call stack（1分）

实战4：Following "Debugging the kernel using Ftrace"（1分）



Quiz 1
-----------------

编写两个模块：一个生产者，一个消费者

生产者模块：不能直接使用`printk`，但是需要每隔一段不固定的时间（random
ms）打印一条（字符串）信息，如下：

> `"%s (%d): count %d random %d\n", __func__, __LINE__, count, random`
> - `count`每次加一
> - `random`为随机数，取值1~1024

消费者模块：打印出生产者模块需要输出的信息，每隔固定时间（1s）打印一次，然后输出一次统计结果：总共打印了多少行（与`count`对比，确定正确性）

两种方案实现：
- 方案一：队列+动态申请内存
- 方案二：缓冲区+互斥
- 也可以提供新的方案
- 比较不同方案的优缺点
- 注意编码风格