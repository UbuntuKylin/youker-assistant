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
import "software" as Software

Rectangle {
    id: softwaredelegate
    scale: 1
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    width: 167
    height: 79
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    Image {
        id: seticon
        source: icon
        anchors.fill: parent
        anchors.topMargin: 7
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            if (flag == "AdobeFlash")
                pageStack.push(adobeflashpage);
            else if (flag == "Chromium")
            {

                pageStack.push(adobeflashpage);
            }
            else if (flag == "EclipseQt")
                pageStack.push(adobeflashpage);
            else if (flag == "Irc")
                pageStack.push(adobeflashpage);
            else if (flag == "Kuaipan")
                pageStack.push(adobeflashpage);
            else if (flag == "KugouMusic")
                pageStack.push(adobeflashpage);
            else if (flag == "Lotus")
                pageStack.push(adobeflashpage);
            else if (flag == "Pps")
                pageStack.push(adobeflashpage);
            else if (flag == "QbitTorrent")
                pageStack.push(adobeflashpage);
            else if (flag == "StarDict")
                pageStack.push(adobeflashpage);
            else if (flag == "Vic")
                pageStack.push(adobeflashpage);
            else if (flag == "VirtualBox")
                pageStack.push(adobeflashpage);
            else if (flag == "Wineqq")
                pageStack.push(adobeflashpage);
            else if (flag == "Wps")
                pageStack.push(adobeflashpage);
            else if (flag == "XChat")
                pageStack.push(adobeflashpage);
            else if (flag == "XunLei")
                pageStack.push(adobeflashpage);
//            softwaredelegate.GridView.view.currentIndex = index;
        }
    }
}
