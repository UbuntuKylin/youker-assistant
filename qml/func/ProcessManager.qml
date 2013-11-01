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
import ProcessType 0.1//1101
import "common" as Common
import "bars" as Bars
Item {
    id: screen; width: parent.width; height: 475
    Rectangle {
        id: setting_widget
        anchors.fill: parent
        //背景
        Image {
            source: "../img/skin/bg-bottom-tab.png"
            anchors.fill: parent
        }
        Item {
            id: views
            width: parent.width
            height: parent.height

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
                text: "任务管理器正在研发中，敬请期待......"
                font.pixelSize: 12
                color: "#383838"
            }


            Column {
                anchors {
                    top: titleimage.bottom
                    topMargin: 40
                    left: parent.left
                    leftMargin: 30
                }
                spacing: 10
                Common.Button {
                    id: listBtn
                    width: 120
                    height: 39
                    text: "列出进程"
                    hoverimage: "green1.png"
//                    anchors.verticalCenter: parent.verticalCenter
                    fontsize: 15
                    onClicked: {
                        processmanager.getProcess();
                    }
                }
                Common.Button {
                    id: killBtn
                    width: 120
                    height: 39
                    text: "杀掉进程"
                    hoverimage: "green1.png"
//                    anchors.verticalCenter: parent.verticalCenter
                    fontsize: 15
                    onClicked: {

                    }
                }
            }
        }
    }
}
