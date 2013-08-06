/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
    width: 114
    height: 40
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string iconName: "homepage.png"
    property string text: "homepage"
//    Image {
//        id: seticon
//        source: "./img/toolWidget/" + iconName
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.fill: parent
//        anchors.top: parent.top
//        anchors.topMargin: 20
//    }
    Column {
        anchors.fill: parent
//        anchors.topMargin: 20
        Image {
            id: seticon
            source: "./img/toolWidget/" + iconName
            anchors.horizontalCenter: parent.horizontalCenter
        }
//        Text {
//            id: btnText
//            anchors.horizontalCenter: parent.horizontalCenter
//            color: "green"
//            text: qsTr(method)
//        }
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    signal send(string a)
    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
//        onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""
        //鼠标放上时
        onEntered: {
            if (text == "homepage") {
                btnImg.source = "./img/toolWidget/homepage-hover.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/toolWidget/systemclear-hover.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/toolWidget/systembeauty-hover.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/toolWidget/systemmessage-hover.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/toolWidget/functioncollection-hover.png"
            }
        }
        //鼠标按下时
        onPressed: {
            if (text == "homepage") {
                btnImg.source = "./img/toolWidget/homepage-hover.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/toolWidget/systemclear-hover.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/toolWidget/systembeauty-hover.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/toolWidget/systemmessage-hover.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/toolWidget/functioncollection-hover.png"
            }
        }
        //要判断松开是鼠标位置
        //鼠标按下松开时
        onReleased: {
            if (text == "homepage") {
                btnImg.source = "./img/toolWidget/homepage.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/toolWidget/systemclear.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/toolWidget/systembeauty.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/toolWidget/systemmessage.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/toolWidget/functioncollection.png"
            }
        }
        //鼠标按下松开再移开时
        onExited: btnImg.source = ""


        onClicked: {
            //kobe:选中项深色块移动
//            menulogo.GridView.view.currentIndex = index;
            if (text == "homepage") {
                menulogo.send("homepage");
                pageStack.push(homepage);
            }
            else if (text == "clearrubbish") {
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    menulogo.send("clearrubbish");
                    pageStack.push(clearrubbish);
                }
                else {
                    systemdispatcher.setup();
                    menulogo.send("clearrubbish");
                    pageStack.push(clearrubbish);
                }
            }
            else if (text == "systemset") {
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    menulogo.send("systemset");
                    pageStack.push(systemset);
                }
                else {
                    systemdispatcher.setup();
                    menulogo.send("systemset");
                    pageStack.push(systemset);
                }
            }

            else if (text == "systemmessage") {
                menulogo.send("systemmessage");
                pageStack.push(systemmessage);
            }
            else if (text == "functioncollection") {
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    menulogo.send("functioncollection");
                    pageStack.push(functioncollection);
                }
                else {
                    systemdispatcher.setup();
                    menulogo.send("functioncollection");
                    pageStack.push(functioncollection);
                }
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
