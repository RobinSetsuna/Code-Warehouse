#ifndef WRITEPROCESSDIALOG_H
#define WRITEPROCESSDIALOG_H

#include <QDialog>

namespace Ui {
class WriteProcessDialog;
}

class WriteProcessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WriteProcessDialog(QWidget *parent = 0);
    ~WriteProcessDialog();

private:
    Ui::WriteProcessDialog *ui;
};

#endif // WRITEPROCESSDIALOG_H
