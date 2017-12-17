#ifndef IO_DEVICE_H
#define IO_DEVICE_H
#include <QList>

struct IO_info{
    int pid;
    int left_time;
};

class IO_device
{
public:
    QList <IO_info> keyboard;
    QList <IO_info> printer;

    IO_device();
    void keyboard_in(int pid, int left_time);
    void printer_in(int pid, int left_time);
    void IO_run();
    ~IO_device();
};

#endif // IO_DEVICE_H
