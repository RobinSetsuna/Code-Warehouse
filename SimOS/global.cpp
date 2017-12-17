#include "dispatcher.h"
#include <memory.h>
#include "io_device.h"

extern const int MEM_PAGES = 10;      //物理页总数
extern const int VIRTUAL_PAGES = 50;   //虚拟地址最大长度
extern const int INSTRCS_PER_PAGE = 2; //每页指令数
extern const int POLLING_CYCLE = 4;    //轮询周期参数
extern const int OS_CYCLE = 2000;      //系统时钟周期

Dispatcher dispatcher(1);
Memory memory(MEM_PAGES);
IO_device io_device;
int MAXPID = 0;

