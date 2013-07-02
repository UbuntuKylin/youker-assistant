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
    width: 850
    height: 600
    id: main
    objectName: "main"
//    anchors.fill: parent
    Image {
        id: bgImg
        anchors.fill: parent
        source: "./img/skin/background.png"
    }

    Column {
        id: layout
        anchors.fill: parent
//        anchors {
//            left: parent.left
//            top: parent.top
//            right: parent.right
//        }
        spacing: 0
        ContentWidget{
            id: contentwidget
            anchors {
                bottom: statuswidget.top
            }
        }
        StatusWidget{
            id: statuswidget
//            anchors.fill: parent
        }
    }
}
