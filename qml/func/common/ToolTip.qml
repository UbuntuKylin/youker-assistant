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
    property string showText
    visible: false
    color: "#383838"

    BorderImage {
        id: borderimage
        source: "../../img/skin/frame.png"
        width: 165
        height: 24
        anchors {
            top: parent.bottom
            topMargin: 15
        }
    }
    Text {
        id: tipText
        anchors {
            left: borderimage.left
            leftMargin: 20
            verticalCenter: borderimage.verticalCenter
        }
        font.pixelSize: 10
        text: showText
        color: "#607684"
    }
}
