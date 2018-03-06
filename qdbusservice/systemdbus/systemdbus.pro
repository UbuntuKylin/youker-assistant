QT += core dbus
QT -= gui

TARGET = kylin-assistant-qsystemdbus-service

TEMPLATE = app

CONFIG += console c++11 link_pkgconfig
CONFIG -= app_bundle

SOURCES += main.cpp \
    systemservice.cpp \
    customdata.cpp \
    customdatalist.cpp

HEADERS += \
    systemservice.h \
    customdata.h \
    customdatalist.h

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
}

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

unix {
service.files = $$PWD/data/com.kylin.assistant.qsystemdbus.service
service.path = $${PREFIX}/share/dbus-1/system-services/

dbus.files = $$PWD/data/com.kylin.assistant.qsystemdbus.conf
dbus.path = /etc/dbus-1/system.d/

binary.files = $$TARGET
binary.path = $${PREFIX}/lib/kylin-assistant/daemon/

INSTALLS += service dbus binary
}
