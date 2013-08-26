/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SessionType 0.1
import SystemType 0.1
import "common" as Common
import "bars" as Bars

Rectangle {
    id: screen; width: parent.width; height: 475
    property SessionDispatcher dis1: sessiondispatcher
    property SystemDispatcher dis2: systemdispatcher
    signal dialogmsg()
    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component:", component.errorString());
     }

    Rectangle {
        id: tools_widget
        anchors {
            fill: parent
            left: parent.right
            leftMargin: 2
            right: parent.left
            rightMargin: 2
        }
//        color: "white"

        Item {
            id: views
            width: parent.width
            height: parent.height

            //左右布局
            Row {
                anchors.fill: parent
                spacing: 0
                //坐边栏
                LeftPage {
                    id: leftbar
//                    anchors.left: parent.left
//                    anchors.leftMargin: -2
                    width: 600; height: screen.height
                }
               RightPage {
                    id: rightbar
//                    anchors.left: leftbar.right
//                    anchors.leftMargin: 0
                    width: screen.width - 600; height: screen.height
                }
            }//左右布局Row
            Item { id: foreground; anchors.fill: parent }
            //左右分割条
            Rectangle {id: midsplitbar1; x: 600; height: screen.height; width: 1; color: "#b9c5cc" }
            Rectangle {id: midsplitbar2; x: 602; height: screen.height; width: 1; color: "#fafcfe" }

        }//Item:views
    }//Rectangle:tools_widget
}//Rectangle:screen
