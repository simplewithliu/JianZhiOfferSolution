## BSP与硬件层的知识

### 1 如何理解BSP

**BSP基本概念**
```
讲到定制 ARM 就涉及到 BSP 的概念和 ARM 构架的特点，其实定制 ARM 嵌入式应用一点儿都不简单。

ARM产品在应用层与硬件之间有一层隔离，成为 BSP(板级支持包)，与 X86 构架里的 BIOS 概念类似，BSP 就是设计开发 ARM 产品的要点。

X86 体系里，BIOS 是支持芯片组（如 945GM)，只要是用同一套芯片组的主板，BIOS 基本上是通用的。

但是ARM产品的BSP是支持底层硬件的，不同的CPU需要不同的BSP，相同的CPU不同的外围芯片也是不同的BSP。

因此客户提出需求的一套方案，往往要针对硬件编制客制化的BSP，我的一些客户还要求加入数据保护功能，需要改动的就更多。

除此之外，操作系统如 WinCE 的 BUG 也要考虑，必要时我们需要打上补丁。
```


http://bbs.eetop.cn/thread-12942-1-1.html
```
bsp可以理解成就是最简单的驱动代码，它属于OS或Firmware的一部分，

在PC平台最小的BSP需完成的任务上就是初始化芯片组上中断控制器、内存控制器、PCI控制器与串口（作为调试接口，如果你没钱买那些昂贵的硬件仿真器），

基本上有这些你就可以对系统板进行调试了，比如DEBUG各种设备驱动：VGA、USB、IDE、MAC、AC97等。

在OS上的driver一般都是可动态加载的，当然嵌入OS里头直接编进去也就行了，对于一个最小的可运行OS核心来说，BSP是必不可少的，但driver不是。
```

https://stackoverflow.com/questions/40509422/embedded-board-support-package

https://stackoverflow.com/questions/21501943/what-is-the-difference-between-physical-device-driver-and-logical-device-driver

https://snappyjack.github.io/articles/2020-01/Windows核心编程入门笔记
```
物理驱动，通常由硬件厂商提供。因为物理驱动要很清楚硬件的结构，要能够准确无误的操作硬件，这不是一般人能够随便写的。

没有硬件的结构，你是无法写物理驱动的。然而我们通常说的驱动开发，基本上是虚拟驱动级别的开发，也就是内核级别的驱动开发，而物理驱动开发，算是硬件级别的开发了。

物理驱动基本上是一系列的电平时序，完成各个部件的操作。

```


https://www.zhihu.com/question/326205733
```

单片机芯片时序图究竟怎么看？

```

**Linux BSP层实现**

https://www.zhihu.com/question/21381796

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch


* 内存管理e820
	
	https://blog.csdn.net/RichardYSteven/article/details/72566891

	https://richardweiyang-2.gitbook.io/kernel-exploring/00-memory_a_bottom_up_view


**UMA统一内存访问架构**
```

可以理解大多数手机SOC都做成了UMA架构，而PC端目前并没有完全流行。

```
https://www.zhihu.com/question/430936274

https://www.zhihu.com/question/430135674

https://www.zhihu.com/question/505504333

https://www.eet-china.com/news/202108190817.html

https://www.eet-china.com/news/202109080900.html

https://zhuanlan.zhihu.com/p/22197994


### 2 CPU相关概念理解

**CPU指令与芯片组**

https://zhuanlan.zhihu.com/p/19893066

http://itfreetraining.com/ap/1b40/
```

A chipset is a collection of items that function as a unit. 

The main component of the chipset are the North and South Bridges and thus the chipset is named after these chips.

A chipset will only work with certain other components. 

For example, a particular chipset will only support certain CPUs and memory types. 

The chipset is like the spinal cord that connects all the other components together, but just like a fruit salad, you have limited choices of what you can use.

(https://quqi.com/516996/7532)

```

**CPU空闲时的状态**

https://zhuanlan.zhihu.com/p/50367649

https://linux.cn/article-9303-1.html

https://kernel.meizu.com/cpuidle.html


**单片机main函数**

https://zhuanlan.zhihu.com/p/459189574

https://electronics.stackexchange.com/questions/30830/what-happens-when-an-embedded-program-finishes
```

为什么指令地址 + 2，可参考：

https://www.macsen.xyz/2021/12/24/第四章-指令系统第二节/

```

https://linux.cn/article-9095-1.html


### 3 中断与调度



**中断处理程序上下文**

https://stackoverflow.com/questions/21848340/interrupts-execution-context
```

发生中断时，CPU会切换上下文执行中断处理程序，而中断处理程序并不属于某个线程，只是内核中的某个方法，执行于中断上下文中。

发生上下文切换时，首先会保存当前执行的上下文任务，由current标记，等待中断返回时，会出现一个调度点，此时判断current是否需要调度。

```



**中断抢占问题**

https://cs.stackexchange.com/questions/29846/can-an-interrupt-handler-be-preempted
```
中断应该是可以被抢占的，但需要保证抢占不会造成错误，这取决于具体的架构实现。

```

https://stackoverflow.com/questions/11779397/what-happens-to-preempted-interrupt-handler

https://docs.microsoft.com/zh-cn/windows-hardware/drivers/kernel/always-preemptible-and-always-interruptible

http://www.wowotech.net/irq_subsystem/soft-irq.html
```

softirq同时在Processor A和B上运行的时候，中断分发给processor A

processor A上的handler仍然会raise softirq，但是并不会调度该softirq。

也就是说，softirq在一个CPU上是串行执行的。

为了性能，同一类型的softirq有可能在不同的CPU上并发执行，softirq的回调函数的时候要考虑重入，考虑并发，要引入同步机制。

为何tasklet性能不如softirq呢？

如果一个tasklet在processor A上被调度执行，那么它永远也不会同时在processor B上执行

也就是说，tasklet是串行执行的（注：不同的tasklet还是会并发的），不需要考虑重入的问题。

```


**内核调度**

https://zhuanlan.zhihu.com/p/163728119

https://www.cnblogs.com/jack204/archive/2012/03/26/2417678.html


**中断上下文禁止调度**

https://www.cnblogs.com/wuchanming/p/4756756.html

http://bbs.chinaunix.net/thread-1618430-1-1.html

http://www.wowotech.net/process_management/schedule-in-interrupt.html



### 4 总线


**基本概念**

https://www.cnblogs.com/Ligo-Z/p/13228056.html

https://cs.nju.edu.cn/swang/CompArchOrg_13F/slides/lecture27.pdf

https://enszhou.github.io/cod/courseware/update/Ch7.pdf

https://www.zhihu.com/question/22471643
```
总线的位数并不绝对与处理器架构强相关

如果说CPU中跟CPU核直接相连的地址线，那么答案是不一定，32位CPU可以有PAE，用的总线地址线位数多于32位。

64位CPU现在市面上的几乎没有64位的，都是4x位。

如果说系统总线，那就更不是了，x86的QPI总线，不区分地址和数据的，都是串行的。
```

https://quqi.com/516996/7591

https://www.zhihu.com/question/29383757
```

为什么要选片，怎样选片

```

https://vga.zol.com.cn/646/6461752_all.html
```

细数主板上曾出现过的插槽

```

**总线的串行和并行**

https://www.zhihu.com/question/27815296
```
A 

串行接口为啥比并行接口快？是因为串口的特性和应用场景，决定了它更加适合采用一些提高单根信道速率的设计方法，这些方法用在并口上并不合适。

B

1 金属信号线之间的串扰非常厉害，噪声难以避免（来自于外界的干扰和自身对外界的干扰即EMI）。

2 多比特传输的信号对齐变得异常艰难。

3 由于走线数量的增加，对系统工程师非常不友好，加之芯片pin脚的数量本就十分宝贵，版级布线的难度急剧增加。

前两个原因导致了严重的信号完整性问题，传输效率变得极其低下，从而又导致了数据完整性的问题。

就在这时，差分电路的优点体现出来了。

C

其实对于芯片而言（从芯片设计角度出发），是喜欢并口而不喜欢串口的。

因为芯片的电路更适合并行处理数据而非串行。

串行提速要提升工作频率，频率提升的天花板又比晶体管规模提升的天花板要低太多。


(https://m.mydrivers.com/newsview.aspx?id=30361)

(http://tech.sina.com.cn/h/2005-06-24/1157645181.shtml)

```

https://www.jianshu.com/p/65281e71753f
```

在具体传输时，按顺序传送一个数据的所有二进制位的脉冲信号，每次一位

被传送的数据在发送部件中必须进行并行数据到串行数据的转换，这个过程称为拆卸

而在接收部件中则需要将串行数据转换成并行数据，这个过程称为装配。

```

https://tldp.org/HOWTO/Serial-HOWTO-4.html
```

The serial port is much more than just a connector. 

It converts the data from parallel to serial and changes the electrical representation of the data. 

Inside the computer, data bits flow in parallel (using many wires at the same time). 

Serial flow is a stream of bits over a single wire (such as on the transmit or receive pin of the serial connector). 

For the serial port to create such a flow, it must convert data from parallel (inside the computer) to serial on the transmit pin (and conversely).

```

