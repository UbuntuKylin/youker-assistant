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
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id: widgetthemepage
    width: parent.width
    height: 475
    property string actiontitle: qsTr("Window theme settings")//窗口主题设置
    property string actiontext: qsTr("Choose the theme what you want. The first is the theme of the currently used.")//选择您想设置的主题。第一个主题为系统当前使用的主题。
    property string selected_theme: ""
    property int themeIndex: 0//序号
    property string init_theme: ""

    Component.onCompleted: {
        statusImage.visible = false;
        var syslist = sessiondispatcher.get_themes_qt();
        widgetthemepage.init_theme = sessiondispatcher.get_theme_qt();
        showText.text = qsTr("[ Current Theme is: ") + widgetthemepage.init_theme + " ]";//[ 当前主题是：
        syslist.unshift(widgetthemepage.init_theme);
        themeModel.clear();
        for(var i=0; i < syslist.length; i++) {
            themeModel.append({"icon": "../../img/skin/" + syslist[i] + ".png", "name": syslist[i]});
            if (i!=0 && syslist[i] == widgetthemepage.init_theme)
                themeModel.remove(i);
        }
        //将系统初始的标题栏字体写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("theme", "widgettheme", widgetthemepage.init_theme);
    }

    ListModel { id: themeModel }

    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    Component {
        id: themegridDelegate
        Item {
            id: griditem
            width: 120; height: 120

            Column {
                 anchors.fill: parent
                 spacing: 10
                 Image {
                    id: seticon
                    source: icon
                    width: 120
                    height: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: btnText
                    height: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: name
                    font.bold: true
                    font.pixelSize: 12
                    color: "#383838"
                }
            }
            Image {
                id: btnImg
                anchors.fill: parent
                source: ""
            }
            MouseArea {
                id: signaltest
                hoverEnabled: true
                anchors.fill: parent
                onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
                onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
                //要判断松开是鼠标位置
                onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
                onExited: btnImg.source = ""
                onClicked: {
//                    griditem.GridView.view.currentIndex = index;
//                    console.log(index);
//                    widgetthemepage.themeIndex = index;
                    widgetthemepage.selected_theme = name;
                    sessiondispatcher.set_theme_qt(name);
                    statusImage.visible = true;
                    showText.text = qsTr("[ Current Theme is: ") + name + " ]";//[ 当前主题是：
                }
            }
        }
    }

    Column {
        id: titlecolumn
        anchors {
            top: parent.top
            topMargin: 44
            left: parent.left
            leftMargin: 80
        }
        Row {
            spacing: 50
            Text {
                text: widgetthemepage.actiontitle
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: showText
                text: ""
                font.pixelSize: 14
                color: "#318d11"
            }
            //status picture
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
         }
        Text {
            text: widgetthemepage.actiontext
            font.pixelSize: 12
            color: "#7a7a7a"
        }
    }
    Item {
        width: parent.width - 60*2
        anchors {
            top: parent.top
            topMargin: 100
            left: parent.left
            leftMargin: 60
        }
        GridView {
            id: themegrid
            anchors.fill: parent
            cellWidth: 156; cellHeight: 156
            model: themeModel
            delegate: themegridDelegate
            focus: true
            cacheBuffer: 1000
//            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
        }
    }
    //顶层工具栏
    Bars.TopBar {
        id: topBar
        width: 28
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        opacity: 0.9
        onButtonClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0) {
                pageStack.push(homepage);
            }
            else if (num == 3) {
                pageStack.push(systemset);
            }
            else if (num == 4) {
                pageStack.push(functioncollection);
            }
        }
    }

    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        showok: false
        showrestore: true
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0) {
                pageStack.push(homepage);
            }
            else if (num == 3) {
                pageStack.push(systemset);
            }
            else if (num == 4) {
                pageStack.push(functioncollection);
            }
        }
        onRestoreBtnClicked: {
            var defaulttheme = sessiondispatcher.read_default_configure_from_qsetting_file("theme", "widgettheme");
            if(defaulttheme == widgetthemepage.selected_theme || widgetthemepage.selected_theme == "") {
            //友情提示：        您系统的当前窗口主题已经为默认主题！
            sessiondispatcher.showWarningDialog(qsTr("Tips: "), qsTr("Your system's current widget theme is the default theme!"), mainwindow.pos.x, mainwindow.pos.y);//友情提示：//您系统的当前窗口主题已经为默认主题！
            }
            else {
                sessiondispatcher.set_theme_qt(defaulttheme);
                statusImage.visible = true;
                showText.text = qsTr("[ Current Theme is: ") + defaulttheme + " ]";//[ 当前主题是：
                widgetthemepage.selected_theme = defaulttheme;
            }
        }
        Timer {
            interval: 5000; running: true; repeat: true
            onTriggered: statusImage.visible = false
        }
    }
}
