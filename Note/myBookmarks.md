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

**Linux BSP层实现**

https://www.zhihu.com/question/21381796

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch


* 内存管理e820
	
	https://blog.csdn.net/RichardYSteven/article/details/72566891

	https://richardweiyang-2.gitbook.io/kernel-exploring/00-memory_a_bottom_up_view


### 2  硬件层

**CPU指令与芯片**

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

**中断处理程序上下文**

https://stackoverflow.com/questions/21848340/interrupts-execution-context
```
发生中断时，CPU会切换上下文执行中断处理程序，而中断处理程序并不属于某个线程，只是内核中的某个方法，执行于中断上下文中。

发生上下文切换时，首先会保存当前执行的上下文任务，由current标记，等待中断返回时，会出现一个调度点，此时判断current是否需要调度。

(https://zhuanlan.zhihu.com/p/163728119)

(https://www.cnblogs.com/wuchanming/p/4756756.html)

```


**中断抢占问题**

https://cs.stackexchange.com/questions/29846/can-an-interrupt-handler-be-preempted
```
中断应该是可以被抢占的，但需要保证抢占不会造成错误，这取决于具体的架构实现。

```

https://stackoverflow.com/questions/11779397/what-happens-to-preempted-interrupt-handler

https://docs.microsoft.com/zh-cn/windows-hardware/drivers/kernel/always-preemptible-and-always-interruptible



### 3  实时操作系统

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

**Linux内核模块的编译和静态库的使用**

http://m.blog.chinaunix.net/uid-26246153-id-3536347.html


**初识boot**

https://askubuntu.com/questions/173248/where-is-the-bootloader-stored-in-rom-ram-or-elsewhere

**库搜索路径**

https://blog.51cto.com/u_15127658/4690108

**ls使用通配符**

https://superuser.com/questions/1416177/run-ls-recursively-with-wildcards


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

**make -C XXX M=XX**
```

在外部编译kernel模块的一种方式，首先通过-C进入到源代码树编译kernel源代码，然后返回到M变量指定目录中，也就是模块所在目录，编译当前模块

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

https://groups.google.com/g/shlug/c/nixMYtbbdZ0
```

CPU 寄存器——>内存控制器——>内存

寄存器是32位的，那么就能寻4G的空间，这也是为什么32的机器上linux(段基址为0)进程空间是4G

但是，我们有看到32的机器上也有用超过4G的内存，并且注意到进程的地址空间没有加大，还是4G

我们知道进程空间映射成页，内核可以把高于4G的内存分页映射到4G的进程地址空间

所以内存控制器的总线宽度必顺大于32位才能访问超过4G的内存

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


***


### 7 Linux驱动模型

**设备树**

https://z.itpub.net/article/detail/1C40A5E8255891E7A26173B2C28E7D31
```

Linux引入设备树主要是为了精简特定于某型号硬件主板的代码

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



**IO总线概念**

https://blog.csdn.net/zz2633105/article/details/118641075




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




## 其他资料位置

**印象笔记**

https://app.yinxiang.com/Home.action

**Chrome书签栏**

[chrome://bookmarks/](chrome://bookmarks/)

**summary文件夹**

[C:\Users\Administrator\Desktop\summary](C:\Users\Administrator\Desktop\summary)

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