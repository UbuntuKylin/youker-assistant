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
//import SystemType 0.1
Rectangle {
    id: scaleMe
    width: 58
    height: 29
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string wordname: ""
    property string flag: ""

    function iconClicked() {
        scaleMe.state = "Details";
        settigsDetails.setTitle = scaleMe.flag;
//        console.log(settigsDetails.setTitle);
    }

    Text {
        text: wordname
        font.pointSize: 10
        color: "#318d11"
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    Connections {
        target: topBar
        //按下返回按钮
        onButtonClicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Original'
        //按下确定按钮
//        onButton2Clicked: {
//            console.log("111111111111");
//            console.log(settigsDetails.setTitle);
//            console.log("222222222222");
//        }
    }

    Connections {
        target: toolBar
        //按下返回按钮
        onQuitBtnClicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Original'
        //按下确定按钮
//        onButton2Clicked: {
//            console.log("111111111111");
//            console.log(settigsDetails.setTitle);
//            console.log("222222222222");
//        }
    }

    states: [
        State {
            name: "Original"; when: seticon.status == Image.Ready
            PropertyChanges { target: scaleMe; scale: 1 }
        },
        State {
            name: "Details"
            PropertyChanges { target: scaleMe; scale: 1 }
            PropertyChanges { target: setting_widget; state: "DetailedView" }//展示细节页面,出现工具栏
        }
    ]
    transitions: [
        Transition {
            from: "Original"; to: "Details"
            ParentAnimation {
                via: foreground
                NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
            }
        },
        Transition {
            from: "Details"; to: "Original"
            ParentAnimation {
                via: foreground
                NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
            }
        }
    ]

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
//        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""


        onClicked: {
            console.log("wordset clicked....");
            //屏幕坏点检测
            if (flag == "CheckScreen")
                sessiondispatcher.send_checkscreen_dialog();
            else
                iconClicked();
//            if (setbtn_flag == "onekey") {
//                console.log("onekey clicked....");
////                systemdispatcher.scan_by_one_key_qt();
//            }
//            else if (setbtn_flag == "set")
//                console.log("set clicked....");
//            else if (setbtn_flag == "message")
//                console.log("message clicked....");
        }
    }
}
