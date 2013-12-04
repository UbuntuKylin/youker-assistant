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
    width: parent.width
    height: 30
    color: "transparent"
    property string uk_version: ""
    Component.onCompleted: {
    }
    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 5
        Image {
            source: "./img/icons/arrowhead.png"
        }
        Text {
            color: "white"
            font.pixelSize: 12
            text: qsTr("main version:") + uk_version//主版本:
        }
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: parent
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            mainwindow.pos = Qt.point(mainwindow.pos.x+delta.x, mainwindow.pos.y+delta.y)
        }


//        anchors.fill: parent
//        property variant previousPosition
//        onPressed: {
//            previousPosition = Qt.point(mouseX, mouseY)
//        }
//        onPositionChanged: {
//            if (pressedButtons == Qt.LeftButton) {
//                var dx = mouseX - previousPosition.x
//                var dy = mouseY - previousPosition.y
//                mainwindow.pos = Qt.point(mainwindow.pos.x + dx, mainwindow.pos.y + dy)
//            }
//        }
    }
}
