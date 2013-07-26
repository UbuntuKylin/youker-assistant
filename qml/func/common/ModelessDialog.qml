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
import QtDesktop 0.1

Rectangle {
    id: dialog
    width: 300
    height: 250
    color: "transparent"

    Image {
        id: bgImg
        anchors.fill: parent
        source: "../../img/skin/background.png"
    }
    Column {
        spacing: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            text: "点击鼠标左键更换颜色,右键退出"
//            anchors.centerIn: parent
            width: quitBtn.width + okBtn.width + 10
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Row {
            spacing: 20
            Button {
                id: quitBtn
                text: qsTr("取消")
                onClicked: {
//                    Qt.quit()
                }
            }
            Button {
                id: okBtn
                text: qsTr("确定")
            }
        }
    }


//    MouseArea {
//          id: mouseRegion
//          anchors.fill: parent
//          property variant clickPos: "1,1"

//          onPressed: {
//              clickPos  = Qt.point(mouse.x,mouse.y)
//          }

//          onPositionChanged: {
//              var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
//              modelessdialog.pos = Qt.point(modelessdialog.pos.x+delta.x,
//                                modelessdialog.pos.y+delta.y)
//          }
//      }


}
