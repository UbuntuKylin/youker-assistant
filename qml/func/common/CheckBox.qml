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
import "./defaultstyle" as DefaultStyle

Item {
    id: checkbox

    property int minimumWidth: defaultStyle.minimumWidth
    property int minimumHeight: defaultStyle.minimumHeight
    property string titleName: ""
    width: Math.max(minimumWidth, backgroundComponent.item.width)
    height: Math.max(minimumHeight, backgroundComponent.item.height)

    property alias containsMouse: behavior.containsMouse
    property Component background: defaultStyle.background
    property Component checkmark: defaultStyle.checkmark

//    property Component checksomeone: defaultStyle.checksomeone

    property color backgroundColor: "#fff";
    property string flag: ""

    // Common API
    signal clicked
    property alias pressed: behavior.pressed
    property alias checked: behavior.checked
//    property string checked_mid:

    Loader {
        id: backgroundComponent
        anchors.centerIn: parent
        sourceComponent: background
    }

    Loader {
        id: checkComponent
        anchors.centerIn: parent
        sourceComponent: checkmark
    }

    Text {
        text: checkbox.titleName
        font.pixelSize: 12
        color: "#383838"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
//        color: "black"
    }
    ButtonBehavior {
        id: behavior
        anchors.fill: parent
        checkable: true
        onClicked:checkbox.clicked()
    }

    DefaultStyle.CheckBoxStyle { id: defaultStyle; styleflag: checkbox.flag }
}
