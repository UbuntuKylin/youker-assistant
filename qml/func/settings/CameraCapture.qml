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
    id: capturepage
    width: parent.width
//    color:"transparent"
    color: "#eeedf0"
    height: 476

    property string actiontitle: qsTr("Camera")//摄像头
    property string actiontext: qsTr("An application to take pictures with the device camera.")//利用摄像头进行简单的拍照和照镜子。

    Component.onCompleted: {
    }

    Row {
        spacing: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 20
        }
        Common.Button {
            id: backBtn
            anchors.verticalCenter: parent.verticalCenter
            picNormal: "../../img/icons/button12-gray.png"
            picHover: "../../img/icons/button12-gray-hover.png"
            picPressed: "../../img/icons/button12-gray-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 70; height: 28
            text: qsTr("Back")//返回
            onClicked: {
                pageStack.pop();
            }
        }
        Column {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                 text: capturepage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: capturepage.actiontext
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    //分割条
    Common.Separator {
        id: top_splitbar
        y: 70
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
    }

    Column{
        spacing: 20
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: top_splitbar.bottom
            topMargin: 100
        }
        Text {
            width: 600
            text: qsTr("Press the [ESC] button to take picture and turn the camera off , the photo saved in home directory by default.")//按下键盘左上方的 [Esc] 按键可以拍照并关闭摄像头，照片保存在当前用户主目录下。
            wrapMode: Text.WordWrap
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            Common.Button {
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Open camera")//开启摄像头
                onClicked: {
                    sessiondispatcher.call_camera_qt();
                }
            }
            Common.Button {
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("View Photos")//查看照片
                onClicked: {
                    sessiondispatcher.open_folder_qt(sessiondispatcher.getHomePath());
                }
            }
        }
    }
}
