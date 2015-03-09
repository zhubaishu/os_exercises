#lec 3 SPOC Discussion

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
 1. 比较UEFI和BIOS的区别。
 	 UEFI是BIOS的继任者，是为了解决BIOS的众多缺点在90年代提出的一种新的方案。特点是，相对于BIOS固定的(如针对不同的结构的磁盘需要BIOS_MBT,GBR等)，UEFI为不同平台上提供统一的服务;比BIOS安全，可以抵御bootkit攻击;启动快。
 1. 描述PXE的大致启动流程。
   	1.客户端个人电脑开机后,在TCP/IP Bootrom 获得控制权之前先做自我测试。
  	2.Bootprom 送出BOOTP/DHCP要求以取得IP。
  	3.如果服务器收到个人电脑所送出的要求,就会送回BOOTP/DHCP回应,内容包括客户端的IP地址,预设网关,及开机映像文件。否则，服务器会忽略这个要求。
  	4.Bootprom由TFTP通讯协议从服务器下载开机映像文件。
  	5.个人电脑通过这个开机映像文件开机,这个开机文件可以只是单纯的开机程式也可以是操作系统。
  	6.开机映像文件将包含kernel loader及压缩过的kernel,此kernel将支持NTFS root系统。
  	7.远程客户端根据下载的文件启动机器。


## 3.2 系统启动流程
 1. 了解NTLDR的启动流程。
     NTLDR文件的是一个隐藏的，只读的系统文件，位置在系统盘的根目录，用来装载操作系统。
     一般情况系统的引导过程是这样:
     1.电源自检程序开始运行
     2.主引导记录被装入内存，并且程序开始执行
     3.活动分区的引导扇区被装入内存
     4.NTLDR从引导扇区被装入并初始化
     5.将处理器的实模式改为32位平滑内存模式
     6.NTLDR开始运行适当的小文件系统驱动程序。小文件系统驱动程序是建立在NTLDR内部的，它能读FAT或NTFS。
     7.NTLDR读boot.ini文件
     8.NTLDR装载所选操作系统
     	如果windows NT/windows 2000/windows XP/windows server 2003这些操作系统被选择，NTLDR运行Ntdetect。
     	对于其他的操作系统，NTLDR装载并运行Bootsect.dos然后向它传递控制。
     	windows NT过程结束。
     9.Ntdetect搜索计算机硬件并将列表传送给NTLDR，以便将这些信息写进\\HKE Y_LOCAL_MACHINE\HARDWARE中。
     10.然后NTLDR装载Ntoskrnl.exe，Hal.dll和系统信息集合。
     11.Ntldr搜索系统信息集合，并装载设备驱动配置以便设备在启动时开始工作
     12.Ntldr把控制权交给Ntoskrnl.exe，这时,启动程序结束,装载阶段开始
 1. 了解GRUB的启动流程。
     硬盘启动以后转向MBR，装载GRUB。GRUB再将控制权给实际操作系统。
 1. 比较NTLDR和GRUB的功能有差异。
     NTLDR功能单一，不能启动其他系统；NTLDR的MBR仅仅是指向操作系统所在的分区中的扇区。
 1. 了解u-boot的功能。
     Universal Boot Loader，可以充当bootloader也可以通过特殊手段从PC机中下载到目标板中（下载模式）。

## 3.3 中断、异常和系统调用比较
 1. 举例说明Linux中有哪些中断，哪些异常？
 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)
 一、进程控制：
	     fork	创建一个新进程
	     clone	按指定条件创建子进程
	     execve	运行可执行文件
	     exit	中止进程
	     _exit	立即中止当前进程
 二、文件系统控制
	     open	打开文件
	     creat	创建新文件
	     close	关闭文件描述字
	     read	读文件
	     write	写文件
	     readv	从文件读入数据到缓冲数组中
	     writev	将缓冲数组里的数据写入文件
三、系统控制
	     ioctl	I/O总控制函数
	     _sysctl	读/写系统参数
	     acct	启用或禁止进程记账
	     getrlimit	获取系统资源上限
四、内存管理
	    brk	改变数据段空间的分配
	    sbrk	参见brk
	    mlock	内存页面加锁
	    munlock	内存页面解锁
五、网络管理
	    getdomainname	取域名
	    setdomainname	设置域名
	    gethostid	获取主机标识号
	    sethostid	设置主机标识号
六、socket控制
	    socket	建立socket
	    bind	绑定socket到端口
	    connect	连接远程主机
	    accept	响应socket连接请求
	    send	通过socket发送信息
