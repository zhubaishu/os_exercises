#lec 3 SPOC Discussion

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
 1. 比较UEFI和BIOS的区别。
 1. 描述PXE的大致启动流程。

## 3.2 系统启动流程
 1. 了解NTLDR的启动流程。
 1. 了解GRUB的启动流程。
 1. 比较NTLDR和GRUB的功能有差异。
 1. 了解u-boot的功能。

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
“int	$0x80”是在进行系统调用，应用int指令触发软中断。SYS_write表示调用的功能号，STDOUT代表文件描述符，hello代表buffer的地址，12代表buffer的大小。这些参数被寄存器保存并在进行系统调用时应用。

 ```
  + 采分点：说明了objdump，nm，file的大致用途，说明了系统调用的具体含义
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 
 ```
 
 1. 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(w2l1)
 

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
 
