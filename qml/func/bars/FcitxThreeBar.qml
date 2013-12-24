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
     id: toolbar

     property bool showok: true
     signal gobackHomeClicked
     signal cancelBtnClicked
     signal finishBtnClicked
     signal gobackBtnClicked

     BorderImage {
 //        source: "../../img/icons/tab.png"
         width: parent.width; height: parent.height + 14; y: -7
     }

     Rectangle{id: splitbar; x:2; width:parent.width - 4 ; height:1; color:"#b9c5cc"}

     Row {
         spacing: 30
         height: 32
         anchors {
             right: parent.right
             rightMargin: 5
             top: splitbar.bottom
             topMargin: 10
         }

         Common.Button {
             id: gobackHome
             hoverimage: "gray1.png"
             text: qsTr("Home")//返回主页
             fontcolor:"#929292"
             fontsize: 13
             width: 94; height: 29
             onClicked: toolbar.gobackHomeClicked()
         }
         Common.Button {
             id: cancelBtn
             visible: toolbar.showok
             hoverimage: "gray1.png"
             text: qsTr("Cancel")//取消
             fontcolor:"#929292"
             fontsize: 13
             width: 94; height: 29
             onClicked: toolbar.cancelBtnClicked()
         }
         Common.Button {
             id: gobackBtn
             hoverimage: "gray1.png"
             text: qsTr("Previous")//上一步
             fontcolor:"#929292"
             fontsize: 13
             width: 94; height: 29
             onClicked: toolbar.gobackBtnClicked()
         }
         Common.Button {
            id: finishBtn
            visible: toolbar.showok
            hoverimage: "green2.png"
            fontsize: 13
            fontcolor:"#ffffff"
            text: qsTr("Apply")//应用
            width: 94; height: 29

            onClicked: toolbar.finishBtnClicked()
         }
      }
   }
