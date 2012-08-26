#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T18:08:48
#
#-------------------------------------------------

QT       += core gui network

TARGET = LANChat
TEMPLATE = app


SOURCES += main.cpp\
        lanchatwindow.cpp \
        data/peernode.cpp \
    net/peerfinder.cpp

HEADERS  += lanchatwindow.h \
        data/peernode.h \
    net/peerfinder.h \
    net/network_defs.h

FORMS    += lanchatwindow.ui
