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
    id: touchpadsetpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property string touchscrolling_mode: ""
    property string actiontitle: "触摸板设置"
    property string actiontext: "通过调整您触摸板的相关设置，使操作更加便捷。"
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        touchpadsetpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();//edge-scrolling
//        console.log("888888888");
//        console.log(touchpadsetpage.touchscrolling_mode);
        if (sessiondispatcher.get_touchpad_enable_qt())
            touchpadswitcher.switchedOn = true;
        else
            touchpadswitcher.switchedOn = false;

        if (sessiondispatcher.get_touchscrolling_use_horizontal_qt())
            horizontalswitcher.switchedOn = true;
        else
            horizontalswitcher.switchedOn = false;
    }

    Connections {
        target: toolBar
        //按下确定按钮
        onOkBtnClicked: {
            if (settigsDetails.setTitle == "TouchpadSet") {
                if (edge.checked == true) {
                    console.log("123");
                    sessiondispatcher.set_touchscrolling_mode_edge_qt();
                }
                else if (twofinger.checked == true) {
                    console.log("1234");
                    sessiondispatcher.set_touchscrolling_mode_twofinger_qt();
                }
            }
        }
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: touchpadsetpage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: touchpadsetpage.actiontext
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
            text: "开关设置"
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
        id: setcontext
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10

        }
        spacing: 40
        Label {
            width: 110
            text: "启用/禁用触摸板:"
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Switch {
            id: touchpadswitcher
            width: 110
            onSwitched: {
                if (touchpadswitcher.switchedOn) {
                    console.log("触摸板开关on---------------");
                    sessiondispatcher.set_touchpad_enable_qt(true);
                }
                else if(!touchpadswitcher.switchedOn) {
                    console.log("触摸板开关off---------------");
                    sessiondispatcher.set_touchpad_enable_qt(false);
                }
            }
        }
    }

    Row {
        id: scrolltitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: setcontext.bottom
            topMargin: 50

        }
        spacing: 5
        Text{
            text: "滚动条设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:688
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Row {
        id: scrollstyle
        spacing: 40
        anchors{
            left: parent.left
            leftMargin: 60
            top: scrolltitle.bottom
            topMargin: 10
        }
        Label {
            width: 110
            text: "触摸板滚动条类型:"
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
//        GroupBox {
//            anchors.verticalCenter: parent.verticalCenter
//                title: qsTr("触摸板滚动模式:")
//            adjustToContentSize: true
            Common.ButtonRow {
                exclusive: true//控制是否联动
                spacing: 80
                Common.CheckBox {
                    id:edge
                    titleName: "edge模式"
                    flag: "radio"
                    onClicked: console.log(edge.checked)
                }
                Common.CheckBox {
                    id: twofinger
                    titleName: "twofinger模式"
                    flag: "radio"
                    onClicked: console.log(twofinger.checked)
                }
//            }
        }
    }


    Row {
        id: horizontalscroll
        spacing: 40
        anchors{
            left: parent.left
            leftMargin: 60
            top: scrollstyle.bottom
            topMargin: 10

        }
        Label {
            width: 110
            text: qsTr("触摸板横向滚动条:")
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Switch {
            id: horizontalswitcher
            width: 110
            onSwitched: {
                if (horizontalswitcher.switchedOn) {
                    console.log("水平on---------------");
                    sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
                }
                else if(!horizontalswitcher.switchedOn) {
                    console.log("水平off---------------");
                    sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
                }
            }
        }
    }



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
//            text: "触摸板滚动条触发方式:"
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
//                    id:edge1
//                    titleName: "edge模式"
//                    onClicked: console.log(edge.checked)
//                }
//                Common.CheckBox {
//                    id: twofinger1
//                    titleName: "twofinger模式"
//                    onClicked: console.log(twofinger.checked)
//                }
////            }
//        }
//    }


}









//Rectangle {
//    id: touchpadsetpage
//    property bool on: true
//    width: parent.width
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property string touchscrolling_mode: ""
//    property string actiontitle: "触摸板设置"
//    property string actiontext: "通过调整您触摸板的相关设置，使操作更加便捷。"
//    //背景
//    Image {
//        source: "../../img/skin/bg-left.png"
//        anchors.fill: parent
//    }

//    Component.onCompleted: {
//        touchpadsetpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();//edge-scrolling
////        console.log("888888888");
////        console.log(touchpadsetpage.touchscrolling_mode);
//        if (sessiondispatcher.get_touchpad_enable_qt())
//            touchpadswitcher.switchedOn = true;
//        else
//            touchpadswitcher.switchedOn = false;

//        if (sessiondispatcher.get_touchscrolling_use_horizontal_qt())
//            horizontalswitcher.switchedOn = true;
//        else
//            horizontalswitcher.switchedOn = false;
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "TouchpadSet") {
//                if (edge.checked == true) {
//                    console.log("123");
//                    sessiondispatcher.set_touchscrolling_mode_edge_qt();
//                }
//                else if (twofinger.checked == true) {
//                    console.log("1234");
//                    sessiondispatcher.set_touchscrolling_mode_twofinger_qt();
//                }
//            }
//        }
//    }

//    Column {
//        spacing: 10
//        anchors.top: parent.top
//        anchors.topMargin: 44
//        anchors.left: parent.left
//        anchors.leftMargin: 80
//        Text {
//             text: touchpadsetpage.actiontitle
//             font.bold: true
//             font.pixelSize: 14
//             color: "#383838"
//         }
//         Text {
//             text: touchpadsetpage.actiontext
//             font.pixelSize: 12
//             color: "#7a7a7a"
//         }
//    }

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
//                id: touchpadlabel
//                width: 110
//                text: qsTr("触摸板开关:")
//                font {
//                    family: touchpadsetpage.fontName
//                    pointSize: touchpadsetpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: touchpadswitcher
//                width: touchpadlabel.width
//                onSwitched: {
//                    if (touchpadswitcher.switchedOn) {
//                        console.log("触摸板开关on---------------");
//                        sessiondispatcher.set_touchpad_enable_qt(true);
//                    }
//                    else if(!touchpadswitcher.switchedOn) {
//                        console.log("触摸板开关off---------------");
//                        sessiondispatcher.set_touchpad_enable_qt(false);
//                    }
//                }
//            }
//        }

//        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
//            Label {
//                id: horizontallabel
//                width: 110
//                text: qsTr("水平:")
//                font {
//                    family: touchpadsetpage.fontName
//                    pointSize: touchpadsetpage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: horizontalswitcher
//                width: horizontallabel.width
//                onSwitched: {
//                    if (horizontalswitcher.switchedOn) {
//                        console.log("水平on---------------");
//                        sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
//                    }
//                    else if(!horizontalswitcher.switchedOn) {
//                        console.log("水平off---------------");
//                        sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
//                    }
//                }
//            }
//        }


//        Row {
//            anchors {
//                left: parent.left
//                leftMargin: 0
//            }
//            anchors.horizontalCenter: parent.horizontalCenter
//            GroupBox {
//                title: qsTr("触摸板滚动模式:")
//                adjustToContentSize: true
//                Common.ButtonRow {
//                    exclusive: true//控制是否联动
//                    spacing: 80
//                    Common.CheckBox {
//                        id:edge
//                        titleName: "edge模式"
//                        onClicked: console.log(edge.checked)
//                    }
//                    Common.CheckBox {
//                        id: twofinger
//                        titleName: "twofinger模式"
//                        onClicked: console.log(twofinger.checked)
//                    }
//                }
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
