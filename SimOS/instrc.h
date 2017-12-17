#ifndef INSTRC_H
#define INSTRC_H
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <qtextstream.h>
#include <QString>

//const int MEM_PAGES = 100;
//const int VIRTUAL_PAGES = 200;
//const int INSTRCS_PER_PAGE = 2;

typedef enum {
    IT_COUNT,		//计算类指令
    IT_KEYBOARD,	//键盘类
    IT_PRINTER,		//打印机
    IT_READ,		//读取文件
    IT_WRITE,		//写文件
    IT_QUIT,        //结束进程***
}instrcType;

class Instrc {

private:
    instrcType type;        //指令类型
    int leftTime;           //剩余时长
    QString fileName;       //文件名？
    int fileSize;           //文件大小
    //前后指令采用容器类实现关联，此处不加指针

    int pageNO;             //指令存放虚拟页号

public:
    Instrc();
    Instrc(instrcType tempType,int tempPageNO);
    Instrc(instrcType tempType, int tempLeftTime,int tempPageNO);  //构造函数
 //   Instrc(instrcType tempType, int tempLeftTime, QString tempFileName, int tempFileSize);  //构造函数

    ~Instrc();
    bool decreaseTime();    //时长减一，成功返回true,失败则返回false表示该指令已经结束
    instrcType getInstrcType(); //返回指令类型
    int getLeftTime();          //返回剩余时长
    QString getFileName();      //返回要操作的文件名
    int getFileSize();          //返回操作文件大小
    int getPageNo(); //返回指令的虚拟页号
};
#endif // INSTRC_H
