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

Item {
    id: btn
    signal clicked
    signal exited
    signal entered
    property string text : ""
    property string hoverimage: "green.png"
    property string fontcolor: "white"
    property int fontsize: 12

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

//    BorderImage {
//        id: buttonImage
//        source: "../../img/icons/" + btn.hoverimage
//        width: btn.width; height: btn.height
//    }
//    BorderImage {
//        id: pressed
//        opacity: 0
//        source: "../../img/icons/unselect.png"
//        width: btn.width; height: btn.height
//    }
//    Image {
//        id: btnImg
//        anchors.fill: parent
//        source: ""
//    }

    Text {
        id: displaytext
        color: btn.fontcolor
        anchors.centerIn: parent//buttonImage
        font.family: "Helvetica"
        font.pixelSize: fontsize
        text: btn.text
        style: Text.Sunken
        styleColor: "#AAAAAA"
    }

//    FontTip {
//        id: fontTip
//        z:11
//        anchors.centerIn: parent
//        visible: false//mouseArea.pressed
//    }

    MouseArea {
        id: mouseRegion
        anchors.fill: parent//buttonImage
        hoverEnabled: true
        onEntered: {
            displaytext.color = "red";
            displaytext.text = qsTr("Click to change font");//点击更换字体
            btn.entered();
//            btnImg.source = "../../img/toolWidget/highlight.png"

//            fontTip.showText = qsTr("Click to change font");//点击更换字体
//            fontTip.visible = true;
        }
        onPressed: {
//            btnImg.source = "../../img/toolWidget/highlight.png"
//            displaytext.text = qsTr("点击更换字体");
        }
        //要判断松开是鼠标位置
        onReleased: {
//            fontTip.visible = false;
//            displaytext.text = btn.text;
        }

        onExited: {
            displaytext.color = btn.fontcolor;
            displaytext.text = btn.text;
            btn.exited();
//            btnImg.source = ""
//            fontTip.visible = false;
        }

        onClicked: {
            btn.clicked();
        }
    }
}
