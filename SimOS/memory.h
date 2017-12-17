#ifndef MEMORY_H
#define MEMORY_H

#include <QList>
#include <pcb.h>


struct Page {
    bool occupiedFlag;      //标志是否占用
    int occupiedPID;        //占用程序ID

    Page() : occupiedFlag(false), occupiedPID(-1) { }
};

class Memory {
private:
    typedef QVector<Page>::iterator PageIter;
    QList <PageIter> LRUList;
public:
    Memory(int pageNum);
    QVector <Page> memory;
    bool getMemory(PCB *process, int virtualPageNO);
    void freeProcessMemory(int pid);
};

#endif // MEMORY_H
