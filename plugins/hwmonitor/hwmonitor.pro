
QT       += widgets dbus x11extras charts

TEMPLATE = lib
CONFIG += plugin \
          link_pkgconfig \
          C++11

DEFINES += QT_MESSAGELOGCONTEXT

include(../../env.pri)
include(../../CommonControl/CommonControl.pri)
include(../../dataworker/dataworker.pri)

TARGET = $$qtLibraryTarget(hwmonitor)
DESTDIR = ..
target.path = $${PLUGIN_INSTALL_DIRS}
INSTALLS += target

LIBS += -L$$[QT_INSTALL_LIBS] -lgsettings-qt

PKGCONFIG     += gsettings-qt

SOURCES += \
    cpufmpage.cpp \
    cpufmsetwidget.cpp \
    devicemonitorpage.cpp \
    hwmonitor.cpp \
    hwmonitorwidget.cpp \
    kaprogressbar.cpp \
    katempitem.cpp \
    kausageitem.cpp

HEADERS += \
    cpufmpage.h \
    cpufmsetwidget.h \
    devicemonitorpage.h \
    hwmonitor.h \
    hwmonitorwidget.h \
    kaprogressbar.h \
    katempitem.h \
    kausageitem.h
