#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T02:04:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    curve3d.hpp \
    curvepainter.hpp \
    matrix4x4.hpp \
    vector3d.hpp

FORMS    += widget.ui
