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

//Item {
//    id: btn
//    signal clicked
//    signal exited
//    signal entered
//    property string text : ""
//    property string hoverimage: "green.png"
//    property string fontcolor: "white"
//    property int fontsize: 12

//    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

//    Text {
//        id: displaytext
//        color: btn.fontcolor
//        anchors.centerIn: parent//buttonImage
//        font.family: "Helvetica"
//        font.pixelSize: fontsize
//        text: btn.text
//    }

//    MouseArea {
//        id: mouseRegion
//        anchors.fill: parent//buttonImage
//        hoverEnabled: true
//        onEntered: {
//            displaytext.color = "#f2390e";
//            displaytext.text = qsTr("Click to change font");//点击更换字体
//            btn.entered();
//        }
//        onPressed: {
//            displaytext.color = btn.fontcolor;
//            displaytext.text = btn.text;
//        }
//        //要判断松开是鼠标位置
//        onReleased: {
//            displaytext.color = btn.fontcolor;
//            displaytext.text = btn.text;
//        }
//        onExited: {
//            displaytext.color = btn.fontcolor;
//            displaytext.text = btn.text;
//            btn.exited();
//        }
//        onClicked: {
//            btn.clicked();
//        }
//    }
//}


Rectangle
{
    id: btn
    width: 58
    height: 29
    signal clicked
    property string text : ""

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string wordname: ""
    property string stateText: qsTr("Click to change font")//点击更换字体

    property int sizeCurrent: 12
    property int sizeNormal
    property int sizeHover
    property int sizePressed

    state:"normal"

    Text {
        id: showBtn
        anchors.centerIn: parent
        color: "#086794"
        text: btn.text
        font {
            family: "Helvetica"
            pixelSize: sizeCurrent
        }
    }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btn.state == "pressed" ? btn.state = "pressed" : btn.state = "hover"
        onExited: btn.state == "pressed" ? btn.state = "pressed" : btn.state = "normal"
        onPressed: btn.state = "pressed"
        onReleased:
        {
            btn.state = "normal";
            btn.clicked();
        }
    }

    states:
    [
        State{
            name:"hover"
            PropertyChanges {
                target: showBtn
                text: btn.stateText
                font.pixelSize: sizeHover
                color: "#f2390e"
            }
            PropertyChanges {
                target: btn
                sizeCurrent: sizeHover
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: showBtn
                text: btn.text
                font.pixelSize: sizeNormal
                color: "#00a0e9"
            }
            PropertyChanges {
                target: btn
                sizeCurrent: sizeNormal
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: showBtn
                text: btn.text
                font.pixelSize: sizePressed
                color: "#f5960d"
            }
            PropertyChanges {
                target: btn
                sizeCurrent: sizePressed
            }
        }
    ]
}
