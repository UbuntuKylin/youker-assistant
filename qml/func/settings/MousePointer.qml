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

Rectangle {
    id: mousepointerpage
    width: parent.width
    height: 476

    property int cursor_size: 24
    property int default_index//系统默认主题的索引
    property string actiontitle: qsTr("Mouse Settings")//鼠标设置
    property string actiontext: qsTr("Replace the theme and size of the mouse pointer,  then click the 'OK' button to confirm. Also, theme change need to restart system.")//更换鼠标指针主题和大小，更改设置后点击＂确定＂按钮进行确认。主题更改需要重新系统才能生效。

    ListModel { id: choices }

    Component.onCompleted: {
        mousepointerpage.cursor_size = sessiondispatcher.get_cursor_size_qt();

        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
        var default_theme = sessiondispatcher.get_uk_default_setting_string("mouse", "cursor-theme");
        var new_list = new Array();
        for(var j=0; j < cursorlist.length; j++) {
            if(cursorlist[j] !== current_cursor_theme) {
                new_list.push(cursorlist[j]);
            }
        }
        new_list.unshift(current_cursor_theme);
        choices.clear();
        for(var k=0; k < new_list.length; k++) {
            choices.append({"text": new_list[k]});
            if (default_theme === new_list[k]) {
                mousepointerpage.default_index = k;
            }
        }
    }

    Row {
        spacing: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 20
        }
        Common.Button {
            id: backBtn
            anchors.verticalCenter: parent.verticalCenter
            picNormal: "../../img/icons/button12-gray.png"
            picHover: "../../img/icons/button12-gray-hover.png"
            picPressed: "../../img/icons/button12-gray-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 70; height: 28
            text: qsTr("Back")//返回
            onClicked: {
                pageStack.pop();
            }
        }
        Column {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
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
    }

    //分割条
    Common.Separator {
        id: top_splitbar
        y: 70
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
    }


    Column {
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 40
        }
        spacing: 20
        Row {
            spacing: 200
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
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
                anchors.verticalCenter: parent.verticalCenter
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    //Attention:配置文件的系统默认值为：DMZ-White，而通过gsetting方法得到的默认值为：Adwaita
                    //这里我们使用配置自带的系统默认值DMZ-White
                    var default_theme= sessiondispatcher.get_uk_default_setting_string("mouse", "cursor-theme");
                    if(cursorcombo.selectedText !== default_theme) {
                        sessiondispatcher.set_cursor_theme_qt(default_theme);
                        systemdispatcher.set_cursor_theme_with_root_qt(default_theme);
                        cursorcombo.selectedIndex = mousepointerpage.default_index;
                    }
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
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
                anchors.verticalCenter: parent.verticalCenter
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var cur_value;
                    if (smallstyle.checked) {
                        cur_value = 24;
                    }
                    else {
                        cur_value = 48;
                    }
                    if (sessiondispatcher.get_uk_default_setting_int("mouse", "cursor-size") !== cur_value) {
                        sessiondispatcher.restore_uk_default_setting("mouse", "cursor-size");
                        var default_value = sessiondispatcher.get_cursor_size_qt();
                        if(default_value === 24) {
                            smallstyle.checked = true;
                        }
                        else if(default_type === 48) {
                            bigstyle.checked = true;
                        }
                    }
                }
            }
        }
    }
}
