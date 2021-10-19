
QT       += widgets dbus x11extras charts

TEMPLATE = lib
CONFIG += plugin \
          link_pkgconfig \
          C++11

DEFINES += QT_MESSAGELOGCONTEXT

include(../../env.pri)
include(../../CommonControl/CommonControl.pri)

TARGET = $$qtLibraryTarget(drivemanage)
DESTDIR = ..
target.path = $${PLUGIN_INSTALL_DIRS}
INSTALLS += target

LIBS += -L$$[QT_INSTALL_LIBS] -lgsettings-qt

PKGCONFIG     += gsettings-qt

SOURCES += \
    driveinfopage.cpp \
    drivemanage.cpp

HEADERS += \
    driveinfopage.h \
    drivemanage.h
