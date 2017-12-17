#include "instrc.h"


Instrc::Instrc(instrcType tempType,int tempPageNO)
{
    type = tempType;
    pageNO = tempPageNO;
}

Instrc::Instrc(instrcType tempType, int tempLeftTime,int tempPageNO)  //构造函数
{
    type = tempType;
    leftTime = tempLeftTime;
    pageNO = tempPageNO;
}
Instrc::Instrc()
{

}

Instrc::~Instrc()
{

}
//Instrc(instrcType tempType, int tempLeftTime, Qstring tempFileName, int tempFileSize);  //构造函数
bool Instrc::decreaseTime()    //时长减一，成功返回true,失败则返回false表示该指令已经结束
{
    if(leftTime == 1)
        return false;
    else
    {
        leftTime--;
        return true;
    }
}

instrcType Instrc::getInstrcType() //返回指令类型
{
    return type;
}


int Instrc::getLeftTime() //返回剩余时长
{
    return leftTime;
}


QString Instrc::getFileName()
{
    return fileName;
}

int Instrc::getFileSize()
{
    return fileSize;
}

int Instrc::getPageNo() //返回指令的虚拟页号
{
    return pageNO;
}
