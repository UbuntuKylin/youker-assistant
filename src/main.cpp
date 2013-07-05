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


//#include <QtGui/QGuiApplication>
//#include "qtquick2applicationviewer/qtquick2applicationviewer.h"
//#include "dispatcher.h"

//#include <QObject>
//#include <QString>
//#include <QStringList>
//#include <QQmlParserStatus>
//#include <QQmlListProperty>
//#include <QQmlExtensionPlugin>
//#include <QQmlComponent>
//#include <QDir>
//#include <QDebug>
//#include <unistd.h>

// Qt
#include <QApplication>
#include <QApplication>
//#include <QQmlComponent>
// local
#include "systemdispatcher.h"
#include "sessiondispatcher.h"
#include "youker-application.h"
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include "quibo.h"

int main(int argc, char** argv)
{
//    qmlRegisterType<Person>("People",1,0,"Person");
    //通过qmlRegisterType<Person>("People",1,0,"Person");
//    向QML中导出Person类，这个类在People包中，在QML中需要使用Person类的
//    话就必须包含People包，通过import People 1.0来包含，之后就可以使用Person
//    创建对象使用来。
//    qmlRegisterType<DispatcherQml>("RegisterMyType", 0, 1, "Dispatcher");
    qmlRegisterType<SessionDispatcher>("SessionType", 0, 1, "SessionDispatcher");
    qmlRegisterType<SystemDispatcher>("SystemType", 0, 1, "SystemDispatcher");
    IhuApplication application(argc, argv);
    if (!application.setup()) {
        return 0;
    }
    return application.exec();

//    QApplication app(argc, argv);
//    QUIBO *ui = new QUIBO();
//    app.exec();

//    QApplication app(argc, argv);
//    IhuApplication ihu;
//    ihu.show();
//    return app.exec();
}
