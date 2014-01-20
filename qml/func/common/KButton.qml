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
    property string showImage
    width: 185
    height: 45
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
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
    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        hoverEnabled: true
        onEntered: { btnImg.source = "../../img/toolWidget/menu_hover.png" }
        onPressed: { btnImg.source = "../../img/toolWidget/menu_press.png" }
        //要判断松开是鼠标位置
        onReleased: { btnImg.source = "../../img/toolWidget/menu_hover.png" }
        onExited: { btnImg.source = "" }
        onClicked: { btn.clicked() }
    }
}
