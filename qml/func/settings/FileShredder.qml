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
    height: 476

    property string actiontitle: qsTr("File Shredder")//文件粉碎机
    property string actiontext: qsTr("Delete files makes it unable to recover.")//彻底删除文件使其无法恢复。
    property string selectedfile

    Component.onCompleted: {
    }

    Connections
    {
        target: shreddispatcher
        onFinishDeleteWork: {
            doingImage.visible = false;
            if (result == 0) {
                shredpage.selectedfile = "";
                showEdit.text = qsTr("No select any file which need to be shredded");
                toolkits.alertMSG(qsTr("Shred success!"));//粉碎成功！
            }
            else {
                toolkits.alertMSG(qsTr("Shred abnormal!"));//粉碎出现异常！
            }
        }
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
//                pageStack.pop();
                pageStack.push(functioncollection);
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

    Column{
        spacing: 30
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: top_splitbar.bottom
            topMargin: 100
        }

        Column {
            spacing: 10
            AnimatedImage {
                id: doingImage
                anchors.horizontalCenter: parent.horizontalCenter
                width: 16
                height: 16
                visible: false
                source: "../../img/icons/move.gif"
            }
            Text {
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
                text: qsTr("The file need to be shredded: ")//需要粉碎的文件：
                wrapMode: Text.WordWrap
            }
            Rectangle {
                width: 409; height: 24
                color: "lightblue"
                Image {
                    id: backgroundImg
                    anchors.fill: parent
                    source: "../../img/icons/gray-bg-normal.png"
                }
                Text {
                    id: showEdit
                    width: backgroundImg.width-30
                    elide: Text.ElideRight
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 10
                    }
                    font.pixelSize: 13
                    color: "#7a7a7a"
                    text: qsTr("No select any file which need to be shredded")//未选择需要粉碎的文件
                }
                Rectangle{
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: 10
                    }
                    width: play.width;height: play.height; color: "transparent"
                    Image {id:play;source: "../../img/icons/folder.png"}
                    Image {
                        id: btnImg1
                        anchors.fill: parent
                        source: ""
                    }
                    MouseArea{
                        anchors.fill:parent
                        hoverEnabled: true
                        onEntered: {
                            btnImg1.source = "../../img/icons/folder_hover.png";
                            backgroundImg.source = "../../img/icons/gray-bg-hover.png";
                        }
                        onPressed: {
                            btnImg1.source = "../../img/icons/folder_hover.png";
                            backgroundImg.source = "../../img/icons/gray-bg-hover.png";
                        }
                        //要判断松开是鼠标位置
                        onReleased: {
                            btnImg1.source = "";
                            backgroundImg.source = "../../img/icons/gray-bg-normal.png";
                        }
                        onExited: {
                            btnImg1.source = "";
                            backgroundImg.source = "../../img/icons/gray-bg-normal.png";
                        }
                        onClicked: {
                            shredpage.selectedfile = "";
                            shredpage.selectedfile = sessiondispatcher.show_file_path_dialog();
                            if (shredpage.selectedfile.length == 0) {
                                showEdit.text = qsTr("No select any file which need to be shredded");
                            }
                            else {
                                showEdit.text = shredpage.selectedfile;
                            }
                        }
                    }
                }
            }
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
                text: qsTr("Shred File")
                onClicked: {
                    if(shredpage.selectedfile.length != 0) {
                        doingImage.visible = true;
                        shreddispatcher.shred_file_qt(shredpage.selectedfile);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-gray-long.png"
                picHover: "../../img/icons/button12-gray-long-hover.png"
                picPressed: "../../img/icons/button12-gray-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Deselect")
                onClicked: {
                    shredpage.selectedfile = "";
                    showEdit.text = qsTr("No select any file which need to be shredded");
                }
            }
        }
    }
}
