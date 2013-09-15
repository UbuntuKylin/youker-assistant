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
import "common" as Common
Rectangle {
    id: home
    anchors.fill: parent
    height: 475
    property SessionDispatcher dis: sessiondispatcher
    signal dialogmsg()

    Component.onCompleted: {
        sessiondispatcher.get_system_message_qt();
    }

    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component:", component.errorString());
     }

    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    //desktop logo
    Image {
        source: "../img/toolWidget/ubuntukylin.png"
        anchors {
            top: parent.top
            topMargin: 230
            right: parent.right
            rightMargin: 70
        }
    }

    Image {
        id: titleimage
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        source: "../img/skin/note-bg.png"
    }
    Text {
        anchors {
            left: parent.left
            leftMargin: 50
            top: parent.top
            topMargin: titleimage.height/2 - 7
        }
        text: "您可以查看相关信息，随时了解系统情况。"
        font.pixelSize: 12
        color: "#383838"
    }

    //上下分割条
    Rectangle {x: 100; y: 90; width: parent.width - 150; height: 1; color: "#ccdadd" }
    Rectangle {x: 100; y: 190; width: parent.width - 150; height: 1; color: "#ccdadd" }
    Rectangle {x: 100; y: 370; width: parent.width - 150; height: 1; color: "#ccdadd" }
    Column {
        anchors {
//            fill: parent
            top: titleimage.bottom
            topMargin: 40
            left: parent.left
            leftMargin: 30
        }
        spacing: 20

        Text {
            id: hardwaretitle
            text: qsTr("硬件信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("处理器:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("cpu")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("内存:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("ram")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }


        Text {
            id: desktoptitle
            text: qsTr("桌面信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("主机名:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("hostname")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("平台:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("platform")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("发行版:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("distribution")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("桌面环境:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("desktopenvironment")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("语言:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("language")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }

        Text {
            id: usertitle
            text: qsTr("用户信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("当前用户:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("currrent_user")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("用户主目录:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("home_path")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
    }
}
