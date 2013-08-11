/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SystemType 0.1
Rectangle {
    id: menulogo
    width: 58
    height: 29
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property SystemDispatcher dis: systemdispatcher
    property string iconName: "onekeyBtn.png"
    property string setbtn_flag: "onekey"

    property string get_msg: ""


    signal send_dynamic_picture(string str);
    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork,按钮恢复使能
    Connections{
         target: systemdispatcher
         onFinishCleanWorkMain: {
             console.log(msg);
            if (msg == "") {
                 menulogo.enabled=true;
             }
             else if (msg == "h") {
                 menulogo.enabled=true;
             }
             else if (msg == "k") {
                 menulogo.enabled=true;
             }
             else if (msg == "u") {
                 menulogo.enabled=true;
             }
             else if (msg == "c") {
                 menulogo.enabled=true;
             }

        }
    }


    Image {
        id: toolImg
//        anchors.horizontalCenter: parent.horizontalCenter
        source: "../img/icons/" + iconName
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        hoverEnabled: true
        anchors.fill: parent

        onEntered: {
            if (menulogo.setbtn_flag == "onekey")
                btnImg.source = "../img/icons/onekeyBtn-hover.png"
            else if (menulogo.setbtn_flag == "smallonekey")
                btnImg.source = "../img/icons/onekey-hover.png"
            else if (menulogo.setbtn_flag == "set")
                btnImg.source = "../img/icons/set-hover.png"
            else if (menulogo.setbtn_flag == "message")
                btnImg.source = "../img/icons/message-hover.png"
        }
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            if (setbtn_flag == "onekey") {
                if(systemdispatcher.get_system_daemon_qt() == "SystemDaemon") {
                    send_dynamic_picture("onekey");
                    systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
                    btnImg.source = "../img/icons/onekeyover.png"  //首页点击后更换图片的位置7-30
                    menulogo.enabled=false;
                }
                else {
                    var value4 = systemdispatcher.setup();
                    if(value4) {
                        send_dynamic_picture("onekey");
                        systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
                        btnImg.source = "../img/icons/onekeyover.png"  //首页点击后更换图片的位置7-30
                        menulogo.enabled=false;
                    }
                    else {
                        sessiondispatcher.send_restartdialog_msg();
                    }
                }
            }
            else if (setbtn_flag == "smallonekey") {
                systemdispatcher.clean_by_second_one_key_qt(systemdispatcher.get_onekey_args2());
                btnImg.source = "../img/icons/clear-over.png"  //首页点击后更换图片的位置7-30
                menulogo.enabled=false;
            }
            else if (setbtn_flag == "set")
                console.log("set clicked....");
            else if (setbtn_flag == "message")
                console.log("message clicked....");
        }

    }
}
