/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SessionType 0.1
import SystemType 0.1
import "common" as Common

Rectangle {
    id: scaleMe
//    scale: 0.0
    scale: 1
    property SessionDispatcher dis1: sessiondispatcher
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    width: 78
    height: 82
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
//    function iconClicked() {
//        scaleMe.state = "Details";
//        settigsDetails.setTitle = flag;
////        console.log(settigsDetails.setTitle);
//    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 7
        Image {
            id: seticon
            source: icon
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: btnText
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
            color: "#383838"
            text: name
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
        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            //屏幕坏点检测
            if (flag == "CheckScreen")
                sessiondispatcher.send_checkscreen_dialog();
            else if (flag == "DesktopiconSet")
                pageStack.push(desktopiconsetpage);
            else if (flag == "BootAnimation") {
                console.log("BootAnimation clicked....");
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    var component_boot = Qt.createComponent("./settings/BootAnimation.qml");
                    if (component_boot.status == Component.Ready) {
                        pageStack.push(component_boot);
                    }
                }
                else {
                    var value5 = systemdispatcher.setup();
                    if(value5) {
                        var component_boot1 = Qt.createComponent("./settings/BootAnimation.qml");
                        if (component_boot1.status == Component.Ready) {
                            pageStack.push(component_boot1);
                        }
                    }
                    else {
                        sessiondispatcher.send_restartdialog_msg();
                    }
                }
            }
            else if (flag == "SoundEffects") {
                console.log("SoundEffects clicked....");
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    var component_sound = Qt.createComponent("./settings/SoundEffects.qml");
                    if (component_sound.status == Component.Ready) {
                        pageStack.push(component_sound);
                    }
                }
                else {
                    var value6 = systemdispatcher.setup();
                    if(value6) {
                        var component_sound1 = Qt.createComponent("./settings/SoundEffects.qml");
                        if (component_sound1.status == Component.Ready) {
                            pageStack.push(component_sound1);
                        }
                    }
                    else {
                        sessiondispatcher.send_restartdialog_msg();
                    }
                }
            }
            else if (flag == "MousePointer")
                pageStack.push(mousepointerpage);
            else if (flag == "TouchpadSet")
                pageStack.push(touchpadsetpage);


            //kobe:选中项深色块移动
//            scaleMe.GridView.view.currentIndex = index;
        }
    }
}
