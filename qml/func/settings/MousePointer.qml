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
    width: parent.width
    height: 475

    property int cursor_size: 24
    property int current_index//当前主题的索引
    property int default_index//系统默认主题的索引
    property string actiontitle: qsTr("Mouse Settings")//鼠标设置
    property string actiontext: qsTr("Replace the theme and size of the mouse pointer,  then click the 'OK' button to confirm. Also, theme change need to restart system.")//更换鼠标指针主题和大小，更改设置后点击＂确定＂按钮进行确认。主题更改需要重新系统才能生效。

    ListModel { id: choices }

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        mousepointerpage.cursor_size = sessiondispatcher.get_cursor_size_qt();
        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
        var default_theme = "DMZ-White";//sessiondispatcher.get_default_theme_sring_qt("mousetheme");
        choices.clear();
        if(current_cursor_theme == default_theme) {
            for(var i=0; i < cursorlist.length; i++) {
                choices.append({"text": cursorlist[i]});
                if (cursorlist[i] == current_cursor_theme) {
                    mousepointerpage.current_index = i;
                    mousepointerpage.default_index = i;
                }
            }
        }
        else {
            for(var j=0; j < cursorlist.length; j++) {
                choices.append({"text": cursorlist[j]});
                if (cursorlist[j] == current_cursor_theme) {
                    mousepointerpage.current_index = j;
                }
                else if (cursorlist[j] == default_theme) {
                    mousepointerpage.default_index = j;
                }
            }
        }
        cursorcombo.selectedIndex = mousepointerpage.current_index;
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
            text: mousepointerpage.actiontitle
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Text {
            text: mousepointerpage.actiontext
            font.pixelSize: 12
            color: "#7a7a7a"
        }
    }

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
            spacing: 314
            Row {
                spacing: 20
                Text {
                    id: cursorthemelabel
                    width: 160
                    text: qsTr("Mouse Pointer Theme:")//鼠标指针主题：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: cursorcombo
                    model: choices
                    width: cursorthemelabel.width
                    onSelectedTextChanged: {
                        sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
                        systemdispatcher.set_cursor_theme_with_root_qt(cursorcombo.selectedText);
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Common.Button {
                hoverimage: "blue.png"
                text: qsTr("Restore")//恢复默认
                width: 94
                height: 29
                fontsize: 13
                onClicked: {
                    //Attention:配置文件的系统默认值为：DMZ-White，而通过gsetting方法得到的默认值为：Adwaita
                    //这里我们使用配置自带的系统默认值DMZ-White
                    sessiondispatcher.set_cursor_theme_qt("DMZ-White");
                    systemdispatcher.set_cursor_theme_with_root_qt("DMZ-White");
                    cursorcombo.selectedIndex = mousepointerpage.default_index;
                }
            }
        }

        Row {
            spacing: 314
            Row {
                spacing: 20
                Text {
                    id: trashlabel
                    width: 160
                    text: qsTr("Cursor Pointer Size:")//光标指针大小：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 134
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
                                }
                            }
                        }
                    }
                    Common.CheckBox {
                        id: bigstyle
                        checked: (mousepointerpage.cursor_size == 48) ? true : false
                        titleName: qsTr("Big Size")//48    大号
                        flag: "radio"
                        onClicked: {
                            if(bigstyle.checked == true) {
                                if(mousepointerpage.cursor_size != 48) {
                                    sessiondispatcher.set_cursor_size_qt(48);
                                    mousepointerpage.cursor_size = 48;
                                }
                            }
                        }
                    }
                }
            }
            Common.Button {
                hoverimage: "blue.png"
                text: qsTr("Restore")//恢复默认
                width: 94
                height: 29
                fontsize: 13
                onClicked: {
                    sessiondispatcher.set_default_theme_qt("cursorsize");
                    var default_value = sessiondispatcher.get_cursor_size_qt();
                    if(default_value == 24) {
                        smallstyle.checked = true;
                    }
                    else if(default_type == 48) {
                        bigstyle.checked = true;
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
    }
}
