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
    id: touchpadpage
    property bool on: true
    width: parent.width
    height: 460
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property string touchscrolling_mode: ""
    Common.Border {
        id: leftborder
    }
    Common.Border {
        id: roightborder
        anchors.right: parent.right
    }

    Component.onCompleted: {
        touchpadpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();//edge-scrolling
//        console.log("888888888");
//        console.log(touchpadpage.touchscrolling_mode);
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
        onButton2Clicked: {
            if (settigsDetails.setTitle == "touchpad") {
//                console.log(touchpadlabel.text);
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

    Label {
        id: touchpad
        text: qsTr("触摸板设置>")
        height: 30
        font.bold: true
        font.family: "Ubuntu"
        elide: Text.ElideRight
        font.pointSize: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 15
        }
    }

    Column {
        spacing: 20
        anchors {
            top: touchpad.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

//        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                id: touchpadlabel
                width: 110
                text: qsTr("触摸板开关:")
                font {
                    family: touchpadpage.fontName
                    pointSize: touchpadpage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: touchpadswitcher
                width: touchpadlabel.width
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
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                id: horizontallabel
                width: 110
                text: qsTr("水平:")
                font {
                    family: touchpadpage.fontName
                    pointSize: touchpadpage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: horizontalswitcher
                width: horizontallabel.width
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


        Row {
            anchors {
                left: parent.left
                leftMargin: 0
            }
            anchors.horizontalCenter: parent.horizontalCenter
            GroupBox {
                title: qsTr("触摸板滚动模式:")
                adjustToContentSize: true
                ButtonRow {
                    exclusive: true//控制是否联动
                    CheckBox {
                        id:edge
                        text: "edge模式"
                        onClicked: console.log(edge.checked)
                    }
                    CheckBox {
                        id: twofinger
                        text: "twofinger模式"
                        onClicked: console.log(twofinger.checked)
                    }
                }
            }
        }

    }//Column

}




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
