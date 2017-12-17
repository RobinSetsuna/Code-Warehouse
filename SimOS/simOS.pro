#-------------------------------------------------
#
# Project created by QtCreator 2017-09-17T08:50:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simOS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processmanagementdialog.cpp \
    memorymanagementdialog.cpp \
    dispatcher.cpp \
    global.cpp \
    instrc.cpp \
    pcb.cpp \
    memory.cpp \
    io_device.cpp \
    io_devicedialog.cpp

HEADERS  += mainwindow.h \
    processmanagementdialog.h \
    memorymanagementdialog.h \
    base.h \
    dispatcher.h \
    instrc.h \
    pcb.h \
    memory.h \
    global.h \
    io_device.h \
    io_devicedialog.h

FORMS    += mainwindow.ui \
    processmanagementdialog.ui \
    memorymanagementdialog.ui \
    io_devicedialog.ui

DISTFILES +=

RESOURCES += \
    qss.qrc
