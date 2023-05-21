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


https://www.zhihu.com/question/430677975/answer/2308439064
```

参考@Young Geng的评论：现在 x86 平台基本不用 UMA 的原因无非就是两点

```

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


**多核通信**

https://blog.csdn.net/YEYUANGEN/article/details/86622753
```

对memory的使用，非易失的存储空间比如NAND、NOR Flash，基本也是由ARM访问，DSP的算法代码作为ARM端OS文件系统的一个文件存在，通过应用程序进行DSP程序的下载和DSP芯片的控制。

外部RAM空间即DDR存储区，是ARM和DSP共享存在的，但是在系统设计的时候，需要把ARM和DSP使用的内存严格物理地址分开，以及预留出一部分用来交互的内存空间。

```

https://juejin.cn/post/7035822881493745694
```

需要说明一点，CPU 和 DSP 之间一般会使用 IPCM（核间通信模块）实现对一段 ddr 地址空间的共享。

但是 DSP 直接访问这段 ddr 的延迟是远大于访问 dram 的延迟，所以对于算子执行过程中需要频繁访问的 ddr 数据，

一般是先使用 dma 将其搬运到 dram 上，算子执行结束后，计算的输出再通过 dma 搬回到 ddr。

```

https://www.st.com/resource/en/product_training/STM32MP1-System-Graphics_Processing_Unit_GPU.pdf
```

The GPU has only one global interrupt. 

This interrupt is used by the low level drivers for graphic API implementation.

```

**可编程DSP与ASIC**

https://blog.csdn.net/qyf__123/article/details/100167293
```

那你可能又要问了，那为什么我们干脆不要用 ASIC 了，全都用 FPGA 不就好了么？

你要知道，其实 FPGA 一样有缺点，那就是它的硬件上有点儿 “浪费”。

```

https://www.zhihu.com/question/348712213
```

澄清软解和硬解的概念

(https://www.zhihu.com/question/61180565/answer/598520764) 评论区可参考

(https://quqi.com/516996/7625)

```





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

https://blog.csdn.net/u014379540/article/details/52502470
```

大部分程序操作都是处理器作为主设备，根据指令来发出地址，读写数据，这时总线地址 == 物理地址。

有一种情况下不是处理器做主设备，DMA controller操作RAM是不需要经过处理器的，DMA controller是主设备，但是因为DMA controller也是挂接在系统总线上，也就是处理器的地址空间中。

所以这时DMA controller发出的地址也是物理地址。

有一种特殊情况下，总线地址与物理地址不同，就是PCI总线。


```

https://zhuanlan.zhihu.com/p/463199854
```

外设（PCIe EP）通过DMA访问内存时，发出的地址就是DMA地址。

结合上面的描述我们可以知道，当设备使用了IOMMU/SMMU时，DMA地址是IO虚拟地址IOVA。

当未使用IOMMU/SMMU时，DMA地址是物理地址PA。

```

http://www.wowotech.net/memory_management/DMA-Mapping-api.html

https://adtxl.com/index.php/archives/315.html

http://bbs.chinaunix.net/thread-2072818-1-1.html
```

context entry中有一个指针指向I/O页表

当设备发起DMA操作时，IOMMU会根据该页表把设备的虚拟DMA地址转换成该设备可以访问内存区域的地址。

所以只要为设备建一张I/O页表，就可以使设备只能访问规定的内存区域了。

当然，也可以把该页表当成跳板，让只能寻址32bit地址空间的设备访问到64bit地址空间中去。

```


https://quqi.com/516996/7612

https://events.static.linuxfound.org/sites/events/files/slides/main.pdf
```

上述 2 个网址介绍了 DMA API and IOMMU API

```

* IOMMU 与 DMA 相关联的图片


	<div align=center>
	<img src="images/iommu and dma 1.png" />
	</div>
	<div align=center><b>图 1</b></div>


	
	<div align=center>
	<img src="images/iommu and dma 2.png" />
	</div>
	<div align=center><b>图 2</b></div>

	
	<div align=center>
	<img src="images/iommu and dma 3.png" />
	</div>
	<div align=center><b>图 3 来源：</b>https://quqi.com/516996/7613</div>



	<div align=center>
	<img src="images/iommu and dma 4.png" />
	</div>
	<div align=center><b>图 4</b></div>
	


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

<div align=center>
	<img src="images/third-party and first-party DMA.jpg" />
</div>

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


http://archive.lwn.net:8080/linux-kernel/75d578c2-a98c-d1ef-1633-6dc5dc3b0913@ti.com/
```

PCI Controller 中提供 DMA，使用 DMAEngine API 的的讨论

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


**DMA mapping API区别于DMA engine API**

https://stackoverflow.com/questions/13720474/dma-engine-api-vs-dma-api
```

@sawdust comment

```

https://stackoverflow.com/questions/35219926/how-to-do-a-single-dma-transaction-in-kernel

https://elinux.org/images/3/32/Pinchart--mastering_the_dma_and_iommu_apis.pdf
```

DMA (mapping) != DMA (engine)

The topic we will focus on is how to manage system memory used for DMA.

This presentation will not discuss the DMA engine API, 

nor will it address how to control DMA operations from a device point of view.

```

### 6 中断控制器总结


**中断概述与硬件组成**

https://chasinglulu.github.io/2019/07/07/中断「interrupt」/

https://chasinglulu.github.io/2019/07/16/中断延迟处理机制「interrupt-delay-processing」/
```

如果在当前CPU所属的__softirq_pending字段中特定softirq对应的bit位未置位，那么该函数就会将其对应bit位置1，以表示至少有一个该softirq是待处理的。

```

https://blog.gmem.cc/linux-kernel-study-note-vol2
```

每个注册的软中断，都会占据上述数组的一个元素，因此最多可能有32个软中断。

在2.6版本的内核，有9个元素已经被占用。 

一个软中断不会抢占另外一个，实际上，只有中断处理程序才能抢占软中断。

但是其它软中断（包括同类型的）可以在别的处理器上运行。

