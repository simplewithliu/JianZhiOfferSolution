### Sept 22 2022

**1 unix domain sockets VS internet sockets**

https://lists.freebsd.org/pipermail/freebsd-performance/2005-February/001143.html


**2 System Bus Matrix**

https://microchipdeveloper.com/32bit:mx-arch-system-bus-matrix


### Sept 28 2022

**1 信号与信道复用技术**

https://iot-book.github.io/2_信号处理基础/S2_模拟信号和数字信号介绍

https://blog.51cto.com/u_14758357/3050713

https://zh-cn.lambdageeks.com/multiplexing-types-tdm-fdm/


**2 谈一谈接口电路**

https://www.jianshu.com/p/9536cd0d4be4

### Oct 10 2022

**1 梯度下降法的神经网络容易收敛到局部最优，为什么应用广泛？**

张大帅的回答 - 知乎
https://www.zhihu.com/question/68109802/answer/260019230


**2 梯度下降的参数更新公式是如何确定的？**

https://www.zhihu.com/question/57747902


### Nov 01 2022

**1 check  main thread STATE and stacktrace**
http://elliotth.blogspot.com/2012/08/how-to-read-dalvik-sigquit-output.html

### Nov 27 2022

**1 Linux Kernel 内存管理介绍**

http://blog.chinaunix.net/uid-29025972-id-5768074.html

https://juejin.cn/post/7153083367670415397

* 缺页处理
	https://blog.csdn.net/bin_linux96/article/details/105326880
	https://ty-chen.github.io/linux-kernel-mmap/

**2 Linux内核虚拟地址空间**

https://fanlv.wiki/2021/07/25/linux-mem/


### Dec 02 2022

**1 Linux内核概览**

https://makelinux.github.io/kernel/map/


### Dec 07 2022

**1 man手册的更新**

https://unix.stackexchange.com/questions/432599/man-pages-when-to-put-a-new-system-call-in-section-2-and-when-in-section-3

https://unix.stackexchange.com/questions/266179/do-i-need-to-write-man-pages-for-c-library


### Dec 11 2022

**1 ION**

https://i.blackhat.com/Asia-22/Friday-Materials/AS-22-Wu-ExplosION-The-Hidden-Mines.pdf

https://blog.csdn.net/qq_40405527/article/details/123578849

https://stackoverflow.com/questions/21174272/need-help-in-understanding-android-memory-allocator

https://elinux.org/Android_Kernel_Features
```
ashmem and pmem are very similar. Both are used for sharing memory between processes. 
ashmem uses virtual memory, whereas pmem uses physically contiguous memory.
```

**2 Flash、RAM、ROM的区别**

https://gist.github.com/but0n/d773f855b1641e156f2d2e40ada9dbdc


### Dec 14 2022

**1 一些内核的书籍**

通过看韦东山的Linux驱动视频可以转行嵌入式底层驱动工程师吗? - Stay Foolish的回答 - 知乎 

https://www.zhihu.com/question/567805075/answer/2784681022


**2 NDK get pid from package name**

https://stackoverflow.com/questions/34072185/ndk-get-pid-from-package-name


### Dec 26 2022

**1 设备控制器**


* 11.2.2 I/O接口及设备控制器

I/O接口是处于一组I/O端口和对应的设备控制器之间的一种硬件电路。它起翻译器的作用，即把I/O端口中的值转换成设备所需要的命令和数据。从另一个角度来看，它检测设备状态的变化，并对起状态寄存器作用的I/O端口进行相应地更新。还可以通过一条IRQ线把这种电路连接到可编程中断控制器上，以使它代表相应的设备发出中断请求。
	
有两类类型的接口：
	
专用I/O接口：专门用于一个特定的硬件设备。在一些情况下，设备控制器与这种I/O接口处于同一块卡中，连接到专用I/O接口上的设备可以是内部设备（位于PC机箱内部的设备），也可以是外部设备（位于PC机箱外部的设备）。例如键盘接口、图形接口、磁盘接口、总线鼠标接口及网络接口都属于专用I/O接口。

通用I/O接口：用来连接多个不同的硬件设备。连接到通用I/O接口上的设备通常都是外部设备。例如并口、串口、通用串行总线（USB）、PCMCIA接口及SCSI接口都属于通用I/O接口。
	
