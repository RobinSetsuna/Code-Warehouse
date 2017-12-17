#include "dispatcher.h"
#include "memory.h"

extern Memory memory;
Dispatcher::Dispatcher(int initialTC) {
    timerCount = initialTC;
    runningProcess = NULL;
}

//调度函数，仅调度，不负责当前运行进程的存放,轮询交给程序实现
bool Dispatcher::dispatch() {
    if (readyQueue.size() == 0) {
        //qDebug() << "no ready to dispatch";
        return false;
    }
    //qDebug() << "dispatch";
    Dispatcher::runningProcess = Dispatcher::readyQueue.takeFirst();
    if (runningProcess != NULL)
        qDebug() << "dispatch:" << runningProcess->getPID();
    if (!readyQueue.empty())
        qDebug() << "readynext:" << readyQueue.at(0)->getPID();
    runningProcess->state = PS_RUNNING;
    return true;
}

//进程状态转换
void Dispatcher::runningToReady() {
    Dispatcher::readyQueue.append(Dispatcher::runningProcess);
    Dispatcher::runningProcess->state = PS_READY;
    Dispatcher::runningProcess = NULL;
    Dispatcher::clearTimerCount();
}

void Dispatcher::runningToWaiting() {
    Dispatcher::runningProcess->state = PS_WAITING;
    Dispatcher::waitingQueue.append(Dispatcher::runningProcess);
    Dispatcher::runningProcess = NULL;
    Dispatcher::clearTimerCount();
}

bool Dispatcher::waitingToReady(int pid) {
    int i;
    for (i = 0; i < Dispatcher::waitingQueue.size(); i++) {
        if (waitingQueue.at(i) -> getPID() == pid) {
            waitingQueue.at(i)->state = PS_READY;
            Dispatcher::readyQueue.append(waitingQueue.takeAt(i));
            return true;
        }
    }
    return false;
}

void Dispatcher::newToReady() {
    int i;
    for (i = 0; i < newQueue.size(); i++) {
        readyQueue.append(newQueue.at(i));
        newQueue.at(i)->state = PS_READY;
    }
    newQueue.clear();
}

//结束当前运行进程,不进行新的分配
void Dispatcher::terminate() {
    //qDebug() << "freeMemory";
    memory.freeProcessMemory(runningProcess->getPID());
    //qDebug() << "fuck u";
    delete runningProcess;
    runningProcess = NULL;
    Dispatcher::clearTimerCount();
}

//添加新进程
void Dispatcher::appendNewProcess(PCB *newProcess) {
    Dispatcher::newQueue.append(newProcess);
}

//判断是否有新进程
bool Dispatcher::isNewProcess() {
    if (Dispatcher::newQueue.size() > 0)
        return true;
    else
        return false;
}

//返回当前所有PCB
QVector <PCB *> Dispatcher::getAllProcesses() {
    QVector <PCB *> tempVec;
    int i;
    for (i = 0; i < Dispatcher::newQueue.size(); ++i) {
        //qDebug() << "newQueue";
        tempVec.append(newQueue.at(i));
    }
    for (i = 0; i < Dispatcher::waitingQueue.size(); ++i) {
        //qDebug() << "waitingQueue";
        tempVec.append(waitingQueue.at(i));
    }
    for (i = 0; i < Dispatcher::readyQueue.size(); ++i) {
        //qDebug() << "readyQueue";
        tempVec.append(readyQueue.at(i));
    }
    if (Dispatcher::runningProcess != NULL)
        tempVec.append(Dispatcher::runningProcess);

    return tempVec;
}

bool Dispatcher::isPolling(int cycle) {
    if (Dispatcher::timerCount % cycle == 0) {
        return true;
    }
    else
        return false;
}

void Dispatcher::increaseTimerCount(int cycle) {
    timerCount++;
    timerCount%=cycle;
}

void Dispatcher::clearTimerCount() {
    Dispatcher::timerCount = 1;
}