```

https://www.zhihu.com/question/545744966/answer/2597497794
```

而是在取指周期中，电路的输入中发现中断线的输入中有电平，计算结果就是切换PC，然后这个时钟周期就从执行指令变成执行中断的计算要求了。

中断行为就会插入到整个执行流中了。

```

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


**硬实时概念**

https://www.zhihu.com/question/558428484/answer/2712013485
```

当然，实时性本质上是一个系统工程，操作系统只能尽可能的提供帮助，而不能控制用户程序的行为。

因此，对于一个实时系统来说，应用程序的设计才是最关键的。

```


**Linux实时补丁**

https://hebinglong.github.io/2018/08/15/Linux操作系统实时性分析/
```

这种方法存在的问题是：很难百分之百保证，在任何情况下，GPOS程序代码绝不会阻碍RTOS的实时行为。

也就是说，通过修改Linux内核，难以保证实时进程的执行不会遭到非实时进程所进行的不可预测活动的干扰。

```


https://www.zhihu.com/question/28925221/answer/90870825


https://cloud.tencent.com/developer/article/1894161
```

注：原文没找到，第一大段中的软实时补丁可能是笔误，应该是硬实时

```

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


https://learn.microsoft.com/zh-cn/windows-hardware/test/wpt/memory-footprint-optimization
```

Sharable pages:Pages that one or more processes can use.

Examples include code pages within executable images (.dll, .exe, and .cpl) or data file pages (.txt, .doc, etc.).

注：kswapd运行时，在Page Cache中，可共享页写回到文件，而私有页写回到交换分区。

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

**磁盘读写**

https://stackoverflow.com/questions/51006070/file-system-block-size-vs-disk-block-size

https://superuser.com/questions/976271/ssd-block-sizing

https://www.zhihu.com/question/26028619



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

https://www.opsdash.com/blog/cpu-usage-linux.html

https://haydenjames.io/what-is-iowait-and-linux-performance/

https://m.elecfans.com/article/2042951.html
```

Linux中top命令的计算方式

```


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

	https://stackoverflow.com/questions/5555632/can-gcc-not-complain-about-undefined-references


**GDB初步**

https://www.cnblogs.com/dongc/p/9690754.html

https://blog.csdn.net/blade2001/article/details/46563805

* Android gdb
  
	https://blog.csdn.net/cigogo/article/details/82655837

	https://blog.csdn.net/tkwxty/article/details/104027151



**Linux内核符号表**

https://mairacanal.github.io/kernel-symbol-table-compilation-more/

https://www.linux.com/training-tutorials/kernel-newbie-corner-kernel-symbols-whats-available-your-module-what-isnt/

http://kerneltravel.net/blog/2020/syscall_ljr_1/

https://zhuanlan.zhihu.com/p/462914789

https://docs.kernel.org/kbuild/modules.html
```

During a kernel build, a file named Module.symvers will be generated. 

Module.symvers contains all exported symbols from the kernel and compiled modules. 

For each symbol, the corresponding CRC value is also stored.

个人理解：最终会被一起编译到内核符号表

```


**arm64 kernel crash 调试方法**

https://www.zhihu.com/column/c_1049317588999479296

https://blog.csdn.net/WANGYONGZIXUE/article/details/128431816


### 4 Linux系统调用知识点

http://nicephil.blinkenshell.org/my_book/ch08s03.html

http://blog.chinaunix.net/uid-28362602-id-3424404.html

https://zhuanlan.zhihu.com/p/55264897

https://gityuan.com/2016/05/21/syscall

https://arthurchiao.art/blog/system-call-definitive-guide-zh/
```

4.2.3 内核空间：syscall入口

```

https://man7.org/linux/man-pages/man2/syscall.2.html

https://man7.org/linux/man-pages/man2/_syscall.2.html
```

上述 2 个网址是调研系统调用返回错误码形式时查的man手册

```

https://stackoverflow.com/a/51837677/14035857
```

If you're looking for syscall number in Linux system, take a look at w3challs

查询系统调用号

```


**流程分析**

https://zhuanlan.zhihu.com/p/361328552

https://zhuanlan.zhihu.com/p/55214097

https://dumphex.github.io/2020/03/01/syscall/
```

以arm64下的mmap系统调用为例

```


**系统调用定义宏 SYSCALL_DEFINEx 的分析**

https://blog.csdn.net/weixin_42992444/article/details/108571515


**Android bionic的系统调用实现**
```

Android bionic的libc库没有直接定义系统调用的具体实现

而是通过gensyscalls.py脚本读取SYSCALLS.TXT文件生成

```

https://blog.csdn.net/qq_22613757/article/details/89852771

https://blog.csdn.net/lijie2664989/article/details/107826733




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



**Linux内核编译的流程**

https://yunyanan.github.io/exploring_kbuild/
```

顶层Makefile通过递归搜索子目录Makefile (相当于嵌套make，参考 跟我一起写Makefile)

文件名写为Makefile优先推荐，其次是Kbuild

跟我一起写Makefile：(https://seisman.github.io/how-to-write-makefile/index.html)

```

https://zhuanlan.zhihu.com/p/362958145 
```

解释了如何递归进入Makefile.build（黄导的知乎专栏，与兰新宇一样优质）

```

https://linux.cn/article-6197-1.html

https://richardweiyang-2.gitbook.io/kernel-exploring/00_index/05_rules_for_single_object



**2 内核调试打印与内核模块名**

https://github.com/PinoTsao/Makefile/blob/master/01.kbuild_summary.md

https://www.cnblogs.com/pengdonglin137/p/5808373.html



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



**kernel内存分配机制**


http://aandds.com/blog/linux-physical-memory-mgmt.html
```

内核把“物理页”作为内存管理的基本单位。

尽管处理器的最小可寻址单位通常为字（甚至字节），但是内存管理单元（MMU，管理内存并把虚拟地址转换为物理地址的硬件）通常以页为单位进行处理。

正因为如此，MMU 以页（page）大小为单位来管理系统中的页表（这也是页表名的来由）。

(https://zhuanlan.zhihu.com/p/488123510)

Linux物理系统内存管理模型

```

