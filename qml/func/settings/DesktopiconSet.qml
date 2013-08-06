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
//import SystemType 0.1
import "../common" as Common


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
    property string default_theme: ""
    property string default_icon_theme: ""
    property string default_cursor_theme: ""

    property string actiontitle: "桌面图标设置"
    property string actiontext: "您可以设置桌面图标主题和控制一些图标是否显示在桌面上。"
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
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
    Connections {
        target: toolBar
        //按下确定按钮
        onOkBtnClicked: {
            if (settigsDetails.setTitle == "DesktopBackground") {

                //default:ubuntukylin-icon-theme
                if (desktopiconsetpage.default_icon_theme != iconcombo.selectedText) {
                    console.log("333");
                    desktopiconsetpage.default_icon_theme = iconcombo.selectedText;
                    sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
                }
                else
                    console.log("444");
            }

        }
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
        Text {
             text: desktopiconsetpage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
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
        spacing: 40
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10

        }
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
            onSelectedTextChanged: console.log(selectedText)
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
                        console.log("桌面图标on---------------");
                        sessiondispatcher.set_show_desktop_icons_qt(true);
                    }
                    else if(!iconswitcher.switchedOn) {
                        console.log("桌面图标off---------------");
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
                text: "家文件夹:"
                font.pixelSize: 12
                color: "#383838"
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: folderswitcher
//                width: parent.width
                onSwitched: {
                    if (folderswitcher.switchedOn) {
                        console.log("根文件夹on---------------");
                        sessiondispatcher.set_show_homefolder_qt(true);
                    }
                    else if(!folderswitcher.switchedOn) {
                        console.log("根文件夹off---------------");
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
                        console.log("网络on---------------");
                        sessiondispatcher.set_show_network_qt(true);
                    }
                    else if(!networkswitcher.switchedOn) {
                        console.log("网络off---------------");
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
                        console.log("垃圾on---------------");
                        sessiondispatcher.set_show_trash_qt(true);
                    }
                    else if(!trashswitcher.switchedOn) {
                        console.log("垃圾off---------------");
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
                        console.log("设备on---------------");
                        sessiondispatcher.set_show_devices_qt(true);
                    }
                    else if(!deviceswitcher.switchedOn) {
                        console.log("设备off---------------");
                        sessiondispatcher.set_show_devices_qt(false);
                    }
                }
            }
        }

    }//Column


//    Row {
//        id: scrollstyle
//        spacing: 40
//        anchors{
//            left: parent.left
//            leftMargin: 60
//            top: scrolltitle.bottom
//            topMargin: 10
//        }
//        Label {
//            width: 110
//            text: "触摸板滚动触发方式:"
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            anchors.verticalCenter: parent.verticalCenter
//        }
////        GroupBox {
////            anchors.verticalCenter: parent.verticalCenter
////                title: qsTr("触摸板滚动模式:")
////            adjustToContentSize: true
//            Common.ButtonRow {
//                exclusive: true//控制是否联动
//                spacing: 80
//                Common.CheckBox {
//                    id:edge
//                    titleName: "边缘触发"//"edge模式"
//                    flag: "radio"
//                    onClicked: console.log(edge.checked)
//                }
//                Common.CheckBox {
//                    id: twofinger
//                    titleName: "双指触发"//"twofinger模式"
//                    flag: "radio"
//                    onClicked: console.log(twofinger.checked)
//                }
////            }
//        }
//    }


//    Row {
//        id: horizontalscroll
//        spacing: 40
//        anchors{
//            left: parent.left
//            leftMargin: 60
//            top: scrollstyle.bottom
//            topMargin: 10

//        }
//        Label {
//            width: 110
//            text: qsTr("触摸板横向滚动条:")
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Switch {
//            id: horizontalswitcher
//            width: 110
//            onSwitched: {
//                if (horizontalswitcher.switchedOn) {
//                    console.log("水平on---------------");
//                    sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
//                }
//                else if(!horizontalswitcher.switchedOn) {
//                    console.log("水平off---------------");
//                    sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
//                }
//            }
//        }
//    }



//    Row {
//        id: workmode
//        spacing: 40
//        anchors{
//            left: parent.left
//            leftMargin: 60
//            top: horizontalscroll.bottom
//            topMargin: 10

//        }
//        Label {
//            width: 110
//            text: "滚动条类型:"
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            anchors.verticalCenter: parent.verticalCenter
//        }
////        GroupBox {
////            anchors.verticalCenter: parent.verticalCenter
////                title: qsTr("触摸板滚动条触发方式:")
////            adjustToContentSize: true
//            Common.ButtonRow {
//                exclusive: true//控制是否联动
//                spacing: 100
//                Common.CheckBox {
//                    id:overlay
//                    titleName: "特色类型" //overlay模式
//                    flag: "radio"
//                    onClicked: console.log(overlay.checked)
//                }
//                Common.CheckBox {
//                    id: legacy
//                    titleName: "标准类型"  //legacy模式
//                    flag: "radio"
//                    onClicked: console.log(legacy.checked)
//                }
////            }
//        }
//    }











}



