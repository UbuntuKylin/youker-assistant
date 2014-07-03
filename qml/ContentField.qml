/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

import QtQuick 1.1
import ToolkitsType 0.1
import SessionType 0.1
import SystemType 0.1
import ProcessType 0.1
import DeviceType 0.1
import "./func/common" as Common
import "./func/settings" as SysSettings
import "./func/page" as HomeView

Rectangle {
    id: main
    width: 850
    height: 476
    objectName: "main"
    radius: 4
    opacity: 1.0
    property string globalFlag: "safepage"

    SessionDispatcher { id: sessiondispatcher }
    SystemDispatcher { id: systemdispatcher }
    Toolkits{ id: toolkits }
    ProcessManager { id: processmanager }
    DeviceManager { id: devicemanager }

    //当用户点击工具栏图标时，接收信号返回当前页面所属的主页面
    Connections
    {
        target: sessiondispatcher
        onBackToHomePage: {
            if(index == 0) {
                pageStack.push(homepage);
            }
            else if(index == 1) {
                pageStack.push(systemmessage);
            }
            else if(index == 2) {
                pageStack.push(clearrubbish);
            }
            else if(index == 3) {
                pageStack.push(systemset);
            }
            else if(index == 4) {
                pageStack.push(functioncollection);
            }
        }
    }

    Common.PageStack {
        id: pageStack
        Component.onCompleted: {
            pageStack.push(homepage);
        }
        Common.Page {
            id: homepage
            visible: false
            HomeView.HomePage {}
        }
        Common.Page {
            id: systemmessage
            visible: false
            HomeView.SystemInfo {}
        }
        Common.Page {
            id: clearrubbish
            visible: false
            HomeView.SystemClean {}
        }
        Common.Page {
            id: systemset
            visible: false
            HomeView.SystemSet {}
        }
        Common.Page {
            id: functioncollection
            visible: false
            HomeView.SystemBox {}
        }
    }
}
