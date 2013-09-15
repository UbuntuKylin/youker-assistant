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
import SystemType 0.1
import "common" as Common
import "bars" as Bars
Item {
    id: screen; width: parent.width; height: 475
    property SystemDispatcher dis: systemdispatcher
    Rectangle {
        id: setting_widget
        anchors.fill: parent
//        color: "white"

        //背景
        Image {
            source: "../img/skin/bg-middle.png"
            anchors.fill: parent
        }
        Item {
            id: views
            width: parent.width
            height: parent.height
            ListModel {
                id: funcmodel
                ListElement {
                    icon: "../img/icons/checkscreen.png"
                    name: "坏点检测"
                    flag: "CheckScreen"
                }
                ListElement {
                    icon: "../img/icons/bootanimation.png"
                    name: "开机动画"
                    flag: "BootAnimation"
                }
                ListElement {
                    icon: "../img/icons/fcitx.png"
                    name: "输入法配置"
                    flag: "FcitxConfigtool"
                  }
                ListElement {
                    icon: "../img/icons/software.png"
                    name: "软件推荐"
                    flag: "SoftWare"
                  }
            }


            Common.Label {
                id: label
                text: "默认工具箱"
                font.bold: true
                font.pixelSize: 16
                color: "#383838"
                anchors {
                    top: parent.top
                    topMargin: 30
                    left: parent.left
                    leftMargin: 35
                }
            }

            GridView {
                id: gridView
                height: parent.height -label.height
                width: parent.width
                anchors {
                    top: label.bottom
                    topMargin: 10
                    left: parent.left
                    leftMargin: 30
                }

                model: funcmodel
                delegate: SettingsDelegate {}
                cacheBuffer: 1000
                //竖列
                cellWidth: (parent.width-2)/8; cellHeight: cellWidth
                //横列
//                cellWidth: (parent.width-2)/6; cellHeight: cellWidth
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
                focus: true
            }
            Item { id: foreground; anchors.fill: parent }
        }
    }
}