//Rectangle {
//    id: desktopbackgroundpage
//    property bool on: true
//    width: parent.width
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property int cursor_size: 24
//    property string default_theme: ""
//    property string default_icon_theme: ""
//    property string default_cursor_theme: ""

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    //OK工具栏
////    Common.OkToolBar {
////        id: oktoolBar
//////        visible: idenfer ? true : false
////        visible: false
////        height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
////        buttonLabel: qsTr("确定")
////        onButtonClicked: {
////            console.log("oktoolbar clicked...");
////        }
////    }


//    Component.onCompleted: {
////        console.log("------55555---------");
//        desktopbackgroundpage.cursor_size = themespinbox.value;
//        desktopbackgroundpage.default_theme = sessiondispatcher.get_theme_qt();
//        desktopbackgroundpage.default_icon_theme = sessiondispatcher.get_icon_theme_qt();
//        desktopbackgroundpage.default_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
////        console.log(desktopbackgroundpage.default_theme);
////        console.log(desktopbackgroundpage.default_icon_theme);
////        console.log(desktopbackgroundpage.default_cursor_theme);
////        console.log(desktopbackgroundpage.cursor_size);


////        var syslist = sessiondispatcher.get_themes_qt();
////        syslist.unshift(desktopbackgroundpage.default_theme);
////        choices1.clear();
////        for(var i=0; i < syslist.length; i++) {
////            choices1.append({"text": syslist[i]});
////            if (i!=0 && syslist[i] == desktopbackgroundpage.default_theme)
////                choices1.remove(i);
////        }

////        var iconlist = sessiondispatcher.get_icon_themes_qt();
////        iconlist.unshift(desktopbackgroundpage.default_icon_themeg);
////        choices2.clear();
////        for(var j=0; j < iconlist.length; j++) {
////            choices2.append({"text": iconlist[j]});
////            if (j!=0 && iconlist[j] == desktopbackgroundpage.default_icon_theme)
////                choices2.remove(j);
////        }

////        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
////        cursorlist.unshift(desktopbackgroundpage.default_cursor_theme);
////        choices3.clear();
////        for(var k=0; k < cursorlist.length; k++) {
////            choices3.append({"text": cursorlist[k]});
////            if (k!=0 && cursorlist[k] == desktopbackgroundpage.default_cursor_theme)
////                choices3.remove(k);
////        }

//        var syslist = sessiondispatcher.get_themes_qt();
//        var current_theme = sessiondispatcher.get_theme_qt();
//        syslist.unshift(current_theme);
//        choices1.clear();
//        for(var i=0; i < syslist.length; i++) {
//            choices1.append({"text": syslist[i]});
//            if (i!=0 && syslist[i] == current_theme)
//                choices1.remove(i);
//        }

//        var iconlist = sessiondispatcher.get_icon_themes_qt();
//        var current_icon_theme = sessiondispatcher.get_icon_theme_qt();
//        iconlist.unshift(current_icon_theme);
//        choices2.clear();
//        for(var j=0; j < iconlist.length; j++) {
//            choices2.append({"text": iconlist[j]});
//            if (j!=0 && iconlist[j] == current_icon_theme)
//                choices2.remove(j);
//        }

//        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
//        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
//        cursorlist.unshift(current_cursor_theme);
//        choices3.clear();
//        for(var k=0; k < cursorlist.length; k++) {
//            choices3.append({"text": cursorlist[k]});
//            if (k!=0 && cursorlist[k] == current_cursor_theme)
//                choices3.remove(k);
//        }

