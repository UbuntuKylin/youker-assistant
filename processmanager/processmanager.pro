#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T09:16:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = processmanager
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH += ../processmanager
DESTDIR = ../libs
CONFIG += link_pkgconfig
PKGCONFIG += libgtop-2.0

UI_DIR += $$PWD/../tmp/processmanager/

RCC_DIR += $$PWD/../tmp/processmanager/

MOC_DIR += $$PWD/../tmp/processmanager/

OBJECTS_DIR = $$PWD/../obj/processmanager


target.source += $$TARGET
target.path = /var/lib/youker-assistant-daemon/libs/
INSTALLS +=target

HEADERS += \
    ../component/plugininterface.h \
    processmanager.h \
    processdialog.h \
    procman.h \
    procapp.h \
    util.h \
    filelist.h \
    ../component/alertdialog.h \
    ../component/toolkits.h \
    ../component/utils.h \
    ../component/kylintitlebar.h \
    ../component/systembutton.h

SOURCES += \
    processmanager.cpp \
    processdialog.cpp \
    procman.cpp \
    util.cpp \
    filelist.cc \
    ../component/alertdialog.cpp \
    ../component/toolkits.cpp \
    ../component/kylintitlebar.cpp \
    ../component/systembutton.cpp

FORMS += \
    ../component/alertdialog.ui

RESOURCES += \
    ../mainui/img.qrc
