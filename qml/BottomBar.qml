/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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
import CloundType 0.1
import ToolkitsType 0.1
import "./func/common" as Common

Rectangle {
    id: bottombar
    width: 850
    height: 26
    color: "transparent"
    property string version: "V1.3.2"

    CloundDispatcher {  id: clounddispatcher  }
    Toolkits{ id: toolkits }

    Connections
    {
        target: clounddispatcher
        onStartShowIPAddress: {
            if (ip_addr === '') {
                iprow.visible = false;
            }
            else {
                iprow.visible = true;
                ip.text = ip_addr;
            }
        }

//        onTellDownloadCloudConfToQML: {
//            if(download == "download_norun") {
////                root.downcloud = false;
//                downloaddynamic.paused = true;
//                downloaddynamic.playing = false;
//                clounddispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The kuaipan4uk is not running!"));
//            }
//            else if(download == "download_notconf") {
////                root.downcloud = false;
//                downloaddynamic.paused = true;
//                downloaddynamic.playing = false;
//                clounddispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Not found the cloud configuration!"));
//            }
//            else if(download == "download_ok") {
////                root.downcloud = false;
//                downloaddynamic.paused = true;
//                downloaddynamic.playing = false;
//                toolkits.alertMSG(qsTr("Download OK!"));//使用完毕！
//            }
//        }
//        onTellUploadCloudConfToQML: {
//            if(upload == "upload_norun") {
////                root.upcloud = false;
//                uploaddynamic.paused = true;
//                uploaddynamic.playing = false;
//                clounddispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The kuaipan4uk is not running!"));
//            }
//            else if(upload == "upload_ok") {
////                root.upcloud = false;
//                uploaddynamic.paused = true;
//                uploaddynamic.playing = false;
//                toolkits.alertMSG(qsTr("Upload OK!"));//上传完成！
//            }
//        }
    }

    Component.onCompleted: {
        clounddispatcher.get_ip_address_qt();
    }
    Row {
        id: versionrow
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        spacing: 2
        Image {
            source: "./img/icons/arrowhead.png"
            width: 18; height: 18
        }
        Text {
            color: "white"
            font.pixelSize: 12
            text: qsTr("main version:") + bottombar.version//主版本：
        }
    }

    Row {
        id: iprow
        visible: false
        anchors {
            right: parent.right
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
//        anchors {
//            left: versionrow.right
//            leftMargin: 20
//            verticalCenter: parent.verticalCenter
//        }
        spacing: 2
        Image {
            source: "./img/icons/ip.png"
            width: 18; height: 18
        }
        Text {
            id: ip
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            font.pixelSize: 12
            text: ""
        }
    }

//    Row {
//        anchors {
//            right: parent.right
//            rightMargin: 3
//            verticalCenter: parent.verticalCenter
//        }
//        spacing: 10
//        Text {
//            id: b1
//            text: qsTr("Use Cloud")//使用云配置
//            visible: false
//        }
//        Text {
//            id: b2
//            text: qsTr("Save Cloud")//保存云配置
//            visible: false
//        }

//        Row {
//            AnimatedImage {//动态图片
//                id: downloaddynamic
//                anchors.verticalCenter: parent.verticalCenter
//                playing: false
//                paused: true
//                width: 24
//                height: 16
//                source: "./img/icons/download.gif"
//            }
//            Common.ColorButton {
//                id: downBtn
//                anchors.verticalCenter: parent.verticalCenter
//                wordname: qsTr("Use Cloud")//使用云配置
//                colorNormal: "white"
//                colorHover: "white"
//                colorPressed: "white"
//                sizeNormal: 12
//                sizeHover: 14
//                sizePressed: 14
//                width: b1.width
//                height: 20
//                onClicked: {
//                    if(clounddispatcher.showConfirmDialog(qsTr("Tips:"), qsTr("It will use the Kingsoft disk cloud configuration!"))) {
//                        downloaddynamic.playing = true;
//                        downloaddynamic.paused = false;
//                        clounddispatcher.download_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//        }
//        Row {
//            AnimatedImage {//动态图片
//                id: uploaddynamic
//                anchors.verticalCenter: parent.verticalCenter
//                width: 24
//                height: 16
//                playing: false
//                paused: true
//                source: "./img/icons/upload.gif"
//            }
//            Common.ColorButton {
//                id: upBtn
//                anchors.verticalCenter: parent.verticalCenter
//                wordname: qsTr("Save Cloud")//保存云配置
//                colorNormal: "white"
//                colorHover: "white"
//                colorPressed: "white"
//                sizeNormal: 12
//                sizeHover: 14
//                sizePressed: 14
//                width: b2.width
//                height: 20
//                onClicked: {
//                    if(clounddispatcher.showConfirmDialog(qsTr("Tips:"), qsTr("It will upload configuration to the Kingsoft disk cloud!"))) {
//                        uploaddynamic.playing = true;
//                        uploaddynamic.paused = false;
//                        clounddispatcher.upload_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//        }
//    }
}
