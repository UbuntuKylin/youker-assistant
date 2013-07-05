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

//import Ubuntu.Components 0.1
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1
Rectangle {
    width: parent.width
    height: 460
//    property Dispatcher dis: mydispather
    property SystemDispatcher dis: systemdispatcher

    //信号绑定，绑定qt的信号myStringChanged，该信号emit时触发onMyStringChanged
    Connections
    {
        target: systemdispatcher
        onMyStringChanged: {
            console.log("******Signal handler received******")
            console.log("******Start******")
            console.log(str)
            text0.text = str
            console.log("******End******")
        }
    }

    Text {
        id: text0
        anchors {top: parent.top; topMargin: 50}
        text: qsTr("clearprogress test by kobe")
        font.bold: true
        font.pointSize: 13
        font.pixelSize: 12
    }

//    ActivityIndicator {
//        id: sendSpinner
//        anchors.centerIn: parent
//        visible: false
//        running: visible
//    }

//    RefreshBar {
//        id: refreshBar
//        anchors {top: parent.top; topMargin: 50}
//        opacity: 0
//        visible: true//opacity > 0 ? true : false
//        Behavior on opacity {
//            NumberAnimation { duration: 200; }
//        }
//    }
}
