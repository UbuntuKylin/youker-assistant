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
import "../common" as Common

import ProcessType 0.1//1101

Rectangle {
    id: scaleMe
    scale: 1
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    //竖列高度和宽度
    width: 83//100
    height: 84//100

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"

    //竖列
    Column {
        anchors.centerIn: parent
        spacing: 10
        Image {
            id: seticon
            source: icon
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: btnText
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            text: qsTr(name)//名字
        }
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            //屏幕坏点检测
            if (flag == "CheckScreen") {
                sessiondispatcher.showCheckscreenDialog();
            }
            else if (flag == "BootAnimation") {
                pageStack.push(Qt.resolvedUrl("../settings/BootAnimation.qml"));
//                pageStack.push(bootanimationpage);
//                var component_boot = Qt.createComponent("./settings/BootAnimation.qml");
//                if (component_boot.status == Component.Ready) {
//                    pageStack.push(component_boot);
//                }
            }
//            else if(flag == "FcitxConfigtool") {
//                pageStack.push(fcitxConfigtoolpage);
//            }
            else if(flag == "ProcessManager") {
//                pageStack.push(processmanagerpage);
                pageStack.push(Qt.resolvedUrl("../settings/ProcessManager.qml"));
            }
            //kobe:选中项深色块移动
            scaleMe.GridView.view.currentIndex = index;
        }
    }
}
