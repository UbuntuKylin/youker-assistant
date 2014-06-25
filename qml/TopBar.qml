/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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
//import SessionType 0.1

Rectangle {
    id: topbar
    width: 850; height: 29
    color: "transparent"
//    SessionDispatcher { id: sessiondispatcher }

//    property int closeleftspace: 1
//    property int minleftspace: 22

//    Component.onCompleted: {
//        var btn_position = sessiondispatcher.get_window_button_align_qt();
//        if(btn_position == "right") {
//            topbar.closeleftspace = 828;
//            topbar.minleftspace = 807;
//        }
//    }

//    Connections
//    {
//        target: sessiondispatcher
//        onStartChangeControlBtnPosition: {
//            if(position == "left") {
//                topbar.closeleftspace = 1;
//                topbar.minleftspace = 22;
//            }
//            if(position == "right") {
//                topbar.closeleftspace = 828;
//                topbar.minleftspace = 807;
//            }
//        }
//        onTellDownloadCloudConfToQML: {//使用云配置后，控件状态根据配置发生相应的变化
//            if(download == "window_button") {
//                var position_mode = sessiondispatcher.get_window_button_align_qt();
//                if(position_mode == "left") {
//                    topbar.closeleftspace = 1;
//                    topbar.minleftspace = 22;
//                }
//                if(position_mode == "right") {
//                    topbar.closeleftspace = 828;
//                    topbar.minleftspace = 807;
//                }
//            }
//        }
//    }

//    SysBtn {
//         iconName: "sys_button_close.png"
//        anchors {
//            left: parent.left
//            leftMargin: topbar.closeleftspace
//        }
//        onClicked: {
//            topbarObject.hideMainWidget();
//        }
//    }
//    SysBtn {
//        iconName: "sys_button_min.png"
//        anchors {
//            left: parent.left
//            leftMargin: topbar.minleftspace
//        }
//        onClicked: {
//            topbarObject.showMinMainWidget();
//        }
//    }
}
