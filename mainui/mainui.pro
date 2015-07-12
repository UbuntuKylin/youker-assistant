#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T08:48:08
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = youker-assistant
DESTDIR = ../
TEMPLATE = app
CONFIG += qt \
    warn_on \
    release \
    link_pkgconfig
PKGCONFIG += opencv
INCLUDEPATH += .

include(../qtsingleapplication/src/qtsingleapplication.pri)

QMAKE_CFLAGS_DEBUG  = -g

#指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
UI_DIR += $$PWD/../tmp/

#指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
RCC_DIR += $$PWD/../tmp/

#指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
MOC_DIR += $$PWD/../tmp/

#指定目标文件(obj)的存放目录
#OBJECTS_DIR += $$PWD/../tmp/

CONFIG(debug,debug|release){
    message(debug)

    DEFINES += _DEBUG

#    DESTDIR = $$PWD/../bin/Debug
    OBJECTS_DIR = $$PWD/../obj/Debug
}

CONFIG(release,debug|release){
    message(release)

#    DESTDIR = $$PWD/../bin/Release
    OBJECTS_DIR = $$PWD/../obj/Release

    QMAKE_CFLAGS    += -Os -s
    QMAKE_CXXFLAGS  += -Os -s
}

inst1.files += res/youker-assistant.png
inst1.path = /usr/share/pixmaps
inst2.files += ../youker-assistant.desktop
inst2.path = /usr/share/applications
inst3.files += res/default/
inst3.path = /var/lib/youker-assistant-daemon/
inst4.files += res/custom/
inst4.path = /var/lib/youker-assistant-daemon/
target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    target

SOURCES += main.cpp\
    mainwindow.cpp \
    titlewidget.cpp \
    loginwidget.cpp \
    actionwidget.cpp \
    homeactionwidget.cpp \
    infoactionwidget.cpp \
    cleaneractionwidget.cpp \
    settingactionwidget.cpp \
    boxactionwidget.cpp \
    toolwidget.cpp \
    contentwidget.cpp \
    infowidget.cpp \
    cleanerwidget.cpp \
    settingwidget.cpp \
    boxwidget.cpp \
    pluginmanager.cpp \
    ../component/kylinlistmodel.cpp \
    ../component/kylinbutton.cpp \
    ../component/kylinmenu.cpp \
    ../component/kylintoolbutton.cpp \
    ../component/kylinswitcher.cpp \
    ../component/systembutton.cpp \
    ../component/kylintitlebar.cpp \
    homepage.cpp \
    ../info/systemwidget.cpp \
    ../info/desktopwidget.cpp \
    ../info/cpuwidget.cpp \
    ../info/memorywidget.cpp \
    ../info/boardwidget.cpp \
    ../info/hdwidget.cpp \
    ../info/nicwidget.cpp \
    ../info/monitorwidget.cpp \
    ../info/audiowidget.cpp \
    ../info/cdrowwidget.cpp \
    ../info/batterywidget.cpp \
    ../info/driverwidget.cpp \
    ../info/computerpage.cpp \
    ../setting/themewidget.cpp \
    ../setting/iconwidget.cpp \
    ../setting/mousewidget.cpp \
    ../setting/voicewidget.cpp \
#    ../setting/animationwidget.cpp \
    ../setting/launcherwidget.cpp \
    ../setting/panelwidget.cpp \
    ../setting/windowwidget.cpp \
    ../setting/fontwidget.cpp \
    ../setting/touchpadwidget.cpp \
#    ../setting/deadpixelwidget.cpp \
    ../setting/conservewidget.cpp \
    ../setting/nautiluswidget.cpp \
    ../component/scrollwidget.cpp \
    ../component/agentlistitem.cpp \
    ../component/quibo.cpp \
    ../component/kylinfontdialog.cpp \
    skincenter.cpp \
    ../component/kylinlistwidgetitem.cpp \
    ../component/kylinlistwidget.cpp \
    ../component/loadinglabel.cpp \
    ../component/alertdialog.cpp \
    ../component/toolkits.cpp \
    ../cleaner/cacheactionwidget.cpp \
    ../cleaner/cleanerdetailwidget.cpp \
    ../cleaner/cleanermainwidget.cpp \
    ../cleaner/cleaneritems.cpp \
    ../dbusproxy/youkersystemdbus.cpp \
    ../dbusproxy/youkersessiondbus.cpp \
    ../info/devicemanager.cpp \
    ../component/settingaction.cpp \
    autostartwidget.cpp \
    ../component/autogroup.cpp \
    kthread.cpp \
    cameramanager.cpp \
    aboutdialog.cpp \
    ../cleaner/cleanlistwidget.cpp \
    ../component/tipdialog.cpp \
    ../component/toolbutton.cpp \
    ../component/cleangroup.cpp \
    ../component/cleanbutton.cpp \
    ../component/cleansubgroup.cpp \
    ../component/cleansubbutton.cpp \
    ../component/cardwidget.cpp \
    ../component/itemcard.cpp \
    upgradedialog.cpp \
    ../component/normalwidget.cpp \
    ../component/normalcard.cpp \
    shadowwidget.cpp

