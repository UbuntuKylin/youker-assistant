TEMPLATE = app
TARGET = youker-assistant
QT += core gui phonon declarative dbus

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
LIBS += -lfcitx-qt -lfcitx-config -lfcitx-utils

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += youker-application.h \
    quibo.h \
    systemdispatcher.h \
    sessiondispatcher.h \
    sudodispatcher.h \
    authdialog.h \
    modaldialog.h \
    warningdialog.h \
    messagedialog.h \
    updatedialog.h \
    qmlaudio.h \
    qrangemodel.h \
    qrangemodel_p.h \
    qstyleitem.h \
    qwheelarea.h \
    qtmenu.h \
    qtmenuitem.h \
    qtoplevelwindow.h \
    qcursorarea.h \
    qtooltiparea.h \
    qtmenubar.h \
    qwindowitem.h \
    qtsplitterbase.h \
    settings.h \
    qdeclarativelinearlayout.h \
    qdeclarativefolderlistmodel.h \
    qdeclarativelayout.h \
    qdeclarativelayoutengine_p.h \
    qdesktopitem.h \
    tray.h \
    fcitxcfgwizard.h \
    qtkeytrans.h \
    qtkeytransdata.h \
    fcitxwarndialog.h \
    KThread.h \
    suspensionframe.h \
    progressdialog.h \
    alertdialog.h \
    toolkits.h

SOURCES += main.cpp \
    youker-application.cpp \
    quibo.cpp \
    systemdispatcher.cpp \
    sessiondispatcher.cpp \
    sudodispatcher.cpp \
    authdialog.cpp \
    authdialog_event.cpp \
    modaldialog.cpp \
    warningdialog.cpp \
    messagedialog.cpp \
    updatedialog.cpp \
    qmlaudio.cpp \
    qrangemodel.cpp \
    qstyleitem.cpp \
    qwheelarea.cpp \
    qtmenu.cpp \
    qtmenuitem.cpp \
    qtoplevelwindow.cpp \
    qcursorarea.cpp \
    qtooltiparea.cpp \
    qtmenubar.cpp \
    qwindowitem.cpp \
    qtsplitterbase.cpp \
    settings.cpp \
    qdeclarativelinearlayout.cpp \
    qdeclarativefolderlistmodel.cpp \
    qdeclarativelayout.cpp \
    qdeclarativelayoutengine.cpp \
    qdesktopitem.cpp \
    tray.cpp \
    fcitxcfgwizard.cpp \
    qtkeytrans.cpp \
    fcitxwarndialog.cpp \
    KThread.cpp \
    suspensionframe.cpp \
    progressdialog.cpp \
    alertdialog.cpp \
    toolkits.cpp
RESOURCES += pixmap.qrc

FORMS += \
    quibo.ui \
    authdialog.ui \
    modaldialog.ui \
    warningdialog.ui \
    messagedialog.ui \
    updatedialog.ui \
    tray.ui \
    fcitxwarndialog.ui \
    suspensionframe.ui \
    progressdialog.ui \
    alertdialog.ui
