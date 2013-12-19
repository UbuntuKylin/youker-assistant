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
import "../common" as Common

Item {
     id: topbar
     property string arrow: "../../img/icons/return.png"
//     property string actiontitle: ""
//     property string actiontext: ""


     signal buttonClicked
//     Common.Button {
//         id: backBtn
//         hoverimage: topbar.arrow
//         width: 28; height: 26
//         onClicked: topbar.buttonClicked()
//     }

     Common.SetBtn {
         id: backBtn
         width: 28
         height: 26
         iconName: "return.png"
         setbtn_flag: "return"
         onClicked: topbar.buttonClicked()
     }
//     Image {
//         id: btnImg
//         anchors.fill: parent
//         source: ""
//     }
//     MouseArea {
//         hoverEnabled: true
//         anchors.fill: backBtn
//         onEntered: backBtn.hoverimage = "../../img/icons/return-hover.png";
//         onPressed: backBtn.hoverimage = "../../img/icons/return-hover.png";
//         //要判断松开是鼠标位置
//         onReleased: backBtn.hoverimage = "../../img/icons/return.png"
//     }
//     Common.SetBtn{
//         id: backBtn
//         setbtn_flag: topbar.arrow
//         iconName:topbar.arrow
//         width: 28; height: 26
//         onClicked: topbar.buttonClicked()
//     }

//     Row {
//         spacing: 10
//         Common.Button {
//             id: backBtn
//             hoverimage: topbar.arrow
//             width: 28; height: 26
//             onClicked: topbar.buttonClicked()
//         }
//         Text {
//             text: topbar.actiontitle
//             anchors.verticalCenter: parent.verticalCenter
//             font.bold: true
//             font.pixelSize: 14
//             color: "#383838"
//         }
//     }
//     Text {
//         anchors.top: parent.top
//         anchors.topMargin: 20
//         anchors.left: parent.left
//         anchors.leftMargin: 30
//         text: topbar.actiontext
//         font.pixelSize: 12
//         color: "#7a7a7a"
//     }
 }
