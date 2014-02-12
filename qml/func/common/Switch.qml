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
    id: container
    signal switched(bool position)
    property string fontName: "Helvetica"
    property int fontSize: 8
    property color fontColor: "black"
    property string imageOn: '../../img/icons/on.png'
    property string imageOff: '../../img/icons/off.png'
    property bool switchedOn: true
    width: 76
    height: 29
    Image {
        id: toggleSwitch
        height: container.height
        source: switchedOn ? imageOn : imageOff
        fillMode: Image.PreserveAspectFit
        smooth: true
    }
    Text {
//        anchors.centerIn: toggleSwitch
        anchors.verticalCenter: toggleSwitch.verticalCenter
        text: switchedOn ?qsTr("     ON") : qsTr("OFF")//已开启      已关闭
        color: container.fontColor
        anchors.left: toggleSwitch.left
        anchors.leftMargin: switchedOn ? 5: 30
        font {
            family: container.fontName
            pointSize: container.fontSize
        }
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        anchors.fill: toggleSwitch
        onClicked: { switchedOn = !switchedOn; switched(switchedOn) }
    }
}
