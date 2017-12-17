#ifndef PROCESSMANAGEMENTDIALOG_H
#define PROCESSMANAGEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class ProcessManagementDialog;
}

class ProcessManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessManagementDialog(QWidget *parent = 0);
    ~ProcessManagementDialog();

private:
    Ui::ProcessManagementDialog *ui;

private slots:
    void RefreshDialog();


};

#endif // PROCESSMANAGEMENTDIALOG_H
