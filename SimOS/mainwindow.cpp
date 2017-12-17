#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processmanagementdialog.h"
#include "memorymanagementdialog.h"
#include "io_device.h"
#include "writeprocessdialog.h"
#include "dispatcher.h"
#include "global.h"
#include "pcb.h"
#include "instrc.h"
#include "io_devicedialog.h"
#include <QMessageBox>


//系统时间刷新
void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->Times->setText(str);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //载入QSS
    QString qss;
    QFile qssFile(":style.ss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    //系统时间
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    QTimer *timer_os = new QTimer(this);
    connect(timer_os,SIGNAL(timeout()),this,SLOT(simOS()));
    timer_os->start(OS_CYCLE);



    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//进程管理槽函数
void MainWindow::on_ProcessManagement_clicked()
{
    ProcessManagementDialog *d = new ProcessManagementDialog();
    d->show();
}

void MainWindow::on_MemoryManagement_clicked()
{
    MemoryManagementDialog *m = new MemoryManagementDialog();
    m->show();
}

void MainWindow::on_WriteProcess_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("导入进程"),
                    NULL,// ".",
                    tr("*.txt*"));

    if(fileName == NULL)
        return;
    PCB* a = new PCB(MAXPID,VIRTUAL_PAGES, fileName);
    if(a->instrcVec.size() == 0)
    {
        QMessageBox::warning(NULL, "警告", "文件内容格式错误", QMessageBox::Yes, QMessageBox::Yes);
        delete a;
        return;
    }
    //调用天飞的接口传输fileName
    dispatcher.appendNewProcess(a);
}

void MainWindow::simOS() {

    if(dispatcher.runningProcess != NULL) {

        //轮询调度
        if (dispatcher.isPolling(POLLING_CYCLE)) {
            qDebug() << "Poll";
            dispatcher.runningToReady();
            dispatcher.dispatch();
        }
        dispatcher.increaseTimerCount(POLLING_CYCLE);
        //qDebug() << "judgePolling";
        //运行程序指令
        runningState state = dispatcher.runningProcess->run();

        if (state == process_running) {
            //暂时没有操作
            //qDebug() << "process_running";
        }
        else if (state == process_block) {
            //qDebug() << "process_block";
            dispatcher.runningToWaiting();
            dispatcher.dispatch();
        }
        else if (state == process_terminate) {
            //qDebug() << "process_terminate";
            dispatcher.terminate();
            dispatcher.dispatch();              //Q指令占据单周期
        }
        else {
            return;
        }
    }
    else {
        //qDebug() << "no runningProcess, dispatch";
        dispatcher.dispatch();
        dispatcher.clearTimerCount();
    }
    //检测new队列
   //qDebug() << "is new";
    if (dispatcher.isNewProcess()) {
        dispatcher.newToReady();
    }
    qDebug() << "io_run";
    io_device.IO_run();
}

void MainWindow::on_pushButton_clicked()
{
    io_devicedialog *i = new io_devicedialog();
    i->show();
}
