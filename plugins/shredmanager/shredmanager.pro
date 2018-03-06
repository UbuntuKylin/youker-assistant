#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T09:16:38
#
#-------------------------------------------------

QT       += core
isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets gui
}


TARGET = shredmanager
TEMPLATE = lib
CONFIG += plugin c++11
DESTDIR = $$_PRO_FILE_PWD_/../

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

target.path = $${PREFIX}/lib/kylin-assistant/plugins/
INSTALLS += target

HEADERS += \
    filewipe.h \
    ../../component/plugininterface.h \
    shredmanager.h \
    shreddialog.h \
    ../../component/toolkits.h \
    ../../component/alertdialog.h \
    ../../component/utils.h \
    ../../component/toolkits.h \
    ../../component/mytitlebar.h \
    ../../component/systembutton.h \
    ../../component/kylineditbutton.h \
    ../widgets/mytristatebutton.h

SOURCES += \
    filewipe.cpp \
    shredmanager.cpp \
    shreddialog.cpp \
    ../../component/alertdialog.cpp \
    ../../component/toolkits.cpp \
    ../../component/mytitlebar.cpp \
    ../../component/systembutton.cpp \
    ../../component/kylineditbutton.cpp \
    ../widgets/mytristatebutton.cpp

OTHER_FILES += \
    shred.json

FORMS += \
    ../../component/alertdialog.ui

RESOURCES += \
    ../../src/img.qrc
