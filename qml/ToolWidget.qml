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
import QtDesktop 0.1
//import "func/common" as Common
//import "func"


Rectangle {
    id: toolwidget
    width: parent.width
    height: 84
    color: "transparent"
    state: "Home"
//    opacity: 0.3

    //-------------------------------start
//    ListModel {
//        id: toolModel
//        ListElement {
//            iconName: "homepage.png"
////            method: "首页"
//            text: "homepage"
//        }
//        ListElement {
//            iconName: "systemclear.png"
////            method: "电脑清理"
//            text: "clearrubbish"
//        }
//        ListElement {
//            iconName: "systembeauty.png"
////            method: "系统设置"
//            text: "systemset"
//        }
//        ListElement {
//            iconName: "systemmessage.png"
////            method: "优化加速"
//            text: "sysmessage"
//        }
//        ListElement {
//            iconName: "functioncollection.png"
////            method: "功能大全"
//            text: "functioncollection"
//        }
//    }
//    GridView {
//        id: gridView
//        height: parent.height
//        width: parent.width
//        anchors {
//            top: parent.top
//            topMargin: 20
//            left: parent.left
//            leftMargin: 15
//        }
//        flow: GridView.LeftToRight
//        model: toolModel
//        delegate: ToolBtn {}
////        cacheBuffer: 1000
////        cellWidth: (parent.width-2)/11; cellHeight: cellWidth
//        cellWidth: 114; cellHeight: 40
//        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
////        focus: true
//    }
    //-------------------------------end


    Row {
        id: tool_line
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 0
        ToolBtn {id: home_tool; iconName: "homepage.png"; text: "homepage"; onSend: toolwidget.state = "Home"}
        Rectangle {id: splitbar1; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar5; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: message_tool;iconName: "systemmessage.png"; text: "systemmessage"; onSend: toolwidget.state = "Message"}
        Rectangle {id: splitbar2; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar6; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: clear_tool; iconName: "systemclear.png"; text: "clearrubbish"; onSend: toolwidget.state = "Clear"}
        Rectangle {id: splitbar3; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar7; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: beauty_tool;iconName: "systembeauty.png";text: "systemset"; onSend: toolwidget.state = "Beauty"}
        Rectangle {id: splitbar4; height: 38; width: 1; color: "#086794" }
        Rectangle {id: splitbar8; height: 38; width: 1; color: "#45a6d4" }
        ToolBtn {id: function_tool;iconName: "functioncollection.png"; text: "functioncollection"; onSend: toolwidget.state = "Function"}
    }



//    Image {
//        id: logo
////        anchors.top: parent.top
////        anchors.topMargin: titlebar.height
//        anchors.right: parent.right
//        anchors.rightMargin: 4
////        width: 140
////        height: 70
//        source: "./img/icons/logo.png"
//    }

    Item { id: foreground; anchors.fill: parent }


    states: [
        State {
            name: "Home"/*; when: (menulogo.text == "homepage")*/
            PropertyChanges { target: home_tool; iconName:  "homepage-active.png"}
            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}

        },
        State {
            name: "Clear"/*; when: (menulogo.text == "clearrubbish")*/
            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
            PropertyChanges { target: clear_tool; iconName:  "systemclear-active.png"}
            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Beauty"/*; when: (menulogo.text == "systemset")*/
            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
            PropertyChanges { target: beauty_tool; iconName:  "systembeauty-active.png"}
            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Message"/*; when: (menulogo.text == "systemmessage")*/
            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
            PropertyChanges { target: message_tool; iconName:  "systemmessage-active.png"}
            PropertyChanges { target: function_tool; iconName:  "functioncollection.png"}
        },
        State {
            name: "Function"/*; when: (menulogo.text == "functioncollection")*/
            PropertyChanges { target: home_tool; iconName:  "homepage.png"}
            PropertyChanges { target: clear_tool; iconName:  "systemclear.png"}
            PropertyChanges { target: beauty_tool; iconName:  "systembeauty.png"}
            PropertyChanges { target: message_tool; iconName:  "systemmessage.png"}
            PropertyChanges { target: function_tool; iconName:  "functioncollection-active.png"}
        }
    ]

}











//Item {
//    id: rectangle1
//    width: parent.width
//    height: 84
////    color: "transparent"
////    opacity: 0.3
//    Row {
//        id: tool_line
//        anchors.left: parent.left
//        anchors.leftMargin: 5
//        spacing: 0
//        ToolBtn {iconName: "homepage.png"; method: "首页"; text: "homepage"; /*dis: mydispather;*/
//        onSend: pageStack.push(homepage)}
//        ToolBtn {iconName: "clearrubbish.png"; method:"电脑清理"; text: "clearrubbish"; /*dis: mydispather;*/
//        onSend: pageStack.push(clearrubbish)}
//        ToolBtn {iconName: "systemset.png"; method: "系统设置"; text: "systemset"; /*dis: mydispather;*/
//        onSend: pageStack.push(systemset)}
//        ToolBtn {iconName: "optimalacceleration.png"; method: "优化加速"; text: "optimalacceleration"; /*dis: mydispather;*/
//        onSend: pageStack.push(optimalacceleration)}
//        ToolBtn {iconName: "searchtrojan.png"; method: "查杀木马"; text: "searchtrojan"; /*dis: mydispather;*/
//        onSend: pageStack.push(searchtrojan)}
//        ToolBtn {iconName: "computerclinic.png"; method: "电脑门诊"; text: "computerclinic"; /*dis: mydispather;*/
//            onSend: {
////                pageStack.clear();
//                pageStack.push(computerclinic);
//            }
//        }
//        ToolBtn {iconName: "fixbug.png"; method: "修复漏洞"; text: "fixbug"; /*dis: mydispather;*/
//        onSend: pageStack.push(fixbug)}
//        ToolBtn {iconName: "systemrepair.png"; method: "系统修复"; text: "systemrepair"; /*dis: mydispather;*/
//        onSend: pageStack.push(systemrepair)}
//        ToolBtn {iconName: "allfunction.png"; method: "功能大全"; text: "allfunction"; /*dis: mydispather;*/
//        onSend: pageStack.push(allfunction)}
//    }


//    Image {
//        id: logo
////        anchors.top: parent.top
////        anchors.topMargin: titlebar.height
//        anchors.right: parent.right
//        anchors.rightMargin: 4
//        width: 140
//        height: 70
//        source: "./img/logo.png"
//    }
//}
