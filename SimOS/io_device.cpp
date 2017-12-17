#include "io_device.h"
#include <QDebug>
#include "global.h"


IO_device::IO_device() { }

void IO_device::keyboard_in(int pid, int left_time)
{
    IO_info info;
    info.left_time = left_time;
    info.pid = pid;
    keyboard.append(info);
    //qDebug() << "添加进入keyboard " << "pid:" << pid;
}

void IO_device::printer_in(int pid, int left_time)
{
    IO_info info;
    info.left_time = left_time;
    info.pid = pid;
    printer.append(info);
    //qDebug() << "添加进入printer " << "pid:" << pid;
}

void IO_device::IO_run()
{
    //qDebug() << "in io_run";
    if(!keyboard.isEmpty())
    {
        //qDebug() << "keyboard";
        if(keyboard.front().left_time == 1)
        {
            //qDebug() << "keyboard出列 " << "pid:" << keyboard.front().pid;
            dispatcher.waitingToReady(keyboard.front().pid);
            for(int i = 0; i < dispatcher.getAllProcesses().size(); i++)
            {
                if(dispatcher.getAllProcesses().at(i)->getPID() == keyboard.front().pid)
                {
                    dispatcher.getAllProcesses().at(i)->PC ++;
                }
            }
            keyboard.pop_front();
        }
        else
            keyboard.front().left_time --;
    }

    if(!printer.isEmpty())
    {
        qDebug() << "in printer";
        if(printer.front().left_time == 1)
        {
            //qDebug() << "out list";
            //qDebug() << "printer出列 " << "pid:" << printer.front().pid;
            dispatcher.waitingToReady(printer.front().pid);
            //qDebug() << "waitingToReady" << printer.front().pid;
            QVector<PCB *> tempVec(dispatcher.getAllProcesses());
            for(int i = 0; i < tempVec.size(); i++)
            {
                //qDebug() << "judge";
                if(tempVec.at(i)->getPID() == printer.front().pid)
                {
                    tempVec.at(i)->PC ++;
                }
            }
            //qDebug() << "PC ++";
            printer.pop_front();
        }
        else
            printer.front().left_time --;
    }
}

IO_device::~IO_device()
{

}