https://learn.sparkfun.com/tutorials/i2c/all
```

10-bit Addresses

In a 10-bit addressing system, two frames are required to transmit the peripheral address. 

The first frame will consist of the code b11110xyz 

where 'x' is the MSB of the peripheral address, y is bit 8 of the peripheral address, and z is the read/write bit as described above. 

The first frame's ACK bit will be asserted by all peripherals which match the first two bits of the address.

串行总线会在一根线上传输数据、地址等，所以必须进行正确的转换。
(https://quqi.com/516996/7592)

```

**总线地址与IOMMU**

https://blog.csdn.net/zyboy2000/article/details/52003160

https://www.owalle.com/2021/11/01/iommu-code/

https://blog.csdn.net/lg2lh/article/details/8041029
```

理解总线地址可以站在设备的视角来看

CPU视角上是物理地址，设备视角就是总线地址

```

https://juejin.cn/post/6844904112652288014

http://www.lujun.org.cn/?p=775
```

上述 2 个网址的关键点

1 某个模块分配的地址比实际用到的要大出很多，

原因是SOC芯片设计时为了简化地址译码电路。

2 另外unic提供了lookat工具可以直接访问spi的从设备PMIC的寄存器地址，实际上是lookat驱动程序内作了转换，

最终还是通过spi接口来访问的。

3 关于unic的AlwaysOn（aon）的spi从设备PMIC的编址设计，其设置在了cpu本身不用的寻址空间内，也就是spi主控的保留空间。

个人的理解是，虽然不能直接访问，但是可以作为单独的地址，与其他设备地址容易区分开，反映了一种层次的关系，也方便开发与调试，

也是一种很不错的设计。

```


**IO接口设备电路**

https://books.google.com.hk/books?id=hyVW6BNNtwQC
```

9.1.2 IO系统的组成

简要介绍了IO接口的一些功能

```

https://blog.csdn.net/weixin_43715360/article/details/120636553




### 5 DMA

**认识DMA**

https://hackaday.com/2021/03/31/direct-memory-access-data-transfer-without-micro-management/

**first-party DMA 总线主控**

https://stackoverflow.com/questions/57009233/what-are-the-most-common-busmaster-operations-and-how-are-they-better-than-regu

https://stackoverflow.com/questions/48659470/why-driver-need-to-map-dma-buffers-when-dma-engine-is-in-device

https://www.rigacci.org/docs/biblio/online/ide_modes/modes_DMA.htm

https://scientific-solutions.com/products/faq/ssi_faq_dma_busmastering.shtml

https://www.sciencedirect.com/topics/engineering/bus-master


**DMA API for first-party DMA**

https://stackoverflow.com/questions/66203274/what-instruction-does-linux-use-to-direct-intel-cpu-to-setup-a-dma-transfer

https://stackoverflow.com/questions/64717372/what-kernel-flags-and-pcie-setting-needed-for-bus-mastering

https://stackoverflow.com/questions/8273568/dma-transfer-to-a-slave-pci-device-in-linux

http://www.tweak3d.net/articles/howbusmaster/3.shtml

https://www.esp32.com/viewtopic.php?t=20245
```

This is because the ESP32 has it inside each peripheral, 

in the same way as bus mastering on PCI/PCIE does not need a separate DMA controller.

```

https://electronics.stackexchange.com/questions/448349/bus-mastering-vs-bus-arbitration


**PCI 总线主控**

http://bbs3.driverdevelop.com/read.php?tid=47779

https://stackoverflow.com/questions/27470885/how-does-dma-work-with-pci-express-devices

https://superuser.com/questions/988136/do-modern-motherboards-allow-a-pci-e-device-to-access-ram-without-involving-the

https://www.ni.com/knowledgebase/8C011426DA96F46D86256F01003E6144

https://books.google.com.hk/books?id=xS2ISRHJqVIC
```

搜索PCI DMA，有简单介绍

```
https://books.google.com.hk/books?id=Ki7zs-Ex2d0C
```

6.B.3. Bus Master

简要介绍总线主控DMA的优势

```

**PCI设备能否使用系统DMA**
```

这里的结论是原则是可以的，但是不推荐或者取决于硬件芯片架构的具体设计

```


https://community.osr.com/discussion/132833

https://d1.amobbs.com/bbs_upload782111/files_39/ourdev_634262EB839K.pdf
```

讨论了一种从模式传输，使用PCI主机主板的DMA控制器
(https://quqi.com/516996/7596)

```

https://stackoverflow.com/questions/56955937/linux-pcie-dma-driver
```

@0andriy Comment评论可以参考

```

**有讨论认为系统central DMA有必要**

https://www.embedded.com/built-in-dma-engines-unleash-power-of-pci-express-switches/

https://patents.google.com/patent/EP0628914A1/en
```
Most devices which attach directly to the PCI bus are generally high performance 32-bit bus master devices which have their own built-in DMA control logic. 

Such bus master devices need not rely on a system-provided DMA controller, 

thereby permitting the device to initiate a DMA transfer by itself instead of relying on the system DMA controller to initiate data transfers. 

A DMA slave device is typically lower performance, less expensive and requires the assistance of a system DMA controller to perform a DMA transfer.

(https://quqi.com/516996/7599 , https://quqi.com/516996/7597)

```

https://stackoverflow.com/questions/28068525/explaination-of-arm-especifically-mobile-peripherals-addressing-and-bus-archit
```

 One process that I'm interested in right now is the work with a dma controller. 
 
 I've wrote an new question about it so it won't be just a little comment here snice it might help a lot of other people to understand important processes.

```

https://books.google.com.hk/books?id=QFe5BQAAQBAJ
```

2.2 Direct Memory Access (Page 23)

简要对比了first-party与third-party DMA

```

**DMA技术的拓展讨论**

https://cwshu.github.io/arm_virt_notes/notes/dma/DMA.html

https://developer.nvidia.com/zh-cn/blog/gpudirect-storage/

https://docs.nvidia.com/cuda/gpudirect-rdma/index.html

https://lwn.net/Articles/767281/


### 6 中断控制器总结

**中断概述与硬件组成**

https://chasinglulu.github.io/2019/07/07/中断「interrupt」/

https://blog.csdn.net/zhoutaopower/article/details/90613988

https://blog.csdn.net/mmphhh/article/details/117351998

https://zhuanlan.zhihu.com/p/399239928


**了解gpio中断级联**


https://blog.csdn.net/weixin_43898067/article/details/117632295

https://www.cnblogs.com/muzihuan/p/5223839.html

https://blog.csdn.net/thisway_diy/article/details/116493986

https://blog.51cto.com/u_15069485/4324959

https://www.zynqnotes.com/pl-ps-interrupt-2





### 7 实时操作系统

**FreeRTOS**

https://www.zhihu.com/question/402744770

https://stackoverflow.com/questions/29293518/interfacing-peripheral-drivers-with-rtos



***


## Linux 知识

### 1 Linux内核缓存

**Page Cache**

https://unix.stackexchange.com/questions/484901/sum-of-cached-memory-and-shared-memory-exceed-total-memory

https://www.evanjones.ca/linux-write-caching.html

https://blog.csdn.net/sinat_22338935/article/details/114320664

https://lonesysadmin.net/2013/12/22/better-linux-disk-caching-performance-vm-dirty_ratio/
```

Those pauses are a result of the cache deciding that there’s too much data to be written asynchronously 
(as a non-blocking background operation, letting the application process continue), 

and switches to writing synchronously (blocking and making the process wait until the I/O is committed to disk). 

Of course, a filesystem also has to preserve write order, so when it starts writing synchronously it first has to destage the cache. 

Hence the long pause.

(https://patents.justia.com/patent/11068414)


```

https://stackoverflow.com/questions/6345020/what-is-the-difference-between-buffer-and-cache-memory-in-linux
```

What is the difference between buffer and cache memory in Linux?

```

https://tldp.org/LDP/tlk/mm/memory.html


**swap与页交换**

https://www.beikejiedeliulangmao.top/linux/cache-and-swap/

https://www.cnblogs.com/zengkefu/p/5647046.html

https://stackoverflow.com/questions/68834671/why-do-we-need-to-write-dirty-pages-back-to-disk-to-evict-it

https://www.kernel.org/doc/gorman/html/understand/understand014.html

https://lwn.net/Articles/690079/

https://chrisdown.name/2018/01/02/in-defence-of-swap.html

```

In defence of swap: common misconceptions

翻译：(https://farseerfc.me/zhs/in-defence-of-swap.html)

```
* vmstat swap

	https://www.0xffffff.org/2019/07/17/42-linux-memory-monitor/
	
	http://www.myjishu.com/?p=80
	