复杂的设备可能需要一个设备控制器来驱动。控制器具有两方面的作用，一是对从I/O接口接收到的高级命令进行解释，并通过向设备发送适当的电信号序列强制设备执行特定的操作；二是对从设备接收到的电信号进行转换和解释，并通过I/O接口修改状态寄存器的值。

磁盘控制器是一种比较典型的设备控制器，它通过I/O接口从微处理器接收诸如“写这个数据块”之类的高级命令，并将其转换成诸如“把磁头定位在正确位置的磁道”上和“把数据写入这个磁道”之类的低级磁盘操作。现在的磁盘控制器相当复杂，因为它们可以把磁盘数据快速保存到内存的缓存区中，还可以根据实际磁盘的几何结构重新安排CPU的高级请求，使其优化。

https://book.aikaiyuan.com/kernel/11.2.2.htm



* 《计算机组成原理》 唐朔飞 P189

可以大概理解设备控制器的概念是从软件上来描述硬件的IO接口部分，也就是与操作系统交互以及受其控制的部分，从而进一步控制外围硬件。


### Jan 03 2023

**1 神经网络 局部最优问题**

https://zhidao.baidu.com/question/361520382448996572.html

https://blog.csdn.net/m0_37957160/article/details/121913311


### Jan 04 2023

**1 drm框架的专栏**

https://blog.csdn.net/weixin_43644245/article/details/120255137

https://blog.csdn.net/weixin_43644245/article/details/122017023

https://xilinx.eetrend.com/content/2019/100043772.html
```
在各类SOC上，CRTC+Endode+Connector一般是集成在一个外设模块挂在系统总线上。
以ARM为例，CRTC/Endoder等需要配置的外设模块，配置接口挂在APB总线，数据接口直接在AHB总线上，实现和Framebuffer的高速通信。
```

**2 MIPI DSI**

https://blog.csdn.net/zhoutaopower/article/details/123648751

https://blog.csdn.net/carolven/article/details/119011502

https://blog.csdn.net/caihaitao2000/article/details/80224976
```
显示串行接口标准定义了主处理器和外围设备之间的协议，是遵守MIPI联盟移动设备接口的标准。
DSI标准建立在现有的DPI(显示像素接口)和DBI(显示总线接口)标准上，采用MIPI联盟标准中定义的像素格式和命令集。
```

https://blog.csdn.net/coldrainbow/article/details/108715583
```
A

从整体流程上看到，DBI、DPI都是相应的控制器将数据发给LCD，
而DSI用的是LTDC产生的数据，LTDC通过内部DBI接口将数据传给SDIHOST，然后才开始下面四层DSI接口协议的处理封包。
所有说DSI是封装了DBI或DPI。与配置DSI时，一定会配置相应的LTDC。

B

LCD显示需要显示控制器，显示控制器是LCD越来越大，功能越来越多的发展结果。 LCD控制器同LCD驱动器是有着本质区别的。简单来说LCD控制器在嵌入式系统中的功能如同显卡在计算机中所起到的作用。
LCD控制器负责把显存（可能是内存中的指定域）中的LCD图形数据传输到LCD驱动器（LCD driver）上，并产生必须的LCD控制信号，从而控制和完成图形的显示，翻转，叠加，缩放等一系列复杂的图形显示功能。
LCD驱动器则只负责把CPU发送的图像数据在LCD显示出来，不会对图像做任何的处理。
LCD控制器可以兼容各种各样的CPU接口以及各种各样的LCD模块的接口，硬件完成复杂图像显示功能（缩放，翻转，叠加，动态等等）
```

**3 primary plane**

https://en.wikipedia.org/wiki/Direct_Rendering_Manager
```
The plane that holds the framebuffer is called the primary plane, and each CRTC must have one associated
```

https://doc.embedfire.com/linux/rk356x/linux_base/zh/latest/linux_app/drm/drm.html
```
通常驱动会把framebuffer绑定到 DRM_PLANE_TYPE_PRIMARY 上

```

https://blog.csdn.net/hexiaolong2009/article/details/84934294
https://github.com/simplewithliu/MyJZOfferSln/blob/master/Note/docs/brezillon-drm-kms.pdf
```
planes的概念
```

https://blog.csdn.net/Damon_X/article/details/111831210
```
文中的参考文档资料
```

