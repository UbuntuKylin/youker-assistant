
QT       += widgets dbus x11extras

TEMPLATE = lib
CONFIG += plugin \
          link_pkgconfig \
          C++11

DEFINES += QT_MESSAGELOGCONTEXT

include(../../env.pri)
include(../../CommonControl/CommonControl.pri)
include(../../dataworker/dataworker.pri)

TARGET = $$qtLibraryTarget(hwparam)
DESTDIR = ..
target.path = $${PLUGIN_INSTALL_DIRS}
INSTALLS += target

LIBS += -L$$[QT_INSTALL_LIBS] -lgsettings-qt
LIBS +=-lX11
LIBS +=-lXrandr
LIBS +=-ludev

PKGCONFIG     += gsettings-qt

SOURCES += \
    batteryinfo.cpp \
    bluetoothinfo.cpp \
    camerainfo.cpp \
    cdrominfo.cpp \
    faninfo.cpp \
    graphicscardinfo.cpp \
    harddiskinfo.cpp \
    hwparam.cpp \
    kabaseinfopage.cpp \
    keyboardinfo.cpp \
    maininfopage.cpp \
    memoryinfo.cpp \
    monitorinfo.cpp \
    motherboardinfo.cpp \
    mouseinfo.cpp \
    netcardinfo.cpp \
    processorinfo.cpp \
    udevhotplugin.cpp \
    voicecardinfo.cpp

HEADERS += \
    batteryinfo.h \
    bluetoothinfo.h \
    camerainfo.h \
    cdrominfo.h \
    faninfo.h \
    graphicscardinfo.h \
    harddiskinfo.h \
    hwparam.h \
    kabaseinfopage.h \
    keyboardinfo.h \
    maininfopage.h \
    memoryinfo.h \
    monitorinfo.h \
    motherboardinfo.h \
    mouseinfo.h \
    netcardinfo.h \
    processorinfo.h \
    udevhotplugin.h \
    voicecardinfo.h
