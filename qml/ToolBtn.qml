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
        onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
//        onEntered: btnImg.source = "./img/toolWidget/systemclear-hover.png"
//        onPressed: btnImg.source = "./img/toolWidget/systemclear-hover.png"
        //systemclear-hover.png
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onReleased: btnImg.source = "./img/toolWidget/systemclear.png"
//        onExited: btnImg.source = "./img/toolWidget/homepage-hover.png"
        onExited: btnImg.source = ""


        onClicked: {
            //kobe:选中项深色块移动
//            menulogo.GridView.view.currentIndex = index;
            if (text == "homepage") {
//                menulogo.state = "Home";
                menulogo.send("homepage");
                pageStack.push(homepage);
            }
            else if (text == "clearrubbish") {
//                menulogo.state = "Clear";
                menulogo.send("clearrubbish");
                pageStack.push(clearrubbish);
            }
            else if (text == "systemset") {
//                menulogo.state = "Beauty";
                menulogo.send("systemset");
//                pageStack.pop(systemset);
                pageStack.push(systemset);
            }

            else if (text == "systemmessage") {
//                menulogo.state = "Message";
                menulogo.send("systemmessage");
                pageStack.push(systemmessage);
            }
            else if (text == "functioncollection") {
//                menulogo.state = "Function";
                menulogo.send("functioncollection");
                pageStack.push(functioncollection);
            }
        }
    }





//    states: [
//        State {
//            name: "Home"; when: (menulogo.text == "homepage")
//            PropertyChanges { target: menulogo; iconName:  "homepage-hover.png"}
//        },
//        State {
//            name: "Clear"/*; when: (menulogo.text == "clearrubbish")*/
//            PropertyChanges { target: menulogo; iconName:  "systemclear-hover.png"}
//        },
//        State {
//            name: "Beauty"/*; when: (menulogo.text == "systemset")*/
//            PropertyChanges { target: menulogo; iconName:  "systembeauty-hover.png"}
//        },
//        State {
//            name: "Message"/*; when: (menulogo.text == "systemmessage")*/
//            PropertyChanges { target: menulogo; iconName:  "systemmessage-hover.png"}
//        },
//        State {
//            name: "Function"/*; when: (menulogo.text == "functioncollection")*/
//            PropertyChanges { target: menulogo; iconName:  "functioncollection-hover.png"}
//        }
//    ]


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
