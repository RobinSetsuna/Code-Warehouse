#include "io_devicedialog.h"
#include "ui_io_devicedialog.h"
#include "io_device.h"
#include "global.h"

void io_devicedialog::RefreshDialog()
{
    //清空表
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->keybordWidget->setRowCount(0);
    ui->keybordWidget->clearContents();
    ui->keybordWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->keybordWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->keybordWidget->setSelectionMode(QAbstractItemView::NoSelection);

    int nRowCount;
    //ui->MemoryManagementWidget->verticalHeader()->setVisible(false);
    for (nRowCount = 0; nRowCount<io_device.keyboard.size(); nRowCount++)
    {
        if (nRowCount == 0) {
            ui->tableWidget->insertRow(nRowCount);
            QTableWidgetItem* pid = new QTableWidgetItem(QString::number(io_device.keyboard[nRowCount].pid));
            pid->setBackgroundColor(QColor(93,172,129));
            ui->tableWidget->setItem(nRowCount,0,pid);
            QTableWidgetItem* left_time = new QTableWidgetItem(QString::number(io_device.keyboard[nRowCount].left_time));
            left_time->setBackgroundColor(QColor(93,172,129));
            ui->tableWidget->setItem(nRowCount,1,left_time);
        }
        else {
            ui->tableWidget->insertRow(nRowCount);
            QTableWidgetItem* pid = new QTableWidgetItem(QString::number(io_device.keyboard[nRowCount].pid));
            ui->tableWidget->setItem(nRowCount,0,pid);
            QTableWidgetItem* left_time = new QTableWidgetItem(QString::number(io_device.keyboard[nRowCount].left_time));
            ui->tableWidget->setItem(nRowCount,1,left_time);
        }
    }

    for (nRowCount = 0; nRowCount<io_device.printer.size(); nRowCount++)
    {
        if (nRowCount == 0) {
            ui->keybordWidget->insertRow(nRowCount);
            QTableWidgetItem* pid = new QTableWidgetItem(QString::number(io_device.printer[nRowCount].pid));
            pid->setBackgroundColor(QColor(93,172,129));
            ui->keybordWidget->setItem(nRowCount,0,pid);
            QTableWidgetItem* left_time = new QTableWidgetItem(QString::number(io_device.printer[nRowCount].left_time));
            left_time->setBackgroundColor(QColor(93,172,129));
            ui->keybordWidget->setItem(nRowCount,1,left_time);
        }
        else {
            ui->keybordWidget->insertRow(nRowCount);
            QTableWidgetItem* pid = new QTableWidgetItem(QString::number(io_device.printer[nRowCount].pid));
            ui->keybordWidget->setItem(nRowCount,0,pid);
            QTableWidgetItem* left_time = new QTableWidgetItem(QString::number(io_device.printer[nRowCount].left_time));
            ui->keybordWidget->setItem(nRowCount,1,left_time);
        }
    }
}

io_devicedialog::io_devicedialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::io_devicedialog)
{
    //this->setGeometry(700,180,700,470);
    //设置刷新Timer
    QTimer *io_timer = new QTimer(this);
    connect(io_timer,SIGNAL(timeout()),this,SLOT(RefreshDialog()));
    io_timer->start(1000);

    //设置窗体固定大小
//    int width = this->geometry().width();
//    int height = this->geometry().height();
//    this->setFixedSize(width,height);
    ui->setupUi(this);
}

io_devicedialog::~io_devicedialog()
{
    delete ui;
}