https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841850/Video+Mixer

https://forums.raspberrypi.com/viewtopic.php?t=333320



### Jan 08 2023

**1 FIFO的读写**

https://tjpuzhanghui.github.io/2020/07/11/SPI驱动分析之SPI Protocol/



### Jan 10 2023

**1 Android soong build系统介绍**

https://www.jianshu.com/p/80013a768a45

**2 Android进阶解密**

https://wzhengo.github.io/15789733843338.html



### Feb 25 2023

**1 lock free**

https://stackoverflow.com/questions/14011849/what-is-lock-free-multithreaded-programming
https://doc.yonyoucloud.com/doc/wiki/project/java-concurrent/non-blocking-algorithms.html
```
lock free 像乐观锁，可以降低延迟
```


### Mar 01 2023

**1 芯片手册**

https://zhuanlan.zhihu.com/p/608306619


**2 模拟/数字信号本质**

https://www.zhihu.com/question/29244850/answer/107289428

https://www.zhihu.com/question/40421992





### Mar 12 2023 

**1 KGDB与JTAG的对比**

https://www.embedded.com/debugging-the-linux-kernel-with-jtag/

https://github.com/simplewithliu/MyJZOfferSln/blob/master/Note/docs/ELC19_Serial_kdb_kgdb.pdf

https://zhuanlan.zhihu.com/p/562727190

https://www.zhihu.com/question/21199781/answer/51376477




### Mar 23 2023 

**1 可重入函数**

https://www.zhihu.com/question/21526405/answer/56823146
```
异步可重入函数与线程安全函数等价吗？ - Acjx的回答 - 知乎
```


**2 汇编的意义**

https://www.zhihu.com/question/26834043/answer/40514515
```
写操作系统只能用汇编和 C 语言吗？ - Kevin嘉宏的回答 - 知乎 
```
https://www.zhihu.com/question/446836487

https://www.zhihu.com/question/315031511




### Apr 07 2023


**1 聊聊内存模型与内存序**

https://www.ccppcoding.com/archives/221


**2 你所不知道的 C 語言：記憶體管理、對齊及硬體特性**

https://hackmd.io/@sysprog/c-memory

**3 为什么SSE需要16字节对齐,64位机器一次也就存取8字节，只要8字节对齐不就能保证完美的存取了吗？**

https://www.zhihu.com/question/323890604

**4 为什么没有普及128位操纵系统的计算机?**

https://www.zhihu.com/question/320332089/answer/1466111036


### Apr 16 2023

**1 USB HUB是否占用USB寻址地址**

https://www.zhihu.com/question/504150597/answer/2263109886
```
分线器是不是可以让电脑拥有更多的USB插口？ - 萧骁的回答 - 知乎
```


### Apr 29 2023

**1 关于全局变量线程间的可见性问题**

https://stackoverflow.com/questions/859690/do-i-need-a-lock-when-only-a-single-thread-writes-to-a-shared-variable

https://www.zhihu.com/question/31325454/answer/51503609
```
评论区：
不加锁的话就没有同步点，这样的话一个线程写入内存能不能立刻让另一个线程读到这个事情本身从逻辑上说是没什么意义的，因为你没法预知2个线程的逻辑执行顺序，在逻辑上也不会要求写线程写入后读线程一定要立刻读到新的值，因为cpu有cache一致性协议，读线程总能在有限步后读到新的内存值，这种情况下不加锁应该是没问题的
```
https://www.zhihu.com/question/31325454/answer/52085494

https://www.zhihu.com/question/31325454/answer/51920170
```
评论区：
这个也要看变量的大小，以及读者如何读取变量。对于 cache line 大小的变量，就是刘然回答的情况3。如果是多个 cache line ，而且写者是 in place 修改，的确是会有问题。这时候可以使用以RCU为代表的 multi version 的更新变量的方法，保证读者读到的旧值也是完整和一致的。或者上锁吧。
```


### May 03 2023

**1 用exec函数执行新程序**

https://blog.csdn.net/str999_cn/article/details/78693438
```
从以上结果看，执行新程序的进程保持了原来进程的进程ID、父进程ID、实际用户ID和实际组ID。同时，调用新的可执行程序后，原有的子进程的映像被替代，不再被执行。
```

