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

Rectangle {
    id: styleBtn
    width: 58
    height: 29
    property int fontSize: 10
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string textColor: "#318d11"
    property string wordname: ""
    signal clicked();

    Text {
        id:textname
        anchors.centerIn: parent
        text: wordname
        font.pointSize: styleBtn.fontSize
        color: styleBtn.textColor//"#318d11"
    }

    Rectangle {
        id: btnImg
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.bottom
        }
        width: textname.width
        height: 1
        color: "transparent"
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.color = styleBtn.textColor//"#318d11"
        onPressed: btnImg.color = styleBtn.textColor//"#318d11"
        //要判断松开是鼠标位置
        onReleased: btnImg.color = styleBtn.textColor//"#318d11"
        onExited: btnImg.color = "transparent"
        onClicked: {
            styleBtn.clicked();
        }
    }
}
