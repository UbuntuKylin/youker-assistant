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

    function show_text(showtext) {
        if(showtext == "i")
            return "卸载";
        else if(showtext == "n")
            return "安装";
        else if(showtext == "u")
            return "升级";
        else
            return "N/A";
    }

    Component.onCompleted: {
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
                text: "详情"//screen.show_text(screen.status_value2)
                onClicked: {
                    if(screen.image_flag == "qt") {
                        content.delegate_name= "eclipse"
                        content.delegate_appname = "Eclipse开发平台"
                        content.delegate_information= "Eclipse"
                        content.delegate_image= "../img/logo/eclipse.jpg"
                        content.delegate_introduction="Eclipse 是一个开放源代码的、基于Java的可扩展开发平台。就其本身而言，它只是一个框架和一组服务，用于通过插件组件构建开发环境。幸运的是，Eclipse 附带了一个标准的插件集，包括Java开发工具（Java Development Kit，JDK）。"
                        content.introduction_image1= "../img/character/eclipse-01.png"
                        content.introduction_image2= "../img/character/eclipse-02.png"
                        content.install_status = sudodispatcher.get_value("eclipse");
                    }
                    pageStack.push(softwarepage);

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
                text: "详情"//screen.show_text(screen.status_value)
                onClicked: {
                    if(screen.image_flag == "qq") {
                        content.delegate_name= "Wineqq"
                        content.delegate_appname = "WineQQ安装程序"
                        content.delegate_information= "QQ"
                        content.delegate_image= "../img/logo/qq.jpg"
                        content.delegate_introduction="借助wine模拟运行的腾讯QQ 2012客户端，选自longene项目。"
                        content.introduction_image1= "../img/character/qq-01.png"
                        content.introduction_image2= "../img/character/qq-02.png"
                        content.install_status = sudodispatcher.get_value("ubiquity");
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
                        content.delegate_name= "qtcreator"
                        content.delegate_appname = "Qt集成开发环境"
                        content.delegate_information= "Qt"
                        content.delegate_image= "../img/logo/qtcreator.jpg"
                        content.delegate_introduction="Qt Creator是跨平台的 Qt IDE， Qt Creator 是 Qt 被 Nokia 收购后推出的一款新的轻量级集成开发环境（IDE）。此 IDE 能够跨平台运行，支持的系统包括 Linux（32 位及 64 位）、Mac OS X 以及 Windows。"
                        content.introduction_image1= "../img/character/qtcreator-01.png"
                        content.introduction_image2= "../img/character/qtcreator-02.png"
                        content.install_status = sudodispatcher.get_value("qtcreator");
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
                            content.delegate_name= "wps"
                            content.delegate_appname = "WPS办公软件"
                            content.delegate_information= "WPS"
                            content.delegate_image= "../img/logo/wps.jpg"
                            content.delegate_introduction="由珠海金山办公软件有限公司与CCN联合实验室合作推出<WPS for UbuntuKylin>系列办公软件，并由珠海金山办公软件有限公司授权UbuntuKylin开源操作系统个人用户作为最终用户免费下载、安装和使 用。经测试，该版本在12.04和13.04上均可使用。"
                            content.introduction_image1= "../img/character/wps-01.png"
                            content.introduction_image2= "../img/character/wps-02.png"
                            content.install_status = sudodispatcher.get_value("ubiquity");
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
                    pageStack.push(softwarepage);
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
//                    screen.status_value = sudodispatcher.get_value("ubiquity");
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
//                    screen.status_value = sudodispatcher.get_value("qtcreator");
//                    screen.status_value2 = sudodispatcher.get_value("ubiquity");
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
//                    screen.status_value = sudodispatcher.get_value("ubiquity");
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
            height: 194
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
                height: parent.height-12
                width: parent.width
                anchors {
                    top: parent.top
                    topMargin: 12
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
                anchors.rightMargin: 4
                height: parent.height-1
                width:11
                color: "lightgrey"
            }
            Rectangle{
                id: button
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 10
                y: gridView.visibleArea.yPosition * (scrollbar.height+(gridView.visibleArea.heightRatio * scrollbar.height))
//                height: gridView.visibleArea.heightRatio * scrollbar.height;
                height: 45
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
                        gridView.contentY = button.y / (scrollbar.height+gridView.visibleArea.heightRatio * scrollbar.height-20) * gridView.contentHeight
                    }
                }
            }
        }
    }

}
