/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
import FcitxCfgWizard 0.1
import ProcessType 0.1
import DeviceType 0.1

Rectangle {
    id: main
    width: 850
    height: 600
    objectName: "main"
    anchors.fill: parent
    property string version: "V1.0.2"
    property string bgName: ""
    property color borderColor: "lightblue"
    SessionDispatcher {
        id: sessiondispatcher
    }
    SystemDispatcher {
        id: systemdispatcher
    }
    FcitxCfgWizard {
        id: fcitxcfgwizard
    }
    Toolkits{
        id: toolkits
    }
    ProcessManager {
        id: processmanager
    }
    DeviceManager {
        id: devicemanager
    }

    Component.onCompleted: {
        main.bgName = sessiondispatcher.setSkin();
        bgImg.source = "./img/skin/" + main.bgName + ".png";
        main.border.width = 1.5;//设置边框宽度
        main.border.color = borderColor;//设置边框颜色
    }

    Connections
    {
        target: sessiondispatcher
        onStartChangeQMLSkin: {
            bgImg.source = "./img/skin/" + skinName + ".png";
        }
    }

    Image {
        id: bgImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        anchors.fill: parent
        property variant previousPosition
        onPressed: {
            previousPosition = Qt.point(mouseX, mouseY)
        }
        onPositionChanged: {
            if (pressedButtons == Qt.LeftButton) {
                var dx = mouseX - previousPosition.x
                var dy = mouseY - previousPosition.y
                mainwindow.pos = Qt.point(mainwindow.pos.x + dx,
                                            mainwindow.pos.y + dy)
            }
        }
    }

    radius: 4
    opacity: 1.0
    Column {
        id: layout
        anchors.fill: parent
        spacing: 3
        ContentWidget{
            id: contentwidget
        }
        StatusWidget{
            id: statuswidget
            version: main.version
        }
    }

    Image {
        id: logo
        width: 191
        height: 54
        anchors {
            top: parent.top
            topMargin: 25
            right: parent.right
            rightMargin: 35
        }
        source: (sessiondispatcher.get_locale_version() == "zh_CN") ? "./img/zh_CN/logo.png" : "./img/en/logo.png"
//        MouseArea {
//            anchors.fill: logo
////            property variant clickPos: "1,1"
//            property variant previousPosition
//            onPressed: {
////                clickPos  = Qt.point(mouse.x,mouse.y)
//                previousPosition = Qt.point(mouseX, mouseY)
//            }
//            onPositionChanged: {
////                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
////                mainwindow.pos = Qt.point(mainwindow.pos.x+delta.x, mainwindow.pos.y+delta.y)
//                if (pressedButtons == Qt.LeftButton) {
//                    var dx = mouseX - previousPosition.x
//                    var dy = mouseY - previousPosition.y
//                    mainwindow.pos = Qt.point(mainwindow.pos.x + dx,
//                                                mainwindow.pos.y + dy)
//                }
//            }
//        }
    }
}
