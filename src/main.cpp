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
#include "systemdispatcher.h"
#include "sessiondispatcher.h"
#include "youker-application.h"
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include "quibo.h"
#include "qmlaudio.h"
#include <QTextCodec>
#include <QProcess>
#include <QDebug>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QDialog>

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
#include <QImage>


void registerTypes()
{
    qmlRegisterType<SessionDispatcher>("SessionType", 0, 1, "SessionDispatcher");
    qmlRegisterType<SystemDispatcher>("SystemType", 0, 1, "SystemDispatcher");
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
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    registerTypes();

    int value_session = system("/usr/bin/youkersession &");
    if (value_session != 0)
        qDebug() << "SessionDaemon Failed!";
    int value_system = system("/usr/bin/youkersystem");
    if (value_system != 0)
        qDebug() << "SystemDaemon Failed!";

    IhuApplication application(argc, argv);
    if (!application.setup()) {
        return 0;
    }
    return application.exec();
}
