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
//import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
import "common" as Common
import QtDesktop 0.1

Item {
    id: rubbishitem; width: parent.width; height: 420
//    property Dispatcher dis: mydispather
    property bool inListView : false
    Rectangle {
        id: background
        anchors.fill: parent; color: "white"
        Item {
            id: views
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: titleBar.height// + 45

            Component {
                id: statusDelegate
                RubbishStatus {
                    id: content
                }
            }
            ListModel {
                id: streamModel
                ListElement {
                    title: "清理插件"
                    picture: "../img/icons/user.png"
                    detailstr: "清理插件包，让系统更瘦"
                    flags: "clear_plugins"
                }
            }

            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height - titlebar.height
                width: parent.width
//                opacity: 1
//                spacing: 10//units.gu(1)
                model: streamModel
//                snapMode: ListView.NoSnap
//                cacheBuffer: parent.height
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
                delegate: RubbishDelegate {}
                cacheBuffer: 1000
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
            }

//            Scrollbar {
//                flickableItem: listView
//                align: Qt.AlignTrailing
//            }
        }

        //垃圾清理自定义标题栏
        Common.MyTitleBar {
            id: titleBar; width: parent.width; height: 45; opacity: 0.9
            btn_text: "开始扫描"
            title: "清理插件"
            description:  "清理插件可以节省磁盘容量"
            btn_flag: "plugins"
        }
    }
}
