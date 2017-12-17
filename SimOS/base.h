#ifndef BASE_H
#define BASE_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QList>

//const int MEM_PAGES = 100;      //物理页总数
//const int VIRTUAL_PAGES = 50;   //虚拟地址最大长度
//const int INSTRCS_PER_PAGE = 2; //每页指令数
//const int POLLING_CYCLE = 4;    //轮询周期参数

//int MAXPID;             //最大ID号
//Dispatcher dispatcher;  //全局调度器
//Memory memory;          //全局内存
//class PCB;

//class base
//{
//public:
//    base();
//};

////////////////////////////////////////////////////////////
////指令数据结构
//typedef enum {
//    IT_COUNT,		//计算类指令
//    IT_KEYBOARD,	//键盘类
//    IT_PRINTER,		//打印机
//    IT_READ,		//读取文件
//    IT_WRITE,		//写文件
//    IT_QUIT,        //结束进程***
//}instrcType;


////程序运行返回三种状态
//enum {
//    process_running,
//    process_block,
//    process_terminate,
//};

//class Instrc {

//private:
//    instrcType type;        //指令类型
//    int leftTime;           //剩余时长
//    QString fileName;       //文件名？
//    int fileSize;           //文件大小
//    //前后指令采用容器类实现关联，此处不加指针

//    int pageNO;             //指令存放虚拟页号

//public:
//    Instrc(instrcType tempType, int tempLeftTime);  //构造函数
//    Instrc(instrcType tempType, int tempLeftTime, QString tempFileName, int tempFileSize);  //构造函数
//    bool decreaseTime();    //时长减一，成功返回true,失败则返回false表示该指令已经结束

//    instrcType getInstrcType(); //返回指令类型
//    int getLeftTime();          //返回剩余时长
//    QString getFileName();      //返回要操作的文件名
//    int getFileSize();          //返回操作文件大小
//};


//////////////////////////////////////////////////////////
//页数据结构,内存
//struct Page {
//    bool occupiedFlag;      //标志是否占用
//    int occupiedPID;        //占用程序ID

//    Page() : occupiedFlag(false), occupiedPID(-1) { }
//};

//class Memory {

//private:



//public:
//    QVector <Page> memory;      //表示内存

//    QList <QVector <Page>::Iterator> LRUList;   //用于LRU算法

//    Memory (int pageNum);    //构造函数，参数是总page数，并初始化迭代器

//    bool getMemory(PCB *process, int virtualPageNO);//注意修改PCB状态
//    void freeProcessMemory(int pid);//释放进程占用内存
//};


//////////////////////////////////////////////////////////////
//PCB数据结构
//typedef enum {
//    PS_NEW,                 //new状态，下同
//    PS_READY,
//    PS_RUNNING,
//    PS_WAITING,
//    PS_TERMINATED,
//}processState;

//class PCB :public QObject{
//    Q_OBJECT
//private:
//    int pID;                //进程ID
//    int runningTime;        //已运行时间
//    processState state;     //进程状态

//public:
//    //int occupiedMemory;     //占用内存,按需分配是当前

//    QVector <int> pageMap;          //每两个指令占用一个页
//    QVector <Instrc> instrcVec;     //指令操作集合
//    QVector <Instrc>::Iterator PC;

//    processState getState();
//    int getPID();
//    int getRunningTime();

//    //构造函数，pid需要全局变量分配，确定虚拟地址空间(pageMap)大小
//    PCB(int pid, int virtualPageSize): pID(pid), pageMap(virtualPageSize, -1) { }

//    int run();      //返回当前进程运行一个周期后的状态
//    QVector <Instrc> getInstrcSet();    //从指令文件中读取指令信息
//    ~PCB() { }

//public slots:
//    void IO_Completed();
//    void page_Completed();
//};

//////////////////////////////////////////////////////////
//队列结构

//class Dispatcher {

//private:

//    QList <PCB *> readyQueue;
//    QList <PCB *> waitingQueue;
//    QList <PCB *> newQueue;         //三种队列

//public:
//    int TimerCount;                 //轮询参数
//    PCB* runningProcess;            //当前运行进程

//    Dispatcher();                   //构造放空

//    PCB* dispatch();                //dispatch函数功能：分配队列

//    bool waitingToReady(int pid);   //状态转换,只有waitingToReady需要进程id,成功返回true，失败返回false
//    void runningToWaiting();
//    void runningToReady();
//    void newToReady();

//    void appendNewProcess(PCB *newProcess);     //添加新进程
//    bool isNewProcess();                        //判断是否有新进程，有进程返回true
//    bool isPolling();                           //判断是否轮询,轮询调度返回true
//    bool terminate();

//    QVector <PCB *> getAllProcesses();          //得到所有队列中以及运行的进程
//};

#endif // BASE_H
