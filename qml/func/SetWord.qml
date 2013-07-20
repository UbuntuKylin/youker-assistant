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
    id: wordset
    width: 58
    height: 29
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string wordname: ""
//    property SystemDispatcher dis: systemdispatcher
//    property string iconName: "onekeyBtn.png"
//    property string setbtn_flag: "onekey"

//    Image {
//        id: toolImg
////        anchors.horizontalCenter: parent.horizontalCenter
//        source: "../img/icons/" + iconName
//    }
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
    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
//        onEntered: {
////            btnImg.source = "../img/toolWidget/menu_hover.png"
//            if (menulogo.setbtn_flag == "onekey")
//                btnImg.source = "../img/icons/onekeyBtn-hover.png"
//            else if (menulogo.setbtn_flag == "set")
//                btnImg.source = "../img/icons/set-hover.png"
//            else if (menulogo.setbtn_flag == "message")
//                btnImg.source = "../img/icons/message-hover.png"
//        }
//        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            console.log("wordset clicked....");
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
