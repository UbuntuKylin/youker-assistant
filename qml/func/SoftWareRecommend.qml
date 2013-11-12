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
import SessionType 0.1
import SystemType 0.1
import SudoType 0.1
import "common" as Common
import "bars" as Bars

Item {
    id: screen; width: parent.width; height: 475
//需要时常变动的变量
    property string image_flag:"wps"
    property string recommendone_image: "../img/skin/wps-small.png"
    property string recommendtwo_image: "../img/skin/qq-small.png"
    property string recommendthree_image: "../img/skin/qt-small.png"
    property string recommendoneimage_image: "../img/skin/wps.png"
    property string recommendimage_text: qsTr("WPS For UbuntuKylin，Linux系统上最好用的办公软件。")
    property string status_value: "n"
    property string status_value2: "n"

    Component.onCompleted: {
    }

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
        Image {
            id: statusImage
            source: "../img/icons/recommend.png"
            anchors{
                right:parent.right
                top: parent.top
            }
        }
        Image{
            anchors.fill:parent
            source: "../img/skin/linecolor.png"
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
                text: "详情"
                onClicked: {
                    sudodispatcher.ready_show_app_page("eclipse");
                    pageStack.push(softwarepage);
                }
            }
            Common.Button{
                width: 80;height: 26
                anchors{
                    verticalCenter:parent.verticalCenter
                    right:parent.right
                    rightMargin: 15
                }
                text: "详情"
                onClicked: {
                    if(screen.image_flag == "wps") {
                        sudodispatcher.ready_show_app_page("wps");
                    }
                    else if(screen.image_flag == "qq") {
                        sudodispatcher.ready_show_app_page("wineqq");
                    }
                    else if(screen.image_flag == "qt") {
                        sudodispatcher.ready_show_app_page("qtcreator");
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
        Item{
            id: recommendone
            width:imageone.width;height: imageone.height
            Image {
                id:imageone
                source: recommendone_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.image_flag = "wps";
                    screen.recommendimage_text = qsTr("WPS,Linux系统上最好用的办公软件。");
                    imagframe.y=colum.y+recommendone.y;
                    recommendoneimage_image="../img/skin/wps.png";
                }
            }
        }
        Item {
            id: recommendtwo
            width:imagetwo.width;height: imagetwo.height
            Image {
                id:imagetwo
                source: recommendtwo_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.image_flag = "qq";
                    screen.recommendimage_text = qsTr("WineQQ，Linux系统上最好用的QQ版本。");
                    imagframe.y=colum.y+recommendtwo.y;
                    recommendoneimage_image="../img/skin/qq.png";
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
                    screen.image_flag = "qt";
                    imagframe.y=colum.y+recommendthree.y;
                    recommendoneimage_image="../img/skin/qt.png";
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

        //收到软件列表信息后添加到QML界面上
        Connections
        {
            target: sudodispatcher
            onSendAppListToQML: {
                funcmodel.clear();
                var num = 0;
                for (var i=0; i< appList.length; i++) {
                    funcmodel.append({"icon": "../img/icons/" + appList[i] + ".png", "flag": appList[i]});
                }
            }
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
                    text:qsTr("推荐金榜单")
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
                ListElement {icon: ""; flag: ""}
            }

            Common.ScrollArea {
                frame:false
                anchors{
                    top:parent.top
                    topMargin: 1
                    left:parent.left
                    leftMargin: 1
                }
                height: parent.height-1
                width: parent.width-1
                Item {
                    width: views.width-20   //列表宽度
                    height: 4 * 95     //列表长度,前面的数字为列表行数
                    //垃圾清理显示内容
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
                }//Item
            }//ScrollArea
        }
    }
}



//Item {
//    id: screen; width: parent.width; height: 475
////需要时常变动的变量
//    property string image_flag:"wps"
//    property string recommendone_image: "../img/skin/wps-small.png"
//    property string recommendtwo_image: "../img/skin/qq-small.png"
//    property string recommendthree_image: "../img/skin/qt-small.png"
//    property string recommendoneimage_image: "../img/skin/wps.png"
//    property string recommendimage_text: "WPS For UbuntuKylin，Linux系统上最好用的办公软件。"
//    property string status_value: "n"
//    property string status_value2: "n"

//    Component.onCompleted: {
//    }
////    Connections
////    {
////        target: sudodispatcher
////        onReGetList: {
////            sudodispatcher.add_source_ubuntukylin_qt();
////            sudodispatcher.check_pkgs_status_qt(sudodispatcher.getAllSoftwareList());
////            sudodispatcher.remove_source_ubuntukylin_qt();
////        }
////    }
////
//    //背景
//    Image {
//        source: "../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }
//    Item {
//        id: recommendimage
//        width: 560
//        height: 210
//        anchors{
//            left: parent.left
//            leftMargin: 25
//            top:parent.top
//            topMargin: 25
//        }
//        Image {
//            anchors.fill:parent
//            source: recommendoneimage_image
//        }
//        Image {
//            id: statusImage
//            source: "../img/icons/recommend.png"
//            anchors{
//                right:parent.right
//                top: parent.top
//            }
//        }
//        Image{
//            anchors.fill:parent
//            source: "../img/skin/linecolor.png"
//        }
//        Rectangle{
//            width: parent.width;height: 30
//            anchors.bottom: parent.bottom
//            color: "transparent"
//            Text{
//                id: desc_text
//                visible: (screen.image_flag == "qt") ? false : true
//                anchors{
//                    left: parent.left
//                    leftMargin: 15
//                    verticalCenter: parent.verticalCenter
//                }
//                color: "white"
//                text:recommendimage_text
//            }
//            Common.Button{
//                id: ecliseBtn
//                visible: (screen.image_flag == "qt") ? true : false
//                width: 80;height: 26
//                anchors{
//                    left: parent.left
//                    leftMargin: 15
//                    verticalCenter: parent.verticalCenter
//                }
//                text: "详情"
//                onClicked: {
//                    if(screen.image_flag == "qt") {
//                        content.delegate_name= "eclipse"
//                        content.delegate_appname = "Eclipse平台(eclipse)"
//                        content.delegate_image= "../img/logo/eclipse.jpg"
//                        content.delegate_introduction="Eclipse 是一个开放源代码的、基于Java的可扩展开发平台。就其本身而言，它只是一个框架和一组服务，用于通过插件组件构建开发环境。幸运的是，Eclipse 附带了一个标准的插件集，包括Java开发工具（Java Development Kit，JDK）。"
//                        content.introduction_image1= "../img/character/eclipse-01.png"
//                        content.introduction_image2= "../img/character/eclipse-02.png"
////                        content.soft_status = sudodispatcher.getSoftwareStatus("eclipse");
//                        content.soft_status = sudodispatcher.check_pkg_status_qt("eclipse");
//                        sudodispatcher.notifySoftwareCurrentStatus(content.soft_status);
//                    }
//                    pageStack.push(softwarepage);
//                }
//            }
//            Common.Button{
//                width: 80;height: 26
//                anchors{
//                    verticalCenter:parent.verticalCenter
//                    right:parent.right
//                    rightMargin: 15
//                }
//                text: "详情"
//                onClicked: {
//                    if(screen.image_flag == "wps") {
//                        sudodispatcher.add_source_ubuntukylin_qt();
//                        content.delegate_name= "wps-office"
//                        content.delegate_appname = "WPS For UbuntuKylin(wps-office)"
//                        content.delegate_image= "../img/logo/wps.jpg"
//                        content.delegate_introduction="Ubuntukylin团队与金山公司合作，于13.04开始首先推出WPS for UbuntuKylin 1.0，并于13.10推出WPS for UbuntuKylin1.2。与1.0版本相比，1.2版进行了稳定性提升、BUG修复、同时增加了数据透视表等功能，使您的文档工作更加专业和轻松。"
//                        content.introduction_image1= "../img/character/wps-01.png"
//                        content.introduction_image2= "../img/character/wps-02.png"
////                        content.soft_status = sudodispatcher.getSoftwareStatus("wps-office");
//                        content.soft_status = sudodispatcher.check_pkg_status_qt("wps-office");
//                        sudodispatcher.notifySoftwareCurrentStatus(content.soft_status);
//                        sudodispatcher.remove_source_ubuntukylin_qt();
//                    }
//                    else if(screen.image_flag == "qq") {
//                        content.delegate_name= "wine-qq2012-longeneteam"
//                        content.delegate_appname = "Wine 1.5.18 patched for qq2012 Beta3"
//                        content.delegate_image= "../img/logo/qq.jpg"
//                        content.delegate_introduction="QQ2012基于官方Beta3版，支持双击deb包安装、支持全局热键、不会自动离线、文件传输正常、ibus中文输入法正常。"
//                        content.introduction_image1= "../img/character/qq-01.png"
//                        content.introduction_image2= "../img/character/qq-02.png"
////                        content.soft_status = sudodispatcher.getSoftwareStatus("wine-qq2012-longeneteam");
//                        content.soft_status = sudodispatcher.check_pkg_status_qt("wine-qq2012-longeneteam");
//                        sudodispatcher.notifySoftwareCurrentStatus(content.soft_status);
//                    }
//                    else if(screen.image_flag == "qt") {
//                        content.delegate_name= "qtcreator"
//                        content.delegate_appname = "Qt平台(qtcreator)"
//                        content.delegate_image= "../img/logo/qtcreator.jpg"
//                        content.delegate_introduction="Qt Creator是跨平台的 Qt IDE， Qt Creator 是 Qt 被 Nokia 收购后推出的一款新的轻量级集成开发环境（IDE）。此 IDE 能够跨平台运行，支持的系统包括 Linux（32 位及 64 位）、Mac OS X 以及 Windows。"
//                        content.introduction_image1= "../img/character/qtcreator-01.png"
//                        content.introduction_image2= "../img/character/qtcreator-02.png"
////                        content.soft_status = sudodispatcher.getSoftwareStatus("qtcreator");
//                        content.soft_status = sudodispatcher.check_pkg_status_qt("qtcreator");
//                        sudodispatcher.notifySoftwareCurrentStatus(content.soft_status);
//                    }
//                    pageStack.push(softwarepage);
//                }
//            }
//        }
//    }
//    Column{
//        id:colum
//        anchors{
//            top:parent.top
//            topMargin: 25
//            right: parent.right
//            rightMargin: 25
//        }
//        spacing: 5
//        Item{
//            id: recommendone
//            width:imageone.width;height: imageone.height
//            Image {
//                id:imageone
//                source: recommendone_image
//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked: {
////                    screen.status_value = sudodispatcher.getSoftwareStatus("qq");
//                    screen.image_flag = "wps";
//                    screen.recommendimage_text = "WPS,Linux系统上最好用的办公软件。";
//                    imagframe.y=colum.y+recommendone.y;
//                    recommendoneimage_image="../img/skin/wps.png";
//                }
//            }
//        }
//        Item {
//            id: recommendtwo
//            width:imagetwo.width;height: imagetwo.height
//            Image {
//                id:imagetwo
//                source: recommendtwo_image
//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked: {
////                    screen.status_value = sudodispatcher.getSoftwareStatus("qq");
//                    screen.image_flag = "qq";
//                    screen.recommendimage_text = "WineQQ，Linux系统上最好用的QQ版本。";
//                    imagframe.y=colum.y+recommendtwo.y;
//                    recommendoneimage_image="../img/skin/qq.png";
//                }
//            }
//        }
//        Item{
//            id: recommendthree
//            width:imagethree.width;height: imagethree.height
//            Image {
//                id:imagethree
//                source: recommendthree_image
//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked: {
////                    screen.status_value = sudodispatcher.getSoftwareStatus("qtcreator");
////                    screen.status_value2 = sudodispatcher.getSoftwareStatus("qq");
//                    screen.image_flag = "qt";
//                    imagframe.y=colum.y+recommendthree.y;
//                    recommendoneimage_image="../img/skin/qt.png";
//                }
//            }
//        }
//    }

//    Image {
//        id: imagframe
//        source: "../img/skin/frame.png"
//        x:colum.x-13;y:colum.y
//        opacity: 0.8
//    }

//    Rectangle {
//        id: views
//        width: parent.width-50
//        height: 227
//        anchors{
//            bottom:parent.bottom
//            left: parent.left
//            leftMargin: 25
//        }
//        clip:true
//        border.color: "#9aa2af"
//        color: "#e6ebfe"
//        Rectangle{
//            id:rec
//            width: parent.width-1;height: 31
//            anchors{
//                top:parent.top
//                topMargin: 1
//                left: parent.left
//                leftMargin: 1
//            }
//            gradient: Gradient{
//                GradientStop{position: 0.0; color: "#e2e2e2"}
//                GradientStop{position: 1.0; color: "#dedede"}
//            }
//            Row{
//                anchors.centerIn: parent
//                spacing: 50
//                Text {
//                    text:"推荐金榜单"
//                    color: "#6b6f70"
//                    font.pixelSize: 14
//                }
//            }
//        }
//        Rectangle{id: splitbar1; anchors{top:rec.bottom;left: parent.left;leftMargin: 1 }width:parent.width-1 ; height:1; color:"#b8bdc3"}
//        Rectangle{id: splitbar2; anchors{top:splitbar1.bottom;left: parent.left;leftMargin: 1  }width:parent.width-1 ; height:1; color:"#ebf0f6"}
//        Item {
//            width: views.width
//            height: 194
//            anchors.bottom: parent.bottom
//            clip:true
//            ListModel {
//                id: funcmodel
//                ListElement {
//                    icon: "../img/icons/kuaipan.png"
//                    flag: "Kuaipan"
//                }
//                ListElement {
//                    icon: "../img/icons/Pps.png"
//                    flag: "Pps"
//                }ListElement {
//                    icon: "../img/icons/kugou.png"
//                    flag: "KugouMusic"
//                }
//                ListElement {
//                    icon: "../img/icons/xunlei.png"
//                    flag: "XunLei"
//                }
//                ListElement {
//                    icon: "../img/icons/stardict.png"
//                    flag: "StarDict"
//                }
//                ListElement {
//                    icon: "../img/icons/adobe-flash.png"
//                    flag: "AdobeFlash"
//                }
//                ListElement {
//                    icon: "../img/icons/vlc.png"
//                    flag: "Vlc"
//                }
//                ListElement {
//                    icon: "../img/icons/chromium.png"
//                    flag: "Chromium"
//                }
//                ListElement {
//                    icon: "../img/icons/virtualbox.png"
//                    flag: "VirtualBox"
//                }
//                ListElement {
//                    icon: "../img/icons/qbittorrent.png"
//                    flag: "QbitTorrent"
//                }
//                ListElement {
//                    icon: "../img/icons/xchat.png"
//                    flag: "XChat"
//                }
//                ListElement {
//                    icon: "../img/icons/lotus.png"
//                    flag: "Lotus"
//                }
//                ListElement {
//                    icon: "../img/icons/openfetion.png"
//                    flag: "OpenFetion"
//                }

////                ListElement {
////                    icon: "../img/icons/eclipse.png"
////                    flag: "Eclipse"
////                }
////                ListElement {
////                    icon: "../img/icons/qt.png"
////                    flag: "Qtcreator"
////                }
////                ListElement {
////                    icon: "../img/icons/qq.png"
////                    flag: "Wineqq"
////                }
////                ListElement {
////                    icon: "../img/icons/wps.png"
////                    flag: "Wps"
////                }
//            }

//            Common.ScrollArea {
//                frame:false
//                anchors{
//                    top:parent.top
//                    topMargin: 1
//                    left:parent.left
//                    leftMargin: 1
//                }
//                height: parent.height-1
//                width: parent.width-1
//                Item {
//                    width: views.width-20   //列表宽度
//                    height: 4 * 95     //列表长度,前面的数字为列表行数
//                    //垃圾清理显示内容
//                    GridView {
//                        id: gridView
//                        height: parent.height-12
//                        width: parent.width
//                        anchors {
//                            top: parent.top
//                            topMargin: 12
//                            left: parent.left
//                            leftMargin: 20
//                        }
//                        model: funcmodel
//                        delegate: SoftwareDelegate {}
//                        cacheBuffer: 1000
//                        cellWidth: 190; cellHeight: 90
//                        focus: true
//                    }
//                }//Item
//            }//ScrollArea

////            GridView {
////                id: gridView
////                height: parent.height-12
////                width: parent.width
////                anchors {
////                    top: parent.top
////                    topMargin: 12
////                    left: parent.left
////                    leftMargin: 20
////                }
////                model: funcmodel
////                delegate: SoftwareDelegate {}
////                cacheBuffer: 1000
////                cellWidth: 190; cellHeight: 90
////                focus: true
////            }
////            Rectangle{
////                id:scrollbar
////                anchors.right: parent.right
////                anchors.rightMargin: 4
////                height: parent.height-1
////                width:13
////                color: "lightgrey"
////            }
////            Rectangle{
////                id: button
////                anchors.right: parent.right
////                anchors.rightMargin: 5
////                width: 12
////                y: gridView.visibleArea.yPosition * (scrollbar.height + 100) //257
//////                height: gridView.visibleArea.heightRatio * scrollbar.height;
////                height: 45
////                radius: 3
////                smooth: true
////                color: "white"
////                border.color: "lightgrey"
////                Column{
////                    anchors.verticalCenter: parent.verticalCenter
////                    anchors.horizontalCenter: parent.horizontalCenter
////                    spacing: 2
////                    Rectangle{
////                        width: 8;height: 1
////                        color: "lightgrey"
////                    }
////                    Rectangle{
////                        width: 8;height: 1
////                        color: "lightgrey"
////                    }
////                    Rectangle{
////                        width: 8;height: 1
////                        color: "lightgrey"
////                    }
////                }
////                MouseArea {
////                    id: mousearea
////                    anchors.fill: button
////                    drag.target: button
////                    drag.axis: Drag.YAxis
////                    drag.minimumY: 0
////                    drag.maximumY: scrollbar.height - button.height
////                    onMouseYChanged: {
////                        gridView.contentY = button.y / (scrollbar.height + 100) * gridView.contentHeight //257
////                    }
////                }
////            }
//        }
//    }
//}
