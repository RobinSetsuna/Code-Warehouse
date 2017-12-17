#include "writeprocessdialog.h"
#include "ui_writeprocessdialog.h"

WriteProcessDialog::WriteProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteProcessDialog)
{
    ui->setupUi(this);
}

WriteProcessDialog::~WriteProcessDialog()
{
    delete ui;
}
