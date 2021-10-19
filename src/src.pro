TARGET = kylin-assistant
DESTDIR = ../
TEMPLATE = app
CONFIG += c++11
#CONFIG += qt warn_on
#CONFIG += release
CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 gio-unix-2.0 gsettings-qt
QT       += core dbus network charts svg KWindowSystem x11extras

LIBS += -lukui-log4qt
LIBS +=-lX11
LIBS +=-lXrandr
LIBS +=-ludev

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets gui
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

include(./qtsingleapplication/qtsingleapplication.pri)
include(../env.pri)
include(../dataworker/dataworker.pri)
include(../commonfunc/commonfunc.pri)

DEFINES += PLUGIN_INSTALL_DIRS='\\"$${PLUGIN_INSTALL_DIRS}\\"'

SOURCES += \
    kleftsideitem.cpp \
    krightwidget.cpp \
    kleftwidget.cpp \
    main.cpp \
    imageutil.cpp \
    mainwindow.cpp \
    xatom-helper.cpp \
    kaaboutdialog.cpp

HEADERS += \
    commondef.h \
    imageutil.h \
    interface.h \
    kajsondef.h \
    kleftsideitem.h \
    krightwidget.h \
    kleftwidget.h \
    mainwindow.h \
    xatom-helper.h \
    kaaboutdialog.h

RESOURCES += \
    res.qrc

desktop.files += ../kylin-assistant.desktop
desktop.path = /usr/share/applications

target.source += $$TARGET
target.path = /usr/bin

INSTALLS +=  \
            target  \
            desktop