* kswapd0与IOWait间的联系

	https://access.redhat.com/solutions/271153

	https://community-archive.progress.com/forums/00018/25396.html

	https://discuss.aerospike.com/t/faq-why-is-cpu-being-used-by-kworker-and-kswapd0-causing-latencies/6465


**pdflush**

https://blog.csdn.net/weixin_33737774/article/details/90621950

https://www.kernel.org/doc/Documentation/sysctl/vm.txt
```
- dirty_background_ratio
- dirty_bytes
- dirty_expire_centisecs
- dirty_ratio
- dirtytime_expire_seconds
- dirty_writeback_centisecs
```

https://docs.gluster.org/en/v3/Administrator%20Guide/Linux%20Kernel%20Tuning/

https://documentation.suse.com/sles/15-SP1/html/SLES-all/cha-tuning-memory.html
```

To understand and tune the memory management behavior of the kernel

```

https://stackoverflow.com/questions/27900221/difference-between-vm-dirty-ratio-and-vm-dirty-background-ratio
```

Difference between vm.dirty_ratio and vm.dirty_background_ratio

```


**元数据同步写的问题**

```

《操作系统概念》 11.7.1 一致性检查 章节中提到避免数据不一致采用元数据同步写

```
> In contrast, the loss of a directory entry on an indexed allocation system can be disastrous, 
> because the data blocks have no knowledge of one another. 
> For this reason, some UNIX file systems cache directory entries for reads, 
> but any write that results in space allocation, or other metadata changes, is done synchronously, 
> before the corresponding data blocks are written. 

https://www.complang.tuwien.ac.at/anton/sync-metadata-updates.html

https://ir.nctu.edu.tw/bitstream/11536/1025/1/A1996VH07500005.pdf
```

上述 2 个网址提出，可以使用异步写元数据提高文件的IO性能

(https://quqi.com/516996/7593)

```





### 2  Linux主线内核代码知识

https://www.zhihu.com/question/423732603

https://www.zhihu.com/question/34027620

https://zhuanlan.zhihu.com/p/66998243

https://www.zhihu.com/question/305421132

https://www.zhihu.com/question/36367269

https://www.zhihu.com/question/482672160

https://www.zhihu.com/question/328645344/answer/1057508024
```
从这里我们看到什么信息呢？

Linux内核开发是一个大熔炉，它包含了大部分顶尖IT公司的开发工作，而且只是这些工作的对外暴露。

我们在Linux内核中做一些简单的修改，背后是我们在自己的领域长期的耕耘，那点修改只是冰山一角，用于保证最终用户可以接纳我们不得不做出的一些接口变化，保证其他团体的进展和我们可以配合。

（这种开发模式，可以参考：https://gitee.com/Kenneth-Lee-2012/know_modern_server_from_kunpeng920_pub/blob/pub/source/认识鲲鹏920：一个服务器SoC/软件构架.rst）

我们为什么要合入Linux主线，而不是自己拉一个分支呢？因为只有Linux主线才能做到“公平公正透明”，我们的基本利益是可以得到保证的。

所有的这些补丁都在给它背书，这些公司承认它的公正，大家觉得这样加代码进来，大家的努力是可以被保证的。

尽管做不到绝对公平，Linus Torvards还天天在那里损人，但大家的身体是诚实的（从这里就可以看出Linus Torvards有多牛逼了，什么是无冕之王，不言之教啊），代码明明都在那里，你都可以拿回家，但大家还是屁颠屁颠要合到Linus手上的那个分支上，要把代码送给他。

因为你不合到他那里，你就保证不了你可以使用其他合作者的特性。
```

http://www.ruanyifeng.com/blog/2010/02/open_android_or_not.html
```
这跟前段时间 Linus 指责 Red Hat 把 Nouveau 并入主线的积极性不高一样，最后 Red Hat 也是把 Nouveau 并入 2.6.33 的主线了么......

没有并入主线对于社区和厂商都不利，社区得不到驱动程序的扩展，厂商也得不到内核新特性的改善。

但是并不是所有模块在一开始的时候都是并入主线的，总是要发展到某个相对成熟的阶段或者解决了潜在的授权问题后才并入的。

总之并入主线对双方都有利，这个问题反应这次 Google 的并入主线积极性不高（不代表不开源），社区打它屁屁了......
```

**如何参与到 Linux 社区中来**

https://opensourceway.community/posts/contribute_to_community/how_to_participate_in_the_linux_community/

http://www.static.linuxfound.org/sites/lfcorp/files/How-Participate-Linux-Community_0.pdf

https://quqi.com/516996/7514


**Linux标准协议**

https://unix.stackexchange.com/questions/467010/is-linux-considered-xsi-compliant-or-largely-so

https://www.cnblogs.com/wangkeqin/p/12382639.html



### 3 Linux系统问题分析与调试


**系统分析和微调指南**

https://documentation.suse.com/zh-cn/sled/15-SP2/single-html/SLED-tuning/index.html


**堆栈打印**

https://stackoverflow.com/questions/3899870/print-call-stack-in-c-or-c

https://stackoverflow.com/questions/5945775/how-to-get-more-detailed-backtrace

https://stackoverflow.com/questions/18679567/alternative-to-backtrace-on-linux-that-can-find-symbols-for-static-functions

https://www.cnblogs.com/clblacksmith/p/8378434.html

* 符号表概念
	
	https://xuanxuanblingbling.github.io/ctf/tools/2019/09/06/symbol/
	
	https://www.cnblogs.com/LiuYanYGZ/p/5550544.html

	https://os.51cto.com/article/652687.html

* 理解 -rdynamic

	https://stackoverflow.com/questions/36692315/what-exactly-does-rdynamic-do-and-when-exactly-is-it-needed
	
	https://stackoverflow.com/questions/2356168/force-gcc-to-notify-about-undefined-references-in-shared-libraries
	
	https://stackoverflow.com/questions/31371867/what-is-the-g-flag-that-permits-undefined-references-in-shared-libraries


**GDB初步**

https://www.cnblogs.com/dongc/p/9690754.html

https://blog.csdn.net/blade2001/article/details/46563805

* Android gdb
  
	https://blog.csdn.net/cigogo/article/details/82655837

	https://blog.csdn.net/tkwxty/article/details/104027151






### 4 Linux系统调用知识点

http://nicephil.blinkenshell.org/my_book/ch08s03.html

http://blog.chinaunix.net/uid-28362602-id-3424404.html

https://zhuanlan.zhihu.com/p/55264897

https://gityuan.com/2016/05/21/syscall


**流程分析**

https://zhuanlan.zhihu.com/p/361328552

https://zhuanlan.zhihu.com/p/55214097


**系统调用定义宏 SYSCALL_DEFINEx 的分析**

https://blog.csdn.net/weixin_42992444/article/details/108571515




### 5 Linux编译问题

**初识Makefile**

https://segmentfault.com/a/1190000016176722

https://jianshu.com/p/2536321c4e53

https://blog.csdn.net/gzxb1995/article/details/102615262



**gcc编译选项**

* gcc哪些编译情况下需要用-l指定链接库路径
  
	https://www.zhihu.com/question/27416153

* gcc -mcpu option
  
	https://community.arm.com/arm-community-blogs/b/tools-software-ides-blog/posts/compiler-flags-across-architectures-march-mtune-and-mcpu

	https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/wiki/Understanding-GCC-mcpu-option



**recursive make 与 non recursive make**
```
两种组织大型项目的编译文件的方式，递归形式的Makefile还是通过类似include方式生成单一的Makefile

```

https://www.oreilly.com/library/view/managing-projects-with/0596006101/ch06.html

https://stackoverflow.com/questions/19307258/how-to-include-a-makefile-into-an-other-makefile

https://stackoverflow.com/questions/50949720/building-dependencies-by-a-recursive-call-to-make
```
It discusses how splitting your dependency graph into multiple makefiles is bad. However, in some cases recursion doesn't do that. 

Recursion can be a powerful tool

```

**驱动模块编译 make -C XXX M=XX**
```

在外部编译kernel模块的一种方式，首先通过-C进入到源代码树编译kernel源代码，然后返回到M变量指定目录中，也就是模块所在目录，使用Kbuild编译当前模块

```

https://segmentfault.com/a/1190000014562776

https://stackoverflow.com/questions/20301591/m-option-in-make-command-makefile


**Makefile文件与Kbuild文件**
```
Kbuild文件属于kernel build系统专有，所以首先会编译顶层的Makefile然后进入到kernel build，再次编译每个目录下的Kbuild文件

```

https://opensource.com/article/18/10/kbuild-and-kconfig
```
The top makefile includes the arch makefile, reads the .config file, descends into subdirectories, 

invokes make on each component's makefile with the help of routines defined in scripts/Makefile.*, 

builds up each intermediate object, and links all the intermediate objects into vmlinux. 

Kernel document Documentation/kbuild/makefiles.txt describes all aspects of these makefiles.
```

