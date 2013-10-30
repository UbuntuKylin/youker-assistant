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
import "common" as Common

Item {
    id: itemtitle
    signal clicked
    width: parent.width
    height: 40
    property bool expanded: true
    property string imageSource: ""
    property string itemTitle: ""
    property string detailstr: ""
    property string arrowSource: "../img/icons/arrow.png"
    Row {
        id: chrominum
        width: parent.width
        spacing: 15
        Common.MainCheckBox{
            id: chrominumcheck
            checked: "true"
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged: {
            }
        }
        Image {
            id: chrominumImage
            fillMode: "PreserveAspectFit"
            height: parent.height*0.9
            source: itemtitle.imageSource
            smooth: true
        }

        Column {
            id: chrominumColumn
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                text: itemtitle.itemTitle
                font.pointSize: 11
                color: "black"
            }
            Text {
                text: itemtitle.detailstr
                font.family: "URW Bookman L"
                font.pointSize: 9
                color: "gray"
            }
        }

        Image {
            id: chrominumarrow
            fillMode: "PreserveAspectFit"
            height: 28
            width: 26
            source: itemtitle.arrowSource
            rotation: itemtitle.expanded ? 0 : -180
            smooth: true
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    itemtitle.clicked();
                    itemtitle.expanded = !itemtitle.expanded;
                }
            }
        }
    }
}
