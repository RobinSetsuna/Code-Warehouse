
#include <memory.h>
#include "global.h"

PCB::PCB(int pid, int virtualPageSize, QString Name): pID(pid), state(PS_NEW), runningTime(0), pageMap(virtualPageSize, -1), instrcVec(getInstrcSet(Name)), PC(PC = instrcVec.begin())  { MAXPID++; }

processState PCB::getState()
{
    return state;
}

int PCB::getPID()
{
    return pID;
}

int PCB::getRunningTime()
{
    return runningTime;
}

//void PCB::IO_Completed(){
//    PC++;
//    dispatcher.waitingToReady(pID);
//}

void PCB::page_Completed(){
    dispatcher.waitingToReady(pID);
}

runningState PCB::run()          //运行中进程处理
{
    if(memory.getMemory(this,PC->getPageNo())) {
        qDebug() << "内存分配成功";
        if(PC->getInstrcType() == IT_COUNT) {
            if(!PC->decreaseTime())
                PC++;
            runningTime ++;
            return process_running;
        }
        else if(PC->getInstrcType() == IT_KEYBOARD) {
            //QTimer::singleShot(PC->getLeftTime()*1000, this, SLOT(IO_Completed()));
            io_device.keyboard_in(pID, PC->getLeftTime());
            //PC ++;
            return process_block;
        }
        else if(PC->getInstrcType() == IT_PRINTER) {
            //QTimer::singleShot(PC->getLeftTime()*1000, this, SLOT(IO_Completed()));
            io_device.printer_in(pID, PC->getLeftTime());
            //PC ++;
            return process_block;
        }
        else if(PC->getInstrcType() == IT_READ) {
            //置空
        }
        else if(PC->getInstrcType() == IT_WRITE) {
            //置空
        }
        else if(PC->getInstrcType() == IT_QUIT) {
 //           qDebug() << "quit";

            return process_terminate;
        }
        else{
            PC++;
        }
    }
    else {
        //缺页中断
        qDebug() << "缺页中断";
        QTimer::singleShot(pageTime, this, SLOT(page_Completed()));
        return process_block;
    }
}


QVector <Instrc> PCB::getInstrcSet(QString Name)
{
    QVector<Instrc> Instrcset;
    QString fileName = Name;
    QString str;
    QFile file(fileName);
    //qDebug()<<"文件路径:"<<Name;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can't open";
        return Instrcset;
    }
    QTextStream in(&file);

    str=in.readLine();//读取一行//如果读取多行
    if(str.size() == 0)
    {
        //qDebug()<<"kong";
        return Instrcset;
    }
    int i = 0,Count = 0;
    int flag = 0;
    while(!str.isNull())
    {
        QString s_time = "";
        if(str.at(0) == 'C'|| str.at(0) == 'K' ||str.at(0) == 'P') //计算机、键盘、打印机指令
        {
            instrcType temp;
            if(str.at(0) == 'C')
                temp = IT_COUNT;
            else if(str.at(0) == 'K')
                temp = IT_KEYBOARD;
            else if(str.at(0) == 'P')
                temp = IT_PRINTER;

            if(str.size() <= 2)
            {
                //qDebug()<<"input invalid";
                return QVector<Instrc>();
            }
            s_time = str.mid(2);

            bool ok;
            int time = s_time.toInt(&ok,10);
            if(time == 0)
            {
                //qDebug()<<"input invalid";
                return QVector<Instrc>();
            }
            if(Count < 2)
                Count++;
            else
            {
                Count = 1;
                i++;
            }
            Instrc Instruction(temp,time,i);
            Instrcset.push_back(Instruction);

        }
        else if(str.at(0) == 'Q')
        {
            if(Count < 2)
                Count++;
            else
            {
                Count = 1;
                i++;
            }
            if(str.size() > 1)
            {
                //qDebug()<<"input invalid";
                return QVector<Instrc>();
            }
            Instrc Instruction(IT_QUIT,i);
            Instrcset.push_back(Instruction);
            flag = 1;
            break;
        }
        else
        {
            //qDebug()<<"input invalid";
            return QVector<Instrc>();
        }
        str = in.readLine();
    }
    file.close();
    if(flag == 1)
        return Instrcset;
    else
    {
        //qDebug()<<"input invalid";
        return QVector<Instrc>();
    }
}
