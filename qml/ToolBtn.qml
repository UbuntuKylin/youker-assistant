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

Rectangle {
    id: menulogo
    width: 114
    height: 40
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string iconName: "homepage.png"
    property string text: "homepage"
    property string showtext

    Image {
        id: seticon
        //如果是中文：img/zh_CN/title/；如果是英文：img/zh_CN/en/
        source: "./img/zh_CN/title/" + iconName
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
            if (text == "homepage") {
                btnImg.source = "./img/zh_CN/title/home-active.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/zh_CN/title/sysinfo-active.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/zh_CN/title/cleanup-active.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/zh_CN/title/feature-active.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/zh_CN/title/toolkits-active.png"
            }
            else {
                btnImg.source = "./img/zh_CN/title/menu_hover.png"
            }
        }
        //鼠标按下时
        onPressed: {
            if (text == "homepage") {
                btnImg.source = "./img/zh_CN/title/home-active.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/zh_CN/title/sysinfo-active.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/zh_CN/title/cleanup-active.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/zh_CN/title/feature-active.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/zh_CN/title/toolkits-active.png"
            }
            else {
                btnImg.source = "./img/zh_CN/title/menu_press.png"
            }
        }
        //要判断松开是鼠标位置
        //鼠标按下松开时
        onReleased: {
            if (text == "homepage") {
                btnImg.source = "./img/zh_CN/title/home.png"
            }
            else if (text == "systemmessage") {
                btnImg.source = "./img/zh_CN/title/sysinfo.png"
            }
            else if (text == "clearrubbish") {
                btnImg.source = "./img/zh_CN/title/cleanup.png"
            }
            else if (text == "systemset") {
                btnImg.source = "./img/zh_CN/title/feature.png"
            }
            else if (text == "functioncollection") {
                btnImg.source = "./img/zh_CN/title/toolkits.png"
            }
            else {
                btnImg.source = "./img/zh_CN/title/menu_hover.png"
            }
        }
        //鼠标按下松开再移开时
        onExited: btnImg.source = ""


        onClicked: {
            //kobe:选中项深色块移动
//            menulogo.GridView.view.currentIndex = index;
            if (text == "homepage") {
                sessiondispatcher.set_page_num(0);
                menulogo.send("homepage");
                pageStack.push(homepage);
            }
            else if (text == "systemmessage") {
                sessiondispatcher.set_page_num(1);
                menulogo.send("systemmessage");
                pageStack.push(systemmessage);
            }
            else if (text == "clearrubbish") {
                sessiondispatcher.set_page_num(2);
                menulogo.send("clearrubbish");
                pageStack.push(clearrubbish);
            }
            else if (text == "systemset") {
                sessiondispatcher.set_page_num(3);
                menulogo.send("systemset");
                pageStack.push(systemset);
            }
            else if (text == "functioncollection") {
                sessiondispatcher.set_page_num(4);
                menulogo.send("functioncollection");
                pageStack.push(functioncollection);
            }
        }
    }

//    Text {
//        id: displaytext
//        color: "white"
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.left: seticon.left
//        anchors.leftMargin: (menulogo.text == "homepage") ? 60: 45
//        font.family: "Arial"
//        font.pixelSize: 14
//        text: menulogo.showtext
//        style: Text.Sunken
//        styleColor: "#AAAAAA"
//    }
}