https://www.linuxjournal.com/content/kbuild-linux-kernel-build-system
```

Once you have your .config file, you are ready to compile your kernel and its modules. 

When you execute a compile target to compile the kernel or the modules, it first executes a binary that reads all the Kconfig files and .config:

$ scripts/kconfig/conf Kconfig

This binary updates (or creates) a C header file with the values you chose for all the configuration symbols. 

This file is include/generated/autoconf.h, and every gcc compile instruction includes it, so the symbols can be used in any source file in the kernel.

The file is composed of thousands of #define macros that describe the state for each symbol.
```

https://www.makelinux.net/ldd3/chp-2-sect-4.shtml


### 6 内存问题

**关于动态加载的理解**

```

如何理解《操作系统概念》中关于动态加载与动态链接的描述：

Unlike dynamic loading, dynamic linking and shared libraries generally require help from the operating system. 

If the processes in memory are protected from one another, then the operating system is the only entity that can check to see 

whether the needed routine is in another process’s memory space 

or that can allow multiple processes to access the same memory addresses.

```

https://stackoverflow.com/questions/10052464/difference-between-dynamic-loading-and-dynamic-linking
```

Therefore, for dynamic linking, there is only one copy of the library code in the memory, which may be not true for dynamic loading. 

That's why dynamic linking needs OS support to check the memory of other processes. 

This feature is very important for language subroutine libraries, which are shared by many programs.

```

https://stackoverflow.com/questions/42426986/does-dlopen-create-multiple-library-instances

https://stackoverflow.com/questions/1745975/load-multiple-copies-of-a-shared-library




**逻辑地址和物理地址以及寻址空间概念**

https://www.zhihu.com/question/382484336

https://liaoph.com/motherboard-and-memory-map/
```

当内存地址被用于为显卡和 PCI 设备保留时，会有更大的空隙。

这就是为什么 32 位的操作系统无法使用 4G 的 RAM。

Linux 中 /proc/iomem 文件列出了这些地址映射范围。

```

https://www.zhihu.com/question/265736936

https://groups.google.com/g/shlug/c/nixMYtbbdZ0
```

CPU 寄存器——>内存控制器——>内存

寄存器是32位的，那么就能寻4G的空间，这也是为什么32的机器上linux(段基址为0)进程空间是4G

但是，我们有看到32的机器上也有用超过4G的内存，并且注意到进程的地址空间没有加大，还是4G

我们知道进程空间映射成页，内核可以把高于4G的内存分页映射到4G的进程地址空间

所以内存控制器的总线宽度必大于32位才能访问超过4G的内存

```

https://www.zhihu.com/question/61974351/answer/205736146

https://www.zhihu.com/question/20536161/answer/1672310610

https://stackoverflow.com/questions/11472484/word-size-and-data-bus

https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available

https://www.zhihu.com/question/377628211/answer/1500681380
```

32位的CPU的意思就是指CPU的数据总线有32位，CPU与内存交换数据时，以及寄存器寄存时，每次的数据交流都是一次4字节，这是CPU字长的根本含义。

而对于CPU而言，指针地址无疑是极其重要的数据之一，不太可能存每次传递地址还要传输两次数据。

所以最大的32位字长就限制了虚拟地址的最大大小。

```

https://zhihu.com/question/309983509/answer/906105774

https://superuser.com/questions/1166698/how-is-the-word-size-often-same-as-pointer-size

https://devblogs.microsoft.com/oldnewthing/20040817-00/?p=38153

https://superuser.com/questions/1139912/does-a-x86-computer-use-the-pci-bus-and-pci-protocols-to-access-memory
```

Main memory access is not a form of general purpose I/O and does not use the Front Side Bus or any other type of general purpose I/O bus; 

it always uses a dedicated memory bus

```

https://blogs.sw.siemens.com/hyperlynx/2017/09/06/understanding-the-ddr-memory-bus/


https://www.zhihu.com/question/36397999/answer/67615103
```

关于内存地址和显存地址，现在的显存动不动就2G了，分配给显存的地址段是不是和8086已经不一样了？

```


**page fault与segmentation fault**

https://leetcode.com/discuss/interview-question/operating-system/125109

https://stackoverflow.com/questions/6950549/segmentation-fault-vs-page-fault
```

When you say "page fault", your description is only covering "valid" page faults. 

Both start with a page-fault hardware exception, and if the OS determines that the process didn't have that page mapped, 

then it's invalid and delivers a SIGSEGV. 

But if it is valid, the page-fault handler can queue up I/O (hard page fault) or do copy-on-write or whatever lazy memory allocation (soft page fault)

```

https://segmentfault.com/q/1010000000253786

https://stackoverflow.com/questions/38506726/can-a-process-read-write-at-any-address-from-its-virtual-memory

https://stackoverflow.com/questions/22981919/why-we-getting-segmentation-fault-instead-of-page-fault

***


### 7 Linux驱动模型

**设备树**

https://quqi.com/516996/7602
```

设备树入门教程

```

https://nu-ll.github.io/2019/10/13/设备树/

https://z.itpub.net/article/detail/1C40A5E8255891E7A26173B2C28E7D31
```

Linux引入设备树主要是为了精简特定于某型号硬件主板的代码

```

https://docs.zephyrproject.org/latest/build/dts/intro.html

http://www.wilson-blog.cn/post/2022/06/07/zephyr.dtree.html
```

上述 2 个网址，对于phandle有详细描述

```

https://opengrok.net/xref/linux-6.0/drivers/phy/samsung/phy-exynos5250-sata.c
```

针对设备树中使用phandle引用的理解，其多用于硬件上的关联性

即该硬件功能的实现需要另一个硬件参与，上述文件举例了在驱动中体现

一个platform_driver的实现关联了一个i2c_client

```

https://www.cnblogs.com/schips/p/linux_driver_dts_the_format_of_dtb.html

https://www.cnblogs.com/downey-blog/p/10486568.html
```

上述 2 个网址 device_node转换成platform_device

```

http://news.eeworld.com.cn/mp/rrgeek/a131415.jspx

https://www.cnblogs.com/pengdonglin137/p/5248114.html
```

基于tiny4412的Linux内核移植 -- 设备树的展开 

作者: 彭东林

```



**驱动模型概念**

https://www.analog.com/media/cn/analog-dialogue/volume-44/number-1/articles/free-and-open-source-software_cn.pdf 
```

针对特定处理器平台，操作系统 (OS) 处理硬件操作的细节。
利用内核 (OS) 内部硬件抽象层 (HAL) 和处理器专用外设驱动程序（例如 I2C 或 SPI 总线驱动程序），通常的设备驱动程序甚至也能独立于处理器平台。
这种方法允许一个设备驱动程序（例如触摸屏数字化仪 AD7879 的驱动程序）可以不加修改地用在任何运行 Linux 的处理器平台上，
Linux 内核之上运行任何图形用户界面 (GUI) 包和适当的应用程序。

(https://quqi.com/516996/7590)

```

https://www.zhihu.com/question/33414159

https://www.cnblogs.com/aaronLinux/p/6661987.html


**平台设备驱动**


https://blog.csdn.net/a568713197/article/details/89642396

https://doc.embedfire.com/linux/stm32mp1/driver/zh/latest/linux_driver/base_platform_driver.html

https://hughesxu.github.io/posts/Linux_device_and_driver_model/




**IO总线概念**

https://blog.csdn.net/zz2633105/article/details/118641075

https://fangkaipeng.com/?p=1439

https://quqi.com/516996/7600
```

ARM Cortex Core Microcontrollers Architecture

```

https://www.cnblogs.com/chengqi521/p/7126758.html
```

burst传输基本概念

```


**设备IO方式**

https://www.cnblogs.com/armlinux/archive/2010/11/26/2396888.html

https://os.51cto.com/article/599356.html
```

独立编址和统一编址，MMIO可以看作为统一编址

这里设备的地址实际上为物理地址，即CPU真正能访问的物理地址空间，一般取决于地址线位宽

```

https://houwanfei.github.io/2020/07/18/操作系统-10-输入输出/
```

内存映射I/O 优点和缺点

```

https://docs.oracle.com/cd/E19253-01/819-7057/hwovr-25/index.html


**伪文件系统**

https://zhuanlan.zhihu.com/p/205166823
```

proc_ops接口

```

https://www.reddit.com/r/linuxquestions/comments/2h0v34/how_does_dev_differ_from_procdevices_in_linux/

https://stackoverflow.com/questions/3245219/when-to-use-proc-and-when-dev

https://unix.stackexchange.com/questions/188886/what-is-in-dev-proc-and-sys
```

上述 3 个网址 对比 /dev 与 /proc

```


https://stackoverflow.com/questions/36119547/registering-linux-device-file-operations-vs-device-attribute

https://unix.stackexchange.com/questions/454863/when-to-use-dev-and-sys-for-userspace-kernel-communication

https://unix.stackexchange.com/questions/715801/what-populates-the-sys-and-dev-directories
```

上述 3 个网址 对比 /dev 与 /sys

```


https://unix.stackexchange.com/questions/249631/how-is-the-data-in-proc-gathered-and-how-reliable-is-it