https://blog.csdn.net/chijiandao3197/article/details/100930630
```

根据上面分析，graphic通过get_free_pages()向kernel的buddy系统申请连续内存，经过一段时间，buddy系统产生了大量碎片

graphic无法获取连续的物理内存，因此通过vmalloc想从buddy系统申请不连续的内存

不幸的是vmalloc的虚拟地址空间耗尽，尽管这时还有大量物理内存，vmalloc申请失败

```

https://stackoverflow.com/questions/27985428/map-several-pages-as-large-region-into-process-memory-space

https://biscuitos.github.io/blog/MMU-Linux4x-VMALLOC/

https://www.cnblogs.com/byeyear/p/3215287.html
```

kmap和vmalloc在应用上的最大区别在于，kmap往往应用于“空间分配”与“地址映射”可以分开的场合

```


https://stackoverflow.com/questions/116343/what-is-the-difference-between-vmalloc-and-kmalloc

https://stackoverflow.com/questions/40890861/why-is-kmalloc-more-efficient-than-vmalloc
```

上述 2 个网址描述了 kmalloc 和 vmalloc 的一些特点

(https://stackoverflow.com/questions/6306192/is-there-a-size-limit-for-kernel-module-in-linux)

早期kernel可能限制了vmalloc大小的分配，由此也限制了module模块大小

```

https://stackoverflow.com/questions/27091182/can-allocation-by-kmalloc-gfp-kernel-be-failed
```

kmalloc (GFP_KERNEL) cannot wait forever unless you add the optional flag __GFP_NOFAIL. 

Note that this one is deprecated on the recent kernel.

```

* 伙伴系统
	```

	伙伴系统存在MAX_ORDER限制，默认最大支持分配4MB连续内存。
	
	在32位上内核在固定映射区一次可访问就是4MB，而且32位的内核虚拟地址也很有限，所以伙伴系统默认设置最大4MB是比较合理的。

	到了64位这个数值可以相应增加，但是大部分Linux设备都是嵌入式设备或普通个人计算机，内存一般不会太大，系统长时间运行后，伙伴系统的碎片问题会比较严重，
	所以分配连续的4MB也不一定能成功，另外考虑可移植性，一般不需要修改这个值。

	但是如果有特殊用途的设备，比如在64位的服务器系统上，一般带有大量内存，可以适当增加这个值。可参考 《用“芯”探核》 中伙伴系统的介绍

	How to request continuous physical memory in Linux ? 介绍了一种伙伴系统的碎片问题。
	(https://feichashao.com/continuous_physical_memory/)

	```

	https://www.byteisland.com/linux-内核-buddy-系统/

	https://normal.zone/blog/2020-12-11-linux-1gb-thp-1/

	https://lwn.net/Articles/865611/

	https://zhuanlan.zhihu.com/p/220068494


* CMA

	https://xie.infoq.cn/article/02bdff58ff0c3e34ca7fe8eb5
	```

	(https://lwn.net/Articles/486301/)

	(https://lwn.net/Articles/753167/)

	```
	
	https://lwn.net/Articles/447405/
	```

	Any device which can only do DMA to a physically contiguous area requires (in the absence of an I/O memory management unit) a physically contiguous buffer to work with.

	This requirement is often a sign of relatively low-end (stupid) hardware; one could hope that such hardware would become scarce over time.

	What we are seeing, though, are devices which have managed to gain capabilities while retaining the contiguous DMA requirement.

	For example, there are video capture engines which can grab full high-definition data, perform a number of transformations on it, 
	
	but still need a contiguous buffer for the result. 

	
	(https://xie.infoq.cn/article/b3b83c6e5d54ca306320aa919)

	通过支持聚集操作的网络接口，待传输的数据不必占用主存的连续空间，

	网卡的 DMA 引擎也可以将分布在不同位置的数据集中到一个数据传输中。

	(https://www.cnblogs.com/jliuxin/p/14129414.html)

	因此从软件层面来说, DMA核心层必须提供scatter-gather的能力
	
	如果DMA控制器本身支持scatter-gather操作, 那就直接配置控制器即可; 如果控制器不支持, 我们就只有用软件模拟了

	```

	https://liujunming.top/2019/08/31/CMA/

	http://www.wowotech.net/memory_management/cma.html

	https://blog.csdn.net/Rong_Toa/article/details/109558234

	https://community.nxp.com/t5/i-MX-Processors-Knowledge-Base/How-to-get-rid-of-CMA/ta-p/1123287



**Linux kernel 内存初始化**


https://blog.csdn.net/xiaoqiaoq0/article/details/108088787

http://www.wowotech.net/?post=357
> 对系统中所有的memory type的region建立对应的地址映射。
> 由于reserved type的memory region是memory type的region的真子集，因此reserved memory 的地址映射也就一并建立了。
```

可以理解为能够被kernel管理的系统物理内存包括常规内存，标记reserved的内存，但不包括标记了no-map的。

常规内存和标记reserved的内存地址都会被正常映射。

(https://blog.csdn.net/jasonactions/article/details/114122304)
在分析启动代码的时候会有一些关于内存管理初始化相关的内容，在此专门将其提取出来，做一个简单的总结。

```



**页表项的构成**

https://chyyuu.gitbooks.io/simple_os_book/content/zh/chapter-3/x86_pages_hardware.html
```

在80x86中的的页表项结构定义如下所示

```

https://learningos.github.io/rcore_step_by_step_webdoc/docs/页表简介.html
```

我们再来看一次 riscv32 中 页表项/页目录项 的结构：

```

https://www.cnblogs.com/vinozly/p/5703215.html
```

x86中的页表结构和页表项格式

```

**内核页表线性映射**


