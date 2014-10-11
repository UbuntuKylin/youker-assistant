TEMPLATE = app
LANGUAGE = C++
TARGET = youker-assistant
QT += core gui declarative dbus xml

CONFIG += qt \
    warn_on \
    release
INCLUDEPATH += .

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

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += homepage.h \
    topbar.h \
    tabbar.h \
    contentfield.h \
    bottombar.h \
    messengerproxy.h \
    kbutton.h \
    icontext.h \
    slidershow.h \
    newcharacter.h \
    quibo.h \
    accountcache.h \
    systemdispatcher.h \
    sessiondispatcher.h \
    modaldialog.h \
    warningdialog.h \
    qrangemodel.h \
    qrangemodel_p.h \
    qstyleitem.h \
    qwheelarea.h \
    qtmenu.h \
    qtmenuitem.h \
    qtoplevelwindow.h \
    qcursorarea.h \
    tray.h \
    kthread.h \
    selectdialog.h \
    weatherdb.h \
    suspensionframe.h \
    alertdialog.h \
    toolkits.h \
    util.h \
    processmanager.h \
    yprocess.h \
    devicemanager.h \
    kfontdialog.h \
    aboutdialog.h \
    commonobject.h \
    clounddispatcher.h \
    monitordispatcher.h \
    acceleratedispatcher.h \
    httpdownload.h \
    shreddispatcher.h

SOURCES += main.cpp \
    homepage.cpp \
    topbar.cpp \
    tabbar.cpp \
    contentfield.cpp \
    bottombar.cpp \
    messengerproxy.cpp \
    kbutton.cpp \
    icontext.cpp \
    slidershow.cpp \
    newcharacter.cpp \
    accountcache.cpp \
    quibo.cpp \
    systemdispatcher.cpp \
    sessiondispatcher.cpp \
    modaldialog.cpp \
    warningdialog.cpp \
    qrangemodel.cpp \
    qstyleitem.cpp \
    qwheelarea.cpp \
    qtmenu.cpp \
    qtmenuitem.cpp \
    qtoplevelwindow.cpp \
    qcursorarea.cpp \
    tray.cpp \
    kthread.cpp \
    selectdialog.cpp \
    weatherdb.cpp \
    suspensionframe.cpp \
    alertdialog.cpp \
    toolkits.cpp \
    util.cpp \
    processmanager.cpp \
    yprocess.cpp \
    devicemanager.cpp \
    kfontdialog.cpp \
    aboutdialog.cpp \
    commonobject.cpp \
    clounddispatcher.cpp \
    monitordispatcher.cpp \
    acceleratedispatcher.cpp \
    httpdownload.cpp \
    shreddispatcher.cpp

RESOURCES += pixmap.qrc

FORMS += \
    quibo.ui \
    modaldialog.ui \
    warningdialog.ui \
    tray.ui \
    suspensionframe.ui \
    alertdialog.ui \
    selectdialog.ui \
    kfontdialog.ui \
    aboutdialog.ui
