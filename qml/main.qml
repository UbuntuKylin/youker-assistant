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
import ToolkitsType 0.1

import SessionType 0.1
import SystemType 0.1
import SudoType 0.1
import FcitxCfgWizard 0.1

Rectangle {
    id: main
    width: 850
    height: 600
    objectName: "main"
    anchors.fill: parent
    property string version: "0.2.1"
    SessionDispatcher {
        id: sessiondispatcher
    }
    SystemDispatcher {
        id: systemdispatcher
    }
    SudoDispatcher {
        id: sudodispatcher
    }
    FcitxCfgWizard {
        id: fcitxcfgwizard
    }
    Toolkits{id: toolkits}


    Image {
        id: bgImg
        anchors.fill: parent
        source: "./img/skin/bg.png"
    }
    radius: 4
//    color: "black"
//    opacity: 0.85
    opacity: 1.0

    Column {
        id: layout
        anchors.fill: parent
        spacing: 0
        ContentWidget{
            id: contentwidget
        }
        StatusWidget{
            id: statuswidget
            uk_version: main.version
        }
    }
    Text {
        anchors {
            top: parent.top
            topMargin: 70
            right: parent.right
            rightMargin: 35
        }
        font.family: "Arial"
        font.pixelSize: 18
        style: Text.Sunken
        styleColor: "#AAAAAA"
        color: "white"
        text: main.version
    }
}
