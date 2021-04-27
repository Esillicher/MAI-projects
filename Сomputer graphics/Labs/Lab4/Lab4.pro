#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T20:00:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab4-ex
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

RESOURCES += \
    resources.qrc

win32:LIBS += -lopengl32