七、用户管理
	    getuid	获取用户标识号
	    setuid	设置用户标志号
	    getgid	获取组标识号
	    setgid	设置组标志号
八、进程间通信
	    sigaction	设置对指定信号的处理方法
	    sigprocmask	根据参数对信号集中的信号执行阻塞/解除阻塞等操作
	    sigpending	为指定的被阻塞信号设置队列
	    sigsuspend	挂起进程等待特定信号
```
  + 采分点：说明了Linux的大致数量（上百个），说明了Linux系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
 1. 以ucore lab8的answer为例，uCore的系统调用有哪些？大致的功能分类有哪些？(w2l1)
 答： ucore 中系统调用有22个
	
	进程控制：	
    			exit
    			fork
    			getpid
    			exec
    			wait
				yield
    			kill
				sleep

	文件操作：
				open
    			close
    			read
    			write
    			seek
    			fstat
    			fsync
				putc
				pgdir
				getcwd
				getdirentry
				dup

	系统控制：
				gettime
				lab6_set_priority

 
 ```
  + 采分点：说明了ucore的大致数量（二十几个），说明了ucore系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.4 linux系统调用分析
 1. 通过分析[lab1_ex0](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex0.md)了解Linux应用的系统调用编写和含义。(w2l1)
 objdump：objdump命令是Linux下的反汇编目标文件或者可执行文件的命令，可以以一种可阅读的格式让用户更多地了解二进制文件可能带有的  附加信息。
     4003b3:	48 85 c0             	test   %rax,%rax
     4003b6:	74 05                	je     4003bd <_init+0x15>
     4003b8:	e8 33 00 00 00       	callq  4003f0 <__gmon_start__@plt>
     4003bd:	48 83 c4 08          	add    $0x8,%rsp
 nm：用来列出目标文件的符号清单。
     0000000000000006 a SYS_close
     000000000000003f a SYS_dup2
     000000000000000b a SYS_execve
     0000000000000001 a SYS_exit
     0000000000000002 a SYS_fork
 file：file是检测文件类型的命令，即文件组织的方式，通常不同的文件类型执行不同的标准。 

系统调用的编写和含义：
“int	$0x80”是在进行系统调用，应用int指令触发软中断。SYS_write表示调用的功能号，STDOUT代表文件描述符，hello代表buffer的地址，12代表buffer的大小。这些参数被寄存器(%eax,%ebx,%ecx,%edx)保存并在进行系统调用时应用。并且返回值保存在%eax中。
代码解释：
		.include "defines.h"          // defines.h 中包含各个中断号
		.data	 					  // 数据段声明
		hello:
			.string "hello world\n"	  // hello为要输出的字符串

		.globl	main	   			  
		main:
			movl	$SYS_write,%eax	  
			movl	$STDOUT,%ebx	 
			movl	$hello,%ecx		  
			movl	$12,%edx		  
			int	$0x80		//  系统调用
			ret

 ```
  + 采分点：说明了objdump，nm，file的大致用途，说明了系统调用的具体含义
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 
 ```
 
 1. 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(w2l1)
 strace：用来跟踪进程执行时的系统调用和所接收的信号，可以跟踪到一个进程产生的系统调用,包括参数，返回值，执行消耗的时间。
系统调用的具体执行过程 ：
	用户程序调用C库API（C库中封装有 INT 0x80 软中断指令）
	若该C库API需要进行系统调用，则会使用INT 0x80软中断指令
	INT 0x80 这条指令的执行会让系统跳转到一个预设的内核空间地址，即system_call函数
	system_call 根据具体的系统调用号，查找系统调用表，转到执行具体的系统调用服务例程
	CPU执行该系统服务例程
	当系统调用完成后，把控制权交回到发起调用的用户进程前
 

 ```
  + 采分点：说明了strace的大致用途，说明了系统调用的具体执行过程（包括应用，CPU硬件，操作系统的执行过程）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.5 ucore系统调用分析
 1. ucore的系统调用中参数传递代码分析。
 1. ucore的系统调用中返回结果的传递代码分析。
 1. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
 1. 以ucore lab8的answer为例，尝试修改并运行代码，分析ucore应用的系统调用执行过程。
 
## 3.6 请分析函数调用和系统调用的区别
 1. 请从代码编写和执行过程来说明。
   1. 说明`int`、`iret`、`call`和`ret`的指令准确功能
 
