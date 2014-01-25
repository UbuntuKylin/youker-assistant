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
import "./func/common" as Common
Rectangle {
    id: root
    width: parent.width
    height: 30
    color: "transparent"
    property string version: ""//优客助手版本号
    property bool upcloud: false//金山快盘云配置使用
    property bool downcloud: false//金山快盘上传云配置

    Component.onCompleted: {
    }
    Row {
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        spacing: 5
        Image {
            source: "./img/icons/arrowhead.png"
        }
        Text {
            color: "white"
            font.pixelSize: 12
            text: qsTr("main version:") + root.version//主版本：
        }
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: parent
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            mainwindow.pos = Qt.point(mainwindow.pos.x+delta.x, mainwindow.pos.y+delta.y)
        }
    }
//    Image {
//        id: downloadImage
//        anchors {
//            right: parent.right
//            rightMargin: 5
//            verticalCenter: parent.verticalCenter

//        }
//        width: 16
//        height: 16
//        source: "./img/icons/move.png"
//        MouseArea {
//            anchors.fill: downloadImage
//            onClicked: {
//                console.log("1111111111");
//                sessiondispatcher.showSkinCenter(/*mainwindow.pos.x, mainwindow.pos.y*/);
//            }
//        }
//    }

//    Row {
//        anchors {
//            right: parent.right
//            rightMargin: 5
//            verticalCenter: parent.verticalCenter
//        }
//        spacing: 10
//        Row {
//            Text {
//                id: downBtn
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Use Cloud Conf")//使用云配置
//                MouseArea {
//                    anchors.fill: downBtn
//                    onClicked: {
//                        root.downcloud = !root.downcloud;
//                    }
//                }
//            }
//            Image {
//                id: downloadImage
//                visible: root.downcloud ? false : true
//                width: 16
//                height: 16
//                source: "./img/icons/move.png"
//            }
//            AnimatedImage {//动态图片
//                id: downloaddynamic
//                visible: root.downcloud ? true : false
//                width: 16
//                height: 16
//                source: "./img/icons/move.gif"
//            }
//        }
//        Row {
//            Text {
//                id: upBtn
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Upload Cloud Conf")//上传云配置
//                MouseArea {
//                    anchors.fill: upBtn
//                    onClicked: {
//                        root.upcloud = !root.upcloud;
//                    }
//                }
//            }
//            Image {
//                id: uploadImage
//                visible: root.upcloud ? false : true
//                width: 16
//                height: 16
//                source: "./img/icons/move.png"
//            }
//            AnimatedImage {//动态图片
//                id: uploaddynamic
//                visible: root.upcloud ? true : false
//                width: 16
//                height: 16
//                source: "./img/icons/move.gif"
//            }
//        }
//    }
}
