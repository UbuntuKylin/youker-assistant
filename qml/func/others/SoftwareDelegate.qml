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
import "../common" as Common

Rectangle {
    id: softwaredelegate
    scale: 1
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    width: 167
    height: 79
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    Image {
        id: seticon
        source: icon
        anchors.fill: parent
        anchors.topMargin: 7
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../../img/toolWidget/highlight.png"
        onPressed: btnImg.source = "../../img/toolWidget/highlight.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../../img/toolWidget/highlight.png"
        onExited: btnImg.source = ""
        onClicked: {
            systemdispatcher.ready_show_app_page(flag);
            pageStack.push(softwarepage);
        }
    }
}
