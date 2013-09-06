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
//import SessionType 0.1
import SystemType 0.1
import "../common" as Common
import "../bars" as Bars
import "../../func" as Func
Rectangle {
    id: adobeflash
    property bool on: true
////需要时常变动的变量
//    property string software_name: "Qafa1asd"
//    property string software_information:"asdasd:asdfsa12   afasf:1231M  asfs:2013-9-1"
//    property string software_image: "../../img/icons/bug.png"
//    property string software_introduction:  "腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
//    property string introduction_image1:  "../../img/skin/HighContrast.png"
//    property string introduction_image2: "../../img/skin/Radiance.png"

    //需要时常变动的变量
        property string software_name: content.delegate_name
        property string software_information: content.delegate_information
        property string software_image: content.delegate_image
        property string software_introduction: content.delegate_introduction
        property string introduction_image1: content.introduction_image1
        property string introduction_image2: content.introduction_image2
    width: parent.width
    height: 475

    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Rectangle{
        width: parent.width-2;height: 36
        color: "lightgrey"
        anchors{
            top:parent.top
            left: parent.left
            leftMargin: 1
        }
        Common.Button{
            width: 80;height: 28
            anchors{
                left: parent.left
                leftMargin: 8
                verticalCenter: parent.verticalCenter
            }
            hoverimage: "blue1.png"
            text:"返回"
            fontcolor: "grey"
            fontsize: 14
            onClicked: {
                pageStack.push(softwarerecommend);
            }
        }
        Text {
            anchors.centerIn: parent
            text:"详细信息"
            color:"grey"
            font.bold: true
            font.pixelSize: 14
        }
    }
    Rectangle{
        width: parent.width-50;height: 110
        anchors{
            top:parent.top
            topMargin: 47
            left: parent.left
            leftMargin: 25
        }
        border.color: "lightgrey"
        Image {
            id: softwareimage
            source: software_image
//            source: softwaredelegate.delegate_image
            anchors{
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }
        Column{
            anchors{
                left: parent.left
                leftMargin: 105
                verticalCenter: parent.verticalCenter
            }
            spacing: 10
            Text{
                id:softwarename
                text:software_name
//                text:softwaredelegate.delegate_name

                font.pixelSize: 18
            }
            Text {
                id: softwareinformation
                text: software_information
//                text:softwaredelegate.delegate_information

                font.pixelSize: 14
            }
        }
        Common.Button{
            width:145;height: 43
            anchors{
                right:parent.right
                rightMargin: 125
                verticalCenter: parent.verticalCenter
            }
            text:"立即下载"
            fontsize: 20
            onClicked: {
                console.log("立即下载")
            }
        }

    }
    Rectangle {
        id: views
        width: parent.width-50
        height: 276
        anchors{
            bottom:parent.bottom
            bottomMargin: 17
            left: parent.left
            leftMargin: 25
        }
        color: "#eeeeee"
        clip:true
        border.color: "#b9c5cc"
        Rectangle{
            width: parent.width-1;height: 31
            anchors{
                top:parent.top
                topMargin: 1
                left: parent.left
                leftMargin: 1
            }
            color: "lightgrey"
            Text {
                anchors.centerIn: parent
                text:"软件介绍"
                color:"grey"
                font.bold: true
                font.pixelSize: 14
            }
        }
        Text {
            id: softwareintroduction
            width: parent.width-30
            anchors{
                left:parent.left
                leftMargin: 15
                top:parent.top
                topMargin: 46
            }
            font.pixelSize: 13
            text: software_introduction
//            text:softwaredelegate.delegate_introduction
            wrapMode: Text.WrapAnywhere
        }
        Row{
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 20
            }
            spacing: 80
            Image {
                id: introductionimage1
                source: introduction_image1
//                source: softwaredelegate.introduction_image1
            }
            Image {
                id: introductionimage2
                source: introduction_image2
//                source: softwaredelegate.introduction_image2
            }
        }
    }

}
