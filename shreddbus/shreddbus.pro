TEMPLATE = app
TARGET = ukshreddbus
QT += core  dbus

target.source += $$TARGET
target.path = /usr/sbin
INSTALLS += target

HEADERS += serverimplementation.h \
    ShredAdaptor.h \
    filewipe.h

SOURCES += main.cpp \
    serverimplementation.cpp \
    ShredAdaptor.cpp \
    filewipe.cpp
