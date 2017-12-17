#include "memory.h"
#include "global.h"

Memory::Memory(int pageNum) : memory(pageNum) { }

bool Memory::getMemory(PCB *process, int virtualPageNO) {
    // 检查进程页表
    QVector<int> &pm = process->pageMap;
    if (pm[virtualPageNO] != -1 && memory[pm[virtualPageNO]].occupiedFlag
        && memory[pm[virtualPageNO]].occupiedPID == process->pID) {
        // 调整LRU队列
        PageIter iter = memory.begin() + virtualPageNO;
        LRUList.removeOne(iter);
        LRUList.append(iter);
        return true;
    }

    // 需要分配内存页
    int sumPages = memory.size();
    if (sumPages > LRUList.size()) {
        // 存在空闲页
        QVector<Page>::iterator selectedPageIter = memory.begin();
        for (; selectedPageIter != memory.end() && selectedPageIter->occupiedFlag;
            ++selectedPageIter);

        selectedPageIter->occupiedFlag = true;
        selectedPageIter->occupiedPID = process->pID;
        LRUList.append(selectedPageIter);

        // 修改进程页表
        pm[virtualPageNO] = selectedPageIter - memory.begin();
    } else {
        // 需要换页
        PageIter iter = LRUList.first();

    // 修改进程页表
        pm[virtualPageNO] = iter - memory.begin();

        LRUList.removeFirst();
        iter->occupiedPID = process->pID;
        LRUList.append(iter);
    }

    // 阻塞当前进程，dispatcher需要可见!
    //dispatcher.runningToWaiting();

    // 开启定时器，将timeout绑定到对应的slot里面
    // startSingleShotTimer(...)

   // qDebug() << "return";
    return false;
}

void Memory::freeProcessMemory(int pid) {
   // qDebug()<< "process id:" << pid;
    for (QList<PageIter>::iterator iter = LRUList.begin(); iter != LRUList.end(); ++iter) {
       // qDebug() << (*iter)->occupiedPID;
    }
    for (QList<PageIter>::iterator iter = LRUList.begin(); iter != LRUList.end();) {
        if ((*iter)->occupiedPID == pid) {
            (*iter)->occupiedFlag = false;
            (*iter)->occupiedPID = -1;
            iter = LRUList.erase(iter);
        } else {
            ++iter;
        }
    }
   // qDebug() << "free end";
}
