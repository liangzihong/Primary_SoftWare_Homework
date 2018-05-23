#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T20:44:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nuclear_fission
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    view_paintlabel.cpp

HEADERS  += mainwindow.h \
    view_paintlabel.h \
    atom.h \
    neutron.h \
    nuclear.h \
    about_math.h

FORMS    += mainwindow.ui
