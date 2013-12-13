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

Item {
    id: delegate
    width: delegate.ListView.view.width; height: 40
    signal sendFlag(string flag);
    Row {
        spacing: 10
        anchors {
            left: parent.left; leftMargin: 15
            verticalCenter: parent.verticalCenter
        }
        //显示图片
        Image {
            id: icon
            width: 20
            height: 20
            source: delegate.ListView.isCurrentItem ? "../img/logo/component/" + iconName + "-active.png" : "../img/logo/component/" + iconName + ".png"
            anchors.verticalCenter: parent.verticalCenter
        }
        //显示文字
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: name
            color: delegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
            font {
                family: "Helvetica"
                pixelSize: 14
                bold: true
            }
        }
    }

    //分割线
    Rectangle {
        width: delegate.width - 4; height: 1; color: "#d8e0e6"
        anchors.bottom: delegate.bottom
        visible: delegate.ListView.isCurrentItem ? false : true
    }

    MouseArea {
        anchors.fill: delegate
        onClicked: {
            delegate.ListView.view.currentIndex = index;
            delegate.sendFlag(flag);
        }
    }
}
