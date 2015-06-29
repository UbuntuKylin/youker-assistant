#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T09:16:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shredmanager
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH += ../shredmanager
DESTDIR = ../libs

UI_DIR += $$PWD/../tmp/shredmanager/

RCC_DIR += $$PWD/../tmp/shredmanager/

MOC_DIR += $$PWD/../tmp/shredmanager/

OBJECTS_DIR = $$PWD/../obj/shredmanager

target.source += $$TARGET
target.path = /var/lib/youker-assistant-daemon/libs/
INSTALLS +=target

HEADERS += \
    filewipe.h \
    ../component/plugininterface.h \
    shredmanager.h \
    shreddialog.h \
    ../component/toolkits.h \
    ../component/alertdialog.h \
    ../component/utils.h \
    ../component/toolkits.h \
    ../component/kylintitlebar.h \
    ../component/systembutton.h \
    ../component/kylineditbutton.h

SOURCES += \
    filewipe.cpp \
    shredmanager.cpp \
    shreddialog.cpp \
    ../component/alertdialog.cpp \
    ../component/toolkits.cpp \
    ../component/kylintitlebar.cpp \
    ../component/systembutton.cpp \
    ../component/kylineditbutton.cpp

FORMS += \
    ../component/alertdialog.ui

RESOURCES += \
    ../mainui/img.qrc
