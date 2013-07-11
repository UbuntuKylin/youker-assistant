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

Rectangle {
    id: menulogo
    width: 78
    height: 82
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    Column {
        anchors.fill: parent
        anchors.topMargin: 7
        Image {
            id: seticon
            source: "./img/toolWidget/" + iconName
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: btnText
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            text: qsTr(method)
        }
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            //kobe:选中项深色块移动
            menulogo.GridView.view.currentIndex = index;
            if (text == "homepage") {
                pageStack.push(homepage)
            }
            else if (text == "clearrubbish") {
                pageStack.push(clearrubbish)
            }
            else if (text == "systemset") {
                pageStack.push(systemset)
            }
            else if (text == "searchtrojan") {
                pageStack.push(searchtrojan)
            }
            else if (text == "fixbug") {
                pageStack.push(fixbug)
            }
            else if (text == "systemrepair") {
                pageStack.push(systemrepair)
            }
            else if (text == "computerclinic") {
                pageStack.push(computerclinic)
            }
            else if (text == "optimalacceleration") {
                pageStack.push(optimalacceleration)
            }
            else if (text == "allfunction") {
                pageStack.push(allfunction)
            }
        }
    }
}






//import QtQuick 1.1
////import RegisterMyType 0.1

//Rectangle {
//    id: menulogo
//    width: 78
//    height: 82
//    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
//    color: "transparent"
//    property string iconName: "homepage.png"
//    property string method: "首页"
//    property string text: "homepage"

//    Column {
//        anchors.fill: parent
//        anchors.topMargin: 7
//        Image {
//            id: toolImg
//            anchors.horizontalCenter: parent.horizontalCenter
//            source: "./img/toolWidget/" + iconName
//        }
//        Text {
//            id: btnText
//            anchors.horizontalCenter: parent.horizontalCenter
//            color: "white"
//            text: qsTr(method)
//        }
//    }

//    Image {
//        id: btnImg
//        anchors.fill: parent
//        source: ""
//    }
//    signal send(string a)
////    onSend: console.log("Send signal:" + a )
////    Loader { id: pageLoader }
//    MouseArea {
//        id: signaltest
//        hoverEnabled: true
//        anchors.fill: parent
//        onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""
//        onClicked: {
//            if (text == "homepage") {
//                menulogo.send("homepage")
//                console.log(text)
//            }
//            else if (text == "clearrubbish") {
//                menulogo.send("clearrubbish")
//                console.log(text)
//            }
//            else if (text == "systemset") {
//                menulogo.send("systemset")
//                console.log(text)
//            }
//            else if (text == "searchtrojan") {
//                menulogo.send("searchtrojan")
////                mydispather.set_value(2)
//                console.log(text)
//            }
//            else if (text == "fixbug") {
//                menulogo.send("fixbug")
//                console.log(text)
//            }
//            else if (text == "systemrepair") {
//                menulogo.send("systemrepair")
//                console.log(text)
//            }
//            else if (text == "computerclinic") {
//                menulogo.send("computerclinic")
//                console.log(text)
//            }
//            else if (text == "optimalacceleration") {
//                menulogo.send("optimalacceleration")
////                mydispather.set_value(1)
//                console.log(text);
//            }
//            else if (text == "allfunction") {
//                menulogo.send("allfunction")
//                console.log(text)
//            }

//        }
//    }

//}
