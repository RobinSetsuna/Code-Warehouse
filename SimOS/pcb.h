#ifndef PCB_H
#define PCB_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QList>
#include <QTimer>
#include "instrc.h"


const int pageTime = 1000;      //内存与外存之间的一次交换page的IO时间，毫秒

//程序运行返回三种状态
typedef enum {
    process_running,
    process_block,
    process_terminate,
}runningState;

//PCB数据结构
typedef enum {
    PS_NEW,                 //new状态，下同
    PS_READY,
    PS_RUNNING,
    PS_WAITING,
    PS_TERMINATED,
}processState;

class PCB :public QObject{
    Q_OBJECT
private:


public:
    int pID;                //进程ID

    int runningTime;        //已运行时间
    processState state;     //进程状态

    QVector <int> pageMap;          //每两个指令占用一个页
    QVector <Instrc> instrcVec;     //指令操作集合
    QVector <Instrc>::Iterator PC;
    //int occupiedMemory;     //占用内存,按需分配是当前

    processState getState();
    int getPID();
    int getRunningTime();

    //构造函数，pid需要全局变量分配，确定虚拟地址空间(pageMap)大小
    PCB(int pid, int virtualPageSize, QString file);

    runningState run();      //返回当前进程运行一个周期后的状态
    QVector <Instrc> getInstrcSet(QString Name);    //从指令文件中读取指令信息
    ~PCB() { }

public slots:
    //void IO_Completed();
    void page_Completed();
};


#endif // PCB_H
