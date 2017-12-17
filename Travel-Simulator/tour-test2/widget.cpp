#include "widget.h"
#include "ui_widget.h"
#include"define.h"
#include<QDebug>
#include<QFile>
#include<QTextCodec>
#include<QString>
#include<QDateTime>
#include<QVBoxLayout>
#include<QMessageBox>
#include<QTableWidget>
#include<QGridLayout>
#include<QTimer>
#include <QPainter>
#include<QPointF>
#include<QFont>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("模拟旅行系统");
    int x[12]={802,743,779,773,805,824,845,640,706,702,840,794};
    int y[12]={222,344,397,425,242,235,149,226,318,367,321,326};
    QString c[12]={"北京","长沙","湛江","海口","衡水","天津","哈尔滨","乌鲁木齐","成都","昆明","上海","合肥"};
    QString v[3]={"火车","汽车","飞机"};
    for(int i=0;i<12;++i)
    {
        coord[0][i]=x[i];
        coord[1][i]=y[i];
        cityList[i]=c[i];
    }
    for(int i=0;i<3;++i)
    {
        way[i]=v[i];
    }

    strategy=1;
    statue=0;
    change_city=-1;

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    this->ui->lineEdit_cityStart->setFocus();
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimeSlot()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::getText()
{
    writeFile("Get data.");
    QTextCodec *code=QTextCodec::codecForName("utf8");
    QFile file(":/new/prefix1/vehicle.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"File could not be opened."<<endl;
        exit(0);
    }
    else
    {
        QTextStream fp(&file);
        fp.setCodec(code);
        for(int i=0;i<MAX_VEHNUM;i++)
        {
            fp>>veh[i].veh_type>>veh[i].site_num;
            //qDebug()<<veh[i].veh_type<<veh[i].site_num;
            for(int j=0;j<veh[i].site_num;j++)
            {
                fp>>veh[i].time_table[j].site_name>>veh[i].time_table[j].arrive_time>>veh[i].time_table[j].price;
            }

        }
    }
    file.close();

    for(int i=0;i<MAX_VEHNUM;i++)
    {
        for(int j=0;j<veh[i].site_num-1;j++)
        {
            for(int k=j+1;k<veh[i].site_num;k++)
            {
                int l;
                l=++veh_graph[veh[i].time_table[j].site_name][veh[i].time_table[k].site_name][0];
                veh_graph[veh[i].time_table[j].site_name][veh[i].time_table[k].site_name][l]=i;
            }
        }
    }
    //return 0;
}

void Widget::on_pushButton_check_clicked()
{

    city_num=checkInput();//检查输入

    if(city_num!=-1)
    {
        if(statue!=3)
        {
            QDateTime time=QDateTime::currentDateTime();//获取系统现在的时间
            QString str=time.toString("h"); //设置显示格式
            time_now=str.toInt();
            point_sum=baseGraph();
        }


        switch(strategy)
        {
            case 1:
            {
                table_col=S1();
                break;
            }
            case 2:
            {
                table_col=S2();
                break;
            }
            case 3:
            {
                table_col=S3();
                break;
            }
        }
    }
    countTime=0;
    statue=1;
    this->update();
//    writeFile_result();
}

int Widget::checkInput()
{
    QString start=this->ui->lineEdit_cityStart->text();
    QString end=this->ui->lineEdit_cityEnd->text();

    writeFile("起点："+start);
    writeFile("终点"+end);
    writeFile("策略："+QString(strategy,10));
    if(start.isEmpty()&&end.isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),tr("请输入起点和终点!"),QMessageBox::Yes);
        return -1;
    }
    else
    {
        city_sta=getCityNum(start);
        city_end=getCityNum(end);
        if(strategy==3)
        {

            QString lim=this->ui->lineEdit_limitTime->text();
            writeFile("限定时间"+lim);
            if(lim.isEmpty())
            {
                QMessageBox::warning(this,tr("Warning"),tr("请输入限制时长!"),QMessageBox::Yes);
                return -1;
            }
            else
            {
                limTime=lim.toInt();
            }
        }

        int num;
        num=setPassCity();

        return num;
    }
}

