# 银行营业厅模拟系统 
##### 我在大一刚开始学习编程的时候与另一个同学一起完成的这个系统，这是程序设计导论的一个课程设计大作业。主要使用C和EasyX图形库开发的银行营业厅管理系统，练习服务策略算法和过程仿真，该系统实现了以下功能<br/>
1）排队策略、银行窗口服务模拟<br/>
2）取号机和VIP身份认证<br/>
3）银行下班机制：到点停止取号，但已有客户必须服务完。<br/>
4）服务过程作文件记录。<br/>

##### 排队策略如下：
基本策略按照先来先服务原则，先到的客户必须先被服务。
###### 策略1：VIP窗口定向服务策略
VIP窗口只对VIP客户进行服务，按照先来先服务原则。
###### 策略2：VIP窗口顺便服务策略
VIP窗口在VIP客户队列为空的时候，转变为普通服务窗口，跟其他窗口一起分担处理普通客户<br/>
VIP窗口在VIP客户出现后要尽快结束普通业务的处理，为VIP客户提供服务<br/>

#### 注意
"vip.dat"文件为VIP用户的记录信息，使用"输入VIP客户资料"进行VIP客户信息的录入，使用"读取VIP客户资料"进行VIP客户信息的读取<br/>
Debug文件夹里是演示用的Debug程序，直接打开"demo.exe"即可运行,其中的"output"为日志文件。<br/>
若使用VC6打开该工程需要在VC的../include路径中添加EasyX库的头文件"graphics.h"<br/>

# Bank-Simulate-System 
##### Another classmate and I together accomplished this system when I was studying programming as an amateur. It is a course-project for Introduction to Computing and How to Program. The project was written by programming language C and used EasyX graphic library to realize graphic display. The project is intended for practicing strategic algorithm and process simulation. The following functions are accomplished.
1)Queueing strategies,bank service simulation<br/>
2)Number-generating machine and VIP identity certification<br/>
3)If the bank is not on duty, number-generating must be stopped and all the existing clients must be served before shut down.<br/>
4)Recording log file<br/>

#### Queueing strategies are as follows:
The foundamental strategy is FIFO, the first arrived must be served first.
###### Strategy1: VIP-Only strategy
VIP window only serve the VIP client.
###### Strategy2: Non-VIP-Only strategy
When VIP client queue is empty, VIP window turn out as common window to serve common client<br/>
When serving common client, if VIP arrives, VIP window must finished the task as soon as possible so as to serve the VIP client.<br/>

#### Note
"vip.dat" is the file for storing VIP info. Please use "输入VIP客户资料" to input extra client info, and "读取VIP客户资料" to display exsiting client info.<br/>
The demo program is in Debug folder. Please click "demo.exe" to see the demo. "Output" is the log file.<br/>
If you want to open the project in VC6, you need to install the EasyX library first.
