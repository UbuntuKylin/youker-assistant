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
    id: menulogo
    width: 114
    height: 40
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string iconName: "homepage.png"
    property string text: "homepage"
    property string showtext
    property string path: "./img/en/title/"

    Component.onCompleted: {
        if(sessiondispatcher.get_locale_version() == "zh_CN") {
            menulogo.path = "./img/zh_CN/title/";
        }
        else {
            menulogo.path = "./img/en/title/";
        }
    }

    Image {
        id: seticon
        source: menulogo.path + iconName
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    signal send(string a);
    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        //鼠标放上时
        onEntered: {
            btnImg.source = "./img/toolWidget/hover-enter.png";
        }
        //鼠标按下时
        onPressed: {
            btnImg.source = "./img/toolWidget/hover-press.png"
        }
        //要判断松开是鼠标位置
        //鼠标按下松开时
        onReleased: {
            btnImg.source = "./img/toolWidget/hover-enter.png";
        }
        //鼠标按下松开再移开时
        onExited: btnImg.source = ""


        onClicked: {
            //kobe:选中项深色块移动
//            menulogo.GridView.view.currentIndex = index;
            if (text == "homepage") {
                menulogo.send("homepage");
                cpp.navigate(0);
            }
            else if (text == "systemmessage") {
                menulogo.send("systemmessage");
                cpp.navigate(1);
            }
            else if (text == "clearrubbish") {
                menulogo.send("clearrubbish");
                cpp.navigate(2);
            }
            else if (text == "systemset") {
                menulogo.send("systemset");
                cpp.navigate(3);
            }
            else if (text == "functioncollection") {
                menulogo.send("functioncollection");
                cpp.navigate(4);
            }
        }
    }
}
