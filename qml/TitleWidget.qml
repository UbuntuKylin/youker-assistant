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
    id: titlebar
    height: 20
    width: parent.width
    color: "transparent"

    property int closeleftspace: 1
    property int minleftspace: 22

    Component.onCompleted: {
        var btn_position = sessiondispatcher.get_window_button_align_qt();
        if(btn_position == "right") {
            titlebar.closeleftspace = 828;
            titlebar.minleftspace = 807;
        }
    }

    Connections
    {
        target: sessiondispatcher
        onStartChangeControlBtnPosition: {
            if(position == "left") {
                titlebar.closeleftspace = 1;
                titlebar.minleftspace = 22;
            }
            if(position == "right") {
                titlebar.closeleftspace = 828;
                titlebar.minleftspace = 807;
            }
        }
    }

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

    SysBtn {
        iconName: "sys_button_close.png"
        anchors {
            left: parent.left
            leftMargin: titlebar.closeleftspace
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mainwindow.hide();
            }
        }
    }
    SysBtn {
        iconName: "sys_button_min.png"
        anchors {
            left: parent.left
            leftMargin: titlebar.minleftspace
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mainwindow.showMinimized();
            }
        }
    }

//    Row {
//        id:row
//        anchors {
//            left: parent.left
//            leftMargin: titlebar.leftspace
//        }

//        SysBtn {
//            iconName: "sys_button_close.png"
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    mainwindow.hide();
////                    systemdispatcher.exit_qt();
////                    sessiondispatcher.exit_qt();
////                    sudodispatcher.exit_qt();
////                    Qt.quit();
//                }
//            }
//        }
//        SysBtn {
//            iconName: "sys_button_min.png"
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    mainwindow.showMinimized();
//                }
//            }
//        }
////        SysBtn {
////            iconName: "title_bar_menu.png"
////            MouseArea {
////                anchors.fill: parent
////                acceptedButtons : Qt.LeftButton
////                onClicked: {
////                    sessiondispatcher.showSkinWidget(/*mainwindow.pos.x, mainwindow.pos.y*/);
////                }
////            }
////        }
//    }
}
