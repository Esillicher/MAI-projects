#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T22:45:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab5
TEMPLATE = app

SOURCES += main.cpp \
    widget.cpp \
    mesh.cpp

HEADERS  += widget.h \
    mesh.h

RESOURCES += \
    resources.qrc

win32:LIBS += -lopengl32

