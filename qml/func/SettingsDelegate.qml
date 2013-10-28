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

import QtQuick 1.1
import SessionType 0.1
import SystemType 0.1
import "common" as Common

Rectangle {
    id: scaleMe
//    scale: 0.0
    scale: 1
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    //竖列高度和宽度
    width: 78
    height: 82
    //横列高度和宽度
//    width: 120
//    height: 78
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
//    function iconClicked() {
//        scaleMe.state = "Details";
//        settigsDetails.setTitle = flag;
//    }

    //竖列
    Column {
        anchors.fill: parent
        anchors.topMargin: 7
        spacing: 5
        Image {
            id: seticon
            source: icon
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: btnText
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            text: qsTr(name)
        }
    }
    //横列
//    Row {
//        anchors.fill: parent
//        anchors.topMargin: 7
//        Image {
//            id: seticon
//            source: icon
//            //横列
//            anchors.verticalCenter: parent.verticalCenter
//            //竖列
////            anchors.horizontalCenter: parent.horizontalCenter
//        }
//        Text {
//            id: btnText
//            //横列
//            anchors.verticalCenter: parent.verticalCenter
//            //竖列
////            anchors.horizontalCenter: parent.horizontalCenter
//            color: "green"
//            text: qsTr(name)
//        }
//    }

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
                sessiondispatcher.showCheckscreenDialog(mainwindow.pos.x, mainwindow.pos.y);
            else if (flag == "BootAnimation") {
                pageStack.push(bootanimationpage);
//                var component_boot = Qt.createComponent("./settings/BootAnimation.qml");
//                if (component_boot.status == Component.Ready) {
//                    pageStack.push(component_boot);
//                }
            }
            else if(flag == "FcitxConfigtool")
            {
                pageStack.push(fcitxConfigtoolpage);

//                scaleMe.emitFcitxRefresh();

            }
            else if(flag == "SoftWare") {
                //进入软件推荐的入口
                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                    if(!sudodispatcher.getUKSignalFlag()) {
                        sudodispatcher.setUKSignalFlag(true);
                        sudodispatcher.bind_signals_after_dbus_start();
                    }
                    //获取所有软件的状态
                    sudodispatcher.check_pkgs_status_qt(sudodispatcher.getAllSoftwareExecNameList());
                    //得到所有软件列表
                    sudodispatcher.getAppListForDisPlay();
                    pageStack.push(softwarerecommend);
                }
                else {
                    sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                        if(!sudodispatcher.getUKSignalFlag()) {
                            sudodispatcher.setUKSignalFlag(true);
                            sudodispatcher.bind_signals_after_dbus_start();
                        }

                        //获取所有软件的状态
                        sudodispatcher.check_pkgs_status_qt(sudodispatcher.getAllSoftwareExecNameList());
                        //得到所有软件列表
                        sudodispatcher.getAppListForDisPlay();
                        pageStack.push(softwarerecommend);
                    }
                }
            }

//            else
//                iconClicked();
            //kobe:选中项深色块移动
            scaleMe.GridView.view.currentIndex = index;
        }
    }
}











//Rectangle {
//    id: scaleMe
////    scale: 0.0
//    scale: 1
//    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
//    //竖列高度和宽度
//    width: 78
//    height: 82
//    //横列高度和宽度
////    width: 120
////    height: 78
//    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
//    color: "transparent"
////    function iconClicked() {
////        scaleMe.state = "Details";
////        settigsDetails.setTitle = flag;
////    }

//    //竖列
//    Column {
//        anchors.fill: parent
//        anchors.topMargin: 7
//        spacing: 5
//        Image {
//            id: seticon
//            source: icon
//            anchors.horizontalCenter: parent.horizontalCenter
//        }
//        Text {
//            id: btnText
//            anchors.horizontalCenter: parent.horizontalCenter
//            color: "green"
//            text: qsTr(name)
//        }
//    }
//    //横列
////    Row {
////        anchors.fill: parent
////        anchors.topMargin: 7
////        Image {
////            id: seticon
////            source: icon
////            //横列
////            anchors.verticalCenter: parent.verticalCenter
////            //竖列
//////            anchors.horizontalCenter: parent.horizontalCenter
////        }
////        Text {
////            id: btnText
////            //横列
////            anchors.verticalCenter: parent.verticalCenter
////            //竖列
//////            anchors.horizontalCenter: parent.horizontalCenter
////            color: "green"
////            text: qsTr(name)
////        }
////    }

//    Image {
//        id: btnImg
//        anchors.fill: parent
//        source: ""
//    }

//    MouseArea {
//        id: signaltest
//        hoverEnabled: true
//        anchors.fill: parent
//        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""
//        onClicked: {
//            //屏幕坏点检测
//            if (flag == "CheckScreen")
//                sessiondispatcher.showCheckscreenDialog(mainwindow.pos.x, mainwindow.pos.y);
//            else if (flag == "BootAnimation") {
//                pageStack.push(bootanimationpage);
////                var component_boot = Qt.createComponent("./settings/BootAnimation.qml");
////                if (component_boot.status == Component.Ready) {
////                    pageStack.push(component_boot);
////                }
//            }
//            else if(flag == "FcitxConfigtool")
//            {
//                pageStack.push(fcitxConfigtoolpage);

////                scaleMe.emitFcitxRefresh();

//            }
//            else if(flag == "SoftWare") {
//                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
//                    if(!sudodispatcher.getUKSignalFlag()) {
//                        sudodispatcher.setUKSignalFlag(true);
//                        sudodispatcher.bind_signals_after_dbus_start();
//                    }
//                    sudodispatcher.add_source_ubuntukylin_qt();
//                    sudodispatcher.check_pkgs_status_qt(sudodispatcher.getAllSoftwareList());
//                    sudodispatcher.remove_source_ubuntukylin_qt();
//                    pageStack.push(softwarerecommend);
//                }
//                else {
//                    sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
//                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
//                        if(!sudodispatcher.getUKSignalFlag()) {
//                            sudodispatcher.setUKSignalFlag(true);
//                            sudodispatcher.bind_signals_after_dbus_start();
//                        }
//                        sudodispatcher.add_source_ubuntukylin_qt();
//                        sudodispatcher.check_pkgs_status_qt(sudodispatcher.getAllSoftwareList());
//                        sudodispatcher.remove_source_ubuntukylin_qt();
//                        pageStack.push(softwarerecommend);
//                    }
//                }
//            }

////            else
////                iconClicked();
//            //kobe:选中项深色块移动
//            scaleMe.GridView.view.currentIndex = index;
//        }
//    }
//}
