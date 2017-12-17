#include "memorymanagementdialog.h"
#include "ui_memorymanagementdialog.h"
#include "global.h"

void MemoryManagementDialog::RefreshDialog()
{
    //清空表
    ui->MemoryManagementWidget->setRowCount(0);
    ui->MemoryManagementWidget->clearContents();
    ui->MemoryManagementWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->MemoryManagementWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    int nRowCount;
 //   ui->MemoryManagementWidget->verticalHeader()->setVisible(false);
    for (nRowCount = 0; nRowCount<memory.memory.size(); nRowCount++)
    {
        ui->MemoryManagementWidget->insertRow(nRowCount);
        switch(memory.memory[nRowCount].occupiedFlag){
            case true:
                ui->MemoryManagementWidget->setItem(nRowCount,0,new QTableWidgetItem("Valid"));
                break;
            case false:
                ui->MemoryManagementWidget->setItem(nRowCount,0,new QTableWidgetItem("Invalid"));
                break;
        }

        ui->MemoryManagementWidget->setItem(nRowCount,1,new QTableWidgetItem(QString::number(memory.memory[nRowCount].occupiedPID)));
    }
}

MemoryManagementDialog::MemoryManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemoryManagementDialog)
{
//    this->setGeometry(630,180,300,500);
    //设置刷新Timer
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(RefreshDialog()));
    timer->start(1000);

    //设置窗体固定大小
//    int width = this->geometry().width();
//    int height = this->geometry().height();
//    this->setFixedSize(width,height);

    ui->setupUi(this);
}

MemoryManagementDialog::~MemoryManagementDialog()
{
    delete ui;
}
