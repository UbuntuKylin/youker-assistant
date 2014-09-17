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
import "../bars" as Bars
import "../others" as Others

Item {
    id: screen; width: parent.width; height: 476
    Rectangle {
        id: setting_widget
        anchors.fill: parent
//        color: "#eeedf0"
//        color: "white"

        //背景
//        Image {
//            source: "../../img/skin/bg-middle.png"
//            anchors.fill: parent
//        }
        //更新列表
        function updateList() {
            funcmodel.clear();//清空
            funcmodel.append({"icon": "../../img/icons/checkscreen.png", "name": qsTr("Dead pixel check"), "flag": "CheckScreen"});//坏点检测
            funcmodel.append({"icon": "../../img/icons/bootanimation.png", "name": qsTr("Boot Animation"), "flag": "BootAnimation"});//开机动画
            funcmodel.append({"icon": "../../img/icons/processmanager.png", "name": qsTr("Task Manager"), "flag": "ProcessManager"});//任务管理器
            funcmodel.append({"icon": "../../img/icons/camera.png", "name": qsTr("Camera"), "flag": "CameraCapture"});//摄像头
            funcmodel.append({"icon": "../../img/icons/shredder.png", "name": qsTr("File Shredder"), "flag": "FileShredder"});//文件粉碎机
        }

        Item {
            id: views
            width: parent.width
            height: parent.height
            ListModel {
                id: funcmodel
                Component.onCompleted: {
                    setting_widget.updateList();
                }
            }

            Common.Label {
                id: label
                text: qsTr("Default toolkits")//默认工具箱
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

            Item {
                width: parent.width - 30*2
                anchors {
                    top: label.bottom
                    topMargin: 10
                    left: parent.left
                    leftMargin: 30
                }
                GridView {
                    id: gridView
                    anchors.fill: parent
                    model: funcmodel
                    delegate: Others.SettingsDelegate {}
                    cacheBuffer: 1000
                    //竖列
                    cellWidth: (parent.width-2)/6; cellHeight: cellWidth
                    //横列
    //                cellWidth: (parent.width-2)/6; cellHeight: cellWidth
                    highlight: Image {source: "../../img/toolWidget/box-hover.png"}
//                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
                    focus: true
                }
            }
            Item { id: foreground; anchors.fill: parent }
        }
    }
}