https://stackoverflow.com/questions/37570127/what-happened-when-kfree-function-called
```

kfree后由于线性映射总时可以访问对应的物理地址，但是访问后是未定义的，kfree可能会作某些处理

(https://th0ar.gitbooks.io/xv6-chinese/content/content/chapter2.html)

函数 kfree 首先将被释放内存的每一字节设为 1

这使得访问已被释放内存的代码所读到的不是原有数据，而是垃圾数据；这样做能让这种错误的代码尽早崩溃

```

https://www.cnblogs.com/beixiaobei/p/10507340.html
```

vfree 释放后会修改页表，因为其不是线性映射的，所以会修改页表项

进程要vfree释放这个区域，其实修改的还是内核页表，会把addr对应的pte页表项设置为0，其它的都不做改变；

那么当进程试图访问一个已经被释放区间的地址addr时候，由于它和内核对于addr的pmd项是一样的，

所以会继续去访问内核页表关于addr的pte页表，最后发现pte页表项为0，又触发了缺页异常。

线性映射是固定的映射：(https://zhuanlan.zhihu.com/p/69329911)

```

https://stackoverflow.com/questions/4535379/do-kernel-pages-get-swapped-out

https://stackoverflow.com/questions/8345300/can-vmalloc-pages-be-swapping-pages


* 内核页表与进程页表
  
	https://www.zhihu.com/question/24916947
	```

	arm32上内核页表会复制一份到进程页表

	内核页表修改时，这种情况下其他进程陷入内核时可能产生缺页

	```

	https://www.tiehichi.site/2021/11/15/ARMv7进程页表/
	```

	arm64使用了两个页表基地址寄存器，不再需要复制

	```


* 线性映射初始化

	https://stackoverflow.com/questions/53060537/is-it-possible-that-the-page-table-is-larger-than-the-physical-memory-if-so-whe
	```

	On a typical CPU with a MMU that supports paging, only a small fraction of the physical addresses that exist address either RAM or MMIO. 

	The rest of the physical address spaced is unused. 

	Typically you would get some sort of exception if you did map those physical addresses not addressing a device to virtual addresses and then try to access them.

	Thus in practice the practical size of a page table is constrained by the amount of RAM and MMIO space that can be addressed. 

	If you have small amounts of RAM you don't need a massive page table described in the example. Most of the entries would be invalid.

	```

	https://zhuanlan.zhihu.com/p/573925459
	```

	从上面流程图可以看到页表映射最终都是调用__create_pgd_mapping函数实现

	下面分析下__create_pgd_mapping会逐级建立映射关系，同时会进行权限的控制

	可以看到建立页表就是填充页表描述符, 本质是填充物理页帧号和权限控制位这两部分内容，最后是通过调用set_pte()填充到对应的页表中

	```

	https://francescoquaglia.github.io/TEACHING/PMMC/SLIDES/kernel-level-memory-management.pdf
	```

	Clearly, we have plenty of room in virtual addressing for directly mapping all the available RAM into kernel pages on most common chipsets
	
	This is the typical approach taken by Linux, where we directly map all the RAM memory

	```

	https://www.cnblogs.com/liuhailong0112/p/14465697.html
	```

	前面的[3]和[4]遍历内核中所有memblock感知到的物理内存，并为这些物理内存建立了虚实映射，映射到虚拟地址空间的线性区域。
	
	这个虚实映射的线性关系为：paddr = vaddr + (PAGE_OFFSET - PHYS_OFFSET)。 这里的(PAGE_OFFSET - PHYS_OFFSET)就是虚地址与物理地址线性映射的偏移。

	也就是说在arm64架构中，系统MMU完成初始化后就可以通过这个线性关系将一个线性区域的虚拟地址转换为物理地址(但是并非所有的虚拟地址对应着有效的物理地址)，
	
	也可以在知道物理地址的情况下将物理地址转换为线性区域虚拟地址供CPU进行访问(理论上linux可探测到的物理内存都可以找到一个合法的线性区域虚拟地址)。

	```

	https://unix.stackexchange.com/questions/513170/does-the-kernel-address-region-in-user-page-tables-need-to-be-updated-in-an-64-b


	https://www.cnblogs.com/Random-Boy/p/13915175.html
	```

	多级页表的按需映射，是页表的基本功能，只是用来节省页表占用内存空间，
	
	而内核的线性映射和这个多级页表的按需映射，其实是两回事，大家需要区别对待。

	这里可以理解为只有可用的物理内存按照多级页表的方式建立起线性映射

	```


* 页表项属性

	https://stackoverflow.com/questions/26837356/what-is-meant-by-invalid-page-table-entry

	https://cs.stackexchange.com/questions/80215/why-do-we-need-the-valid-invalid-bit-in-a-page-table
	```

	有效-无效位主要是起到保护作用和换页标记作用

	```


**内核页表的 section map**

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/commit/arch/arm64/mm/mmu.c?id=206a2a73a62d37c8b8f6ddd3180c202b2e7298ab
> We have the capability to map 1GB level 1 blocks when using a 4K granule.

https://zhuanlan.zhihu.com/p/363856783

https://blog.csdn.net/yhb1047818384/article/details/109169979

https://forums.raspberrypi.com/viewtopic.php?t=227139




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

https://zhuanlan.zhihu.com/p/577974561
```

linux 内核字符驱动char_dev源码分析

cdev结构不一定是与子设备号一一对应的，一个cdev可以有多个子设备号，子设备号的管理取决于驱动程序的实现

```


**平台设备驱动**


http://www.wowotech.net/device_model/platform_device.html

https://doc.embedfire.com/linux/stm32mp1/driver/zh/latest/linux_driver/base_platform_driver.html

https://blog.csdn.net/a568713197/article/details/89642396

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
```

PCI 地址域包含三种不同的地址空间： 配置、内存以及 I/O 空间

```

