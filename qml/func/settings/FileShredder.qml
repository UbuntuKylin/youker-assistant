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
    id: shredpage
    width: parent.width
//    color:"transparent"
    color: "#eeedf0"
    height: 476

    property string actiontitle: qsTr("File Shredder")//文件粉碎机
    property string actiontext: qsTr("Crush stubborn files.")//彻底粉碎无法删除的顽固文件。
    property string selectedfile

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
                 text: shredpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: shredpage.actiontext
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

//    Common.Button {
//        anchors{
//            horizontalCenter: parent.horizontalCenter
//            top: top_splitbar.bottom
//            topMargin: 100
//        }
//        picNormal: "../../img/icons/button12.png"
//        picHover: "../../img/icons/button12-hover.png"
//        picPressed: "../../img/icons/button12-hover.png"
//        fontcolor:"#ffffff"
//        fontsize: 12
//        width: 100; height: 28
//        text: qsTr("Select File")//选择文件
//        onClicked: {
//            var result = sessiondispatcher.show_file_path_dialog();
//            if(result.length != 0) {
//                var value = systemdispatcher.start_to_destroy_file(result);
//                if (value == 0) {
//                    toolkits.alertMSG(qsTr("Shred success!"));//粉碎成功！
//                }
//                else {
//                    toolkits.alertMSG(qsTr("Shred abnormal!"));//粉碎出现异常！
//                }
//            }
//        }
//    }

    Column{
        spacing: 20
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: top_splitbar.bottom
            topMargin: 100
        }
        Text {
            id: showLabel
            visible: (shredpage.selectedfile.length == 0) ? false : true
            width: 600
            text: qsTr("The selected file path: ") + shredpage.selectedfile//选中的文件路径：
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
                text: qsTr("Select File")//选择文件
                onClicked: {
                    shredpage.selectedfile = "";
                    shredpage.selectedfile = sessiondispatcher.show_file_path_dialog();
                }
            }
            Common.Button {
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Shred File")//查看照片
                onClicked: {
                    if(shredpage.selectedfile.length != 0) {
                        var value = systemdispatcher.start_to_destroy_file(shredpage.selectedfile);
                        if (value == 0) {
                            shredpage.selectedfile = "";
                            toolkits.alertMSG(qsTr("Shred success!"));//粉碎成功！
                        }
                        else {
                            toolkits.alertMSG(qsTr("Shred abnormal!"));//粉碎出现异常！
                        }
                    }
                }
            }
        }
    }
}