int Widget::getCityNum(QString city)
{
    if(QString::localeAwareCompare(city, QObject::tr("北京"))==0)
        return 0;
    else if(QString::localeAwareCompare(city, QObject::tr("长沙"))==0)
        return 1;
    else if(QString::localeAwareCompare(city, QObject::tr("湛江"))==0)
        return 2;
    else if(QString::localeAwareCompare(city, QObject::tr("海口"))==0)
        return 3;
    else if(QString::localeAwareCompare(city, QObject::tr("衡水"))==0)
        return 4;
    else if(QString::localeAwareCompare(city, QObject::tr("天津"))==0)
        return 5;
    else if(QString::localeAwareCompare(city, QObject::tr("哈尔滨"))==0)
        return 6;
    else if(QString::localeAwareCompare(city, QObject::tr("乌鲁木齐"))==0)
        return 7;
    else if(QString::localeAwareCompare(city, QObject::tr("成都"))==0)
        return 8;
    else if(QString::localeAwareCompare(city, QObject::tr("昆明"))==0)
        return 9;
    else if(QString::localeAwareCompare(city, QObject::tr("上海"))==0)
        return 10;
    else if(QString::localeAwareCompare(city, QObject::tr("合肥"))==0)
        return 11;
    else
        QMessageBox::warning(this,tr("Warning"),tr("请正确输入城市的名字!"),QMessageBox::Yes);
}


void Widget::on_comboBox_startegy_currentIndexChanged(int index)
{
    strategy=index+1;
}


int Widget::setPassCity()
{
    int count=0;
    pathway[0]=city_sta;
    if( ui->checkBox_beijing->isChecked() )
    {
        count++;
        pathway[count]=0;
    }
    if( ui->checkBox_changsha->isChecked() )
    {
        count++;
        pathway[count]=1;
    }
    if( ui->checkBox_zhanjiang->isChecked() )
    {
        count++;
        pathway[count]=2;
    }
    if( ui->checkBox_haikou->isChecked() )
    {
        count++;
        pathway[count]=3;
    }
    if( ui->checkBox_henshui->isChecked() )
    {
        count++;
        pathway[count]=4;
    }
    if( ui->checkBox_tianjin->isChecked() )
    {
        count++;
        pathway[count]=5;
    }
    if( ui->checkBox_haerbin->isChecked() )
    {
        count++;
        pathway[count]=6;
    }
    if( ui->checkBox_wlmqi->isChecked() )
    {
        count++;
        pathway[count]=7;
    }
    if( ui->checkBox_chendu->isChecked() )
    {
        count++;
        pathway[count]=8;
    }
    if( ui->checkBox_kunming->isChecked() )
    {
        count++;
        pathway[count]=9;
    }
    if( ui->checkBox_shanghai->isChecked() )
    {
        count++;
        pathway[count]=10;
    }
    if( ui->checkBox_heifei->isChecked() )
    {
        count++;
        pathway[count]=11;
    }
    pathway[count+1]=city_end;
    return count;
}

void Widget::clean(void)
{
    int i,j;
    for(i=0;i<5;++i)
    {
        for(j=0;j<12;++j)
        {
            route[i][j]=-1;
        }
    }
}


void Widget::qtimeSlot()
{
    QFont ft;
    ft.setPointSize(20);
    ft.setBold(true);

    if(statue==1)
    {
        timer->setInterval(10000);
        int virTime;
        virTime=time_now+countTime;
        QString s = QString::number(virTime%24, 10);
        ++countTime;
        this->ui->labeltime->setStyleSheet("font-size : 16px");
        this->ui->labeltime->setText(s+":00");

        this->update ();
    }
    else if(statue==0)
    {
        timer->setInterval(1000);
        QDateTime time=QDateTime::currentDateTime();//获取系统现在的时间
        QString str=time.toString("h"); //设置显示格式
        this->ui->labeltime->setStyleSheet("font-size : 16px");
        this->ui->labeltime->setText(str+":00");

    }

}



void Widget::on_pushButton_exit_clicked()
{
    statue=0;
    timer->setInterval(1000);
    this->update();
}


