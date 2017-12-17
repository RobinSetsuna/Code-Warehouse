#ifndef PROCESSMANAGEMENTWINDOW_H
#define PROCESSMANAGEMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ProcessManagementWindow;
}

class ProcessManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProcessManagementWindow(QWidget *parent = 0);
    ~ProcessManagementWindow();

private:
    Ui::ProcessManagementWindow *ui;
};

#endif // PROCESSMANAGEMENTWINDOW_H