HEADERS  += mainwindow.h \
    titlewidget.h \
    actionwidget.h \
    homeactionwidget.h \
    infoactionwidget.h \
    cleaneractionwidget.h \
    settingactionwidget.h \
    boxactionwidget.h \
    toolwidget.h \
    loginwidget.h \
    contentwidget.h \
    infowidget.h \
    cleanerwidget.h \
    settingwidget.h \
    boxwidget.h \
    pluginmanager.h \
    ../component/plugininterface.h \
    ../component/kylinlistmodel.h \
    ../component/utils.h \
    ../component/kylinbutton.h \
    ../component/kylinmenu.h \
    ../component/kylintoolbutton.h \
    ../component/kylinswitcher.h \
    ../component/systembutton.h \
    ../component/kylintitlebar.h \
    homepage.h \
    ../info/systemwidget.h \
    ../info/desktopwidget.h \
    ../info/cpuwidget.h \
    ../info/memorywidget.h \
    ../info/boardwidget.h \
    ../info/hdwidget.h \
    ../info/nicwidget.h \
    ../info/monitorwidget.h \
    ../info/audiowidget.h \
    ../info/cdrowwidget.h \
    ../info/batterywidget.h \
    ../info/driverwidget.h \
    ../info/computerpage.h \
    ../setting/themewidget.h \
    ../setting/iconwidget.h \
    ../setting/mousewidget.h \
    ../setting/voicewidget.h \
#    ../setting/animationwidget.h \
    ../setting/launcherwidget.h \
    ../setting/panelwidget.h \
    ../setting/windowwidget.h \
    ../setting/fontwidget.h \
    ../setting/touchpadwidget.h \
#    ../setting/deadpixelwidget.h \
    ../setting/conservewidget.h \
    ../setting/nautiluswidget.h \
    ../component/scrollwidget.h \
    ../component/agentlistitem.h \
    ../component/quibo.h \
    ../component/kylinfontdialog.h \
    skincenter.h \
    ../component/kylinlistwidgetitem.h \
    ../component/kylinlistwidget.h \
    ../component/loadinglabel.h \
    ../component/alertdialog.h \
    ../component/toolkits.h \
    ../cleaner/cacheactionwidget.h \
    ../cleaner/cleanerdetailwidget.h \
    ../cleaner/cleanermainwidget.h \
    ../cleaner/cleaneritems.h \
    ../dbusproxy/youkersystemdbus.h \
    ../dbusproxy/youkersessiondbus.h \
    ../info/devicemanager.h \
    ../component/settingaction.h \
    autostartwidget.h \
    ../component/autogroup.h \
    kthread.h \
    cameramanager.h \
    aboutdialog.h \
    ../cleaner/cleanlistwidget.h \
    ../component/tipdialog.h \
    ../component/toolbutton.h \
    ../component/cleangroup.h \
    ../component/cleanbutton.h \
    ../component/cleansubgroup.h \
    ../component/cleansubbutton.h \
    ../component/cardwidget.h \
    ../component/itemcard.h \
    upgradedialog.h \
    ../component/normalwidget.h \
    ../component/normalcard.h \
    shadowwidget.h

FORMS    += \
    ../component/quibo.ui \
    ../component/alertdialog.ui \
    autostartwidget.ui \
#    aboutdialog.ui \
    ../cleaner/cleanlistwidget.ui \
    ../cleaner/cleanerdetailwidget.ui \
    ../component/itemcard.ui \
    ../component/normalcard.ui

RESOURCES += \
    img.qrc
