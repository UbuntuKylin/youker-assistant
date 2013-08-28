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
//import SystemType 0.1
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id: desktopiconsetpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property int cursor_size: 24
    property string default_icon_theme: ""
    property string init_icon_theme: ""
    property bool init_icon_theme_flag: false

    property string actiontitle: "桌面图标设置"
    property string actiontext: "您可以设置桌面图标主题和控制一些图标是否显示在桌面上。"
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        desktopiconsetpage.default_icon_theme = sessiondispatcher.get_icon_theme_qt();
        desktopiconsetpage.init_icon_theme = desktopiconsetpage.default_icon_theme;
        desktopiconsetpage.init_icon_theme_flag = false;
        var iconlist = sessiondispatcher.get_icon_themes_qt();
        var current_icon_theme = sessiondispatcher.get_icon_theme_qt();
        iconlist.unshift(current_icon_theme);
        choices.clear();
        for(var j=0; j < iconlist.length; j++) {
            choices.append({"text": iconlist[j]});
            if (j!=0 && iconlist[j] == current_icon_theme)
                choices.remove(j);
        }


        if (sessiondispatcher.get_show_desktop_icons_qt())
            iconswitcher.switchedOn = true;
        else
            iconswitcher.switchedOn = false;

        if (sessiondispatcher.get_show_homefolder_qt())
            folderswitcher.switchedOn = true;
        else
            folderswitcher.switchedOn = false;

        if (sessiondispatcher.get_show_network_qt())
            networkswitcher.switchedOn = true;
        else
            networkswitcher.switchedOn = false;

        if (sessiondispatcher.get_show_trash_qt())
            trashswitcher.switchedOn = true;
        else
            trashswitcher.switchedOn = false;

        if (sessiondispatcher.get_show_devices_qt())
            deviceswitcher.switchedOn = true;
        else
            deviceswitcher.switchedOn = false;
    }

    ListModel {
        id: choices
        ListElement { text: "" }
    }
    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row{
            spacing: 50
            Text {
                 text: desktopiconsetpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            //status picture
            Image {
                id: statusImage
                visible: false
                source: "../../img/toolWidget/finish.png"
                fillMode: "PreserveAspectFit"
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             text: desktopiconsetpage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }


    Row {
        id: settitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120

        }
        spacing: 5
        Text{
            text: "图标主题设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:700
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Row {
        id: themeline
        spacing: 170
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10

        }
        Row{
            spacing: 40
            Text {
                id: iconthemelabel
                text: "图标主题"
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.ComboBox {
                id: iconcombo
                model: choices
                width: 200
                onSelectedTextChanged: {/*console.log(selectedText)*/}
            }
        }
        Row{
            spacing: 38
            Common.Button {
                id: okBtn
                width: 95;height: 30
                hoverimage: "green2.png"
                text: "确定"
                onClicked: {
                    desktopiconsetpage.init_icon_theme_flag = true;
                    if (desktopiconsetpage.default_icon_theme != iconcombo.selectedText) {
                        desktopiconsetpage.default_icon_theme = iconcombo.selectedText;
                        sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
                        statusImage.visible = true;
                    }
                }
            }
            Common.Button {
                hoverimage: "blue2.png"
                text: "使用默认设置"
                width: 124
                height: 30
                onClicked: {
                    if(desktopiconsetpage.init_icon_theme_flag == true) {
                        desktopiconsetpage.init_icon_theme_flag;
                        sessiondispatcher.set_icon_theme_qt(desktopiconsetpage.init_icon_theme);
                        statusImage.visible = true;
                    }
                    else
                        sessiondispatcher.send_warningdialog_msg("友情提示：", "您系统的图标主题已经为默认设置！");
                }
            }
//            Common.Button {
//                id: okBtn
//                width: 95;height: 30
////                hoverimage: "ok.png"
//                text:"确定"
//                onClicked: {
//                    desktopiconsetpage.init_icon_theme_flag = true;
//                    if (desktopiconsetpage.default_icon_theme != iconcombo.selectedText) {
//                        desktopiconsetpage.default_icon_theme = iconcombo.selectedText;
//                        sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                        statusImage.visible = true;
//                    }
//                }
//            }
//            Common.Button {
////                hoverimage: "use.png"
//                text:"使用默认设置"
//                color1: "#57bffc"
//                color2: "#2384c8"
//                bordercolor: "#31a0ee"
//                width: 124
//                height: 30
//                onClicked: {
//                    if(desktopiconsetpage.init_icon_theme_flag == true) {
//                        desktopiconsetpage.init_icon_theme_flag;
//                        sessiondispatcher.set_icon_theme_qt(desktopiconsetpage.init_icon_theme);
//                        statusImage.visible = true;
//                    }
//                    else
//                        sessiondispatcher.send_warningdialog_msg("友情提示：", "您系统的图标主题已经为默认设置！");
//                }
//            }
            Timer {
                     interval: 5000; running: true; repeat: true
                     onTriggered: statusImage.visible = false
                 }
        }
    }

    Row {
        id: icontitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: themeline.bottom
            topMargin: 30

        }
        spacing: 5
        Text{
            text: "桌面图标显示控制"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:678
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Column {
        anchors{
            left: parent.left
            leftMargin: 60
            top: icontitle.bottom
            topMargin: 10
        }
        spacing: 10
        Row {
            spacing: 20
            Common.Label {
                id: desktopiconlabel
                width: 170
                text: "由文件管理器处理桌面:"
                font.pixelSize: 12
                color: "#383838"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: iconswitcher
                width: desktopiconlabel.width
                onSwitched: {
                    if (iconswitcher.switchedOn) {
                        sessiondispatcher.set_show_desktop_icons_qt(true);
                    }
                    else if(!iconswitcher.switchedOn) {
                        sessiondispatcher.set_show_desktop_icons_qt(false);
                    }
                }
            }

        }

        Row {
            spacing: 20
            Common.Label {
                id: homefolderlabel
                width: 170
                text: "我的文档:"
                font.pixelSize: 12
                color: "#383838"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: folderswitcher
//                width: parent.width
                onSwitched: {
                    if (folderswitcher.switchedOn) {
                        sessiondispatcher.set_show_homefolder_qt(true);
                    }
                    else if(!folderswitcher.switchedOn) {
                        sessiondispatcher.set_show_homefolder_qt(false);
                    }
                }
            }
        }

        Row {
            spacing: 20
            Common.Label {
                id: networklabel
                width: 170
                text: "网络:"
                font.pixelSize: 12
                color: "#383838"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: networkswitcher
//                width: parent.width
                onSwitched: {
                    if (networkswitcher.switchedOn) {
                        sessiondispatcher.set_show_network_qt(true);
                    }
                    else if(!networkswitcher.switchedOn) {
                        sessiondispatcher.set_show_network_qt(false);
                    }
                }
            }
        }

        Row {
            spacing: 20
            Common.Label {
                id: trashlabel
                width: 170
                text: "回收站:"
                font.pixelSize: 12
                color: "#383838"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: trashswitcher
//                width: parent.width
                onSwitched: {
                    if (trashswitcher.switchedOn) {
                        sessiondispatcher.set_show_trash_qt(true);
                    }
                    else if(!trashswitcher.switchedOn) {
                        sessiondispatcher.set_show_trash_qt(false);
                    }
                }
            }
        }


        Row {
            spacing: 20
            Common.Label {
                id: devicelabel
                width: 170
                text: "移动设备:"
                font.pixelSize: 12
                color: "#383838"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: deviceswitcher
//                width: parent.width
                onSwitched: {
                    if (deviceswitcher.switchedOn) {
                        sessiondispatcher.set_show_devices_qt(true);
                    }
                    else if(!deviceswitcher.switchedOn) {
                        sessiondispatcher.set_show_devices_qt(false);
                    }
                }
            }
        }

    }//Column

    //顶层工具栏
    Bars.TopBar {
        id: topBar
        width: 28
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        opacity: 0.9
        onButtonClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        showok: false
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {
            //default:ubuntukylin-icon-theme
//            if (desktopiconsetpage.default_icon_theme != iconcombo.selectedText) {
//                desktopiconsetpage.default_icon_theme = iconcombo.selectedText;
//                sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//            }
        }
    }
}
