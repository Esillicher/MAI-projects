#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T15:10:50
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab6-ex
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp

HEADERS  += window.h

RESOURCES += \
    resources.qrc

win32:LIBS += -lopengl32

