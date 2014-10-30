/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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
import CloundType 0.1

Rectangle {
    id: bottombar
    width: 850
    height: 26
    color: "transparent"
    property string version: "V1.3.2"

    CloundDispatcher {  id: clounddispatcher  }

    Connections
    {
        target: clounddispatcher
        onStartShowIPAddress: {
            if (ip_addr === '') {
                iprow.visible = false;
            }
            else {
                iprow.visible = true;
                ip.text = ip_addr;
            }
        }
    }

    Component.onCompleted: {
        clounddispatcher.get_ip_address_qt();
    }
    Row {
        id: versionrow
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        spacing: 2
        Image {
            source: "./img/icons/arrowhead.png"
            width: 18; height: 18
        }
        Text {
            color: "white"
            font.pixelSize: 12
            text: qsTr("main version:") + bottombar.version//主版本：
        }
    }

    Row {
        id: iprow
        visible: false
        anchors {
            right: parent.right
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
        spacing: 2
        Image {
            source: "./img/icons/ip.png"
            width: 18; height: 18
        }
        Text {
            id: ip
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            font.pixelSize: 12
            text: ""
        }
    }
}
