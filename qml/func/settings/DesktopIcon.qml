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
//import RegisterMyType 0.1
import SessionType 0.1
//import SystemType 0.1
import QtDesktop 0.1
import "../common" as Common

Rectangle {
    id: desktopiconpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property string actiontitle: "桌面图标显示设置"
    property string actiontext: "控制如网络、垃圾箱、根文件夹等图标在桌面上的显示"
//    property Dispatcher dis: mydispather


    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
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

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "DesktopIcon")
//                console.log("DesktopIcon ok");
//        }
//    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: desktopiconpage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: desktopiconpage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }



    //------------------
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
            text: "桌面图标显示控制"
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


    Column {
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10
        }
        spacing: 20
        Row {
            spacing: 20
            Label {
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
            Label {
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
            Label {
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
            Label {
                id: trashlabel
                width: 170
                text: "垃圾箱:"
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
            Label {
                id: devicelabel
                width: 170
                text: "设备:"
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
    //------------------








//    Column {
//        spacing: 20
//        anchors {
//            top: parent.top
//            topMargin: 120
////            left: parent.left
////            leftMargin: 60
//            horizontalCenter: parent.horizontalCenter
//        }

////        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
//            Label {
//                id: desktopiconlabel
//                width: 170
//                text: qsTr("由文件管理器处理桌面:")
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: iconswitcher
//                width: desktopiconlabel.width
//                onSwitched: {
//                    if (iconswitcher.switchedOn) {
//                        console.log("桌面图标on---------------");
//                        sessiondispatcher.set_show_desktop_icons_qt(true);
//                    }
//                    else if(!iconswitcher.switchedOn) {
//                        console.log("桌面图标off---------------");
//                        sessiondispatcher.set_show_desktop_icons_qt(false);
//                    }
//                }
//            }

//        }

//        Row {
//            Label {
//                id: homefolderlabel
//                width: 170
//                text: qsTr("家文件夹:")
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: folderswitcher
////                width: parent.width
//                onSwitched: {
//                    if (folderswitcher.switchedOn) {
//                        console.log("根文件夹on---------------");
//                        sessiondispatcher.set_show_homefolder_qt(true);
//                    }
//                    else if(!folderswitcher.switchedOn) {
//                        console.log("根文件夹off---------------");
//                        sessiondispatcher.set_show_homefolder_qt(false);
//                    }
//                }
//            }
//        }

//        Row {
//            Label {
//                id: networklabel
//                width: 170
//                text: qsTr("网络:")
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: networkswitcher
////                width: parent.width
//                onSwitched: {
//                    if (networkswitcher.switchedOn) {
//                        console.log("网络on---------------");
//                        sessiondispatcher.set_show_network_qt(true);
//                    }
//                    else if(!networkswitcher.switchedOn) {
//                        console.log("网络off---------------");
//                        sessiondispatcher.set_show_network_qt(false);
//                    }
//                }
//            }
//        }

//        Row {
//            Label {
//                id: trashlabel
//                width: 170
//                text: qsTr("垃圾:")
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: trashswitcher
////                width: parent.width
//                onSwitched: {
//                    if (trashswitcher.switchedOn) {
//                        console.log("垃圾on---------------");
//                        sessiondispatcher.set_show_trash_qt(true);
//                    }
//                    else if(!trashswitcher.switchedOn) {
//                        console.log("垃圾off---------------");
//                        sessiondispatcher.set_show_trash_qt(false);
//                    }
//                }
//            }
//        }


//        Row {
//            Label {
//                id: devicelabel
//                width: 170
//                text: qsTr("设备:")
//                font {
//                    family: desktopiconpage.fontName
//                    pointSize: desktopiconpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: deviceswitcher
////                width: parent.width
//                onSwitched: {
//                    if (deviceswitcher.switchedOn) {
//                        console.log("设备on---------------");
//                        sessiondispatcher.set_show_devices_qt(true);
//                    }
//                    else if(!deviceswitcher.switchedOn) {
//                        console.log("设备off---------------");
//                        sessiondispatcher.set_show_devices_qt(false);
//                    }
//                }
//            }
//        }

//    }//Column

}


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
