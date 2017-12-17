#ifndef GLOBAL_H
#define GLOBAL_H


#include "dispatcher.h"
#include <memory.h>
#include "io_device.h"

extern const int MEM_PAGES;      //物理页总数
extern const int VIRTUAL_PAGES;   //虚拟地址最大长度
extern const int INSTRCS_PER_PAGE; //每页指令数
extern const int POLLING_CYCLE;    //轮询周期参数
extern const int OS_CYCLE;

extern Dispatcher dispatcher;
extern Memory memory;
extern int MAXPID;
extern IO_device io_device;


#endif // GLOBAL_H
