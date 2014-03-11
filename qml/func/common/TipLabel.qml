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
    id: btn
    property string showImage
    property string kflag
    width: 19
    height: 13

    Image {
        id: buttonImage
        source: btn.showImage
        width: btn.width; height: btn.height
    }

    ToolTip {
        id: toolTip
        visible: false//mouseArea.pressed
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent//buttonImage
        hoverEnabled: true
        onEntered: {
            if (kflag == "yes") {
                toolTip.showText = qsTr("Support cloud conf");
                toolTip.visible = true;
            }
            else if (kflag == "no") {
                toolTip.showText = qsTr("No support cloud conf");
                toolTip.visible = true;
            }
        }
        onReleased: {
            toolTip.visible = false;
        }
        onExited: {
            toolTip.visible = false;
        }
    }
}
