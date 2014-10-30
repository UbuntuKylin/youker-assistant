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

Item {
     id: progressbar

     property int minimum: 0
     property int maximum: 100
     property int value: 0
     property alias color: gradient1.color
     property alias secondColor: gradient2.color

     width: 250; height: 23
     clip: true

     BorderImage {
         source: "../../img/skin/progress-bg.png"
         width: parent.width; height: parent.height
         border { left: 4; top: 4; right: 4; bottom: 4 }
     }

     Rectangle {
         id: highlight

         property int widthDest: ((progressbar.width * (value - minimum)) / (maximum - minimum) - 6)

         width: highlight.widthDest
         Behavior on width { SmoothedAnimation { velocity: 1200 } }

         anchors { left: parent.left; top: parent.top; bottom: parent.bottom; margins: 3 }
         radius: 1
         gradient: Gradient {
             GradientStop { id: gradient1; position: 0.0 }
             GradientStop { id: gradient2; position: 1.0 }
         }

     }
     Text {
         anchors { right: highlight.right; rightMargin: 6; verticalCenter: parent.verticalCenter }
         color: "white"
         font.bold: true
         text: Math.floor((value - minimum) / (maximum - minimum) * 100) + '%'
     }
 }
