
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
    property alias color : rectangle.color

    BorderImage {
        anchors.fill: rectangle
        anchors { leftMargin: 0; topMargin: 0; rightMargin: -8; bottomMargin: -8 }
        border { left: 10; top: 10; right: 10; bottom: 10 }
//        source: "../images/shadow.png"; smooth: true
        source: "./img/skin/bg-bottom-tab.png"; smooth: true
    }

    Rectangle { id: rectangle; anchors.fill: parent; radius:5}
}
