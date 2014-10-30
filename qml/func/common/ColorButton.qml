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

Rectangle
{
    id: btn
    width: 58
    height: 29
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string wordname: ""

    property string colorCurrent: ""
    property string colorNormal: ""
    property string colorHover: ""
    property string colorPressed: ""

    property int sizeCurrent
    property int sizeNormal
    property int sizeHover
    property int sizePressed

    signal clicked

    state:"normal"

    Text {
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 2
        }
        text: wordname
        font.pixelSize: sizeCurrent
        color: colorCurrent
    }


    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btn.state == "pressed" ? btn.state = "pressed" : btn.state = "hover"
        onExited: btn.state == "pressed" ? btn.state = "pressed" : btn.state = "normal"
        onPressed: btn.state = "pressed"
        onReleased:
        {
            btn.state = "normal";
            btn.clicked();
        }
    }

    states:
    [
        State{
            name:"hover"
            PropertyChanges {
                target: btn
                colorCurrent: colorHover
                sizeCurrent: sizeHover
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: btn
                colorCurrent: colorNormal
                sizeCurrent: sizeNormal
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: btn
                colorCurrent: colorPressed
                sizeCurrent: sizePressed
            }
        }

    ]
}
