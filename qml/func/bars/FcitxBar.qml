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
     signal cancelBtnClicked
     signal gobackBtnClicked
     signal continueBtnClicked

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
             id: cancelBtn
             visible: toolbar.showok
             picNormal: "../../img/icons/button12-gray.png"
             picHover: "../../img/icons/button12-gray-hover.png"
             picPressed: "../../img/icons/button12-gray-hover.png"
             text: qsTr("Cancel")//取消
             fontcolor:"#707070"
             fontsize: 12
             width: 70; height: 28
             onClicked:
             {
                 toolbar.cancelBtnClicked()
             }
         }

         Common.Button {
            id: gobackBtn
            visible: toolbar.showok
            picNormal: "../../img/icons/button12-gray-long.png"
            picHover: "../../img/icons/button12-gray-long-hover.png"
            picPressed: "../../img/icons/button12-gray-long-hover.png"
            text: qsTr("Previous")//上一步
            fontcolor:"#707070"
            fontsize: 12
            width: 100; height: 28
            onClicked: toolbar.gobackBtnClicked()
         }
         Common.Button {
             id: continueBtn
             picNormal: "../../img/icons/button12-gray-long.png"
             picHover: "../../img/icons/button12-gray-long-hover.png"
             picPressed: "../../img/icons/button12-gray-long-hover.png"
             text: qsTr("Next")//下一步
             fontcolor:"#707070"
             fontsize: 12
             width: 100; height: 28
             onClicked: toolbar.continueBtnClicked()
         }
     }
}
