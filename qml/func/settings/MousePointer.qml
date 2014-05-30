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
//        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
//        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
//        var default_theme = "DMZ-White";//sessiondispatcher.get_default_theme_sring_qt("mousetheme");
//        choices.clear();
//        if(current_cursor_theme == default_theme) {
//            for(var i=0; i < cursorlist.length; i++) {
//                choices.append({"text": cursorlist[i]});
//                if (cursorlist[i] == current_cursor_theme) {
//                    mousepointerpage.current_index = i;
//                    mousepointerpage.default_index = i;
//                }
//            }
//        }
//        else {
//            for(var j=0; j < cursorlist.length; j++) {
//                choices.append({"text": cursorlist[j]});
//                if (cursorlist[j] == current_cursor_theme) {
//                    mousepointerpage.current_index = j;
//                }
//                else if (cursorlist[j] == default_theme) {
//                    mousepointerpage.default_index = j;
//                }
//            }
//        }
//        cursorcombo.selectedIndex = mousepointerpage.current_index;




        var index = 0;
        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
        var default_theme = "DMZ-White";//sessiondispatcher.get_default_theme_sring_qt("mousetheme");
        for(var i=0; i < cursorlist.length; i++) {
            if (current_cursor_theme == cursorlist[i]) {
                index = i;
                mousepointerpage.current_index = i;
            }
            if (default_theme == cursorlist[i]) {
                mousepointerpage.default_index = i;
            }
        }
        choices.clear();
        if (index == 0) {
            for(var j=0; j < cursorlist.length; j++) {
                choices.append({"text": cursorlist[j]});
            }
        }
        else {
            cursorlist.unshift(current_cursor_theme);
            for(var k=0; k < cursorlist.length; k++) {
                choices.append({"text": cursorlist[k]});
                if (k!=0 && cursorlist[k] == current_cursor_theme){
                    choices.remove(k);
                }
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
//            hoverimage: "button12-gray.png"
            picNormal: "../../img/icons/button12-gray.png"
            picHover: "../../img/icons/button12-gray-hover.png"
            picPressed: "../../img/icons/button12-gray-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 70; height: 28
            text: qsTr("Back")//返回
            onClicked: {
                var num = sessiondispatcher.get_page_num();
                if (num == 0) {
                    pageStack.push(homepage);
                }
                else if (num == 1) {
                    pageStack.push(systemmessage);
                }
                else if (num == 2) {
                    pageStack.push(clearrubbish);
                }
                else if (num == 3) {
                    pageStack.push(systemset);
                }
                else if (num == 4) {
                    pageStack.push(functioncollection);
                }
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
        y: 60
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
            topMargin: 50
        }
        spacing: 20
        z: 11
        Row {
            spacing: 200
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
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
            spacing: 200
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
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
}
