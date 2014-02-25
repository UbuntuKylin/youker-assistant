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
Rectangle {
    id: menulogo
    width: 39
    height: 43
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string iconName: ""
    signal clicked();   //如果没有选中任何清理项，提示警告框！first page

    Image {
        id: toolImg
        source: "../../img/icons/" + iconName
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        hoverEnabled: true
        anchors.fill: parent

        onEntered: {
            if(menulogo.iconName == "return.png") {
                btnImg.source = "../../img/icons/return-hover.png";
            }
            else {
                btnImg.source = "../../img/toolWidget/highlight.png";
            }
        }
        onPressed: {
            if(menulogo.iconName == "return.png") {
                btnImg.source = "../../img/icons/return-hover.png";
            }
            else {
                btnImg.source = "../../img/toolWidget/highlight.png";
            }
        }
        //要判断松开是鼠标位置
        onReleased: {
            if(menulogo.iconName == "return.png") {
                btnImg.source = "../../img/icons/return.png";
            }
            else {
                btnImg.source = "../../img/icons/" + iconName;
            }
        }
        onExited: btnImg.source = ""
        onClicked: {
            menulogo.clicked();
        }
    }
}