**2 Linux博文，内容来源基本是ULK**

https://www.halolinux.us/kernel-reference/


**3 gcc与g++编译器**

https://www.zhihu.com/question/20940822

https://zhuanlan.zhihu.com/p/341177816

https://stackoverflow.com/questions/45912291/how-does-gcc-decide-which-libraries-to-implicitly-include


**4 Bionic 简介**

https://blog.csdn.net/weixin_34204057/article/details/91999401

**5 Why do you have to link the math library in C?**

https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c

https://stackoverflow.com/questions/40198922/why-could-c-include-stdio-h-and-invoke-printf-method-which-is-cplatformubu

https://stackoverflow.com/questions/45912291/how-does-gcc-decide-which-libraries-to-implicitly-include

https://jdhao.github.io/2020/12/10/gcc_library_link_issue/




### May 20 2023

**1 并发编程示例之原子操作**

https://hackmd.io/@sysprog/concurrency-atomics

http://www.gpfeng.com/?p=451

https://www.brainkart.com/article/Operating-System---Provided-Atomics_9518/

https://randu.org/tutorials/threads/

https://www.parallellabs.com/2011/04/09/pthread-mutex-lock-and-thread-safety/


### May 21 2023

**1 MarkDown 插入数学公式**

https://juejin.cn/post/6844903554575155207


**2 MIT 6.828 实现操作系统（MIT 6.S081）**

https://www.zhihu.com/column/c_1273723917820215296


### June 04 2023

**1 神奇，C代码竟然能当成shell脚本一样“直接”执行**

https://zhuanlan.zhihu.com/p/143231248


**2 关闭kaslr**

https://zhuanlan.zhihu.com/p/581990743


### June 12 2023

**1 C语言中使用struct的位置本身就可以作为前向声明**

https://stackoverflow.com/questions/9999512/forward-declaration-of-a-struct-in-c
```
Basically, you never need to forward declare struct b on its own, 

because it always declares the partial type on the line itself when you use it to perform a pure declaration, so this is redundant code.

The only benefit of this type of forward declaration is it can be used with a typedef. 

In C++, you don't need the typedef because struct and typedefs are in the same identifier namespace, 

so therefore struct b becomes useful because it now declares b, so you will see it in C++.

也可以参考：(https://en.cppreference.com/w/c)

```

**2 DMA知识点补充内容**

https://gaoyichao.com/Xiaotu/?book=stm32&title=直接内存访问DMA

https://learn.lianglianglee.com/专栏/深入浅出计算机组成原理/48  DMA：为什么Kafka这么快？.md

https://zhuanlan.zhihu.com/p/618143764

https://www.huangrongzhen.ink/?p=381


### July 19 2023

**1 sysfs的分析**

https://blog.csdn.net/zdy0_2004/article/details/51712140

**2 Git常用操作**

https://zhuanlan.zhihu.com/p/534492797
```
盘点Linux内核下Git基本原理及各种骚操作
```

**3 Android 的 so 文件加载机制**

https://www.ucloud.cn/yun/2678.html

https://stackoverflow.com/questions/37246792/forcing-cpu-abi-to-armeabi-v7a-on-android

### Aug 13 2023

**1 LCD知识点总结**

http://www.xhhtech.com.cn/9505/全球显示驱动芯片ic厂商一览，华为海思入局

https://blog.csdn.net/qq_45475007/article/details/125370696

https://juejin.cn/post/7135631218787221541
```
结合文档：
https://github.com/simplewithliu/MyJZOfferSln/blob/master/Note/docs/an2790-tft-lcd-interfacing-with-the-highdensity-stm32f10xxx-fsmc-stmicroelectronics.pdf
```


https://blog.csdn.net/qq_695538007/article/details/9318705
```
了解LCD模组中的驱动IC与控制IC，实际上有时候并不明确区分

结合文档：TFT-LCD时序控制器（T-CON）的研究

参考：(https://zhuanlan.zhihu.com/p/430134493)
```

https://www.cnblogs.com/juwan/p/13069102.html


**2 傅里叶变换**

https://iot-book.github.io/3_傅里叶分析/S4_离散傅里叶分析/

https://www.toutiao.com/article/6704447250900189703/

https://www.zhihu.com/question/484749484
```
为什么持续时间短的信号，频谱较宽？
```