//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "theme") {
//                console.log("-----------------");
////                sessiondispatcher.set_theme_qt(syscombo.selectedText);
////                sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
////                sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
////                console.log(current_theme.text);
////                console.log(syscombo.selectedText);
////                console.log(current_icon_theme.text);
////                console.log(iconcombo.selectedText);
////                console.log(current_cursor_theme.text);
////                console.log(cursorcombo.selectedText);
//                //default:ubuntukylin-theme
//                if (desktopbackgroundpage.default_theme != syscombo.selectedText) {
//                    console.log("111");
//                    desktopbackgroundpage.default_theme = syscombo.selectedText;
//                    sessiondispatcher.set_theme_qt(syscombo.selectedText);
//                }
//                else
//                    console.log("222");
//                //default:ubuntukylin-icon-theme
//                if (desktopbackgroundpage.default_icon_theme != iconcombo.selectedText) {
//                    console.log("333");
//                    desktopbackgroundpage.default_icon_theme = iconcombo.selectedText;
//                    sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                }
//                else
//                    console.log("444");
//                //default:DMZ-White
//                if (desktopbackgroundpage.default_cursor_theme != cursorcombo.selectedText) {
//                    console.log("555");
//                    desktopbackgroundpage.default_cursor_theme = cursorcombo.selectedText;
//                    sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
//                }
//                else
//                    console.log("666");
//                //default:24
//                if (desktopbackgroundpage.cursor_size != themespinbox.value) {
//                    desktopbackgroundpage.cursor_size = themespinbox.value;
//                    sessiondispatcher.set_cursor_size_qt(themespinbox.value);
//                }
////                console.log("*********************88");
////                console.log(current_theme.text);
////                console.log(syscombo.selectedText);
////                console.log(current_icon_theme.text);
////                console.log(iconcombo.selectedText);
////                console.log(current_cursor_theme.text);
////                console.log(cursorcombo.selectedText);
////                console.log(desktopbackgroundpage.cursor_size);
////                console.log(themespinbox.value);

//            }

////                console.log(themespinbox.value);
////                console.log(themelabel.text);
//        }
//    }
//    ListModel {
//        id: choices0
//        ListElement { text: "" }
//    }
//    ListModel {
//        id: choices1
//        ListElement { text: "kobe999" }
//    }
//    ListModel {
//        id: choices2
//        ListElement { text: "kobe888" }
//    }
//    ListModel {
//        id: choices3
//        ListElement { text: "kobe777" }
//    }


//    Label {
//        id: theme
//        text: qsTr("主题设置>")
//        height: 30
//        font.bold: true
//        font.family: "Ubuntu"
//        elide: Text.ElideRight
//        font.pointSize: 20
//        anchors {
//            top: parent.top
//            topMargin: 10
//            left: parent.left
//            leftMargin: 15
//        }
//    }

//    Column {
//        spacing: 20
//        anchors {
////            top: parent.top
////            topMargin: 20
//            top: theme.bottom
//            topMargin: 20
//            horizontalCenter: parent.horizontalCenter
//        }

////        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
//            Label {
//                id: systhemelabel
//                width: 110
//                text: qsTr("系统主题:")
//                font {
//                    family: desktopbackgroundpage.fontName
//                    pointSize: desktopbackgroundpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: syscombo
//                model: choices1
//                width: cursorthemelabel.width

//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_theme
////                text: sessiondispatcher.get_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: iconthemelabel
//                width: 110
//                text: qsTr("图标主题:")
//                font {
//                    family: desktopbackgroundpage.fontName
//                    pointSize: desktopbackgroundpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: iconcombo
//                model: choices2
//                width: cursorthemelabel.width
//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_icon_theme
////                text: sessiondispatcher.get_icon_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: cursorthemelabel
//                width: 110
//                text: qsTr("cursor主题:")
//                font {
//                    family: desktopbackgroundpage.fontName
//                    pointSize: desktopbackgroundpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: cursorcombo
//                model: choices3
//                width: cursorthemelabel.width
//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_cursor_theme
////                text: sessiondispatcher.get_cursor_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: trashlabel
//                width: 110
//                text: qsTr("cursor大小:")
//                font {
//                    family: desktopbackgroundpage.fontName
//                    pointSize: desktopbackgroundpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            SpinBox {
//                id: themespinbox
//                width: trashlabel.width
////                width: 97
//                minimumValue: 0//32
//                maximumValue: 64
//                value: sessiondispatcher.get_cursor_size_qt()
////                value: 48
//            }
//        }
//    }//Column

//}












