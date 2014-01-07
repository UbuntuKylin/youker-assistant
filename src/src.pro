TEMPLATE = app
TARGET = youker-assistant
QT += core gui phonon declarative dbus

#DEPENDPATH += $$PWD/
#INCLUDEPATH += $$PWD/

inst1.files += image/youker-assistant.png
inst1.path = /usr/share/pixmaps
inst2.files += ../youker-assistant.desktop
inst2.path = /usr/share/applications
target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    target

include(../qtsingleapplication/src/qtsingleapplication.pri)
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
    alertdialog.h \
    toolkits.h \
    skinswidget.h \
    skingrid.h \
    locationdialog.h \
    wizarddialog.h \
    changecitydialog.h \
    util.h \
    processmanager.h \
    yprocess.h \
    sourcedialog.h \
    devicemanager.h \
    kfontdialog.h

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
    alertdialog.cpp \
    toolkits.cpp \
    skinswidget.cpp \
    skingrid.cpp \
    locationdialog.cpp \
    wizarddialog.cpp \
    changecitydialog.cpp \
    util.cpp \
    processmanager.cpp \
    yprocess.cpp \
    sourcedialog.cpp \
    devicemanager.cpp \
    kfontdialog.cpp

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
    alertdialog.ui \
    locationdialog.ui \
    wizarddialog.ui \
    changecitydialog.ui \
    sourcedialog.ui \
    kfontdialog.ui
