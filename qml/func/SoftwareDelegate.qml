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
import "common" as Common
import "software" as Software

Rectangle {
    id: softwaredelegate

////传给软件推荐二级界面的值
//    property string delegate_name: "Qafa1asd"
//    property string delegate_information: "asdasd:asdfsa12   afasf:1231M  asfs:2013-9-1"
//    property string delegate_image: "../../img/icons/bug.png"
//    property string delegate_introduction: "腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
//    property string introduction_image1: "../../img/skin/HighContrast.png"
//    property string introduction_image2: "../../img/skin/Radiance.png"
//    property string mystatus1: ""
//    property string mystatus2: ""
//    property string mystatus3: ""



    //信号绑定，绑定qt的信号
    Connections
    {
        target: sudodispatcher
        onFinishSoftwareFetch: {
            console.log(type);
            console.log(msg);
        }
        onFinishSoftwareApt: {
            console.log(type);
            console.log(msg);
        }
        onFinishSoftwareCheckStatus: {
//            console.log("Software statusDict->");
//            var statusdata = statusDict;
//            for (var i=0; i< statusdata.length; i++) {
////                var splitlist = statusdata[i].split(":");
//                console.log(statusdata[i]);
//            }
//            mystatus1 = statusDict[0];
//            mystatus2 = statusDict[1];
//            mystatus3 = statusDict[2];
        }
    }


    scale: 1
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    width: 167
    height: 79
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
//    Software.AdobeFlash{width: 0;height: 0; opacity: 0}
    Image {
        id: seticon
        source: icon
        anchors.fill: parent
        anchors.topMargin: 7
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            if (flag == "AdobeFlash"){
//                    sudodispatcher.
            console.log("clicked adobeflash->");
                content.install_status = sudodispatcher.check_pkg_status_qt("ubiquity");
//                console.log(softwaredelegate.mystatus1);
//                console.log(softwaredelegate.mystatus2);
//                console.log(softwaredelegate.mystatus3);
                    content.delegate_name= "ubiquity";//softwaredelegate.mystatus3;
                    content.delegate_information= "1111111111111   1111:11111  11111:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"

                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Chromium"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "EclipseQt"){
                    content.delegate_name= "Q333333"
                    content.delegate_information= "33333333   333333:33333  333333:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Irc"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Kuaipan"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "KugouMusic"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Lotus"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Pps"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "QbitTorrent"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "StarDict"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Vic"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "VirtualBox"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Wineqq"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "Wps"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "XChat"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
            else if (flag == "XunLei"){
                    content.delegate_name= "Q222222"
                    content.delegate_information= "222222222   22222:2222  2222:2013-9-1"
                    content.delegate_image= "../../img/icons/bug.png"
                    content.delegate_introduction="腾讯QQ（统一简称“QQ”）是腾讯公司开发的一款基于Internet的即时通信（IM）软件。腾讯QQ支持在线聊天、视频电话、点对点断点续传文件、共享文件、网络硬盘、自定义面板、QQ邮箱等多种功能，并可与移动通讯终端等多种通讯方式相连."
                    content.introduction_image1= "../../img/skin/HighContrast.png"
                    content.introduction_image2= "../../img/skin/Radiance.png"
                    pageStack.push(adobeflashpage);
                }
//            softwaredelegate.GridView.view.currentIndex = index;
        }
    }
}
