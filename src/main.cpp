/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QApplication>
#include "fcitxcfgwizard.h"
#include "toolkits.h"
#include "systemdispatcher.h"
#include "sessiondispatcher.h"
#include "sudodispatcher.h"
#include "youker-application.h"
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include "qmlaudio.h"
#include <QTextCodec>
#include <QProcess>
#include <QDebug>
#include <sys/types.h>
#include "qrangemodel.h"
#include "qstyleitem.h"
#include "qwheelarea.h"
#include "qtmenu.h"
#include "qtmenubar.h"
#include "qwindowitem.h"
#include "qdesktopitem.h"
#include "qcursorarea.h"
#include "qtooltiparea.h"
#include "qtsplitterbase.h"
#include "qdeclarativelinearlayout.h"
#include "settings.h"
#include <QDeclarativeExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtCore/QTimer>
#include <QFileSystemModel>
#include <qdeclarative.h>
#include <qdeclarativeextensionplugin.h>
#include <qdeclarativeengine.h>
#include <qdeclarativeitem.h>
#include <qdeclarativeimageprovider.h>
#include <qdeclarativeview.h>
#include "KThread.h"
#include <QtSingleApplication>
#include "processmanager.h"
#include <QTranslator>

void registerTypes() {
    qmlRegisterType<Toolkits>("ToolkitsType", 0, 1, "Toolkits");
    qmlRegisterType<SessionDispatcher>("SessionType", 0, 1, "SessionDispatcher");
    qmlRegisterType<SystemDispatcher>("SystemType", 0, 1, "SystemDispatcher");
    qmlRegisterType<SudoDispatcher>("SudoType", 0, 1, "SudoDispatcher");
    qmlRegisterType<ProcessManager>("ProcessType", 0, 1, "ProcessManager");
    qmlRegisterType<FcitxCfgWizard>("FcitxCfgWizard", 0, 1, "FcitxCfgWizard");
    qmlRegisterType<QmlAudio>("AudioType", 0, 1, "QmlAudio");
    qmlRegisterType<QRangeModel>("RangeModelType", 0, 1, "RangeModel");
    qmlRegisterType<QStyleItem>("StyleItemType", 0, 1, "StyleItem");
    qmlRegisterType<QWheelArea>("WheelAreaType", 0, 1, "WheelArea");
    qmlRegisterType<QtMenu>("MenuType", 0, 1, "Menu");
    qmlRegisterUncreatableType<QtMenuBase>("MenuBaseType", 0, 1, "NativeMenuBase", QLatin1String("Do not create objects of type NativeMenuBase"));
    qmlRegisterType<QCursorArea>("CursorAreaType", 0, 1, "CursorArea");
    qmlRegisterType<QTooltipArea>("TooltipAreaType", 0, 1, "TooltipArea");
    qmlRegisterType<QtMenuBar>("MenuBarType", 0, 1, "MenuBar");
    qmlRegisterType<QtMenuItem>("MenuItemType", 0, 1, "MenuItem");
    qmlRegisterType<QtMenuSeparator>("SeparatorType", 0, 1, "Separator");
    qmlRegisterType<QFileSystemModel>("FileSystemModelType", 0, 1, "FileSystemModel");
    qmlRegisterType<QtSplitterBase>("SplitterType", 0, 1, "Splitter");
    qmlRegisterType<Settings>("SettingsType", 0, 1, "Settings");
    qmlRegisterType<QWindowItem>("WindowType", 0, 1, "Window");
    qmlRegisterType<QDeclarativeRowLayout>("RowLayoutType", 0, 1, "RowLayout");
    qmlRegisterType<QDeclarativeColumnLayout>("ColumnLayoutType", 0, 1, "ColumnLayout");
    qmlRegisterUncreatableType<QDeclarativeLayout>("LayoutType", 0, 1, "Layout",
                                                   QLatin1String("Do not create objects of type Layout"));
    qmlRegisterUncreatableType<QDesktopItem>("DesktopType",0,1,"Desktop", QLatin1String("Do not create objects of type Desktop"));
}

int main(int argc, char** argv)
{
    //单程序运行处理
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
        return 0;

    //编码处理
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QString locale = QLocale::system().name();
    QTranslator translator;
    if(locale == "zh_CN") {
        //加载Qt和QML文件的国际化
        if(!translator.load("youker-assistant_" + locale + ".qm",
                            ":/translate/translation/"))
            qDebug() << "Load translation file："<< "youker-assistant_" + locale + ".qm" << " failed!";
        else
            app.installTranslator(&translator);
    }

    //加载Qt对话框默认的国际化
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    //注册QML模块
    registerTypes();

    //启动sessiondbus和systemdbus服务
    int value_session = system("/usr/bin/youkersession &");
    if (value_session != 0)
        qDebug() << "SessionDaemon Failed!";
    int value_system = system("/usr/bin/youkersystem");
    if (value_system != 0)
        qDebug() << "SystemDaemon Failed!";

    //启动画面
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/pixmap/image/feature.png"));
    splash->setDisabled(true);
    splash->show();
    splash->showMessage(QObject::tr("starting...."), Qt::AlignHCenter|Qt::AlignBottom, Qt::black);//优客助手正在启动中....
    //同时创建主视图对象
    IhuApplication application;
    splash->showMessage(QObject::tr("loading module data...."), Qt::AlignHCenter|Qt::AlignBottom, Qt::black);//正在加载模块数据....
    //数据处理
    application.setup();
    //显示主界面，并结束启动画面
    application.showQMLWidget();
    splash->finish(&application);
    delete splash;
    return app.exec();
}


/*
a 	ARRAY 数组
b 	BOOLEAN 布尔值
d 	DOUBLE IEEE 754双精度浮点数
g 	SIGNATURE 类型签名
i 	INT32 32位有符号整数
n 	INT16 16位有符号整数
o 	OBJECT_PATH 对象路径
q 	UINT16 16位无符号整数
s 	STRING 零结尾的UTF-8字符串
t 	UINT64 64位无符号整数
u 	UINT32 32位无符号整数
v 	VARIANT 可以放任意数据类型的容器，数据中包含类型信息。例如glib中的GValue。
x 	INT64 64位有符号整数
y 	BYTE 8位无符号整数
() 	定义结构时使用。例如"(i(ii))"
{} 	定义键－值对时使用。例如"a{us}"

a表示数组，数组元素的类型由a后面的标记决定。例如：
    "as"是字符串数组。
    数组"a(i(ii))"的元素是一个结构。用括号将成员的类型括起来就表示结构了，结构可以嵌套。
    数组"a{sv}"的元素是一个键－值对。"{sv}"表示键类型是字符串，值类型是VARIANT。
*/
