#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T08:01:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tour-test2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    define.cpp \
    strategy_1_2.cpp \
    strategy3.cpp

HEADERS  += widget.h \
    define.h \
    head.h

FORMS    += widget.ui \
    table.ui

RESOURCES += \
    resource.qrc