https://stackoverflow.com/questions/59113831/what-is-the-benefit-of-calling-ioread-functions-when-using-memory-mapped-io
```

In fact they do more than that, 

handling endianness (They also handle endianness, accessing device memory as little-endian. Or ioread32be for big-endian) 

and some compile-time reordering memory-barrier semantics that Linux chooses to include in these functions. 

And even a runtime barrier after reads, because of DMA.

(https://www.cnblogs.com/dylanin1999/p/16583285.html)

使用 IO API 的方式主要并不是同步考虑

对于arm来说，单条访存汇编指令都是原子的，多核smp也是，因为有总线仲裁所以cpu可以单独占用总线直到指令结束

(https://wudaijun.com/2018/02/go-sync-map-implement/)
(https://docs.google.com/presentation/d/1JkOUQ07nr0WQ8SKqcWA5D3M0v1gUdAwgNBbUcMhhGis/htmlpresent)

补充：原子的访存指令

```

https://docs.kernel.org/driver-api/device-io.html
```

On most architectures it is a regular pointer that points to a virtual memory address and can be offset or dereferenced,

but in portable code, it must only be passed from and to functions that explicitly operated on an __iomem token, 
 
in particular the ioremap() and readl()/writel() functions.

While on most architectures, ioremap() creates a page table entry for an uncached virtual address pointing to the physical MMIO address, 

some architectures require special instructions for MMIO.

```

https://breezetemple.github.io/2019/01/30/mmap-and-malloc/
```

在 kernel 里使用 ioremap 分配出来的一段 memory 不经过 cache 并且物理地址是连续的，

而 user space 里使用 malloc 分配出来的 memory 则没有以上保证，我看不出来在 MMU enable 的情况下物理地址是否连续对 memory 的读写效率有什么影响，

所以问题应该在是否经过 cache 这里，我也不是很确定。

感觉不是 ioremap 的问题，因为我用 get_free_pages 申请内核管理的一段连续内存再 mmap 给应用，情况也是一样。 

```

