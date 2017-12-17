#include "processmanagementdialog.h"
#include "ui_processmanagementdialog.h"
#include <QTimer>
#include <QTableWidgetItem>
#include <QDebug>
#include <QString>
#include "global.h"

void ProcessManagementDialog::RefreshDialog()
{
    //清空表
    ui->ProcessTableWidget->setRowCount(0);
    ui->ProcessTableWidget->clearContents();
    ui->ProcessTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ProcessTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ProcessTableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    //qDebug() << "refresh, size:" << dispatcher.getAllProcesses().size() ;
    int nRowCount;
    int flag_meet_ready = 0;
    QVector <PCB *> tempVec(dispatcher.getAllProcesses());
    for (nRowCount = 0; nRowCount<tempVec.size(); nRowCount++)
    {
        ui->ProcessTableWidget->insertRow(nRowCount);
        //pID
        if(flag_meet_ready == 0 && tempVec[nRowCount]->getState() == 1)
        {
            QTableWidgetItem* item_id = new QTableWidgetItem(QString::number(tempVec[nRowCount]->getPID()));
            item_id->setBackgroundColor(QColor(208,90,110));
            ui->ProcessTableWidget->setItem(nRowCount,0,item_id);
            flag_meet_ready = 1;
        }
        else
            ui->ProcessTableWidget->setItem(nRowCount,0,new QTableWidgetItem(QString::number(tempVec[nRowCount]->getPID())));
        //进程状态
        if(tempVec[nRowCount]->getState() == 0) {
                QTableWidgetItem* item_new = new QTableWidgetItem("New");
                item_new->setBackgroundColor(QColor(247,217,76));
                ui->ProcessTableWidget->setItem(nRowCount,1,item_new);
        }
        else if(tempVec[nRowCount]->getState() == 1){
                QTableWidgetItem* item_ready = new QTableWidgetItem("Ready");
                item_ready->setBackgroundColor(QColor(231,148,96));
                ui->ProcessTableWidget->setItem(nRowCount,1,item_ready);
        }
        else if(tempVec[nRowCount]->getState() == 2){
                QTableWidgetItem* item_running = new QTableWidgetItem("Running");
                item_running->setBackgroundColor(QColor(93,172,129));
                ui->ProcessTableWidget->setItem(nRowCount,1,item_running);
        }
        else if(tempVec[nRowCount]->getState() == 3){
                QTableWidgetItem* item_waiting = new QTableWidgetItem("Waiting");
                item_waiting->setBackgroundColor(QColor(110,117,164));
                ui->ProcessTableWidget->setItem(nRowCount,1,item_waiting);
        }
        else if(tempVec[nRowCount]->getState() == 4){
                ui->ProcessTableWidget->setItem(nRowCount,1,new QTableWidgetItem("Terminated"));
        }
        //当前执行的指令
        switch(tempVec[nRowCount]->PC->getInstrcType()) {
            case 0:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("COUNT"));
                break;
            case 1:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("KEYBOARD"));
                break;
            case 2:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("PRINTER"));
                break;
            case 3:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("READ"));
                break;
            case 4:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("WRITE"));
                break;
            case 5:
                ui->ProcessTableWidget->setItem(nRowCount,2,new QTableWidgetItem("QUIT"));
                break;
        }
        //已执行时间
        ui->ProcessTableWidget->setItem(nRowCount,3,new QTableWidgetItem(
                                            QString::number(tempVec[nRowCount]->getRunningTime())));
    }
    //ui->ProcessTableWidget->sortByColumn(0,Qt::AscendingOrder);
}

ProcessManagementDialog::ProcessManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessManagementDialog)
{
    this->setGeometry(700,180,605,771);
    //设置刷新Timer
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(RefreshDialog()));
    timer->start(1000);

    //设置窗体固定大小
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height);



    ui->setupUi(this);

}

ProcessManagementDialog::~ProcessManagementDialog()
{
    delete ui;
}

