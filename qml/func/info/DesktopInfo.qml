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

Rectangle {
    id: home
    width: parent.width; height: 476

    function init_data() {
        sessiondispatcher.get_system_message_qt();
        desktoptext.text = sessiondispatcher.getSingleInfo("desktopenvironment");
        distributiontext.text = sessiondispatcher.getSingleInfo("distribution");
        languagetext.text = sessiondispatcher.getSingleInfo("language");
        usertext.text = sessiondispatcher.getSingleInfo("currrent_user");
        hometext.text = sessiondispatcher.getSingleInfo("home_path");
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "desktop") {
                home.init_data();
            }
        }
    }

    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component: ", component.errorString());
     }

    Column {
        anchors {
            top: parent.top
            topMargin: 40
            left: parent.left
            leftMargin: 30
        }
        spacing: 20
        Row {
            Common.Label {
                id: desktoptitle
                text: qsTr("Desktop Info")//桌面信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - desktoptitle.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Desktop Environment: ")//桌面环境：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: desktoptext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Distribution: ")//发行版：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: distributiontext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Language: ")//语言：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: languagetext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }

            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("User: ")//当前用户：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: usertext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Home Folder: ")//用户主目录：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: hometext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }
    }

    //desktop logo
    Image {
        id: logo
        source: "../../img/toolWidget/ubuntukylin.png"
        opacity: 0.5
        anchors {
            top: parent.top
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
}
