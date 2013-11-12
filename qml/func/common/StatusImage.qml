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
    id: statusImage
    width: 49
    height: 20
    property string iconName: "yellow.png"
    property string text: qsTr("未完成")

    Image {
        id: statusImg
//        anchors.horizontalCenter: parent.horizontalCenter
        source: "../../img/toolWidget/" + iconName
    }
    Text {
        id: displaytext
        color: "white"
        anchors.centerIn: statusImg
        font.family: "Helvetica"
        font.pixelSize: 12
        text: statusImage.text
        style: Text.Sunken
        styleColor: "#AAAAAA"
    }
}
