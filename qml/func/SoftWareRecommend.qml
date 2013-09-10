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
import SessionType 0.1
import SystemType 0.1
import SudoType 0.1
import "common" as Common
import "bars" as Bars
Item {
    id: screen; width: parent.width; height: 475
//需要时常变动的变量
    property string image_flag:"qq"
    property string recommendone_image: "../img/skin/qq-small.png"
    property string recommendtwo_image: "../img/skin/qt-small.png"
    property string recommendthree_image: "../img/skin/wps-small.png"
    property string recommendoneimage_image: "../img/skin/qq.png"
    property string recommendimage_text: "WineQQ,Linux系统上最好用的QQ版本。"
    property string status_value: "n"
    property string status_value2: "n"

    Component.onCompleted: {
//        sudodispatcher.check_pkgs_status_qt(pkgNameList);
    }
//    //信号绑定，绑定qt的信号
//    Connections
//    {
//        target: sudodispatcher
//        onFinishSoftwareFetch: {
//            console.log(type);
//            console.log(msg);
//        }
//        onFinishSoftwareApt: {
//            console.log(type);
//            console.log(msg);
//        }
//        onFinishSoftwareCheckStatus: {
//            console.log("Software statusDict->");
//            console.log(statusDict);
//        }
//    }

        //背景
    Image {
        source: "../img/skin/bg-middle.png"
        anchors.fill: parent
    }
    Item {
        id: recommendimage
        width: 560
        height: 210
        anchors{
            left: parent.left
            leftMargin: 25
            top:parent.top
            topMargin: 25
        }
        Image {
            anchors.fill:parent
            source: recommendoneimage_image
        }
        Image{
            anchors.fill:parent
            source: "../img/skin/linecolor.png"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
//                console.log("pageStack.push(image_flag);")
//                pageStack.push(image_flag);
            }
        }
        Rectangle{
            width: parent.width;height: 30
            anchors.bottom: parent.bottom
            color: "transparent"
            Text{
                id: desc_text
                visible: (screen.image_flag == "qt") ? false : true
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                text:recommendimage_text
            }
            Common.Button{
                id: ecliseBtn
                visible: (screen.image_flag == "qt") ? true : false
                width: 80;height: 26
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                text: {
                    if(screen.status_value2 == "i")
                        "卸载"
                    else if(screen.status_value2 == "n")
                        "安装"
                    else if(screen.status_value2 == "u")
                        "升级"
                }
                onClicked: {
                    console.log("eclipse clicked....");
//                    screen.status_value2 = sudodispatcher.check_pkg_status_qt("eclipse");
//                    if(screen.status_value2 == "n") {
//                        console.log("start to install....");
//                        sudodispatcher.show_progress_dialog();
//                        sudodispatcher.install_pkg_qt("qq");
//                    }
//                    else if(screen.status_value2 == "i") {
//                        console.log("is installed already, start to uninstall....");
//                        sudodispatcher.show_progress_dialog();
//                        sudodispatcher.uninstall_pkg_qt("eclipse");
//                    }
//                    else if(screen.status_value2 == "u") {
//                        console.log("is installed already, start to update....");
//                        sudodispatcher.show_progress_dialog();
//                        sudodispatcher.update_pkg_qt("eclipse");
//                    }
                }
            }
            Common.Button{
                width: 80;height: 26
                anchors{
                    verticalCenter:parent.verticalCenter
                    right:parent.right
                    rightMargin: 15
                }
                text: {
                    if(screen.status_value == "i")
                        "卸载"
                    else if(screen.status_value == "n")
                        "安装"
                    else if(screen.status_value == "u")
                        "升级"
                }
                onClicked: {
                    if(screen.image_flag == "qq") {
                        console.log("qq clicked....");
//                        screen.status_value = sudodispatcher.check_pkg_status_qt("qq");
//                        if(screen.status_value == "n") {
//                            console.log("start to install....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.install_pkg_qt("qq");
//                        }
//                        else if(screen.status_value == "i") {
//                            console.log("is installed already, start to uninstall....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.uninstall_pkg_qt("qq");
//                        }
//                        else if(screen.status_value == "u") {
//                            console.log("is installed already, start to update....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.update_pkg_qt("qq");
//                        }
                    }
                    else if(screen.image_flag == "qt") {
                        console.log("qt clicked....");
//                        screen.status_value = sudodispatcher.check_pkg_status_qt("qtcreator");
//                        if(screen.status_value == "n") {
//                            console.log("start to install....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.install_pkg_qt("qtcreator");
//                        }
//                        else if(screen.status_value == "i") {
//                            console.log("is installed already, start to uninstall....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.uninstall_pkg_qt("qtcreator");
//                        }
//                        else if(screen.status_value == "u") {
//                            console.log("is installed already, start to update....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.update_pkg_qt("qtcreator");
//                        }
                    }
                    else if(screen.image_flag == "wps") {
                        console.log("wps clicked....");
//                        screen.status_value = sudodispatcher.check_pkg_status_qt("wps");
//                        if(screen.status_value == "n") {
//                            console.log("start to install....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.install_pkg_qt("wps");
//                        }
//                        else if(screen.status_value == "i") {
//                            console.log("is installed already, start to uninstall....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.uninstall_pkg_qt("wps");
//                        }
//                        else if(screen.status_value == "u") {
//                            console.log("is installed already, start to update....");
//                            sudodispatcher.show_progress_dialog();
//                            sudodispatcher.update_pkg_qt("wps");
//                        }
                    }
                }
            }
        }
    }
    Column{
        id:colum
        anchors{
            top:parent.top
            topMargin: 25
            right: parent.right
            rightMargin: 25
        }
        spacing: 5
        Item {
            id: recommendone
            width:imageone.width;height: imageone.height
            Image {
                id:imageone
                source: recommendone_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.status_value = sudodispatcher.get_value("ubiquity");
                    screen.image_flag = "qq";
                    screen.recommendimage_text = "WineQQ,Linux系统上最好用的QQ版本。";
                    imagframe.y=colum.y+recommendone.y;
                    recommendoneimage_image="../img/skin/qq.png";
                }
            }
        }
        Item{
            id: recommendtwo
            width:imagetwo.width;height: imagetwo.height
            Image {
                id:imagetwo
                source: recommendtwo_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.status_value = sudodispatcher.get_value("qtcreator");
                    screen.status_value2 = sudodispatcher.get_value("ubiquity");
                    screen.image_flag = "qt";
                    imagframe.y=colum.y+recommendtwo.y;
                    recommendoneimage_image="../img/skin/qt.png";
                }
            }
        }
        Item{
            id: recommendthree
            width:imagethree.width;height: imagethree.height
            Image {
                id:imagethree
                source: recommendthree_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.status_value = sudodispatcher.get_value("ubiquity");
                    screen.image_flag = "wps";
                    screen.recommendimage_text = "WPS,Linux系统上最好用的办公软件。";
                    imagframe.y=colum.y+recommendthree.y;
                    recommendoneimage_image="../img/skin/wps.png";
                }
            }
        }
    }

    Image {
        id: imagframe
        source: "../img/skin/frame.png"
        x:colum.x-13;y:colum.y
        opacity: 0.8
    }

    Rectangle {
        id: views
        width: parent.width-50
        height: 227
        anchors{
            bottom:parent.bottom
            left: parent.left
            leftMargin: 25
        }
        clip:true
        border.color: "#9aa2af"
        color: "#e6ebfe"
        Rectangle{
            id:rec
            width: parent.width-1;height: 31
            anchors{
                top:parent.top
                topMargin: 1
                left: parent.left
                leftMargin: 1
            }
            gradient: Gradient{
                GradientStop{position: 0.0; color: "#e2e2e2"}
                GradientStop{position: 1.0; color: "#dedede"}
            }
            Row{
                anchors.centerIn: parent
                spacing: 50
                Text {
                    text:"推荐金榜单"
                    color: "#6b6f70"
                    font.pixelSize: 14
                }
            }
        }
        Rectangle{id: splitbar1; anchors{top:rec.bottom;left: parent.left;leftMargin: 1 }width:parent.width-1 ; height:1; color:"#b8bdc3"}
        Rectangle{id: splitbar2; anchors{top:splitbar1.bottom;left: parent.left;leftMargin: 1  }width:parent.width-1 ; height:1; color:"#ebf0f6"}
        Item {
            width: views.width
            height: 180
            anchors.bottom: parent.bottom
            clip:true
            ListModel {
                id: funcmodel
                ListElement {
                    icon: "../img/icons/adobe-flash.png"
                    flag: "AdobeFlash"
                }
                ListElement {
                    icon: "../img/icons/lotus.png"
                    flag: "Lotus"
                }
                ListElement {
                    icon: "../img/icons/qq.png"
                    flag: "Wineqq"
                }
                ListElement {
                    icon: "../img/icons/wps.png"
                    flag: "Wps"
                }
                ListElement {
                    icon: "../img/icons/eclipse.png"
                    flag: "Eclipse"
                  }
                ListElement {
                    icon: "../img/icons/qt.png"
                    flag: "Qtcreator"
                  }
                ListElement {
                    icon: "../img/icons/chromium.png"
                    flag: "Chromium"
                }
                ListElement {
                    icon: "../img/icons/kuaipan.png"
                    flag: "Kuaipan"
                }
                ListElement {
                    icon: "../img/icons/kugou.png"
                    flag: "KugouMusic"
                  }
                ListElement {
                    icon: "../img/icons/Pps.png"
                    flag: "Pps"
                }
                ListElement {
                    icon: "../img/icons/qbittorrent.png"
                    flag: "QbitTorrent"
                  }
                ListElement {
                    icon: "../img/icons/stardict.png"
                    flag: "StarDict"
                }
                ListElement {
                    icon: "../img/icons/vic.png"
                    flag: "Vic"
                }
                ListElement {
                    icon: "../img/icons/virtualbox.png"
                    flag: "VirtualBox"
                  }
                ListElement {
                    icon: "../img/icons/xchat.png"
                    flag: "XChat"
                }
                ListElement {
                    icon: "../img/icons/xunlei.png"
                    flag: "XunLei"
                }
            }
            GridView {
                id: gridView
                height: parent.height
                width: parent.width
                anchors {
                    top: parent.top
                    left: parent.left
                    leftMargin: 20
                }
                model: funcmodel
                delegate: SoftwareDelegate {}
                cacheBuffer: 1000
                cellWidth: 190; cellHeight: 90
                focus: true
            }
            Rectangle{
                id:scrollbar
                anchors.right: parent.right
                anchors.rightMargin: 8
                height: parent.height-5
                width:5
                color: "lightgrey"
            }
            Rectangle{
                id: button
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 12
                y: gridView.visibleArea.yPosition * scrollbar.height
                height: gridView.visibleArea.heightRatio * scrollbar.height;
                radius: 3
                smooth: true
                color: "white"
                border.color: "lightgrey"
                Column{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                }
                MouseArea {
                    id: mousearea
                    anchors.fill: button
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height
                    onMouseYChanged: {
                        gridView.contentY = button.y / scrollbar.height * gridView.contentHeight
                    }
                }
            }
        }
    }

}
