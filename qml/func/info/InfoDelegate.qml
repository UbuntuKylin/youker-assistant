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
import "common" as Common
Item {
    id: container
    property string fontName: "Helvetica"
    property int fontSize: 10
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""

    signal clicked
    width: 680
    height: 20
    clip: true

    Row {
        spacing: 10
        Common.Label {
            text: title
            font.pixelSize: 14
            color: "#7a7a7a"
            width: 100
            height: 20
        }
        Text {
            id: slotText
            text: result
            font.pixelSize: 14
            color: "#7a7a7a"
            height: 20
        }
    }
}
