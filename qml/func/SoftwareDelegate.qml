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

Rectangle {
    id: softwaredelegate
    //信号绑定，绑定qt的信号
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
//            var statusdata = statusDict;
//            for (var i=0; i< statusdata.length; i++) {
////                var splitlist = statusdata[i].split(":");
//                console.log(statusdata[i]);
//            }
//            mystatus1 = statusDict[0];
//            mystatus2 = statusDict[1];
//            mystatus3 = statusDict[2];
//        }
//    }


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
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../img/toolWidget/highlight.png"
        onPressed: btnImg.source = "../img/toolWidget/highlight.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/highlight.png"
        onExited: btnImg.source = ""
        onClicked: {
            if (flag == "AdobeFlash"){
                content.install_status = sudodispatcher.check_pkg_status_qt("ubiquity");
                content.delegate_name= "ubiquity";
                content.delegate_appname = "Adobe Flash Player插件"
                content.delegate_information= "AdobeFlash"
                content.delegate_image= "../img/logo/adobe-flash.jpg"
                content.delegate_introduction="下载和安装Adobe Flash Player插件。Adobe Flash Player插件支持播放在线媒体和其他动态内容。"
                content.introduction_image1= "../img/character/flash-01.png"
                content.introduction_image2= "../img/character/flash-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Chromium"){
                content.delegate_name= "chromium-bsu"
                content.delegate_appname = "Chromium-bsu射击游戏"
                content.delegate_information= "Chromium"
                content.delegate_image= "../img/logo/chromium-bsu.jpg"
                content.delegate_introduction="Chromium-bsu是一个高速的纵向飞行射击游戏。在游戏中你是Chromium B.S.U货运飞船的船长，负责给前线部队提供补给。你的飞船有一小队机器人战斗机，你可以在Chromium飞船的控制室里安全的遥控它们战斗。"
                content.introduction_image1= "../img/character/Chromium-bsu-01.png"
                content.introduction_image2= "../img/character/Chromium-bsu-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Eclipse"){
                content.delegate_name= "eclipse"
                content.delegate_appname = "Eclipse开发平台"
                content.delegate_information= "Eclipse"
                content.delegate_image= "../img/logo/eclipse.jpg"
                content.delegate_introduction="Eclipse 是一个开放源代码的、基于Java的可扩展开发平台。就其本身而言，它只是一个框架和一组服务，用于通过插件组件构建开发环境。幸运的是，Eclipse 附带了一个标准的插件集，包括Java开发工具（Java Development Kit，JDK）。"
                content.introduction_image1= "../img/character/eclipse-01.png"
                content.introduction_image2= "../img/character/eclipse-02.png"
                content.install_status = sudodispatcher.get_value("eclipse");
            }
            else if (flag == "Qtcreator"){
                content.delegate_name= "qtcreator"
                content.delegate_appname = "Qt集成开发环境"
                content.delegate_information= "Qt"
                content.delegate_image= "../img/logo/qtcreator.jpg"
                content.delegate_introduction="Qt Creator是跨平台的 Qt IDE， Qt Creator 是 Qt 被 Nokia 收购后推出的一款新的轻量级集成开发环境（IDE）。此 IDE 能够跨平台运行，支持的系统包括 Linux（32 位及 64 位）、Mac OS X 以及 Windows。"
                content.introduction_image1= "../img/character/qtcreator-01.png"
                content.introduction_image2= "../img/character/qtcreator-02.png"
                content.install_status = sudodispatcher.get_value("qtcreator");
                console.log(content.install_status);
            }
            else if (flag == "Kuaipan"){
                content.delegate_name= "kuaipan"
                content.delegate_appname = "Chromium-bsu射击游戏"
                content.delegate_information= "金山快盘"
                content.delegate_image= "../img/logo/kuaipan.jpg"
                content.delegate_introduction="UbuntuKylin团队与金山公司联合开发的“Linux版网盘客户端”，具备文件同步、备份和共享功能。"
                content.introduction_image1= "../img/character/kugou-01.png"
                content.introduction_image2= "../img/character/kugou-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "KugouMusic"){
                content.delegate_name= "kugou"
                content.delegate_appname = "酷狗音乐"
                content.delegate_information= "酷狗音乐"
                content.delegate_image= "../img/logo/kugou.jpg"
                content.delegate_introduction="酷狗音乐在线播放器，支持歌手/歌曲搜索功能。"
                content.introduction_image1= "../img/character/kugou-01.png"
                content.introduction_image2= "../img/character/kugou-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Lotus"){
                content.delegate_name= "lotus"
                content.delegate_appname = "莲"
                content.delegate_information= "UbuntuKylin通讯软件"
                content.delegate_image= "../img/logo/lotus.jpg"
                content.delegate_introduction="基于XMPP协议的即时通讯软件，由ubuntukylin团队研发。"
                content.introduction_image1= "../img/character/lotus-01.png"
                content.introduction_image2= "../img/character/lotus-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Pps"){
                content.delegate_name= "pps"
                content.delegate_appname = "PPS网络播放器"
                content.delegate_information = "PPS"
                content.delegate_image = "../img/logo/pps.jpg"
                content.delegate_introduction ="全球华人最喜爱的网络电视，电视 电影 动漫 综艺娱乐，越多人看越流畅！"
                content.introduction_image1 = "../img/character/pps-01.png"
                content.introduction_image2 = "../img/character/pps-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "QbitTorrent"){
                content.delegate_name= "qbittorrent"
                content.delegate_appname = "BitTorrent下载工具"
                content.delegate_information= "BitTorrent客户端"
                content.delegate_image= "../img/logo/qbittorrent.jpg"
                content.delegate_introduction="BitTorrent客户端基于Qt4图形与RASTERBAR的BT协议接口，使用C++编写。它是一个功能丰富的轻量级客户端，与uTorrent非常相似。"
                content.introduction_image1= "../img/character/qbittorrent-01.png"
                content.introduction_image2= "../img/character/qbittorrent-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "StarDict"){
                content.delegate_name= "stardict"
                content.delegate_appname = "星际译王"
                content.delegate_information= "星际译王"
                content.delegate_image= "../img/logo/stardict.jpg"
                content.delegate_introduction="星际译王是用GTK+2.x写成的跨平台的多语言词典。具有通配符匹配、鼠标查词、模糊查找等强大功能。"
                content.introduction_image1= "../img/character/stardict-01.png"
                content.introduction_image2= "../img/character/stardict-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Vic"){
                content.delegate_name= "vic"
                content.delegate_appname = "Vlc播放器"
                content.delegate_information= "Vic"
                content.delegate_image= "../img/logo/vic.jpg"
                content.delegate_introduction="vlc是一款自由、开源的跨平台多媒体播放器及框架，可播放大多数多媒体文件，以及DVD、音频CD、VCD及各类流媒体协议。"
                content.introduction_image1= "../img/character/vlc-01.png"
                content.introduction_image2= "../img/character/vlc-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "VirtualBox"){
                content.delegate_name= "virtualbox"
                content.delegate_appname = "VirtualBox虚拟机"
                content.delegate_information= "VirtualBox"
                content.delegate_image= "../img/logo/virtualbox.jpg"
                content.delegate_introduction="VirturlBox是x86虚拟化自由软件，它可以使windows，DOS，BSD以及Linux等大量x86操作系统运行在Linux系统上。"
                content.introduction_image1= "../img/character/virtualbox-01.png"
                content.introduction_image2= "../img/character/virtualbox-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Wineqq"){
                content.delegate_name= "Wineqq"
                content.delegate_appname = "WineQQ安装程序"
                content.delegate_information= "QQ"
                content.delegate_image= "../img/logo/qq.jpg"
                content.delegate_introduction="借助wine模拟运行的腾讯QQ 2012客户端，选自longene项目。"
                content.introduction_image1= "../img/character/qq-01.png"
                content.introduction_image2= "../img/character/qq-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "Wps"){
                content.delegate_name= "wps"
                content.delegate_appname = "WPS办公软件"
                content.delegate_information= "WPS"
                content.delegate_image= "../img/logo/wps.jpg"
                content.delegate_introduction="由珠海金山办公软件有限公司与CCN联合实验室合作推出<WPS for UbuntuKylin>系列办公软件，并由珠海金山办公软件有限公司授权UbuntuKylin开源操作系统个人用户作为最终用户免费下载、安装和使 用。经测试，该版本在12.04和13.04上均可使用。"
                content.introduction_image1= "../img/character/wps-01.png"
                content.introduction_image2= "../img/character/wps-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            else if (flag == "XChat"){
                content.delegate_name= "xchat"
                content.delegate_appname = "XChat通讯软件"
                content.delegate_information= "XChat"
                content.delegate_image= "../img/logo/xchat.jpg"
                content.delegate_introduction="XChat是一个使用GTK+的图形化IRC客户端，它的外观体验类似于Amiga上的AmIRC。XChat支持mIRC扩展DCC RESUME和mIRC颜色代码、多服务器多频道的窗口、对话窗口，以及一个插件API。"
                content.introduction_image1= "../img/character/xchat-01.png"
                content.introduction_image2= "../img/character/xchat-02.png"
                content.install_status = sudodispatcher.get_value("xchat");
            }
            else if (flag == "XunLei"){
                content.delegate_name= "xunlei"
                content.delegate_appname = "迅雷下载工具"
                content.delegate_information= "迅雷"
                content.delegate_image= "../img/logo/xunlei.jpg"
                content.delegate_introduction="借助wine模拟运行的迅雷客户端。"
                content.introduction_image1= "../img/character/xunlei-01.png"
                content.introduction_image2= "../img/character/xunlei-02.png"
                content.install_status = sudodispatcher.get_value("ubiquity");
            }
            pageStack.push(softwarepage);
        }
    }
}