https://unix.stackexchange.com/questions/504844/proc-in-kernel-modules

https://unix.stackexchange.com/questions/4884/what-is-the-difference-between-procfs-and-sysfs


```

上述 3 个网址 对比 /proc 与 /sys

```

* udev规则与devtmpfs

	https://stackoverflow.com/questions/65932709/how-are-device-nodes-created-in-embedded-linux-without-udev

	https://lfs.xry111.site/zh_CN/development/chapter09/udev.html
	```

	内核通过 devtmpfs 直接创建设备文件，任何希望注册设备节点的驱动程序都要通过 devtmpfs (经过驱动程序核心) 实现。
	
	当一个 devtmpfs 实例被挂载到 /dev 时，设备节点将被以固定的名称、访问权限和所有者首次创建。

	很快，内核会向 udevd 发送一个 uevent。根据 /etc/udev/rules.d，/usr/lib/udev/rules.d，以及 /run/udev/rules.d 目录中文件指定的规则，
	
	udevd 将为设备节点创建额外的符号链接，修改其访问权限，所有者，或属组，或者修改该对象的 udevd 数据库条目 (名称)。

	```

	https://blog.csdn.net/lickylin/article/details/101922106

	https://blog.csdn.net/zdy0_2004/article/details/51686283
	```

	上述 2 个网址主要讲解了devtmpfs

	```

	https://blog.csdn.net/u014674293/article/details/121627305

	https://github.com/leaveye/blogging/blob/master/content/writing-udev-rules.md
	```

	上述 2 个网址主要讲解 udev 的配置规则

	```

* udev 知识点精要

	https://unix.stackexchange.com/questions/161674/are-there-alternatives-to-using-udev

	https://www.binss.me/blog/sysfs-udev-and-Linux-Unified-Device-Model/
	```

	sysfs、udev和它们背后的Linux统一设备模型

	```

	https://github.com/microcai/gentoo-handbook/blob/master/fs.tex
	```

	由于udev启动的时候需要解析数千个rules文件，遍历数万个/sys文件，所以启动速度非常慢。大约需要数秒的事件才能完成udev的启动。
	
	而/dev如此重要，他必须是init启动的第一个程序。这就大大延迟了开机速度。

	所以新捣鼓了一个 devtmpfs 文件系统，结合了devfs和tmpfs的文件系统。这样udev的启动可以被延迟到需要的时候，udev就算不启动，也有devtmpfs提供的设备文件。
	
	udev启动后也只需要修改而不是重新创建，所以加快了系统的启动速度。udev在新版本中已经要求内核必须有devtmpfs支持了。所以编译内核的时候，千万别把devtmpfs选项去掉哦~。

	由于udev对开机过程来说是个非常重要的程序，所以现如今已经和systemd合并。udev是systemd的一部分了。

	```

* /dev 目录知识精要

	https://unix.stackexchange.com/a/715810
	```

	Linux操作系统在/dev目录中创建设备节点，早期/dev目录是挂载的磁盘文件系统，用户可以手动的通过mknod创建设备节点，或者通过启动脚本预先将已知的设备节点创建好。

	但是后来增加了热插拔设备的需求，这样静态的创建设备节点显然不适应热插拔的情况。

	为了动态的管理设备节点，Linux引入了udev和sysfs，通过udev来处理内核上报的各类热插拔等事件，同时将/dev挂载到tmpfs文件系统上，以提高设备节点的增删效率。

	但是udev同样存在开机启动的效率问题，内核又开发了devtmpfs文件系统挂载到/dev目录中，在内核中创建设备节点，udev只负责管理。

	```	

	https://unix.stackexchange.com/questions/454863/when-to-use-dev-and-sys-for-userspace-kernel-communication

	http://velep.com/archives/334.html

	https://unix.stackexchange.com/questions/18239/understanding-dev-and-its-subdirs-and-files

	https://unix.stackexchange.com/questions/280390/why-is-dev-a-subdirectory-of-the-root
	
	https://unix.stackexchange.com/questions/552483/understanding-dev-folder-in-linux-android


