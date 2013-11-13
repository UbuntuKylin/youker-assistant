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
import SystemType 0.1

Rectangle {
    id: toolwidget
    width: parent.width
    height: 84
    color: "transparent"
    state: "Home"
//    opacity: 0.3

    Row {
        id: tool_line
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 0
        //首页 系统信息  系统清理  系统美化  功能大全
        ToolBtn {id: home_tool; iconName: "001.png"; text: "homepage"; showtext:qsTr("HomePage"); onSend: toolwidget.state = "Home"}
        Rectangle {id: splitbar1; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar5; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: message_tool;iconName: "002.png"; text: "systemmessage"; showtext:qsTr("SystemMessage"); onSend: toolwidget.state = "Message"}
        Rectangle {id: splitbar2; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar6; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: clear_tool; iconName: "003.png"; text: "clearrubbish"; showtext:qsTr("SystemClear"); onSend: toolwidget.state = "Clear"}
        Rectangle {id: splitbar3; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar7; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: beauty_tool;iconName: "004.png";text: "systemset"; showtext:qsTr("SystemBeauty"); onSend: toolwidget.state = "Beauty"}
        Rectangle {id: splitbar4; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar8; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: function_tool;iconName: "005.png"; text: "functioncollection"; showtext:qsTr("FunctionCollection"); onSend: toolwidget.state = "Function"}
//        ToolBtn {id: home_tool; iconName: "homepage.png"; text: "homepage"; showtext:"首页"; onSend: toolwidget.state = "Home"}
//        Rectangle {id: splitbar1; height: 38; width: 1; color: "#086794" }
//        Rectangle {id: splitbar5; height: 38; width: 1; color: "#45a6d4" }
//        ToolBtn {id: message_tool;iconName: "systemmessage.png"; text: "systemmessage"; showtext:"系统信息"; onSend: toolwidget.state = "Message"}
//        Rectangle {id: splitbar2; height: 38; width: 1; color: "#086794" }
//        Rectangle {id: splitbar6; height: 38; width: 1; color: "#45a6d4" }
//        ToolBtn {id: clear_tool; iconName: "systemclear.png"; text: "clearrubbish"; showtext:"系统清理"; onSend: toolwidget.state = "Clear"}
//        Rectangle {id: splitbar3; height: 38; width: 1; color: "#086794" }
//        Rectangle {id: splitbar7; height: 38; width: 1; color: "#45a6d4" }
//        ToolBtn {id: beauty_tool;iconName: "systembeauty.png";text: "systemset"; showtext:"系统美化"; onSend: toolwidget.state = "Beauty"}
//        Rectangle {id: splitbar4; height: 38; width: 1; color: "#086794" }
//        Rectangle {id: splitbar8; height: 38; width: 1; color: "#45a6d4" }
//        ToolBtn {id: function_tool;iconName: "functioncollection.png"; text: "functioncollection"; showtext:"功能大全"; onSend: toolwidget.state = "Function"}
    }

    Item { id: foreground; anchors.fill: parent }


    states: [
        State {
            name: "Home"
            PropertyChanges { target: home_tool; iconName:  "0001.png"}
            PropertyChanges { target: clear_tool; iconName:  "002.png"}
            PropertyChanges { target: beauty_tool; iconName:  "003.png"}
            PropertyChanges { target: message_tool; iconName:  "004.png"}
            PropertyChanges { target: function_tool; iconName:  "005.png"}
//            PropertyChanges { target: home_tool; iconName:  "homepage-active.png"}
//            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
//            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
//            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
//            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}

        },
        State {
            name: "Clear"
            PropertyChanges { target: home_tool; iconName:  "001.png"}
            PropertyChanges { target: clear_tool; iconName:  "0002.png"}
            PropertyChanges { target: beauty_tool; iconName:  "003.png"}
            PropertyChanges { target: message_tool; iconName:  "004.png"}
            PropertyChanges { target: function_tool; iconName:  "005.png"}
//            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
//            PropertyChanges { target: clear_tool; iconName:  "systemclear-active.png"}
//            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
//            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
//            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Beauty"
            PropertyChanges { target: home_tool; iconName:  "001.png"}
            PropertyChanges { target: clear_tool; iconName:  "002.png"}
            PropertyChanges { target: beauty_tool; iconName:  "0003.png"}
            PropertyChanges { target: message_tool; iconName:  "004.png"}
            PropertyChanges { target: function_tool; iconName:  "005.png"}
//            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
//            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
//            PropertyChanges { target: beauty_tool; iconName:  "systembeauty-active.png"}
//            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
//            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Message"
            PropertyChanges { target: home_tool; iconName:  "001.png"}
            PropertyChanges { target: clear_tool; iconName:  "002.png"}
            PropertyChanges { target: beauty_tool; iconName:  "003.png"}
            PropertyChanges { target: message_tool; iconName:  "0004.png"}
            PropertyChanges { target: function_tool; iconName:  "005.png"}
//            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
//            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
//            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
//            PropertyChanges { target: message_tool; iconName:  "systemmessage-active.png"}
//            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Function"
            PropertyChanges { target: home_tool; iconName:  "001.png"}
            PropertyChanges { target: clear_tool; iconName:  "002.png"}
            PropertyChanges { target: beauty_tool; iconName:  "003.png"}
            PropertyChanges { target: message_tool; iconName:  "004.png"}
            PropertyChanges { target: function_tool; iconName:  "0005.png"}
//            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
//            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
//            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
//            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
//            PropertyChanges { target: function_tool; iconName:  "functioncollection-active.png"}
        }
    ]

}
