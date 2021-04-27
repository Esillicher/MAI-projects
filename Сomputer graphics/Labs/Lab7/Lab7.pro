#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T13:27:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab7
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    b-spline.hpp \
    bezier-spline.hpp \
    lagrange-curve.hpp

FORMS    += widget.ui
