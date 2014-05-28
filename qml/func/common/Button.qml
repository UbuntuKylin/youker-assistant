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


Rectangle
{
    id: btn

    property string picCurrent: ""
    property string picNormal: ""
    property string picHover: ""
    property string picPressed: ""

    property string text : ""
//    property string hoverimage: "button16.png"
    property string fontcolor: "#ffffff"
    property int fontsize: 12

    signal clicked
    signal exited
    signal entered
    width: 27
    height: 22
    color:"#00000000"
    state:"normal"

//    Image
//    {
//        source: picCurrent;
//    }
    BorderImage {
        id: buttonImage
        source: picCurrent
        width: btn.width; height: btn.height
    }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            btn.entered();
            btn.state == "pressed" ? btn.state = "pressed" : btn.state = "hover";
        }
        onExited: {
            btn.exited();
            btn.state == "pressed" ? btn.state = "pressed" : btn.state = "normal";
        }
        onPressed: btn.state = "pressed"
        onReleased:
        {
            btn.state = "normal";
            btn.clicked();
        }
    }

    Text {
        id: displaytext
        color: btn.fontcolor
        anchors.centerIn: buttonImage
        font.family: "Helvetica"
        font.pixelSize: fontsize
        text: btn.text
    }

    states:
    [
        State{
            name:"hover"
            PropertyChanges {
                target: btn
                picCurrent:picHover
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: btn
                picCurrent:picNormal
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: btn
                picCurrent:picPressed
            }
        }
    ]
}

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

//    BorderImage {
//        id: buttonImage
//        source: "../../img/icons/" + btn.hoverimage
//        width: btn.width; height: btn.height
//    }
////    BorderImage {
////        id: pressed
////        opacity: 0
////        source: "../../img/icons/unselect.png"
////        width: btn.width; height: btn.height
////    }
//    Image {
//        id: btnImg
//        anchors.fill: parent
//        source: ""
//    }
//    MouseArea {
//        id: mouseRegion
//        anchors.fill: buttonImage
//        hoverEnabled: true
//        onEntered: {
//            btn.entered();
//            btnImg.source = "../../img/toolWidget/highlight.png"
//        }
//        onPressed: {
//            btnImg.source = "../../img/toolWidget/highlight.png"
//        }
//        //要判断松开是鼠标位置
//        onReleased: {
//        }

//        onExited: {
//            btn.exited();
//            btnImg.source = ""
//        }

//        onClicked: {
//            btn.clicked();
//        }
//    }

//    Text {
//        id: displaytext
//        color: btn.fontcolor
//        anchors.centerIn: buttonImage
//        font.family: "Helvetica"
//        font.pixelSize: fontsize
//        text: btn.text
//        style: Text.Sunken
//        styleColor: "#AAAAAA"
//    }
////    states: [
////        State {
////            name: "Pressed"
////            when: mouseRegion.pressed == true
////            PropertyChanges { target: pressed; opacity: 1 }
////        }
////    ]
//}