* ALSA的配置与udev (/dev/snd/*)

	http://wiki.dreamrunner.org/public_html/Embedded-System/FilesystemOverview.html
	```

	The “sysinit” line tells init to run the /etc/init.d/rcS script to set up the system.

	A simple etc/init.d/rcS file could assume file systems existed in the kernel and would simply mount the mount points as needed. 
	
	A more complicated one would test for the existence of file systems and if found, mount them; if not found, find ways to still get the system booted.

	The author has taken the etc/init.d/rcS and mdev.conf files from the V2.6.22.18-OMAP3 release for a simple example. 
	
	The rcS script will test for the existence of file systems and mount them accordingly.

	```
	
	https://bootlin.com/doc/legacy/audio/embedded_linux_audio.pdf

	https://alsa.opensrc.org/Udev



**显卡与显存** 


https://www.st.com/resource/zh/application_note/an4861-lcdtft-display-controller-ltdc-on-stm32-mcus-stmicroelectronics.pdf

https://www.st.com/resource/en/application_note/an4861-lcdtft-display-controller-ltdc-on-stm32-mcus-stmicroelectronics.pdf
```

显卡最早期也就是显示适配器，只是用来显示图像的，其中的显存也基本上指帧缓存，也就是用来显示一帧图像的

显存可以直接位于系统内存的固定区域中，如上述网址中介绍，LCD控制器在内存中取帧数据到FIFO中用于VGA刷屏

但一般追求高性能的设备，会将显存集成到显示卡中，这样显卡在处理数据时不会受限于系统内存的访问带来的延迟
（https://www.spo-comm.de/en/blog/know-how/integrated-vs-dedicated-graphics-card-features-differences-etc.）



上述网址归档：(https://quqi.com/516996/7604) (https://quqi.com/516996/7607)

了解FMC：(https://www.jianshu.com/p/62d1ef042d0c) (https://quqi.com/516996/7610)

```


https://blog.csdn.net/weixin_40009664/article/details/91360349
```

依照刷新率的速度，每刷一次显示数据都需要从内存中读取数据输出给LCD显示。

在这个情况下帧率跟刷新率就应该一样的了，即只要改变LCD控制器所指向内存范围内的内容，就可以刷新率的速度（帧率）输出。

当然这个内存关系非常密切，如果内存速度（总线频率）跟不上，而LCD配置的刷新率太快，也就是出现了内存带宽不够的现象，导致显示闪或者抖动的现象（特别是下半屏）。

```


https://blog.csdn.net/huan447882949/article/details/80523108
>
> 很多人可能都会问驱动LCD的数据应该放在什么地方，是怎么被搬运过去的。
>
> 其实很简单，S3C2410的LCD控制模块自带了DMA控制器，我们只要在SDRAM里面开一块空间，然后设定要DMA的起始地址(LCDSADDR1寄存器)和结束地址LCDSADDR2）就OK了。
>
> 实际上，应该说大部分的带有LCD控制器的MCU，都是采用类似的方式
>
```

对于soc片上LCD控制器为了保证刷屏性能，一般都会配置内置DMA，负责与RAM交换数据

```


https://community.nxp.com/t5/LPC-Microcontrollers/lcd-framebuffer-bus-techinal-question/m-p/515785
```

性能优化方案讨论

```


https://d1.amobbs.com/bbs_upload782111/files_17/ourdev_468849.doc  

> 在这个系统中，SDRAM Controller处的冲突是影响整个系统性能的关键。
>
> 以SDRAM时钟频率为100MHz计算，16bit位宽的SDRAM其数据总带宽为200MByte/s，640*480*2Bytes*60Hz的TFT LCD要占用36MByte/s左右的带宽，
>
> 这对于还要处理其他任务的处理器来说是很大的影响。
>
> 解决的办法是另外增加一块SDRAM，专门用作Frame buffer，这样就可以有效减少对系统总线带宽的占用。
```

这里介绍使用外部RAM的LCD控制器

增加一块独立的SDRAM应该理解为LCD控制器增加内存控制器，单独访问SDRAM，减少与系统DRAM的争用。

归档：(https://quqi.com/516996/7605)

```


https://www.ti.com/lit/an/spma082/spma082.pdf
```

As the display resolution increases, the more frame buffer is needed. 

A 480 x 272 display with 16-bit color depth would require 261KB of frame buffer. 

As expected, the TM4C129 internal SRAM is not sufficient in this scenario.

In this case, an external memory dedicated for the frame buffer and accessed through the EPI interface is required.

归档：(https://quqi.com/516996/7608)

```

https://www.cnblogs.com/locean/p/5110371.html

https://www.intechopen.com/chapters/80636
```

上述 2 个网址 LCD控制器设计的内容介绍

```


https://www.isy.liu.se/en/edu/kurs/TSTE12/laboration/TSTE12_Lab2_200912.pdf

https://www.edaboard.com/threads/vga-controller-and-accessing-external-sram.266866/
```

上述 2 个网址介绍了使用外部RAM的VGA控制器

```


https://community.nxp.com/t5/i-MX-Processors-Knowledge-Base/Memory-Management-on-i-MX6-Android/ta-p/1102563
```
When i.MX Android is running, the DDR memory will be used by the following components:

1 Linux Kernel reserved space

2 Normal zone space managed by kernel’s MM (high memory zone is also included) 

3 Reserved memory for GPU drivers

4 Reserved space for framebuffer BG triple buffers

```


https://www.quora.com/What-is-the-difference-between-Linux-framebuffer-and-GPUs-memory

https://zhuanlan.zhihu.com/p/60504398

https://developer.huawei.com/consumer/cn/forum/topic/0202325573372840117




**显示器显示原理**

https://www.ifanr.com/1422341
```

了解CRT

```

https://electronics.stackexchange.com/questions/523972/are-all-pixels-addressed-simultaneously-in-one-frame

https://superuser.com/questions/1193999/do-monitors-not-atomically-instantaneously-refresh-their-pixels




**framebuffer驱动与DRM驱动框架**

https://doc.embedfire.com/linux/stm32mp1/driver/zh/latest/linux_driver/framework_drm.html

https://www.jianshu.com/p/f315b68bc73c

https://stackoverflow.com/questions/38893679/is-a-linux-framebuffer-driver-a-video-card-driver

https://unix.stackexchange.com/questions/312851/what-is-the-difference-between-linux-framebuffer-and-gpus-memory

https://community.khronos.org/t/how-much-video-memory-is-used-by-framebuffer/46963

https://groups.google.com/g/icvideo/c/2iHQV4xTNgs

https://www.zhihu.com/question/29250067

https://www.zhihu.com/question/30635966


**了解GPIO**

* 开漏/开集输出原理
	https://zhuanlan.zhihu.com/p/41942876
	http://www.aschip.com/info-detail.php?InfoId=35
	https://blog.csdn.net/Naiva/article/details/90045788




https://wiki.t-firefly.com/zh_CN/Core-3588J/usage_gpio.html
```

硬件电路细节
(https://www.elecfans.com/d/1884243.html)

上拉电阻、下拉电阻概念补充 
(https://www.cnblogs.com/lulipro/p/7675167.html)

这个是文字的锅，跟上拉没有关系，这个电阻就是保护作用，
IO口输出高电平的时候，这个电阻用来保护负载，防止烧毁负载，IO口输出低电平的时候，用来保护IC，防止IC烧毁
(https://zhuanlan.zhihu.com/p/84538293)

```

https://zhuanlan.zhihu.com/p/67412073

https://blog.csdn.net/qq_42384937/article/details/82970224
```

引脚控制
(https://elinux.org/images/b/b6/Pin_Control_Subsystem_Overview.pdf)

(https://imgtec.eetrend.com/sites/imgtec.eetrend.com/files/201403/forum/1763-3052-di12zhangioduankou.pdf)
(https://quqi.com/516996/7603)

```

https://www.51cto.com/article/709066.html

https://learn.microsoft.com/zh-cn/windows/uwp/devices-sensors/enable-usermode-access
```

运行时引脚复用

```

https://www.eet-china.com/mp/a33048.html

https://electronics.stackexchange.com/questions/97085/gpio-pcie-programing



### 8 Linux系统特性与机制

**初识boot**

https://askubuntu.com/questions/173248/where-is-the-bootloader-stored-in-rom-ram-or-elsewhere

https://www.zhihu.com/question/534378582
```

所以总结来说：硬件在uboot的作用阶段，就必须按照uboot的规则进行驱动，但是后续的Linux系统并不认可这个驱动。

等Linux打跑了uboot（Linux接管cpu运行），硬件必须要重新和Linux系统认识认识，否则怎么能愉快的一起玩耍呢？

```

**Linux内核模块的编译和静态库的使用**

http://m.blog.chinaunix.net/uid-26246153-id-3536347.html


**ls使用通配符**

https://superuser.com/questions/1416177/run-ls-recursively-with-wildcards


**库搜索路径**

https://blog.51cto.com/u_15127658/4690108


**Linux信号机制**

https://blog.csdn.net/orangeboyye/article/details/125596135

https://kernel.meizu.com/linux-signal.html

https://blog.csdn.net/wangquan1992/article/details/108511628

https://shunlqing.github.io/inbox/signal.html
```

信号机制常被称为“软件中断”，但是信号和中断其实没有联系。信号是在软件层面对中断机制的一种模拟。

```

https://www.oreilly.com/library/view/linux-device-drivers/0596005903/ch06.html
```

如果存在信号，会如何影响驱动程序？

To this end, the driver returns -ERESTARTSYS to the caller; 

this value is used internally by the virtual filesystem (VFS) layer,

which either restarts the system call or returns -EINTR to user space. 

```

https://zhuanlan.zhihu.com/p/454795322
```

Linux的进程信号处理过程

```

https://blog.51cto.com/u_15703183/5463647



**32位平台的64位除法运算**

https://stackoverflow.com/questions/68063150/warning-aeabi-uldivmod-undefined-symbol-in-opendla-ko

https://stackoverflow.com/questions/45099231/why-does-linux-kernel-use-do-div-instead-of
```

上述 2 个网址，提示了kernel中的实现

```
https://www.cnblogs.com/AANA/p/16373834.html

https://stackoverflow.com/questions/42559378/division-operation-with-64-bits-on-32-bits-embedded-system


**关于动态链接器 ld.so**

https://unix.stackexchange.com/questions/448937/is-ld-so-an-executable

https://stackoverflow.com/questions/44224327/loading-the-dynamic-linker

https://stackoverflow.com/questions/37026193/how-is-ld-linux-so-itself-linked-and-loaded


**标准库的链接**

https://senlinzhan.github.io/2017/03/20/动态库/

http://c.biancheng.net/view/2382.html



## 并发问题


### 1  volatile关键字的知识


**volatile与内存屏障总结**

https://zhuanlan.zhihu.com/p/43526907

* x86 volatile

	https://yizhang82.dev/atomic-vs-volatile-x86

	https://stackoverflow.com/questions/4976703/volatile-variable-and-atomic-operations-on-visual-c-x86

	```

	x86 processors do not use out-of-order execution.
	
	But this doesn't stop the compiler optimizer from reordering instructions.

	```
* MSVC about x86 volatile

	https://stackoverflow.com/questions/60669710/in-c-can-we-guarantee-a-happen-before-between-two-threads-by-volatile-memor

	```
	Practically speaking, your code may produce a sequence of x86 instructions that will behave as you would expect. 

	This would be a pure coincidence given that:

	......

	Most compilers will avoid reordering code around volatile operations. 

	Some compilers, like MSVC, for example, even consider volatile operations as compiler fences. That is not the case with gcc though. 

	Luckily, the __volatile__ qualifier prevents the compiler from reordering the asm block (and the fence it implements) with the surrounding code. 

	This will make the asm blocks with hardware fences effective with that compiler and compatible ones.

	```

	https://stackoverflow.com/questions/68742664/what-are-cases-where-the-msvc-c-compiler-option-volatilems-and-volatileiso

	```

	volatile is never going to compile to memory barrier instructions on x86 (32 or 64-bit).
	
	x86's strong memory model doesn't need them for the release/acquire semantics that /volatile:ms guarantees. 
	
	On x86 it just needs to limit compile-time reordering. (I don't think it's meaningless on x86, @NathanOliver) 
	
	Presumably MSVC's optimizer used to happen to do that, and people took advantage.
	
	now it's enshrined as officially supported via this option even if the current optimizer can for example do dead-store elimination or other reordering across volatile if you don't stop it. 

	(https://godbolt.org/z/n9n4o5s6q)

	```

	https://stackoverflow.com/questions/26307071/does-the-c-volatile-keyword-introduce-a-memory-fence

	```

	In x86 asm, every load is an acquire-load, and every store is a release-store. 
	
	To provide those semantics while compiling C++, MSVC merely has to avoid compile-time reordering. 
	
	So a read of a volatile variable is a compiler-barrier for reordering loads/stores, but doesn't result in extra instructions. 
	
	For the same reason, atomic_thread_fence(mo_acquire) doesn't emit any instructions on x86, just like atomic_signal_fence(mo_acquire) on every architecture. 
	
	Only atomic_thread_fence(mo_seq_cst) requires an MFENCE.

	```

### 2 进程间同步机制

https://zhuanlan.zhihu.com/p/49214500

https://stackoverflow.com/questions/5297813/cross-process-synchronization-in-java

https://bbs.csdn.net/topics/391942429

### 3 多进程间读写同一个文件

https://www.jianshu.com/p/b5a731940ff9
```
关于系统调用原子操作的理解，原书是这样说的：

The Linux Programming Interface

5.1 Atomicity and Race Conditions
```
> Atomicity is a concept that we’ll encounter repeatedly when discussing the operation of system calls. Various system call operations are executed atomically. By this, we mean that the kernel guarantees that all of the steps in the operation are completed without being interrupted by another process or thread.
> 
> Atomicity is essential to the successful completion of some operations. In particular, it allows us to avoid race conditions (sometimes known as race hazards). A race condition is a situation where the result produced by two processes (or threads) operating on shared resources depends in an unexpected way on the relative order in which the processes gain access to the CPU(s).
```
实际上这里的意思应该是保护系统调用本身这个过程，参考《操作系统概念》 5.1.3 抢占调度。
```

https://www.zhihu.com/question/20906432

https://stackoverflow.com/questions/17431813/c-read-and-thread-safety-linux

https://stackoverflow.com/questions/10566328/using-fseek-fwrite-from-multiple-processes-to-write-to-different-areas-of-a-file

https://stackoverflow.com/questions/7842511/safe-to-have-multiple-processes-writing-to-the-same-file-at-the-same-time-cent


### 4 内存模型与内存屏障


**锁的实现需要内存屏障支持**

https://www.hitzhangjie.pro/blog/locks实现背后不为人知的故事

https://stackoverflow.com/questions/50951011/how-does-a-mutex-lock-and-unlock-functions-prevents-cpu-reordering


**acquire and release语义**

https://preshing.com/20120930/weak-vs-strong-memory-models/
> In a sequentially consistent memory model, there is no memory reordering. 
> It’s as if the entire program execution is reduced to a sequential interleaving of instructions from each thread. 
> In particular, the result r1 = r2 = 0 from Memory Reordering Caught in the Act becomes impossible.
```
一般CPU不会做成顺序一致性，这样开销太大，

但是可以通过full memory fence指令来避免StoreLoad乱序，辅助实现Sequential Consistency

(http://mintomic.github.io/lock-free/memory-fences/)

```

https://preshing.com/20120913/acquire-and-release-semantics/

https://preshing.com/20130922/acquire-and-release-fences/
> What’s cool is that neither acquire nor release semantics requires the use of a #StoreLoad barrier, 
> which is often a more expensive memory barrier type.
```

在某些场景下，不需要顺序一致性，只要保证Synchronizes-With Relationships

```

**as-if语义**

https://stackoverflow.com/questions/15027925/is-the-execution-of-java-code-within-a-single-thread-guaranteed-to-be-sequential

https://stackoverflow.com/questions/72480399/does-compiler-need-to-care-about-other-threads-during-optimizations


**信号量与条件变量**

https://dengzuoheng.github.io/cpp-concurency-pattern-3-semaphore

https://stackoverflow.com/questions/3710017/how-to-write-your-own-condition-variable-using-atomic-primitives

https://www.reploop.org/blog/2020/02/introduction-to-thread-synchronization.html
```

1 互斥锁只能被加锁的线程解锁，但是信号量可以被任意线程释放。如果你仅仅需要一个锁机制的话，这会导致困惑和微妙的问题；

2 信号量是用来编排线程的信号机制，但是互斥锁是保护共享资源的锁机制。

你不应改使用信号量来保护共享资源，也不应该将互斥锁用于信号机制：这样你的意图对你和你的代码读者会更明确。

```


### 5 互斥锁的实现


**锁释放与线程唤醒**
```

一般的实现：当某个锁释放后，内核会通知等待锁的线程队列中的第一个线程进入到就绪态等待调用，

但是是否会调用取决于调度器，也许更高的优先级线程会先被调用后抢锁。

```

https://stackoverflow.com/questions/4953478/how-does-mutex-or-semaphore-wake-up-processes

https://stackoverflow.com/questions/42428049/will-a-thread-waiting-on-a-mutex-get-the-ownership-immediately-after-mutex-unlo

https://stackoverflow.com/questions/14947191/what-is-the-pthread-mutex-lock-wake-order-with-multiple-threads-waiting

https://stackoverflow.com/questions/40873469/how-does-pthread-mutex-unlock-work-and-do-threads-come-up-at-the-same-time

https://www.zhihu.com/question/283318421/answer/431232214


***

## Android


### 1  存储知识


**storage/emulated/0**

https://android.stackexchange.com/questions/205430/what-is-storage-emulated-0


### 2 IPC问题

**跨进程数据共享与文件描述符**

https://source.android.com/devices/architecture/hidl-cpp/types#handle

**跨进程通信java与native进程同步**

https://stackoverflow.com/questions/20073051/synchronization-between-a-java-app-and-c-app-in-windows

https://stackoverflow.com/questions/15771763/can-java-and-c-c-applications-share-semaphores

https://stackoverflow.com/questions/44744804/how-can-you-use-a-mutex-between-c-sharp-and-java-processes


### 3 编译问题

**AOSP平台如何使用aar库**

https://stackoverflow.com/questions/42968311/aar-support-in-android-mk-dependencies-are-not-picked-up-by-aosp-build

https://stackoverflow.com/questions/70565929/jni-not-added-even-though-it-is-in-aar-file-in-aosp

https://stackoverflow.com/questions/70454506/loadlibrary-fails-when-added-aar-library-to-system-service
```

If you look at AOSP apps with native code, you won't find the .so files inside aars or apks, 
but find them inside system libs folders

```

### 4  源码分析

**魅族内核团队**

https://kernel.meizu.com/

**eLinux Android**

https://elinux.org/Android_Portal

### 5 权限问题

**特权应用权限问题**

https://stackoverflow.com/questions/19868138/what-is-the-difference-between-system-apps-and-privileged-apps-on-android

https://wrlus.com/android-security/system-apps-and-cve-2020-0391/

https://wrlus.com/android-security/android-app-protect/

https://balalals.cn/archives/android中是系统应用和非系统应用区别
```

特权应用和SELinux概念中的system_app应该不完全相同，system_app更强调其访问系统资源的能力

```

### 6 调试方法

**kernel log**

https://segmentfault.com/a/1190000038276523
```

kernel log可以使用两种方法实时打印

1 adb shell logcat -b kernel > DeskTop （可以输出进程号和线程号）

2 adb shell dmesg -n 8
  adb shell dmesg -T -w > DeskTop （标准格式）

```

**adb 命令**

https://zhuanlan.zhihu.com/p/161324514


**trace dump机制**

https://www.jianshu.com/p/6b5f8c9abd31

https://www.jianshu.com/p/f2713f371589

https://issuetracker.google.com/issues/236790598


### 7 JNI使用总结

https://blog.csdn.net/qq_20404903/article/details/80662352

https://doc.yonyoucloud.com/doc/wiki/project/jni-ndk-developer-guide/recommend.html

https://www.ibm.com/docs/zh/sdk-java-technology/8?topic=collector-overview-jni-object-references

* isCopy
  
	https://stackoverflow.com/questions/30992989/is-iscopy-field-always-necessary-in-android

	https://stackoverflow.com/questions/54597057/in-jni-function-when-i-change-an-array-in-place-that-was-passed-from-java-code-t

	https://www.ibm.com/docs/zh/sdk-java-technology/7?topic=cp-using-iscopy-flag-1

	https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/functions.html

* native层使用Assets

	https://stackoverflow.com/questions/10941802/cant-access-aassetmanager-in-native-code-passed-from-java-in-wallpaperservice

	https://stackoverflow.com/questions/10409125/android-read-text-file-from-asset-folder-using-c-ndk

	https://stackoverflow.com/questions/4779955/android-assets-c-jni/


***

## C/C++

### 1 内联方法

**C++ inline**

https://stackoverflow.com/questions/1760291/is-compiler-allowed-to-ignore-inline-in-case-of-template-specialization

```

In any case, even if the compiler decided to always generate ordinary calls to an inline function (i.e. to always "ignore inline"), 
it is still required to treat the function as inline for the purposes of ODR. 

How the compiler is going to do it is the problem of the compiler.

In ISO C and C++, you can freely use inline void f(void) {} in header files -- although for different reasons!

In ISO C, it does not provide an external definition at all. 

In ISO C++ it does provide an external definition; however C++ has an additional rule (which C doesn't), 
that if there are multiple external definitions of an inline function, then the compiler sorts it out and picks one of them.

```

**C99 inline**

https://stackoverflow.com/questions/31108159/what-is-the-use-of-the-inline-keyword-in-c

https://stackoverflow.com/questions/6312597/is-inline-without-static-or-extern-ever-useful-in-c99
```

The inline f() definition does not actually emit any code, so it results in an undefined symbol at link time. 

The static keyword causes the definition to emit (locally visible) code. These are the semantics... 

An optimizing compiler might actually expand the code inline in either case, or even without the inline keyword. 

In C, the inline keyword has more to do with scoping and linkage rules than with actual inlining.

inline will not generate an out-of-line version, but might call one (which you therefore must define in some other compilation unit). 

The one-definition rule applies, though; the out-of-line version must have the same code as the inline offered here, in case the compiler calls that instead.

```

https://stackoverflow.com/questions/68004269

https://en.cppreference.com/w/c/language/inline

https://www.zhihu.com/question/270847649


### 2 C语言的错误处理

https://blog.popkx.com/c-language-traps-and-skills-section-15-error-handling-is-too-cumbersome-cant-you-write-without-it/

https://www.thegeekstuff.com/2010/10/linux-error-codes

### 3 C语言typedef redefinition

https://stackoverflow.com/questions/26955590/forward-declaration-throws-redefinition-error

https://stackoverflow.com/questions/26240370/why-are-typedef-identifiers-allowed-to-be-declared-multiple-times


### 4 C++ 特性讨论

**IO流**

https://www.zhihu.com/question/439348190


**可变参数宏**

https://blog.csdn.net/lijian2017/article/details/104836447

https://wenfh2020.com/2017/10/28/cpp-log-format/


### 5 异常处理机制


**什么是异常安全**

https://stackoverflow.com/questions/9665433/which-kind-of-code-is-considered-exception-safe
```

Exception Safety is not about handling exceptions, 

it is about guaranteeing a number of properties about the program even in the presence of exceptions.

```

https://stackoverflow.com/questions/1853243/do-you-really-write-exception-safe-code
```

Writing exception-safe code in C++ is not so much about using lots of try { } catch { } blocks. 

It's about documenting what kind of guarantees your code provides.

```

https://stackoverflow.com/questions/65271783/exception-safety-strong-guarantee-vs-basic-guarantee

https://groups.google.com/g/pongba/c/MmvVdvfjeGM

https://learn.microsoft.com/zh-cn/cpp/cpp/how-to-design-for-exception-safety?view=msvc-170
```

在 try 语句和 throw 语句之间调用的函数无需了解与所引发异常有关的任何信息。 

但是，这些函数必须进行设计，以便它们在异常可能从下向上传播时“意外地”超出范围，而这样做不会留下部分创建的对象、泄漏的内存或处于不稳定状态的数据结构。

```

https://www.zhihu.com/question/485379072/answer/2117378154
```

异常安全不是说出了异常之后catch住这就叫安全了，它还需要保证出现异常时：

1 申请的资源被正确地释放了；

2 执行到一半的逻辑能够完全回滚，或者至少回滚到一个安全点，不对程序的后续执行产生副作用；

```


**何时需要异常处理**

https://www.zhihu.com/question/548087328/answer/2659324777

https://www.zhihu.com/question/418933312/answer/1448939381

https://www.zhihu.com/question/423653914/answer/1502182187


**异常与错误码**

https://zhuanlan.zhihu.com/p/142296984

https://sg-first.gitbooks.io/frankhb-talk-c-c-/content/cpp-exceptions.html

https://techsingular.net/2012/11/15/programming-in-lua（二）－-异常与错误码/




***

## CMake


### 1  概览

**cmake使用指南**
https://www.zhihu.com/column/c_200294809

**官方教程**
https://cmake.org/cmake/help/latest/guide/tutorial/

**优秀个人教程**
https://www.wilson-blog.cn/post/2021/02/12/cmake.html


### 2  CMake安装

https://zhuanlan.zhihu.com/p/92214456


### 3  语法部分

**set命令的使用**

https://stackoverflow.com/questions/31037882/whats-the-cmake-syntax-to-set-and-use-variables
```

Lists using set():

set(MyList "a" "b" "c")
set(MyList ${MyList} "d")

Or better with list():

list(APPEND MyList "a" "b" "c")
list(APPEND MyList "d")

```

https://blog.csdn.net/jsa158/article/details/52347384
```

此时，控制台中将分别打印出"a;b"和"ab"。这是因为，不带引号时，${myvar}是一个列表，包含了两个值，而message中相当于接收到了两个参数"a"、"b"，因此输出"ab"。

而带有引号时，引号中的内容整体将作为一个参数存在。

(https://www.cnblogs.com/pandamohist/p/13698075.html)

另一个比较特别的地方是，给变量赋值时，可以不用使用引号，例如：set(myvar a "b" c d)。

```
**target_compile_definitions**

https://stackoverflow.com/questions/34709286/cmake-configure-deep-sub-folder-tree

https://stackoverflow.com/questions/30546677/cmake-how-to-set-multiple-compile-definitions-for-target-executable

**target_include_directories**

https://stackoverflow.com/questions/26243169/cmake-target-include-directories-meaning-of-scope

https://stackoverflow.com/questions/48055414/cmake-copy-header-file-to-output-directory

**target_link_libraries**

https://stackoverflow.com/questions/26037954/cmake-target-link-libraries-interface-dependencies

https://cmake.org/pipermail/cmake/2016-May/063400.html

### 4  make install 命令

https://softwareengineering.stackexchange.com/questions/381924/why-should-makefiles-have-an-install-target

https://www.linuxquestions.org/questions/linux-software-2/what-does-make-install-actually-do-712942/

### 5  Pthread

https://stackoverflow.com/questions/23250863/difference-between-pthread-and-lpthread-while-compiling

https://sft.its.cern.ch/jira/browse/ROOT-6585
```
CMAKE_THREAD_LIBS_INIT 

This variable is set to what needs to be set to link with the thread library for the target OS. 

I am assuming that CMake folks do the work correctly. 

If it is empty it means that for this particular system you do not need to add any additional library to have a threads enabled.

Looking at the code of FindThreads.cmake I can see:

    # Check if pthread functions are in normal C library
    CHECK_SYMBOL_EXISTS(pthread_create pthread.h CMAKE_HAVE_LIBC_CREATE)
    if(CMAKE_HAVE_LIBC_CREATE)
        set(CMAKE_THREAD_LIBS_INIT "")
        set(CMAKE_HAVE_THREADS_LIBRARY 1)
        set(Threads_FOUND TRUE)
    endif()

So, it is included in the C library. A the truth is that I can build and run without problems.

```

***

## 杂项


**早站会的意义讨论 v2ex**

https://www.v2ex.com/t/823927


**美国大学研究：经常使用谷歌搜索引擎的用户，对自己的智商更“谜之自信”**

https://www.ithome.com/0/583/749.htm

**网络博主的技术总结**

https://dreamgoing.github.io/




## 其他资料位置

### 1 知识点标记

**Chrome书签栏**

[chrome://bookmarks/](chrome://bookmarks/)

**印象笔记**

https://app.yinxiang.com/Home.action


**知乎个人主页**

https://www.zhihu.com/people/tang-mu-shang-wei


### 2 专题总结

**summary文件夹**

[C:\Users\Administrator\Desktop\summary](C:\Users\Administrator\Desktop\summary)


**OneNote笔记**

Steve的笔记本/技术追求

<div align=center>
	<img src="images/XXX.jpg" />
</div>
<div align=center>图 1 XXX</div>

***

***










## 其他 Archived



**1 Linux系统调度**

jianshu.com/p/d1de1f293e3b

**2 CPU指令周期、CPU周期与时钟周期**

zhuanlan.zhihu.com/p/90829922

**3 初始化VS**

开始 -> 所有程序 -> Microsoft Visual Studio -> Visual Studio Tools -> VS X86本机工具命令提示

在弹出的命令行对话框中，cd .. ，退到上一级目录，然后cd Common7/IDE，进入目录后输入：devenv.exe/resetuserdata

**4 关于BMP文件与图像存储**

blog.csdn.net/qq_31094099/article/details/80286201

cnblogs.com/dasusu/p/9789389.html

**5 关系型数据库与文件系统**

softwareengineering.stackexchange.com/questions/190482

**6 类模板友元**

cnblogs.com/sarahzhang0104/p/5769994.html

**7 UDP丢包原因总结**

jianshu.com/p/7f4700a5e970

### Java部分

**1 Java中的volatile**

cnblogs.com/dolphin0520/p/3920373.html

blog.csdn.net/Hellowenpan/article/details/103202898

**2 Java子线程中的异常**

cnblogs.com/charlesblc/p/6175617.html

zhuanlan.zhihu.com/p/136571068

blog.csdn.net/kincym/article/details/78341100

**3 哈希表模质数**

blog.csdn.net/largecub233/article/details/71210210

**4 Java类的加载**

cnblogs.com/jimxz/p/3974939.html

blog.csdn.net/weixin_36344031/article/details/82533800

iteye.com/blog/nickfover-2145212

infoworld.com/article/3040564

**5 泛型类中的反射**

zhuanlan.zhihu.com/p/69132741

blogjava.net/calvin/archive/2009/12/10/43830.html

stackoverflow.com/questions/8655921

### Android部分

**1 使用Intent传递对象**

blog.csdn.net/weixin_37418246/article/details/80739882

**2 ContentProvider启动流程分析**

jianshu.com/p/b23e47cbe581

blog.csdn.net/itachi85/article/details/72618688

jianshu.com/p/74014e1b18b0

**3 Android中PagerSlidingTabStrib自定义导航栏**

jianshu.com/p/ccb4ced85165

**4 BroadcastReceiver广播接收者**

blog.csdn.net/lfdfhl/article/details/39190069

**5 Android targetSdkVersion原理**

race604.com/android-targetsdkversion/

***