//import QtQuick 1.1
////import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
//import QtDesktop 0.1
//import "../common" as Common
//import "../common" as Common
//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
////    property Dispatcher dis: mydispather

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    Component.onCompleted: {
////        choices.clear();
////        choices.append({"text": mydispather.get_themes()[0]});
////        choices.append({"text": mydispather.get_themes()[1]});
////        choices.append({"text": mydispather.get_themes()[2]});
////        choices.append({"text": mydispather.get_themes()[3]});

////        streamModel.sync();
//    }

//    ListModel {
//        id: choices
//        ListElement { text: "theme" }
//        ListElement { text: "lixiang" }
//        ListElement { text: "ps" }
//        ListElement { text: "baby" }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onButton2Clicked: {
////            console.log("111111111111");
////            console.log(settigsDetails.setTitle);
//            if (settigsDetails.setTitle == "theme")
//                console.log(themelabel.text);
////            console.log("222222222222");
//        }
//    }

//    Column {
//        spacing: 20
//        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            Label {
//                id:themelabel
//                width: 110
//                text: qsTr("ps1-model")
//            }
//            ComboBox {
//                id: combobox
//                model: choices;
//                width: parent.width;
////                KeyNavigation.tab: t1
////                KeyNavigation.backtab: button2
////                onSelectedIndexChanged: console.log(selectedText)
//            }
//            Button {
//                id: button1
//                text: qsTr("确定")
//                width: 96
//                tooltip:"This is an interesting tool tip"
//                //                KeyNavigation.tab: button2
//                //                KeyNavigation.backtab: frame.tabBar
//                onClicked: {

//                }
//            }
//        }
//        Row {
//            Label {
//                id: modelabel1
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox2
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel3
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox4
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel5
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox6
//                x: 110
//            }
//        }


//    }//Column

//}





//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Column {
//        spacing: 20
//        anchors.top: parent.top
//        anchors.topMargin: 30
//        anchors.left: parent.left
//        anchors.leftMargin: 30

//        Row {
//            Label {
//                id: hidelabel
//                width: 110
//                text: qsTr("自动隐藏:")
//            }
//            CheckBox {
//                id: enabledCheck
//                text: qsTr("开启")
//                checked: false
//                onCheckedChanged: {}
//                onClicked: {
////                    enabledCheck.checked = !enabledCheck.checked;
////                    if (enabledCheck.checked == true) {
//////                        enabledCheck.checked = false;
////                        enabledCheck.text = qsTr("关闭");
////                    }
////                    else if (enabledCheck.checked == false){
//////                        enabledCheck.checked = true;
////                        enabledCheck.text = qsTr("开启");
////                    }
//                }
//            }

////            Common.Switch {
////                id: themeSwitch
////                anchors.right: parent.right
////                height: parent.height
////                spacing: 8
////                textOn: qsTr("On")
////                textOff: qsTr("Off")
////                fontColor: "#666666"
////                onSwitched: lancherpage.on = position
//////                id: switchLauncher
////////                checked: false
//////                x: 130
////////                onClicked: {
////////                    //kobe: wait for adding function
////////                    mydispather.set_launcher(switchLauncher.checked)
////////                }
////            }
//        }

//        Row {
//            Label {
//                id: sizelabel
//                width: 110
//                text: qsTr("图标大小:")
//            }
//            Slider {
//                id: slider
//                x: 130
////                function formatValue(v) { return v.toFixed(2) }
//                minimumValue: 0
//                maximumValue: 100
//                value: 0
////                live: true
////                onTouched: {
////                    console.log(slider.value)
////                }
//            }
//        }

//        Row {
//            Label {
//                id: locationlabel
//                width: 110
//                text: qsTr("位置:")
//            }
//            RadioButton {
//                id: radioleft
//                x: 130
////                text: "靠左"
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel1
//                width: 110
//                text: qsTr("输入用户名:")
//            }
//            TextField {
//                id: textfield1
//                placeholderText: qsTr("put your username")
//                echoMode: TextInput.Normal
////                hasClearButton: true
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield1.text)
//                }
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel2
//                width: 110
//                text: qsTr("输入密码:")
//            }
//            TextField {
//                id: textfield2
//                placeholderText: qsTr("put your password")
////                hasClearButton: true
//                echoMode: TextInput.Password
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield2.text)
//                }

//            }
//        }

//        Row {
//            Label {
//                id: progresslabel
//                width: 110
//                text: qsTr("进度显示:")
//            }
//            ProgressBar {
//                id: progressbar
////                indeterminate: true
//                value: 24
//                minimumValue: 0
//                maximumValue: 100

//            }
//        }

//        Row {
//            Label {
//                id: modelabel
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox
//                x: 110
////                titel1: "111111111"
////                titel2: "222222222"
////                titel3: "333333333"
////                flags: "launcher"
//            }

//        }
//    }
//}
