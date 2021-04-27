#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T00:43:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    body.cpp

HEADERS  += widget.h \
    tetraeder.hpp \
    piramid.h \
    n_prizm.h \
    paraboloid.h \
    body.h


FORMS    += widget.ui
