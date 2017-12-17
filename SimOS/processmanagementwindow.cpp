#include "processmanagementwindow.h"
#include "ui_processmanagementwindow.h"

ProcessManagementWindow::ProcessManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProcessManagementWindow)
{
    ui->setupUi(this);
}

ProcessManagementWindow::~ProcessManagementWindow()
{
    delete ui;
}
