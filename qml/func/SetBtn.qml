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
    property string iconName: "homepage.png"
    property string method: "Launcher"
    property string text: "launcher"

    Column {
        anchors.fill: parent
        anchors.topMargin: 7
        Image {
            id: toolImg
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../img/toolWidget/" + iconName
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
        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            if (text == "launcher") {
//                pageStack.pop()
                console.log("22222222222222");
                pageStack.push(launcher);
//                menulogo.send("homepage")
//                console.log(text)
            }
            else if (text == "search") {
//                pageStack.pop();
                pageStack.push(search);
            }
            else if (text == "panel") {
//                pageStack.pop();
                pageStack.push(panel);
            }
            else if (text == "switcher") {
//                pageStack.pop();
                pageStack.push(switcher);
            }
            else {
//                pageStack.pop();
                pageStack.push(homepage);
            }
        }
    }

}