void Widget::paintEvent(QPaintEvent *event)
{
    if(statue==1)
    {
        int i;
        int time1;
        int order;
        int des=-1;
        int time_pre;
        time_pre=time_now+countTime-1;

        while((time_pre%10+(time_pre/10)%10*10)>24)
        {
            time_pre=time_pre-24+100;
        }

        for (i=0;i<table_col;i++)        //找出当前所在城市
        {
            if (route[1][i]<time_pre&&time_pre<route[1][i+1])
                des=i;
            if(route[1][i]==time_pre&&i!=0)
                des=i;
        }

        if (des==-1)                       //特殊情况
        {
            if (time_pre<route[1][0])
            {
                //printf("您现在在%s,等待前往%s的%d次%s\n",city[route[0][0]],city[route[0][1]],route[4][0],way[route[3][0]]);
                QString veh;
                QString veh_time;
                veh=QString::number(route[4][0], 10);
                veh_time=QString::number(route[1][0], 10);
                this->ui->labelstatus->setStyleSheet("font-size : 13px");
                this->ui->labelstatus->adjustSize();
                this->ui->labelstatus->setWordWrap(true);
                this->ui->labelstatus->setAlignment(Qt::AlignTop);
                this->ui->labelstatus->setText("您现在在"+cityList[route[0][0]]+",等待"+veh_time+"点出发前往"+cityList[route[0][1]]+"的第"+veh+"次"+way[route[3][0]]);

                QPainter painter(this);
                painter.setPen(Qt::red);
                painter.setBrush(Qt::red);
                painter.drawEllipse(coord[0][route[0][0]]-1.2,coord[1][route[0][0]]-1.2,6.5,6.5);
                change_city=route[0][0];
                change_time=time_pre;

            }
            else if(time_pre==route[1][0])
            {
                //printf("您现在在前往%s的第%d次%s上\n",city[route[0][1]],route[4][0],way[route[3][0]]);
                QString veh;
                veh=QString::number(route[4][0], 10);
                this->ui->labelstatus->setStyleSheet("font-size : 15px");
                this->ui->labelstatus->setText("您现在在在前往"+cityList[route[0][1]]+"的第"+veh+"次"+way[route[3][0]]+"上");

                QPainterPath path;
                path.moveTo(coord[0][route[0][0]],coord[1][route[0][0]]);
                path.lineTo(coord[0][route[0][1]],coord[1][route[0][1]]);
                QPainter painter(this);
                if(route[3][0]==0)  painter.setPen(Qt::green);
                else if(route[3][0]==1)  painter.setPen(Qt::yellow);
                else if(route[3][0]==2)  painter.setPen(Qt::blue);
                painter.drawPath(path);
                change_city=route[0][1];
                change_time=route[1][1];
            }
            else if (time_pre>=route[1][table_col])
            {
                //printf("您已经到达目的地\n");
                QPointF myPoint[1]={QPointF(coord[0][route[0][table_col]],coord[1][route[0][table_col]])};
                QPainter painter(this);
                painter.setPen(Qt::red);
                painter.drawPolygon(myPoint,1);

                this->ui->labelstatus->setStyleSheet("font-size : 15px");
                this->ui->labelstatus->setText("您已经到达目的地");
                change_city=route[0][table_col];
                statue=0;

            }
        }
        if (des!=-1)
        {
            order=route[4][des];
            for (i=0;i<=veh[order].site_num;i++)
            {
                if (veh[order].time_table[i].site_name==route[0][des])
                    time1=veh[order].time_table[i].arrive_time;
            }
            if (route[1][des]<=time_pre&&time_pre<=time1)
            {
                //printf("您现在在%s,等待前往%s的%d次%s\n",city[route[0][des]],city[route[0][des+1]],route[4][des],way[route[3][des]]);
                QString veh;
                QString veh_time;
                veh=QString::number(route[4][des], 10);
                veh_time=QString::number(time1, 10);
                this->ui->labelstatus->setStyleSheet("font-size : 13px");
                this->ui->labelstatus->setText("您现在在"+cityList[route[0][des]]+",等待"+veh_time+"点出发前往"+cityList[route[0][des+1]]+"的第"+veh+"次"+way[route[3][des]]);

                QPainter painter(this);
                painter.setPen(Qt::red);
                painter.setBrush(Qt::red);
                painter.drawEllipse(coord[0][route[0][des]]-1.2,coord[1][route[0][des]]-1.2,6.5,6.5);
                change_city=route[0][des];
                change_time=time_pre;
            }
            if (time1<time_pre&&time_pre<=route[1][des+1])
            {
                //printf("您现在在前往%s的%d次%s上\n",city[route[0][des+1]],route[4][des],way[route[3][des]]);
                QString veh;
                veh=QString::number(route[4][des], 10);
                this->ui->labelstatus->setStyleSheet("font-size : 15px");
                this->ui->labelstatus->setText("您现在在前往"+cityList[route[0][des+1]]+"的第"+veh+"次"+way[route[3][des]]+"上");

                QPainterPath path;
                path.moveTo(coord[0][route[0][des]],coord[1][route[0][des]]);
                path.lineTo(coord[0][route[0][des+1]],coord[1][route[0][des+1]]);
                QPainter painter(this);
                if(route[3][0]==0)  painter.setPen(Qt::green);
                else if(route[3][0]==1)  painter.setPen(Qt::yellow);
                else if(route[3][0]==2)  painter.setPen(Qt::blue);
                painter.drawPath(path);
                change_city=route[0][des+1];
                change_time=route[1][des+1];
            }
        }
    }
    else if(statue==0)
    {
        QPointF myPoint[1]={QPointF(coord[0][route[0][1]],coord[1][route[0][1]])};
        QPainter painter(this);
        painter.setPen(Qt::black);
        painter.drawPolygon(myPoint,1);
    }

}


