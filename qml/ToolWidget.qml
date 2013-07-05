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
import SystemType 0.1
Rectangle {
    id: rectangle1
    width: parent.width
    height: 84
    color: "transparent"
    Row {
        id: tool_line
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 0
        ToolBtn {iconName: "homepage.png"; method: "首页"; text: "homepage"; /*dis: mydispather;*/
        onSend: pageStack.push(homepage)}
        ToolBtn {iconName: "clearrubbish.png"; method:"电脑清理"; text: "clearrubbish"; /*dis: mydispather;*/
        onSend: pageStack.push(clearrubbish)}
        ToolBtn {iconName: "systemset.png"; method: "系统设置"; text: "systemset"; /*dis: mydispather;*/
        onSend: pageStack.push(systemset)}
        ToolBtn {iconName: "optimalacceleration.png"; method: "优化加速"; text: "optimalacceleration"; /*dis: mydispather;*/
        onSend: pageStack.push(optimalacceleration)}
        ToolBtn {iconName: "searchtrojan.png"; method: "查杀木马"; text: "searchtrojan"; /*dis: mydispather;*/
        onSend: pageStack.push(searchtrojan)}
        ToolBtn {iconName: "computerclinic.png"; method: "电脑门诊"; text: "computerclinic"; /*dis: mydispather;*/
            onSend: {
//                pageStack.clear();
                pageStack.push(computerclinic);
            }
        }
        ToolBtn {iconName: "fixbug.png"; method: "修复漏洞"; text: "fixbug"; /*dis: mydispather;*/
        onSend: pageStack.push(fixbug)}
        ToolBtn {iconName: "systemrepair.png"; method: "系统修复"; text: "systemrepair"; /*dis: mydispather;*/
        onSend: pageStack.push(systemrepair)}
        ToolBtn {iconName: "allfunction.png"; method: "功能大全"; text: "allfunction"; /*dis: mydispather;*/
        onSend: pageStack.push(allfunction)}
    }
    Image {
        id: logo
//        anchors.top: parent.top
//        anchors.topMargin: titlebar.height
        anchors.right: parent.right
        anchors.rightMargin: 4
        width: 140
        height: 70
        source: "./img/logo.png"
    }
}
