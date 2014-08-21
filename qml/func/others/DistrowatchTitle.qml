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

Item {
    id: distrowathchtitle

    Item {
        width: 15
        anchors {
            left: parent.left
            leftMargin: 5
            verticalCenter: parent.verticalCenter
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Rank")//名次
            font {
                family: "Helvetica"
                pixelSize: 10
            }
        }
    }
    Item {
        width: 113
        anchors {
            left: parent.left
            leftMargin: 15
            verticalCenter: parent.verticalCenter
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Distribution")//发行
            font {
                family: "Helvetica"
                pixelSize: 10
            }
        }
    }
    Item {
        width: 25
        anchors {
            left: parent.left
            leftMargin: 143
            verticalCenter: parent.verticalCenter
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("T.H")
            font {
                family: "Helvetica"
                pixelSize: 10
            }
        }
    }
    Item {
        width: 25
        anchors {
            left: parent.left
            leftMargin: 188
            verticalCenter: parent.verticalCenter
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Y.H")
            font {
                family: "Helvetica"
                pixelSize: 10
            }
        }
    }
}
