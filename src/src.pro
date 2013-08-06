TEMPLATE = app
TARGET = youker-assistant
QT += core gui phonon declarative dbus widgets

DEPENDPATH += $$PWD/
INCLUDEPATH += $$PWD/

inst1.files += image/youker-assistant.png
inst1.path = /usr/share/pixmaps
inst2.files += ../youker-assistant.desktop
inst2.path = /usr/share/applications
target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    target

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += youker-application.h \
    quibo.h \
    systemdispatcher.h \
    sessiondispatcher.h \
    authdialog.h \
    modaldialog.h \
    warningdialog.h \
    messagedialog.h \
    qmlaudio.h \
    qrangemodel.h \
    qrangemodel_p.h \
    qstyleitem.h \
    qwheelarea.h \
    qtmenu.h \
    qtmenuitem.h \
    qtoplevelwindow.h

SOURCES += main.cpp \
    youker-application.cpp \
    quibo.cpp \
    systemdispatcher.cpp \
    sessiondispatcher.cpp \
    authdialog.cpp \
    authdialog_event.cpp \
    modaldialog.cpp \
    warningdialog.cpp \
    messagedialog.cpp \
    qmlaudio.cpp \
    qrangemodel.cpp \
    qstyleitem.cpp \
    qwheelarea.cpp \
    qtmenu.cpp \
    qtmenuitem.cpp \
    qtoplevelwindow.cpp

RESOURCES += pixmap.qrc

FORMS += \
    quibo.ui \
    authdialog.ui \
    modaldialog.ui \
    warningdialog.ui \
    messagedialog.ui