* mmap

	https://stackoverflow.com/questions/45972/mmap-vs-reading-blocks

	https://csstormq.github.io/blog/计算机系统篇之虚拟内存（4）：再探%20mmap



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
(https://www.spo-comm.de/en/blog/know-how/integrated-vs-dedicated-graphics-card-features-differences-etc.)


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
> 其实很简单，S3C2410的LCD控制模块自带了DMA控制器，我们只要在SDRAM里面开一块空间，然后设定要DMA的起始地址(LCDSADDR1寄存器)和结束地址(LCDSADDR2)就OK了。
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

(https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841683/Linux+Reserved+Memory)

```


https://www.quora.com/What-is-the-difference-between-Linux-framebuffer-and-GPUs-memory

https://zhuanlan.zhihu.com/p/60504398

https://developer.huawei.com/consumer/cn/forum/topic/0202325573372840117




**显示器显示原理**

https://www.ifanr.com/1422341
```

了解CRT

```

https://blog.csdn.net/xishuang_gongzi/article/details/54287219
```

正常的TFT一行的显示周期是 前消隐 + 实际点输出 + 后消隐

```

https://electronics.stackexchange.com/questions/523972/are-all-pixels-addressed-simultaneously-in-one-frame

https://superuser.com/questions/1193999/do-monitors-not-atomically-instantaneously-refresh-their-pixels

https://focuslcds.com/mipi-display-serial-interface-dsi/


**framebuffer驱动与DRM驱动框架**

https://doc.embedfire.com/linux/stm32mp1/driver/zh/latest/linux_driver/framework_drm.html

https://www.jianshu.com/p/f315b68bc73c

https://stackoverflow.com/questions/38893679/is-a-linux-framebuffer-driver-a-video-card-driver

https://unix.stackexchange.com/questions/312851/what-is-the-difference-between-linux-framebuffer-and-gpus-memory

https://community.khronos.org/t/how-much-video-memory-is-used-by-framebuffer/46963

https://groups.google.com/g/icvideo/c/2iHQV4xTNgs

https://www.zhihu.com/question/29250067

https://www.zhihu.com/question/30635966

* plane

	https://blog.csdn.net/qq_30599505/article/details/126206374

	https://embear.ch/blog/drm-framebuffer

	https://blog.csdn.net/qq_38350702/article/details/114265983
	```

	上述 3 个网址介绍了DRM框架中plane的概念。

	plane不是硬件模块，而是包含了从CRTC获取了buffer的内存对象。

	持有framebuffer的plane称为primary plane。（其他的plane也可以说内容来自framebuffer）
	
	每个CRTC必须有一个primary plane，因为它是CRTC视频模式数据的来源，比如像素大小、像素格式、刷新率等。

	如果display controller支持硬件cursor overlays，则CRTC可能还具有与其关联的cursor plane。

	```

	https://xilinx.github.io/kria-apps-docs/kv260/2022.1/build/html/docs/nlp-smartvision/docs/sw_arch_platform_nlp.html
	```

	A plane represents an image source that can be blended with or overlayed on top of a CRTC frame buffer during the scan-out process. 
	
	Planes are associated with a frame buffer to optionally crop a portion of the image memory (source) and scale it to a destination size. 
	
	The DP Tx display pipeline does not support cropping or scaling, 
	
	therefore both video and graphics plane dimensions have to match the CRTC mode (i.e., the resolution set on the display). 

	```

* CRTC

	https://blog.csdn.net/weixin_43824344/article/details/118313846
	```

	阴极管的上下文，简单来说是显示输出的上下文，对显示buffer进行扫描，并产生时序信号的硬件模块，通常指Display Controller，

	CRTC对内（输入）连接framebuffer的地址，对外（输出）连接Encoder，
	
	扫描了framebuffer的内容之后，再叠加planes的内容，最后传递给Encoder。

	```

	https://blog.csdn.net/weixin_29014939/article/details/117013522
	```

	显卡主要是由三类设备组成：

	Processing logic 指的是神秘的 GPU 模块，
	
	Display controller 指的是 LCDC 控制器，
	
	Hardware video acceleration 指的就是具体的显示接口 HDMI、eDP、...

	```

	https://zhuanlan.zhihu.com/p/421532503

	https://juejin.cn/post/7132777622487957517
	```

	上述 2 个网址介绍了一些DPU合成的知识

	```




**了解GPIO**

* 开漏/开集输出原理

	https://zhuanlan.zhihu.com/p/41942876
	
	http://www.aschip.com/info-detail.php?InfoId=35
	
	https://blog.csdn.net/Naiva/article/details/90045788




https://wiki.t-firefly.com/zh_CN/Core-3588J/usage_gpio.html
```

(https://www.elecfans.com/d/1884243.html)

硬件电路细节

(https://www.cnblogs.com/lulipro/p/7675167.html)

上拉电阻、下拉电阻概念补充 

(https://www.zhihu.com/question/23167435/answer/167825884) 评论区可参考 

(https://zhuanlan.zhihu.com/p/84538293)

这个是文字的锅，跟上拉没有关系，这个电阻就是保护作用，

IO口输出高电平的时候，这个电阻用来保护负载，防止烧毁负载，IO口输出低电平的时候，用来保护IC，防止IC烧毁

```

https://zhuanlan.zhihu.com/p/67412073

https://blog.csdn.net/qq_42384937/article/details/82970224
```

引脚控制：(https://elinux.org/images/b/b6/Pin_Control_Subsystem_Overview.pdf)

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


https://stackoverflow.com/questions/53850202/signal-handler-and-multithreading
```

If you resend the signal, the signal is momentarily blocked until the signal handler ends the execution.

In fact as explained here, blocked signals are set to pending, but not queued.

信号处理的基本机制，可以结合 CSAPP 8.5 理解

```

https://stackoverflow.com/questions/15651964/linux-can-a-signal-handler-excution-be-preempted

https://stackoverflow.com/questions/6128547/is-execution-of-signal-handler-un-preemptible-in-linux
```

上述 2 个网址介绍了信号处理函数的可抢占性，信号处理函数与其他用户空间函数特性相似

```


https://devarea.com/linux-handling-signals-in-a-multithreaded-application

https://stackoverflow.com/questions/27965761/where-does-signal-handler-executed

https://stackoverflow.com/questions/22005719/which-thread-handles-the-signal
```

上述 3 个网址介绍了信号处理函数执行时的所在线程

According to POSIX.1, a process-directed signal (sent using kill(2), for example) should be handled by a single, arbitrarily selected thread within the process.

```




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


**进程阻塞后操作系统的工作**

https://www.zhihu.com/question/492983429

***


## 并发问题


### 1 volatile关键字的知识


**谈谈 C/C++ 中的volatile**

https://liam.page/2018/01/18/volatile-in-C-and-Cpp/



**volatile与缓存一致性**

https://blog.csdn.net/weixin_42417004/article/details/117118027
```

注意，此时CPU是使用LDR访存指令来访问内存，但是仍然没有得到正确的内存数据。

即使使用volatile关键字也无济于事，因为volatile是在指令级上影响C语言到汇编语言的关键字，

但是CPU在访问内存时，仍然需要经过cache的缓冲。

```


**volatile与内存屏障总结**


https://stackoverflow.com/questions/61307639/why-do-we-need-both-read-and-write-barriers

https://zhuanlan.zhihu.com/p/43526907
```

上述 2 个网址介绍了 x86 中的volatile与内存屏障

代码中仍然使用lfence()与sfence()这两个内存屏障应该也是一种长远的考虑。

按照Interface写代码是最保险的，万一Intel以后出一个采用弱一致模型的CPU，遗留代码出问题就不好了。

目前在X86下面视为编译器屏障即可。

```

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

这里应该理解为对于用户层来说，系统调用应保证是线程安全的，具体实现上是内核开发者的职责。

另外系统调用本身这个过程也应该保护，参考《操作系统概念》 5.1.3 抢占调度。

```

https://www.zhihu.com/question/20906432

https://stackoverflow.com/questions/17431813/c-read-and-thread-safety-linux

https://stackoverflow.com/questions/10566328/using-fseek-fwrite-from-multiple-processes-to-write-to-different-areas-of-a-file

https://stackoverflow.com/questions/7842511/safe-to-have-multiple-processes-writing-to-the-same-file-at-the-same-time-cent



### 4 内存模型与内存屏障



**多核重排序问题**


https://stackoverflow.com/questions/71768672/can-cpu-out-of-order-execution-cause-memory-reordering

https://elsonlee.github.io/2020/05/25/reorder-detection/

https://www.zhihu.com/question/296949412/answer/747494794
```

上述 3 个网址简要说明了多核出现CPU乱序的原因

1. 编译优化
2. CPU自身优化
3. store buffer下会导致的看似“重排序”的现象

```


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

(https://chonghw.github.io/)

preshing并发编程系列文章的翻译

```


https://lwn.net/Articles/847481/
```

Linux kernel有如下定义

LoadLoad屏障：smp_load_acquire(), smp_rmb()

LoadStore屏障：smp_load_acquire(), smp_store_release()

StoreStore屏障：smp_store_release(), smp_wmb()

(https://www.qemu.org/docs/master/devel/atomics.html)
Memory barriers control the order of references to shared memory. They come in six kinds:
Atomic operations other than qatomic_set() and qatomic_read() have either acquire or release semantics 

(https://tinylab.org/memory-ordering-part2/)

```





**锁的实现需要内存屏障支持**

https://www.hitzhangjie.pro/blog/locks实现背后不为人知的故事

https://stackoverflow.com/questions/50951011/how-does-a-mutex-lock-and-unlock-functions-prevents-cpu-reordering




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


**lock free**

https://www.zhihu.com/question/295904223/answer/514363565

https://www.zhihu.com/question/577529159/answer/2892615304

https://www.zhihu.com/question/53303879/answer/142089019

https://zhuanlan.zhihu.com/p/386422612
```

RCU 是一种非阻塞同步的例子

(https://www.cs.yale.edu/homes/aspnes/pinewiki/ObstructionFreedom.html)

While there exist lock-free implementation with this property, 

there is a particularly simple implementation using CAS that is only obstruction-free.

```

https://en.wikipedia.org/wiki/Read-copy-update
```

RCU is perhaps the most common non-blocking algorithm for a shared data structure. 

RCU is completely wait-free for any number of readers. 

Single-writer implementations RCU are also lock-free for the writer.

Some multi-writer implementations of RCU are lock-free.

Other multi-writer implementations of RCU serialize writers with a lock.

(https://hackmd.io/@sysprog/linux-rcu)

```

https://www.v2ex.com/t/766626
```

无锁的定义和锁倒是没有直接联系，只要求当任意线程在任意时刻卡死时（但是不能死光）

起码剩下的线程中至少还有一个能继续跑（无等待就是剩下没死的线程都能继续跑）

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


**lock prefix 与原子操作**

http://web.mit.edu/rhel-doc/3/rhel-as-en-3/i386-prefixes.html
```

The bus lock prefix lock inhibits interrupts during execution of the instruction it precedes. 

(This is only valid with certain instructions; see a 80386 manual for details).

```

https://stackoverflow.com/questions/55180452/interrupting-an-assembly-instruction-while-it-is-operating

https://stackoverflow.com/questions/27837731/is-x86-cmpxchg-atomic-if-so-why-does-it-need-lock
```

On a single-CPU system, cmpxchg is atomic with respect to other threads, or any other code running on the same CPU core. 

(But not to "system" observers like a memory-mapped I/O device, or a device doing DMA reads of normal memory, 

so lock cmpxchg was relevant even on uniprocessor CPU designs).

```

**spin_lock使用场景**

https://blog.csdn.net/bob_fly1984/article/details/38042763



***


### 6 缓存一致性


**Cache与DMA一致性问题**

https://zhuanlan.zhihu.com/p/109919756

https://pebblebay.com/a-guide-to-using-direct-memory-access-in-embedded-systems-part-two/
```

Some system hardware designs include a mechanism called bus snooping or cache snooping; 

the snooping hardware notices when an external DMA transfer refers to main memory using an address that matches data in the cache, 

and either flushes/invalidates the cache entry or “redirects” the transfer 

so that the DMA transfers the correct data and the state of the cache entry is updated accordingly.  

In systems with snooping, DMA drivers don’t have to worry about cache coherency.

When the hardware doesn’t have snooping, DMA-based device drivers usually use one of two techniques to avoid cache coherency problems. 

(https://pebblebay.com/direct-memory-access-embedded-systems/)

```

https://mp.weixin.qq.com/s/H0aAs3Osvl8uugj4NfRbmA
```

《宋宝华：深入理解cache对写好代码至关重要》

这些API把底层的硬件差异封装掉了，如果硬件不支持CPU和设备的cache同步的话，延时还是比较大的。

那么，对于底层硬件而言，更好的实现方式，应该仍然是硬件帮我们来搞定。

比如我们需要修改总线协议，延伸红线的触角：

当设备访问RAM的时候，可以去snoop CPU的cache

(https://zhuanlan.zhihu.com/p/508439396)

第一种方案是使用硬件cache一致性的方案，需要SOC中CCI这种IP的支持

(https://blog.csdn.net/wll1228/article/details/117650015)

上面说的是常规DMA，有些SoC可以用硬件做CPU和外设的cache coherence，例如在SoC中集成了叫做"Cache Coherent interconnect"的硬件

```


***


## Android


### 1 存储知识


**storage/emulated/0**

https://android.stackexchange.com/questions/205430/what-is-storage-emulated-0


**FDE与FBE**

https://new.qq.com/omn/20200205/20200205A0BZF400.html



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

**关于Android.bp中的required属性**
```

native库分为.a静态库和.so动态库，编译时分别使用static_libs和shared_libs添加依赖，这两者都是编译时依赖，

其中静态库直接打包进原始文件中，动态库编译为独立的so模块位于某个可查找路径中。

编译时依赖有一个特点，某个源文件必须知道它所依赖模块的符号以使用它，这就必须引入头文件，同时编译时会对so库进行链接。

但是对于so库的使用还有一种方式就是运行时动态加载，编译时不需要头文件，通过系统库提供的某种方法解析出库中的符号来使用，比较典型的就是jni库。

我们引用jni库从来不会在java文件中包含c的头文件，所以使用的是jvm提供的loadlibray方法动态加载，解析作为jni的so库符号提供给java使用，这种情况下依赖jni的so库模块使用required依赖就可以了。

```

**关于Android.bp中的aidl_interface**

https://cs.android.com/android/platform/superproject/+/master:frameworks/av/media/libaaudio/src/Android.bp
```

注：一个使用示例 name: "aaudio-aidl",

```

**Android Studio 2021 查看CMake信息**

* CMake编译log输出
```
    
D:\_DeskTopStorage\AndroidStudioProjects\CppTest\app\build\intermediates\cxx\Debug\1u3c266n\meta\arm64-v8a\cmake_server_log.txt

```

* CMake参数设置
``` 

D:\_DeskTopStorage\AndroidStudioProjects\CppTest\app\.cxx\Debug\1u3c266n\armeabi-v7a\metadata_generation_command.txt

```



**JVM类共享**

https://stackoverflow.com/questions/13496307/can-multiple-jvm-processes-share-memory-for-common-classes
```

At this time and with the Oracle VM, this isn't possible.

IBM JDK has a jvm parameter to achieve this

```

https://stackoverflow.com/questions/13939516/share-classes-between-jvms

https://juejin.cn/post/6844903897958449166
```

Dalvik 拥有预加载—共享机制，不同应用之间在运行时可以共享相同的类，拥有更高的效率

而 JVM 不存在这种共享机制，不同的程序，打包后的程序都是彼此独立的，

即使包中使用了同样的类，运行时也是单独加载和运行的，无法进行共享

(https://www.zhihu.com/question/20207106)

```
https://www.zhihu.com/question/43690819



### 4 源码分析

**魅族内核团队**

https://kernel.meizu.com/


**eLinux Android**

https://elinux.org/Android_Portal

https://www.infoq.cn/article/akthyldshhvho*ea0m1f
```

他表示，Android 内核起初是一个来自主线的长期稳定（LTS）版本；

这些版本结合 Android 核心的专有代码构成了Android公共内核版本。

供应商选择一个公共内核，然后添加更多的树外代码，从而创建一个特定于片上系统（SoC ）的内核，并提供给设备制造商。

```


### 5 权限问题


**特权应用权限问题**

https://stackoverflow.com/questions/19868138/what-is-the-difference-between-system-apps-and-privileged-apps-on-android

https://wrlus.com/android-security/system-apps-and-cve-2020-0391/

https://wrlus.com/android-security/android-app-protect/

https://pierrchen.blogspot.com/2016/09/an-walk-through-of-android-uidgid-based.html

https://balalals.cn/archives/android中是系统应用和非系统应用区别
```

特权应用和SELinux概念中的system_app应该不完全相同，system_app更强调其访问系统资源的能力

```


**intent机制**

https://stackoverflow.com/questions/54538924/does-setting-the-package-name-make-an-implicit-intent-explicit



**签名**

https://tinylab.org/android-signature/

https://blog.csdn.net/tkwxty/article/details/109892763



### 6 调试方法

**kernel log**

https://segmentfault.com/a/1190000038276523
```

kernel log可以使用两种方法实时打印

1 adb shell logcat -b kernel > DeskTop/kernel.log （可以输出进程号和线程号）

2 adb shell dmesg -n 8
  adb shell dmesg -T -w > DeskTop/kernel.log （标准格式）

注意在代码中打印kernel log时，调用打印方法时要在打印内容的最后添加换行符

```

**adb 命令**

https://zhuanlan.zhihu.com/p/161324514


**trace dump机制**

https://www.jianshu.com/p/6b5f8c9abd31

https://www.jianshu.com/p/f2713f371589

https://issuetracker.google.com/issues/236790598


**性能问题log分析**

https://stackoverflow.com/questions/57132218/openglrenderer-davey


https://developer.android.com/studio/profile/cpu-profiler
```

使用 CPU 性能剖析器检查 CPU 活动

跟踪Java方法调用堆栈选择 ：Sample Java Methods

跟踪native方法调用堆栈选择：Sample C/C++ Functions

```

**simpleperf火焰图**
```

ums512_1h10:/system/bin #./simpleperf record -p 564 -g -e task-clock --duration 10 --trace-offcpu

将生成的perf.data文件pull到某个路径下，在该路径下使用python执行NDK工具中的report_html.py

```

https://blog.crazytaxii.com/posts/flame_graphs/


**使用perfetto**


https://developer.android.com/studio/command-line/perfetto

https://perfetto.dev/docs/quickstart/android-tracing

https://blog.csdn.net/lezhang123/article/details/117216140
```

上述 3 个网址总结使用方法如下：

1. 编写perfetto_config.pbtx

可以使用网页版在线生成相关配置：(https://ui.perfetto.dev/#!/record)

如下是一个比较常用的：(https://www.jianshu.com/p/48b822e10453)

注意设置缓冲区大小和最大时长相关联，二者要匹配

2. 将配置文件导入	

adb push C:\Users\peng.lv\Desktop\ylog\perfetto\perfetto_config.pbtx /data/misc/perfetto-configs

3. 抓取perfetto trace

adb shell perfetto --txt -c /data/misc/perfetto-configs/perfetto_config.pbtx -o /data/misc/perfetto-traces/trace.perfetto-trace

4. 导出perfetto trace

adb pull /data/misc/perfetto-traces/trace.perfetto-trace DeskTop/ylog

5. 也可以使用record_android_trace，这是一个python脚本，具体命令可以看其中的代码

python C:\Users\peng.lv\Desktop\ylog\perfetto\record_android_trace -o DeskTop/ylog/trace_file1.perfetto-trace -t 10s -b 32mb sched am ......


```


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



### 8 Android 内存分析

**Android ION**

https://lwn.net/Articles/480055/

https://lwn.net/Articles/792733/

https://toutiao.io/posts/omeo2u/preview
```

Android ION作为一种内存管理框架被DMA-BUF取代

```

https://www.jianshu.com/p/5fe57566691f
```

ashmem在设计层面上和ion十分相似，也是先通过ashmem访问获取对应匿名内存文件的fd，最后所有的访问都是在这段内存文件上处理。

但是有一点是ashmem怎么也无法比的，那就是ion实际上是生成DMA直接访问内存。

原本ashmem的方式需要从GPU访问到CPU再到内存中的地址，但是在这里就变成了GPU直接访问修改DMA，CPU也能直接修改DMA。

其次就是那就是ion很好的处理了不同内核模块，进程之间共享内存的问题。

```


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


**const &绑定函数返回的临时值**

https://stackoverflow.com/questions/37649236/why-not-always-assign-return-values-to-const-reference



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


### 6 编译器行为


**内存地址对齐**

https://www.cnblogs.com/kn-zheng/p/17074479.html
```

编译器自身帮我们保证，会给它分配一个对齐的地址

```

https://blogs.oracle.com/solaris/post/where-does-misaligned-data-come-from

https://stackoverflow.com/questions/55867320/is-the-address-of-malloc-size-t-3-aligned-for-any-type
```

上述 2 个网址介绍了 fundamental alignment，并不是所有情况下都保证内存对齐

```



***

## CMake


### 1  概览

**cmake使用指南**

https://www.zhihu.com/column/c_200294809

**官方教程**

https://cmake.org/cmake/help/latest/guide/tutorial/

**优秀个人教程**

https://www.wilson-blog.cn/post/2021/02/12/cmake.html

https://ukabuer.me/blog/more-modern-cmake/

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

https://stackoverflow.com/questions/60605281/do-cmake-namespaces-actually-mean-anything
```

使用预置库

Using target names containing :: in a target_link_libraries(…) call 

will ensure that CMake resolves this only to so-called IMPORTED targets that are found via find_package(…). 

```

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


**霜神的博客**

https://halfrost.com/


***



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
<div align=center><b>图 1</b> XXX</div>

***


