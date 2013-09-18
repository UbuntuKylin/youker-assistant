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
import SessionType 0.1
import "../common" as Common
import "../bars" as Bars
Rectangle {
    id: documentfontpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

//    property int cursor_size: 24
    property SessionDispatcher dis: sessiondispatcher
    property string document_font: "Helvetica"
    property bool document_font_flag: false
    property string actiontitle: "文档字体设置"
    property string actiontext: "根据您的喜好设置文档字体，通过“使用默认设置”按钮，可以将对应的字体恢复到优客助手启动时的默认字体。"
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        documentfontpage.document_font_flag = false;
        documentfontpage.document_font = sessiondispatcher.get_document_font_qt();
    }

    Connections
    {
        target: sessiondispatcher
        onNotifyFontStyleToQML: {
            if (font_style == "documentfont") {
                documentfontpage.document_font_flag = true;
                docufont.text = sessiondispatcher.get_document_font_qt();
            }
            else if (font_style == "documentfont_default") {
                documentfontpage.document_font_flag = false;
                docufont.text = sessiondispatcher.get_document_font_qt();
            }
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
                 text: documentfontpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            //status picture
            Image {
                id: statusImage
                visible: false
                source: "../../img/toolWidget/finish.png"
                fillMode: "PreserveAspectFit"
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             text: documentfontpage.actiontext
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
        spacing: 5
        Text{
            text: "文档字体设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:680
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Row {
        id:re
        spacing: 10
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 15
        }
        Common.Label {
            id: documentfontlabel
            width: 110
            text: "当前文档字体:"
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            id: docufont
//                text: sessiondispatcher.get_document_font_qt()
            text: documentfontpage.document_font
            width: 200
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Row{
        anchors{
            left: re.left
            leftMargin: 490
            top: settitle.bottom
            topMargin: 10
        }
        spacing: 26

        Common.Button {
            id: docufontBtn
            hoverimage: "blue4.png"
            text: "更换字体"
            fontcolor: "#086794"
            width: 105
            height: 30
            onClicked: sessiondispatcher.show_font_dialog("documentfont");
        }
        Common.Button {
            hoverimage: "blue2.png"
            text: "恢复默认"
            width: 105
            height: 30
            onClicked: {
                if(documentfontpage.document_font_flag == true) {
                    sessiondispatcher.set_document_font_qt_default(documentfontpage.document_font);
                    sessiondispatcher.restore_default_font_signal("documentfont_default");
                    statusImage.visible = true;
                }
                else
                    sessiondispatcher.showWarningDialog("友情提示：","您系统的当前文档字体已经为默认字体！", mainwindow.pos.x, mainwindow.pos.y);
            }
        }
        Timer {
                 interval: 5000; running: true; repeat: true
                 onTriggered: statusImage.visible = false
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
        showok: false
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {}
    }
}
