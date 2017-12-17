#ifndef MEMORYMANAGEMENTDIALOG_H
#define MEMORYMANAGEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class MemoryManagementDialog;
}

class MemoryManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryManagementDialog(QWidget *parent = 0);
    ~MemoryManagementDialog();

private:
    Ui::MemoryManagementDialog *ui;

public slots:

    void RefreshDialog();
};

#endif // MEMORYMANAGEMENTDIALOG_H
