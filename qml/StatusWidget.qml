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
import "./func/common" as Common
Rectangle {
    id: root
    width: parent.width
    height: 30
    color: "transparent"
    property string version: ""//优客助手版本号
//    property bool upcloud: false//金山快盘云配置使用
//    property bool downcloud: false//金山快盘上传云配置

    Connections
    {
        target: sessiondispatcher
        onTellDownloadCloudConfToQML: {
            if(download == "download_norun") {
//                root.downcloud = false;
                downloaddynamic.paused = true;
                downloaddynamic.playing = false;
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The kuaipan4uk is not running!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else if(download == "download_notconf") {
//                root.downcloud = false;
                downloaddynamic.paused = true;
                downloaddynamic.playing = false;
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Not found the cloud configuration!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else if(download == "download_ok") {
//                root.downcloud = false;
                downloaddynamic.paused = true;
                downloaddynamic.playing = false;
                toolkits.alertMSG(qsTr("Download OK!"), mainwindow.pos.x, mainwindow.pos.y);//使用完毕！
            }
        }
        onTellUploadCloudConfToQML: {
            if(upload == "upload_norun") {
//                root.upcloud = false;
                uploaddynamic.paused = true;
                uploaddynamic.playing = false;
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The kuaipan4uk is not running!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else if(upload == "upload_ok") {
//                root.upcloud = false;
                uploaddynamic.paused = true;
                uploaddynamic.playing = false;
                toolkits.alertMSG(qsTr("Upload OK!"), mainwindow.pos.x, mainwindow.pos.y);//上传完成！
            }
        }
    }

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


    Row {
        anchors {
            right: parent.right
            rightMargin: 3
            verticalCenter: parent.verticalCenter
        }
        spacing: 10
        Text {
            id: b1
            text: qsTr("Use Cloud")//使用云配置
            visible: false
        }
        Text {
            id: b2
            text: qsTr("Save Cloud")//保存云配置
            visible: false
        }

        Row {
            AnimatedImage {//动态图片
                id: downloaddynamic
                playing: false
                paused: true
                width: 25
                height: 25
                source: "./img/icons/download.gif"
            }
            Common.ColorButton {
                id: downBtn
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Use Cloud")//使用云配置
                textColor: "white"
                fontSize: 8
                width: b1.width
                height: 20
                onClicked: {
                    downloaddynamic.playing = true;
                    downloaddynamic.paused = false;
                    sessiondispatcher.download_kysoft_cloud_conf_qt();
                }
            }


        }
        Row {
            AnimatedImage {//动态图片
                id: uploaddynamic
                width: 25
                height: 25
                playing: false
                paused: true
                source: "./img/icons/upload.gif"
            }
            Common.ColorButton {
                id: upBtn
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Save Cloud")//保存云配置
                textColor: "white"
                fontSize: 8
                width: b2.width
                height: 20
                onClicked: {
                    uploaddynamic.playing = true;
                    uploaddynamic.paused = false;
                    sessiondispatcher.upload_kysoft_cloud_conf_qt();
                }
            }

        }
    }

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
//                anchors.verticalCenter: parent.verticalCenter
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Use Cloud Conf")//使用云配置
//                MouseArea {
//                    anchors.fill: downBtn
//                    onClicked: {
////                        root.downcloud = !root.downcloud;
////                        console.debug("00000");
////                        if(root.downcloud) {
////                            console.debug("1111");
////                            downloaddynamic.playing = true;
////                            downloaddynamic.paused = false;
////                        }
////                        else {
////                            console.debug("2222");
////                            downloaddynamic.paused = true;
////                            downloaddynamic.playing = false;
////                        }
//                        downloaddynamic.playing = true;
//                        downloaddynamic.paused = false;
//                        sessiondispatcher.download_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//            AnimatedImage {//动态图片
//                id: downloaddynamic
//                playing: false
//                paused: true
//                width: 25
//                height: 25
//                source: "./img/icons/download.gif"
//            }
//        }
//        Row {
//            Text {
//                id: upBtn
//                anchors.verticalCenter: parent.verticalCenter
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Upload Cloud Conf")//上传云配置
//                MouseArea {
//                    anchors.fill: upBtn
//                    onClicked: {
////                        root.upcloud = !root.upcloud;
////                        console.debug("00000");
////                        if(root.upcloud) {
////                            console.debug("1111");
////                            uploaddynamic.playing = true;
////                            uploaddynamic.paused = false;
////                        }
////                        else {
////                            console.debug("2222");
////                            uploaddynamic.paused = true;
////                            uploaddynamic.playing = false;
////                        }
//                        uploaddynamic.playing = true;
//                        uploaddynamic.paused = false;
//                        sessiondispatcher.upload_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//            AnimatedImage {//动态图片
//                id: uploaddynamic
////                visible: root.upcloud ? true : false
//                width: 25
//                height: 25
//                playing: false
//                paused: true
//                source: "./img/icons/upload.gif"
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
//                anchors.verticalCenter: parent.verticalCenter
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Use Cloud Conf")//使用云配置
//                MouseArea {
//                    anchors.fill: downBtn
//                    onClicked: {
//                        root.downcloud = true;
//                        sessiondispatcher.download_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//            AnimatedImage {//动态图片
//                id: downloaddynamic
//                visible: root.downcloud ? false : true
//                width: 25
//                height: 25
//                source: "./img/icons/download.png"
//            }
////            Image {
////                id: downloadImage
////                visible: root.downcloud ? false : true
////                width: 25
////                height: 25
////                source: "./img/icons/download.png"
////            }
////            AnimatedImage {//动态图片
////                id: downloaddynamic
////                visible: root.downcloud ? true : false
////                width: 16
////                height: 16
////                source: "./img/icons/move.gif"
////            }
//        }
//        Row {
//            Text {
//                id: upBtn
//                anchors.verticalCenter: parent.verticalCenter
//                color: "white"
//                font.pixelSize: 12
//                text: qsTr("Upload Cloud Conf")//上传云配置
//                MouseArea {
//                    anchors.fill: upBtn
//                    onClicked: {
//                        root.upcloud = true;
//                        sessiondispatcher.upload_kysoft_cloud_conf_qt();
//                    }
//                }
//            }
//            Image {
//                id: uploadImage
//                visible: root.upcloud ? false : true
//                width: 25
//                height: 25
//                source: "./img/icons/upload.png"
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
