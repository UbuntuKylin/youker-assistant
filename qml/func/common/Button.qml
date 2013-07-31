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
Item {
    id: btn
    signal clicked
//    property string text
//    property string text : ""
    property string hoverimage: "scan-start.png"
    BorderImage {
        id: buttonImage
        source: "../../img/icons/" + btn.hoverimage
        width: btn.width; height: btn.height
    }
    BorderImage {
        id: pressed
        opacity: 0
        source: "../../img/icons/unselect.png"
        width: btn.width; height: btn.height
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        hoverEnabled: true
//        id: signaltest
//        anchors.fill: parent

//        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""

        onEntered: {
            if (hoverimage == "return.png")
                btnImg.source = "../../img/icons/return-hover.png"
            else if (hoverimage == "sort.png")
                btnImg.source = "../../img/icons/sort-hover.png"
            else if (hoverimage == "selectpic.png")
                btnImg.source = "../../img/icons/selectpic-hover.png"
            else
                btnImg.source = "../../img/toolWidget/menu_hover.png"
        }
        onPressed: {
            if (hoverimage == "return.png")
                btnImg.source = "../../img/icons/return-hover.png"
            else if (hoverimage == "sort.png")
                btnImg.source = "../../img/icons/sort-hover.png"
            else if (hoverimage == "selectpic.png")
                btnImg.source = "../../img/icons/selectpic-hover.png"
            else
                btnImg.source = "../../img/toolWidget/menu_press.png"

        }
        //要判断松开是鼠标位置
        onReleased: {
            if (hoverimage == "return.png")
                btnImg.source = "../../img/icons/return.png"
            else if (hoverimage == "sort.png")
                btnImg.source = "../../img/icons/sort.png"
            else if (hoverimage == "selectpic.png")
                btnImg.source = "../../img/icons/selectpic.png"
            else
                btnImg.source = "../../img/toolWidget/menu_hover.png"
        }

        onExited: btnImg.source = ""



        onClicked: { btn.clicked(); }
    }
//    Text {
//        color: "white"
////        visible: (btn.text == "") ? false : true
//        anchors.centerIn: buttonImage; font.bold: true; font.pixelSize: 15
//        text: btn.text; style: Text.Raised; styleColor: "black"
//    }
    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: pressed; opacity: 1 }
        }
    ]
}
