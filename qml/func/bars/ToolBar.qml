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
import "../common" as Common
Item {
     id: toolbar
     property bool showok: true
     property bool showrestore: false
     signal quitBtnClicked
     signal okBtnClicked
     signal restoreBtnClicked

     BorderImage {
//         source: "../../img/icons/tab.png"
         width: parent.width; height: parent.height + 14; y: -7
     }

     Rectangle{id: splitbar; x:2; width:parent.width - 4 ; height:1; color:"#b9c5cc"}

     Row {
         spacing: 19
         height: 32
         anchors {
             right: parent.right
             rightMargin: 42
             top: splitbar.bottom
             topMargin: 10
         }

         Common.Button {
             id: okBtn
             visible: toolbar.showok
             picNormal: "../../img/icons/button12-gray.png"
             picHover: "../../img/icons/button12-gray-hover.png"
             picPressed: "../../img/icons/button12-gray-hover.png"
             fontcolor:"#707070"
             fontsize: 12
             width: 70; height: 28
             text: qsTr("OK")//确定
             onClicked: toolbar.okBtnClicked()
         }
         Common.Button {
             id: restoreBtn
             visible: toolbar.showrestore
             picNormal: "../../img/icons/button12-lightblue-long.png"
             picHover: "../../img/icons/button12-lightblue-long-hover.png"
             picPressed: "../../img/icons/button12-lightblue-long-hover.png"
             fontcolor:"#707070"
             fontsize: 12
             width: 100; height: 28
             text: qsTr("Restore")//恢复默认
             onClicked: toolbar.restoreBtnClicked()
         }
         Common.Button {
             id: quitBtn
             picNormal: "../../img/icons/button12-gray.png"
             picHover: "../../img/icons/button12-gray-hover.png"
             picPressed: "../../img/icons/button12-gray-hover.png"
             fontcolor:"#707070"
             fontsize: 12
             width: 70; height: 28
             text: qsTr("Back")//返回
             onClicked: toolbar.quitBtnClicked()
         }
     }
}
