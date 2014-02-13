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
    property string showImage
    property string kflag
    width: 185
    height: 45
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    property string path: "../../img/en/"
    Component.onCompleted: {
        if(sessiondispatcher.get_locale_version() == "zh_CN") {
            btn.path = "../../img/zh_CN/";
        }
        else {
            btn.path = "../../img/en/";
        }
    }

    Image {
        id: buttonImage
        source: btn.showImage
        width: btn.width; height: btn.height
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    //------------------------
//    ToolTip {
//        id: toolTip
//        showText: qsTr("Please use UbuntuKylin forum account...")
//        visible: false//mouseArea.pressed
//    }
    //------------------------

    MouseArea {
        id: mouseArea
        anchors.fill: parent//buttonImage
        hoverEnabled: true
        onEntered: {
            if (kflag == "login") {
                btnImg.source = btn.path + "login-hover.png";
//                toolTip.visible = true;
            }
            else {
                btnImg.source = "../../img/toolWidget/button-hover.png"
            }
        }
        onPressed: {
            if (kflag == "login") {
                btnImg.source = btn.path + "login-hover.png"
            }
            else {
                btnImg.source = "../../img/toolWidget/button-hover.png"
            }
//            toolTip.visible = false;
        }
        //要判断松开是鼠标位置
        onReleased: {
            if (kflag == "login") {
                btnImg.source = btn.path + "login-hover.png"
            }
            else {
                btnImg.source = "../../img/toolWidget/button-hover.png"
            }
//            toolTip.visible = false;
        }
        onExited: {
            btnImg.source = "";
//            toolTip.visible = false;
        }
        onClicked: { btn.clicked() }
    }
}
