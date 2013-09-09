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
    property string image_flag:""
    property string recommendone_image: "../img/skin/qq-small.png"
    property string recommendtwo_image: "../img/skin/qt-small.png"
    property string recommendthree_image: "../img/skin/wps-small.png"
    property string recommendoneimage_image: "../img/skin/qq.png"
    property string recommendimage_text: "Winasd     asfsaff:asdfasdfa 2012 asd"

    Component.onCompleted: {
//        sudodispatcher.check_pkgs_status_qt(pkgNameList);
    }
    //信号绑定，绑定qt的信号
    Connections
    {
        target: sudodispatcher
//        onFinishSoftwareFetch: {
//            console.log(type);
//            console.log(msg);
//        }
//        onFinishSoftwareApt: {
//            console.log(type);
//            console.log(msg);
//        }
        onFinishSoftwareCheckStatus: {
            console.log("Software statusDict->");
            console.log(statusDict);
        }
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
        Image{
            anchors.fill:parent
            source: "../img/skin/linecolor.png"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("pageStack.push(image_flag);")
//                pageStack.push(image_flag);
            }
        }
        Rectangle{
            width: parent.width;height: 30
            anchors.bottom: parent.bottom
            color: "transparent"
            Text{
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                text:recommendimage_text
            }
            Common.Button{
                width: 80;height: 26
                anchors{
                    verticalCenter:parent.verticalCenter
                    right:parent.right
                    rightMargin: 15
                }
                text:"安装"
                onClicked: {
                    console.log("下载下载下载下载下载下载");
//                    sudodispatcher.show_progress_dialog();
                    console.log(mainwindow.pos.x);
                    console.log(mainwindow.pos.y);
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
                    imagframe.y=colum.y+recommendone.y
                    recommendoneimage_image="../img/skin/qq.png"
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
                    imagframe.y=colum.y+recommendtwo.y
                    recommendoneimage_image="../img/skin/qt.png"
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
                    imagframe.y=colum.y+recommendthree.y
                    recommendoneimage_image="../img/skin/wps.png"
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
//                Common.Button{
//                    id:recommended_top
//                    width:110;height: 25
//                    text:"推荐金榜单"
//                    hoverimage:"blue1.png"
//                    onClicked: {
//                        fontcolor="white"
//                        hoverimage="blue1.png"
//                        download_top.fontcolor="grey"
//                        download_top.hoverimage="gray1-hover.png"
//                    }
//                }
//                Common.Button{
//                    id:download_top
//                    width: 110;height: 25
//                    text:"下载排行榜"
//                    fontcolor: "grey"
//                    hoverimage:"gray1-hover.png"
//                    onClicked: {
//                        fontcolor="white"
//                        hoverimage="blue1.png"
//                        recommended_top.fontcolor="grey"
//                        recommended_top.hoverimage="gray1-hover.png"
//                    }
//                }
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
                    icon: "../img/icons/chromium.png"
                    flag: "Chromium"
                }
                ListElement {
                    icon: "../img/icons/irc.png"
                    flag: "EclipseQt"
                  }
                ListElement {
                    icon: "../img/icons/irc.png"
                    flag: "Irc"
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
                    icon: "../img/icons/lotus.png"
                    flag: "Lotus"
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
                    icon: "../img/icons/virtualbox.png"
                    flag: "Wineqq"
                }
                ListElement {
                    icon: "../img/icons/xchat.png"
                    flag: "Wps"
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
                cellWidth: (parent.width-8)/4; cellHeight: 90
    //                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true
            }
        }
    }

}
