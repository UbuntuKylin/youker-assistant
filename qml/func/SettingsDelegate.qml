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
import RegisterMyType 0.1
import "common" as Common

Item {
    id: mysettings
    signal senditemset(string itemset)
    Column {
        anchors.fill: parent
        //---------------------Unity设置start---------------------
//            Common.SetTitle {
//                id: unity_title
//            }

        Row {
            Image {
                id: refreshArrow0
                source: "../img/icons/settings.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text0
//                    x: 30
//                    y: 11
                width: 69
                height: 20
                text: qsTr("Unity")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
            }
        }
        Row {
            anchors.left: parent.left
            anchors.leftMargin: 3
            spacing: 25
            SetBtn {iconName: "homepage.png"; method: "Launcher"; text: "launcher"}
            SetBtn {iconName: "clearrubbish.png"; method: "Search"; text: "search"}
            SetBtn {iconName: "optimalacceleration.png"; method: "Panel"; text: "panel"}
            SetBtn {iconName: "searchtrojan.png"; method: "Switcher"; text: "switcher"}
            SetBtn {iconName: "computerclinic.png"; method: "WebApps"; text: "webapps"}
            SetBtn {iconName: "fixbug.png"; method: "Additonal_uinty"; text: "additonal_uinty"}
        }
        //---------------------Unity设置end---------------------


        //---------------------窗体设置start---------------------
        Row {
            Image {
                id: refreshArrow1
                source: "../img/icons/about.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text1
                width: 69
                height: 20
                text: qsTr("Window Manager")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
            }
        }
        Row {
            anchors.left: parent.left
            anchors.leftMargin: 3
            spacing: 25
            SetBtn {iconName: "homepage.png"; method: "General"; text: "general"}
            SetBtn {iconName: "clearrubbish.png"; method: "WorkspaceSettings"; text: "workspacesettings"}
            SetBtn {iconName: "optimalacceleration.png"; method: "WindowSpread"; text: "windowspread"}
            SetBtn {iconName: "searchtrojan.png"; method: "WindowSnapping"; text: "windowsnapping"}
            SetBtn {iconName: "computerclinic.png"; method: "Hotcorners"; text: "hotcorners"}
            SetBtn {iconName: "fixbug.png"; method: "Additional_window"; text: "Additional_window"}
        }
        //---------------------窗体设置end---------------------

        //---------------------皮肤设置start---------------------
        Row {
            Image {
                id: refreshArrow2
                source: "../img/icons/history.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text2
                width: 69
                height: 20
                text: qsTr("Apprearance")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
            }
        }
        Row {
            anchors.left: parent.left
            anchors.leftMargin: 3
            spacing: 25
            SetBtn {iconName: "homepage.png"; method: "Theme"; text: "homepage"}
            SetBtn {iconName: "clearrubbish.png"; method: "Icons"; text: "clearrubbish"}
            SetBtn {iconName: "optimalacceleration.png"; method: "Cursor"}
            SetBtn {iconName: "searchtrojan.png"; method: "Font"; text: "searchtrojan"}
            SetBtn {iconName: "computerclinic.png"; method: "WindowControls"; text: "computerclinic"}
        }
        //---------------------皮肤设置end---------------------


        //---------------------系统设置start---------------------
        Row {
            Image {
                id: refreshArrow3
                source: "../img/icons/about.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text3
                width: 69
                height: 20
                text: qsTr("System")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
            }
        }
        Row {
            anchors.left: parent.left
            anchors.leftMargin: 3
            spacing: 25
            SetBtn {iconName: "homepage.png"; method: "DesktopIcons"; text: "desktopIcons"}
            SetBtn {iconName: "clearrubbish.png"; method: "Security"; text: "security"}
            SetBtn {iconName: "optimalacceleration.png"; method: "Scrolling"; text: "scrolling"}
        }
        //---------------------系统设置end---------------------
    }//Column

}//Item
