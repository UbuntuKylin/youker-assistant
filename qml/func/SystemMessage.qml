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

Item {
    id: home; width: parent.width; height: 475
    Rectangle {
        anchors.fill: parent
        //背景
        Image {
            source: "../img/skin/bg-bottom-tab.png"
            anchors.fill: parent
        }
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
            text: qsTr("You can view the relevant information, and understand the system at any time.")//您可以查看相关信息，随时了解系统情况。
            font.pixelSize: 12
            color: "#383838"
        }

        Common.Button{
            width: 80
            height: 26
            anchors{
                verticalCenter:parent.verticalCenter
                right:parent.right
                rightMargin: 15
            }
            text: qsTr("Details")//详情
            onClicked: {
                systemdispatcher.get_detail_system_message_qt();
            }
        }

        Column {
            anchors {
                top: titleimage.bottom
                topMargin: 40
                left: parent.left
                leftMargin: 30
            }
            spacing: 20

            Row {
                Text {
                    id: hardwaretitle
                    text: qsTr("Hardware information")//硬件信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - hardwaretitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("CPU:")//处理器:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("cpu")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Memory:")//内存:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("ram")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }

            Row {
                Text {
                    id: desktoptitle
                    text: qsTr("Desktop information")//桌面信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - desktoptitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Host name:")//主机名:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("hostname")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Platform:")//平台:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("platform")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Distribution:")//发行版:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("distribution")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Environment:")//桌面环境:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("desktopenvironment")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Language:")//语言:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("language")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }

            Row {
                Text {
                    id: usertitle
                    text: qsTr("User information")//用户信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - usertitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("User:")//当前用户:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("currrent_user")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Home directory:")//用户主目录:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("home_path")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
        }
    }
}
