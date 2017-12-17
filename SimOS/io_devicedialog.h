#ifndef IO_DEVICEDIALOG_H
#define IO_DEVICEDIALOG_H

#include <QWidget>

namespace Ui {
class io_devicedialog;
}

class io_devicedialog : public QWidget
{
    Q_OBJECT

public:
    explicit io_devicedialog(QWidget *parent = 0);
    ~io_devicedialog();

private:
    Ui::io_devicedialog *ui;

public slots:
    void RefreshDialog();
};

#endif // IO_DEVICEDIALOG_H
