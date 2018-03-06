QT += core dbus
QT -= gui

TARGET = kylin-assistant-qsessiondbus-service

TEMPLATE = app

CONFIG += console c++11 link_pkgconfig
CONFIG -= app_bundle

SOURCES += main.cpp \
    sessionservice.cpp \
    ./data/sessionadaptor.cpp

HEADERS += \
    sessionservice.h \
    ./data/sessionadaptor.h

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
service.files = $$PWD/data/com.kylin.assistant.qsessiondbus.service
service.path = $${PREFIX}/share/dbus-1/services/

binary.files = $$TARGET
binary.path = $${PREFIX}/lib/kylin-assistant/daemon/

INSTALLS += service binary
}
