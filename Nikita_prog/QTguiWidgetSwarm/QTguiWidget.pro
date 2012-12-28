#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T10:46:40
#
#-------------------------------------------------

QT       += core gui

TARGET = QTguiWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ../Swarm.cpp

HEADERS  += widget.h \
    ui_widget.h \
    ../Swarm.h

FORMS    += widget.ui

OTHER_FILES += \
    HiveTrace.txt
