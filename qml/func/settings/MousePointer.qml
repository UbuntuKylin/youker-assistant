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
    id: mousepointerpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property int cursor_size: 24
    property string default_cursor_theme: ""

    property string actiontitle: qsTr("Mouse settings")//鼠标设置
    property string actiontext: qsTr("Replace the mouse pointer theme and size, click 'OK' button to confirm.")//更换鼠标指针主题和大小，更改设置后点击“确定”按钮进行确认。
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        mousepointerpage.cursor_size = sessiondispatcher.get_cursor_size_qt();
        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
        mousepointerpage.default_cursor_theme = current_cursor_theme;
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


    ListModel {
        id: choices
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
        Rectangle{
            width: mousepointerpage.width - mousetitle.width - 40 * 2
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
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
                text: qsTr("Mouse pointer theme")//鼠标指针主题
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
        }

        Row {
            spacing: 20
            Text {
                id: trashlabel
                text: qsTr("Mouse pointer size")//鼠标指针大小
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.ButtonRow {
                exclusive: true//控制是否联动
                spacing: 60
                Common.CheckBox {
                    id: smallstyle
                    checked: (mousepointerpage.cursor_size == "24") ? true : false
//                    checked: (sessiondispatcher.get_cursor_size_qt() == "24") ? true : false
                    titleName: qsTr("Small size")//24   小号
                    flag: "radio"
                    onClicked: {}
                }
                Common.CheckBox {
                    id: bigstyle
                    checked: (mousepointerpage.cursor_size == "36") ? true : false
//                    checked: (sessiondispatcher.get_cursor_size_qt() == "36") ? true : false
                    titleName: qsTr("Big size")//36     大号
                    flag: "radio"
                    onClicked: {}
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
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("返回")
//            button2Label: qsTr("确定")
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {
            if (mousepointerpage.default_cursor_theme != cursorcombo.selectedText) {
                mousepointerpage.default_cursor_theme = cursorcombo.selectedText;
                sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
            }

            if(smallstyle.checked == true)
                sessiondispatcher.set_cursor_size_qt(24);
            else if(bigstyle.checked == true)
                sessiondispatcher.set_cursor_size_qt(36);
            statusImage.visible = true;
        }
        Timer {
                 interval: 5000; running: true; repeat: true
                 onTriggered: statusImage.visible = false
             }
    }
}
