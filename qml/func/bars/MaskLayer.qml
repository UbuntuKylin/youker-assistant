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
    id: masklayer
    width: parent.width; height: 475
    color: "gray"
    //背景
//    Image {
//        source: "../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }
    AnimatedImage {
        width: 16
        height: 16
        source: "../../img/icons/move.gif"
        anchors.centerIn: parent
    }
}
