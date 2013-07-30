TEMPLATE = app
TARGET = youker-assistant
QT += declarative dbus widgets
DEPENDPATH += $$PWD/
INCLUDEPATH += $$PWD/

inst1.files += image/youker-assistant.png
inst1.path = /usr/share/pixmaps
inst2.files += ../youker-assistant.desktop
inst2.path = /usr/share/applications
#inst3.files += ./libstyleplugin.so
#inst3.path = /usr/lib/i386-linux-gnu/qt4/imports/QtDesktop/plugin/
target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    target

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH = /usr/lib/i386-linux-gnu/qt4/imports/Qt/labs/components/plugin
QML_IMPORT_PATH = /usr/lib/i386-linux-gnu/qt4/imports/QtDesktop/plugin

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += youker-application.h \
    quibo.h \
    systemdispatcher.h \
    sessiondispatcher.h \
    authdialog.h \
    modaldialog.h \
    warningdialog.h \
    messagedialog.h

SOURCES += main.cpp \
    youker-application.cpp \
    quibo.cpp \
    systemdispatcher.cpp \
    sessiondispatcher.cpp \
    authdialog.cpp \
    authdialog_event.cpp \
    modaldialog.cpp \
    warningdialog.cpp \
    messagedialog.cpp


OTHER_FILES += youker-assistant/ihu.png

RESOURCES += pixmap.qrc

FORMS += \
    quibo.ui \
    authdialog.ui \
    modaldialog.ui \
    warningdialog.ui \
    messagedialog.ui