void Widget::on_pushButton_change_clicked()
{
    if(statue==1)
    {
        this->update();
        time_now=change_time;
        statue=2;
        city_sta=change_city;
        this->ui->lineEdit_cityStart->setText(cityList[city_sta]);
        this->ui->lineEdit_cityEnd->setText("");
        QString s=QString::number(time_now, 10);
        QMessageBox::warning(this,tr("Warning"),"系统将以时间："+s+"为出发时间"+
                                                "，以"+cityList[city_sta]+"为起点为您重新规划线路",QMessageBox::Yes);
    this->ui->lineEdit_cityEnd->setFocus();
    this->ui->lineEdit_cityEnd->setText("");
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("请输入起点和终点!"),QMessageBox::Yes);
    }
}


void Widget::writeFile(QString eventType)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式

    QTextCodec *code=QTextCodec::codecForName("utf8");
   // QFile file(":/new/prefix1/log.txt");
    QFile file("log.txt");
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QMessageBox::critical(NULL, "提示", "无法创建文件"); 
    }
    else
    {
        QTextStream in(&file);
        in.setCodec(code);
        in<<str<<"\n";

        in << eventType << "\n";
        in.flush();
        //close the log file
        file.close();
    }

}


void Widget::writeFile_result()
{

    QTextCodec *code=QTextCodec::codecForName("utf8");
    QFile file("log.txt");
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
    }
    else
    {
        QTextStream in(&file);
        in.setCodec(code);
        //in<<str<<"\n";
        in<<"必经城市：";
        for(int i=1;i<table_col-1;++i)
        {
            in<<cityList[pathway[i]];
        }
        in<<"\n"<<"结果："<<"\n";
        int i,j;
        QString title[]={"城市","到达时间","价格","方式","班次"};
        for(i=0;i<5;++i)
        {
            in<<title[i];
            if(i!=1)
                in<<"\t";
            for(j=0;j<table_col;++j)
            {
                if(route[i][j]!=-1)
                    switch(i)
                    {
                    case 0:
                        in<<cityList[route[i][j]]<<"\t";
                        break;
                    case 3:
                        in<<way[route[i][j]]<<"\t";
                        break;
                    case 1: case 2: case 4:
                        in<<QString(route[i][j],10)<<"\t";
                        break;
                    }

            }
            in<<"\n";
        }
        in.flush();
        file.close();
    }
}














