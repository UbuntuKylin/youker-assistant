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

    property string picCurrent: ""
    property string picNormal: ""
    property string picHover: ""
    property string picPressed: ""

    property string text : ""
    property string fontcolor: "#ffffff"
    property int fontsize: 12

    signal clicked
    signal exited
    signal entered
    width: 27
    height: 22
    color:"#00000000"
    state:"normal"

    BorderImage {
        id: buttonImage
        source: picCurrent
        width: btn.width; height: btn.height
    }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            btn.entered();
            btn.state == "pressed" ? btn.state = "pressed" : btn.state = "hover";
        }
        onExited: {
            btn.exited();
            btn.state == "pressed" ? btn.state = "pressed" : btn.state = "normal";
        }
        onPressed: btn.state = "pressed"
        onReleased:
        {
            btn.state = "normal";
            btn.clicked();
        }
    }

    Text {
        id: displaytext
        color: btn.fontcolor
        anchors.centerIn: buttonImage
        font.family: "Helvetica"
        font.pixelSize: fontsize
        text: btn.text
    }

    states:
    [
        State{
            name:"hover"
            PropertyChanges {
                target: btn
                picCurrent:picHover
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: btn
                picCurrent:picNormal
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: btn
                picCurrent:picPressed
            }
        }
    ]
}
