/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

Rectangle {
    id: toolwidget
    width: parent.width
    height: 84
    color: "transparent"
    state: "Home"
    Row {
        id: tool_line
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 0
        //首页 系统信息  系统清理  系统美化  功能大全
        ToolBtn {id: home_tool; iconName: "home.png"; text: "homepage"; /*showtext:qsTr("Home"); */onSend: toolwidget.state = "Home"}
        Rectangle {id: splitbar1; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar5; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: message_tool;iconName: "sysinfo.png"; text: "systemmessage"; /*showtext:qsTr("SysInfo"); */onSend: toolwidget.state = "Message"}
        Rectangle {id: splitbar2; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar6; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: clear_tool; iconName: "cleanup.png"; text: "clearrubbish"; /*showtext:qsTr("Cleanup"); */onSend: toolwidget.state = "Clear"}
        Rectangle {id: splitbar3; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar7; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: beauty_tool;iconName: "feature.png";text: "systemset"; /*showtext:qsTr("Feature"); */onSend: toolwidget.state = "Beauty"}
        Rectangle {id: splitbar4; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar8; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: function_tool;iconName: "toolkits.png"; text: "functioncollection"; /*showtext:qsTr("Toolkits");*/ onSend: toolwidget.state = "Function"}
    }
    Item { id: foreground; anchors.fill: parent }
    states: [
        State {
            name: "Home"
            PropertyChanges { target: home_tool; iconName: "home-active.png"}
            PropertyChanges { target: message_tool; iconName: "sysinfo.png"}
            PropertyChanges { target: clear_tool; iconName: "cleanup.png"}
            PropertyChanges { target: beauty_tool; iconName: "feature.png"}
            PropertyChanges { target: function_tool; iconName: "toolkits.png"}
        },
        State {
            name: "Message"
            PropertyChanges { target: home_tool; iconName: "home.png"}
            PropertyChanges { target: message_tool; iconName: "sysinfo-active.png"}
            PropertyChanges { target: clear_tool; iconName: "cleanup.png"}
            PropertyChanges { target: beauty_tool; iconName: "feature.png"}
            PropertyChanges { target: function_tool; iconName: "toolkits.png"}
        },
        State {
            name: "Clear"
            PropertyChanges { target: home_tool; iconName: "home.png"}
            PropertyChanges { target: message_tool; iconName: "sysinfo.png"}
            PropertyChanges { target: clear_tool; iconName: "cleanup-active.png"}
            PropertyChanges { target: beauty_tool; iconName: "feature.png"}
            PropertyChanges { target: function_tool; iconName: "toolkits.png"}
        },
        State {
            name: "Beauty"
            PropertyChanges { target: home_tool; iconName: "home.png"}
            PropertyChanges { target: message_tool; iconName: "sysinfo.png"}
            PropertyChanges { target: clear_tool; iconName: "cleanup.png"}
            PropertyChanges { target: beauty_tool; iconName: "feature-active.png"}
            PropertyChanges { target: function_tool; iconName: "toolkits.png"}
        },
        State {
            name: "Function"
            PropertyChanges { target: home_tool; iconName: "home.png"}
            PropertyChanges { target: message_tool; iconName: "sysinfo.png"}
            PropertyChanges { target: clear_tool; iconName: "cleanup.png"}
            PropertyChanges { target: beauty_tool; iconName: "feature.png"}
            PropertyChanges { target: function_tool; iconName: "toolkits-active.png"}
        }
    ]
}
