#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QList>
#include <QVector>
#include <pcb.h>

class Dispatcher {

private:
//    int timerCount;                 //轮询参数

    QList <PCB *> readyQueue;
    QList <PCB *> waitingQueue;
    QList <PCB *> newQueue;         //三种队列

public:
    int timerCount;                 //test

    PCB* runningProcess;            //当前运行进程

    Dispatcher(int initialTC);                   //构造放空

    bool dispatch();                //dispatch函数功能：分配队列

    bool waitingToReady(int pid);   //状态转换,只有waitingToReady需要进程id,成功返回true，失败返回false
    void runningToWaiting();
    void runningToReady();
    void newToReady();

    void appendNewProcess(PCB *newProcess);     //添加新进程
    bool isNewProcess();                        //判断是否有新进程，有进程返回true
    bool isPolling(int cycle);                  //判断是否轮询,轮询调度返回true
    void terminate();
    void increaseTimerCount(int cycle);
    void clearTimerCount();

    QVector <PCB *> getAllProcesses();          //得到所有队列中以及运行的进程
};
#endif // DISPATCHER_H
