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
Item {
    id: screen; width: parent.width; height: 475
    Rectangle {
        id: setting_widget
        anchors.fill: parent
        //背景
        Image {
            source: "../img/skin/bg-middle.png"
            anchors.fill: parent
        }
        Item {
            id: views
            width: parent.width
            height: parent.height
            ListModel {
                id: funcmodel
                ListElement {
                    icon: "../img/icons/adobe-flash.png"
                    flag: "AdobeFlash"
                }
                ListElement {
                    icon: "../img/icons/chromium.png"
                    flag: "Chromium"
                }
                ListElement {
                    icon: "../img/icons/irc.png"
                    flag: "EclipseQt"
                  }
                ListElement {
                    icon: "../img/icons/irc.png"
                    flag: "Irc"
                }
                ListElement {
                    icon: "../img/icons/kuaipan.png"
                    flag: "Kuaipan"
                }
                ListElement {
                    icon: "../img/icons/kugou.png"
                    flag: "KugouMusic"
                  }
                ListElement {
                    icon: "../img/icons/lotus.png"
                    flag: "Lotus"
                }
                ListElement {
                    icon: "../img/icons/Pps.png"
                    flag: "Pps"
                }
                ListElement {
                    icon: "../img/icons/qbittorrent.png"
                    flag: "QbitTorrent"
                  }
                ListElement {
                    icon: "../img/icons/stardict.png"
                    flag: "StarDict"
                }
                ListElement {
                    icon: "../img/icons/vic.png"
                    flag: "Vic"
                }
                ListElement {
                    icon: "../img/icons/virtualbox.png"
                    flag: "VirtualBox"
                  }
                ListElement {
                    icon: "../img/icons/virtualbox.png"
                    flag: "Wineqq"
                }
                ListElement {
                    icon: "../img/icons/xchat.png"
                    flag: "Wps"
                }
                ListElement {
                    icon: "../img/icons/xchat.png"
                    flag: "XChat"
                }
                ListElement {
                    icon: "../img/icons/xunlei.png"
                    flag: "XunLei"
                }
            }
            GridView {
                id: gridView
                height: parent.height
                width: parent.width
                anchors {
                    top: parent.top
                    topMargin: 10
                    left: parent.left
                    leftMargin: 30
                }
                model: funcmodel
                delegate: SoftwareDelegate {}
                cacheBuffer: 1000
                cellWidth: (parent.width-2)/4; cellHeight: cellWidth
//                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true
            }
            Item { id: foreground; anchors.fill: parent }
        }
    }
}
