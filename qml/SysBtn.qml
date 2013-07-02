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
    width: btnImg.width/4
    height: btnImg.height
    clip: true
    color: "transparent"
    property string iconName
    Image {
        id: btnImg
        source: "./img/sysButton/" + iconName
        x: 0
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.x = 0-parent.width
        onPressed: btnImg.x = 0-parent.width*2
        //要判断鼠标松开时位置
        onReleased: btnImg.x = 0-parent.width*3
        onExited: btnImg.x = 0
    }
}
