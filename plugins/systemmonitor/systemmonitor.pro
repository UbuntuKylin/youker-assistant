#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T09:16:38
#
#-------------------------------------------------

QT += core

isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets gui svg
}

TARGET = systemmonitor
TEMPLATE = lib
DESTDIR = $$_PRO_FILE_PWD_/../
CONFIG += plugin c++11 link_pkgconfig
PKGCONFIG += libgtop-2.0 libsystemd
#gio-2.0
#LIBS +=-lgio-2.0 -lglib-2.0

target.path = $${PREFIX}/lib/kylin-assistant/plugins/
INSTALLS += target

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

HEADERS += \
    systemmonitor.h \
    ../../component/plugininterface.h \
    processmanager.h \
    processdialog.h \
    processlistwidget.h \
    processlistitem.h \
    processworker.h \
    util.h \
    ../../component/utils.h \
    ../widgets/mydialog.h \
    ../widgets/mytristatebutton.h \
    ../widgets/myunderlinebutton.h \
    ../widgets/myhoverbutton.h \
    propertiesdialog.h \
    processcategory.h \
    processdata.h \
    ../widgets/myactiongroup.h \
    ../widgets/myactiongroupitem.h \
    ../widgets/myaction.h \
    monitortitlewidget.h \
    resourcesdialog.h \
    filesystemdialog.h \
    filesystemworker.h \
    filesystemdata.h \
    ../widgets/mysearchedit.h \
    networkwidget.h \
    networkflow.h \
    cpuratewidget.h \
    cpuballwidget.h \
    smoothcurvegenerator.h \
    memorywidget.h \
    memorycircle.h \
    networkindicator.h \
    resourcesindicator.h \
    resourcescategory.h \
    filesystemlistwidget.h \
    filesystemlistitem.h \
    filesystemwatcher.h \
    renicedialog.h \
    ../../component/mytitlebar.h

SOURCES += \
    systemmonitor.cpp \
    processmanager.cpp \
    processdialog.cpp \
    processlistwidget.cpp \
    processlistitem.cpp \
    processworker.cpp \
    util.cpp \
    ../widgets/mydialog.cpp \
    ../widgets/mytristatebutton.cpp \
    ../widgets/myunderlinebutton.cpp \
    ../widgets/myhoverbutton.cpp \
    propertiesdialog.cpp \
    processcategory.cpp \
    ../widgets/myactiongroup.cpp \
    ../widgets/myactiongroupitem.cpp \
    ../widgets/myaction.cpp \
    monitortitlewidget.cpp \
    resourcesdialog.cpp \
    filesystemdialog.cpp \
    filesystemworker.cpp \
    filesystemdata.cpp \
    ../widgets/mysearchedit.cpp \
    networkwidget.cpp \
    networkflow.cpp \
    cpuratewidget.cpp \
    cpuballwidget.cpp \
    smoothcurvegenerator.cpp \
    memorywidget.cpp \
    memorycircle.cpp \
    networkindicator.cpp \
    resourcesindicator.cpp \
    resourcescategory.cpp \
    filesystemlistwidget.cpp \
    filesystemlistitem.cpp \
    filesystemwatcher.cpp \
    renicedialog.cpp \
    ../../component/mytitlebar.cpp

OTHER_FILES += \
    systemmonitor.json

RESOURCES += \
    ../../src/img.qrc
