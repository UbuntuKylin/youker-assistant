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
//Rectangle {
Item {
    height: 20
    width: parent.width
//    color: "transparent"
//    opacity: 0.3

//    Text {
//        anchors.top: parent.top
//        anchors.topMargin: 4
//        anchors.right: parent.right
//        anchors.rightMargin: 14
//        color: "black"
//        font.bold: true
//        text: qsTr("系统助手 0.1.0")
//    }


    //竖列菜单
    //---------------------------
    ContextMenu {
        id : menu
        MenuItem {
            text : "kobe01"

//            onSelected: {

//            }

//            onSelected : {
//                console.log("change spin");
//                //menu.selected
//                console.log(menu.selectedText)
//            }
        }
        MenuItem {
            text : "kobe02"
//            onSelected : {
//                console.log("verson msg");
//                console.log(menu.selectedText)
//            }
        }
        MenuItem {
            text : "kobe03"
//            onSelected : {
//                console.log("connect author");
//                console.log(menu.selectedText)
//            }
        }

        model: ListModel {
            id: menuitem
            ListElement { text: "更换皮肤"/*; iconName: "./img/icons/history.png"*/}
            ListElement { text: "版本信息"/*; iconName: "./img/icons/about.png"*/ }
            ListElement { text: "联系作者"/*; iconName: "./img/icons/settings.png"*/ }
        }
    }
    //---------------------------



    MouseArea {
          id: mouseRegion
          anchors.fill: parent;
          property variant clickPos: "1,1"

          onPressed: {
              clickPos  = Qt.point(mouse.x,mouse.y)
          }

          onPositionChanged: {
              var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
              mainwindow.pos = Qt.point(mainwindow.pos.x+delta.x,
                                mainwindow.pos.y+delta.y)
          }
      }

    Row {
        id:row
        anchors.left: parent.left
        anchors.leftMargin: 1

        SysBtn {
            iconName: "sys_button_close.png"
//            iconName: "closeBtn.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Qt.quit();
                }
            }
        }
        SysBtn {
            iconName: "sys_button_min.png"
//            iconName: "minBtn.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    WindowControl.showMinimized();
                }
            }
        }
        SysBtn {
            iconName: "title_bar_menu.png"
//            iconName: "SkinButton.png"

            MouseArea {
                anchors.fill: parent
                acceptedButtons : Qt.LeftButton//Qt.RightButton
//                property variant clickPos: "1,1"
//                onPressed: {
//                    clickPos  = Qt.point(mouse.x,mouse.y)
//                }
//                  onClicked: menu.showPopup(clickPos.x, clickPos.y)
                onClicked: menu.showPopup(row.x, row.y+20)
//
            }
        }

//        SysBtn {iconName: "sys_button_max.png"}

    }
}
