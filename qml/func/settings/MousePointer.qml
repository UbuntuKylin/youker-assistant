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
import "../common" as Common
import "../bars" as Bars
Rectangle {
    id: mousepointerpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property int cursor_size: 24
    property string selected_cursor_theme: ""//存放用户选择确认后的主题

    property string actiontitle: qsTr("Mouse Settings")//鼠标设置
    property string actiontext: qsTr("Replace the theme and size of the mouse pointer,  then click the 'OK' button to confirm. Also, theme change need to restart system.")//更换鼠标指针主题和大小，更改设置后点击＂确定＂按钮进行确认。主题更改需要重新系统才能生效。
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        mousepointerpage.cursor_size = sessiondispatcher.get_cursor_size_qt();
        sessiondispatcher.write_default_configure_to_qsetting_file("theme", "cursorsize", mousepointerpage.cursor_size);
        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
        //将系统初始的图标主题写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("theme", "cursortheme", current_cursor_theme);
        showText.text = qsTr("[ Current Cursor Theme: ") + current_cursor_theme + " ]";//[ 当前光标主题是：
        mousepointerpage.selected_cursor_theme = current_cursor_theme;
        cursorlist.unshift(current_cursor_theme);
        choices.clear();
        for(var k=0; k < cursorlist.length; k++) {
            choices.append({"text": cursorlist[k]});
            if (k!=0 && cursorlist[k] == current_cursor_theme)
                choices.remove(k);
        }

    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row {
            spacing: 50
            Text {
                 text: mousepointerpage.actiontitle
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
             text: mousepointerpage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    ListModel { id: choices }

    Row {
        id: settitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120

        }
        Text{
            id: mousetitle
            text: qsTr("Mouse settings")//鼠标设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: mousepointerpage.width - mousetitle.width - 40 * 2
        }
    }

    Column {
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10
        }
        spacing: 20
        Row {
            spacing: 20
            Text {
                id: cursorthemelabel
                text: qsTr("Mouse Pointer Theme")//鼠标指针主题
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.ComboBox {
                id: cursorcombo
                model: choices
                width: 150
    //            width: cursorthemelabel.width
                onSelectedTextChanged: {/*console.log(selectedText)*/}
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Button {
                id: okBtn
                width: 105;height: 30
                hoverimage: "green2.png"
                text: qsTr("OK")//确定
                onClicked: {
                    if (mousepointerpage.selected_cursor_theme != cursorcombo.selectedText) {
                        mousepointerpage.selected_cursor_theme = cursorcombo.selectedText;
                        sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
                        systemdispatcher.set_cursor_theme_with_root_qt(cursorcombo.selectedText);
                        showText.text = qsTr("[ Current Cursor Theme: ") + cursorcombo.selectedText + " ]";//[ 当前光标主题是：
                        statusImage.visible = true;
                    }
                }
            }
        }

        Row {
            spacing: 20
            Text {
                id: trashlabel
                text: qsTr("Cursor Pointer Size")//光标指针大小
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.ButtonRow {
                exclusive: true//控制是否联动
                spacing: 60
                Common.CheckBox {
                    id: smallstyle
                    checked: (mousepointerpage.cursor_size == 24) ? true : false
                    titleName: qsTr("Small Size")//24   小号
                    flag: "radio"
                    onClicked: {
                        if(smallstyle.checked == true) {
                            if(mousepointerpage.cursor_size != 24) {
                                sessiondispatcher.set_cursor_size_qt(24);
                                mousepointerpage.cursor_size = 24;
                                statusImage.visible = true;
                            }
                        }
                    }
                }
                Common.CheckBox {
                    id: bigstyle
                    checked: (mousepointerpage.cursor_size == 36) ? true : false
                    titleName: qsTr("Big Size")//36     大号
                    flag: "radio"
                    onClicked: {
                        if(bigstyle.checked == true) {
                            if(mousepointerpage.cursor_size != 36) {
                                sessiondispatcher.set_cursor_size_qt(36);
                                mousepointerpage.cursor_size = 36;
                                statusImage.visible = true;
                            }
                        }
                    }
                }
            }
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
            //20140219
//            sessiondispatcher.set_default_theme_qt("mousetheme");
//            var defaulttheme = sessiondispatcher.get_cursor_theme_qt();
//            systemdispatcher.set_cursor_theme_with_root_qt(defaulttheme);
//            showText.text = qsTr("[ Current Cursor Theme: ") + defaulttheme + " ]";//[ 当前光标主题是：
//            statusImage.visible = true;
            var defaulttheme = sessiondispatcher.read_default_configure_from_qsetting_file("theme", "cursortheme");
            var defaultsize = sessiondispatcher.read_default_configure_from_qsetting_file("theme", "cursorsize");

            if((defaulttheme == mousepointerpage.selected_cursor_theme) && (defaultsize == mousepointerpage.cursor_size)) {
                sessiondispatcher.showWarningDialog(qsTr("Tips: "), qsTr("Cursor configure is the default configuration!"), mainwindow.pos.x, mainwindow.pos.y);//友情提示：//光标配置已经为默认设置！
            }
            else {
                if(defaulttheme != mousepointerpage.selected_cursor_theme) {
                    sessiondispatcher.set_cursor_theme_qt(defaulttheme);
                    systemdispatcher.set_cursor_theme_with_root_qt(defaulttheme);
                    mousepointerpage.selected_cursor_theme = defaulttheme;
                    showText.text = qsTr("[ Current Cursor Theme: ") + defaulttheme + " ]";//[ 当前光标主题是：
                    cursorcombo.selectedIndex = 0;
                }
                if(defaultsize != mousepointerpage.cursor_size) {
                    sessiondispatcher.set_cursor_size_qt(defaultsize);
                    mousepointerpage.cursor_size = defaultsize;
                    if(defaultsize == 24) {
                        smallstyle.checked = true;
                    }
                    else if(defaultsize == 36) {
                        bigstyle.checked = true;
                    }
                }
                statusImage.visible = true;
            }
        }
        Timer {
             interval: 5000; running: true; repeat: true
             onTriggered: statusImage.visible = false
        }
    }
}
