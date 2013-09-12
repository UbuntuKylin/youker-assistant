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
//import SystemType 0.1
import "../common" as Common
import "../bars" as Bars

//Gtk:GtkFontButton

//     http://www.doc88.com/p-313626987748.html
//Qt:QFontDialog
//           http://www.kuqin.com/qtdocument/qfontdialog.html
//QColorDialog
//              http://www.kuqin.com/qtdocument/qcolordialog.html
Rectangle {
    id: titlebarfontpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

//    property int cursor_size: 24
    property SessionDispatcher dis: sessiondispatcher
    property string titlebar_font: "Helvetica"
    property bool titlebar_font_flag: false
    property string actiontitle: "标题栏字体设置"
    property string actiontext: "根据您的喜好设置标题栏字体，通过“使用默认设置”按钮，可以将对应的字体恢复到优客助手启动时的默认字体。"
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        titlebarfontpage.titlebar_font_flag = false;
        titlebarfontpage.titlebar_font = sessiondispatcher.get_window_title_font_qt();
    }


    //信号绑定，绑定qt的信号finishSetFont，该信号emit时触发onFinishSetFont
    Connections
    {
        target: sessiondispatcher
        onFinishSetFont: {
            if (font_style == "titlebarfont") {
                titlebarfontpage.titlebar_font_flag = true;
                titlefont.text = sessiondispatcher.get_window_title_font_qt();
            }
            else if (font_style == "titlebarfont_default") {
                titlebarfontpage.titlebar_font_flag = false;
                titlefont.text = sessiondispatcher.get_window_title_font_qt();
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
                 text: titlebarfontpage.actiontitle
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
             text: titlebarfontpage.actiontext
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
            text: "标题栏字体设置"
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
        id:te
        spacing: 10
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 15
        }
        Common.Label {
            id: windowtitlefontlabel
            width: 110
            text: "当前标题栏字体:"
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            id: titlefont
//                text: sessiondispatcher.get_window_title_font_qt()
            text: titlebarfontpage.titlebar_font
            width: 200
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Row{
        anchors{
            left: te.left
            leftMargin: 470
            top: settitle.bottom
            topMargin: 10
        }
        spacing: 10
        Common.Button {
            id: titlefontBtn
            hoverimage: "blue4.png"
            text: "更换字体"
            width: 124
            height: 30
            onClicked: sessiondispatcher.show_font_dialog("titlebarfont");
        }
        Common.Button {
//                anchors.left: titlefontBtn.right
//                anchors.leftMargin: 10
            hoverimage: "blue2.png"
            text: "使用默认设置"
            width: 124
            height: 30
            onClicked: {
                if(titlebarfontpage.titlebar_font_flag == true) {
                    sessiondispatcher.set_window_title_font_qt_default(titlebarfontpage.titlebar_font);
                    sessiondispatcher.restore_default_font_signal("titlebarfont_default");
                    statusImage.visible = true;
                }
                else
                    sessiondispatcher.send_warningdialog_msg("友情提示：","您系统的窗体标题栏字体已经为默认字体！", mainwindow.pos.x, mainwindow.pos.y);
            }
        }
//        Common.Button {
//            id: titlefontBtn
////            hoverimage: "changefont.png"
//            text:"更换字体"
//            width: 124
//            height: 30
//            onClicked: sessiondispatcher.show_font_dialog("titlebarfont");
//        }
//        Common.Button {
////                anchors.left: titlefontBtn.right
////                anchors.leftMargin: 10
////            hoverimage: "use.png"
//            text:"使用默认设置"
//            color1: "#57bffc"
//            color2: "#2384c8"
//            bordercolor: "#31a0ee"
//            width: 124
//            height: 30
//            onClicked: {
//                if(titlebarfontpage.titlebar_font_flag == true) {
//                    sessiondispatcher.set_window_title_font_qt_default(titlebarfontpage.titlebar_font);
//                    sessiondispatcher.restore_default_font_signal("titlebarfont_default");
//                    statusImage.visible = true;
//                }
//                else
//                    sessiondispatcher.send_warningdialog_msg("友情提示：","您系统的窗体标题栏字体已经为默认字体！");
//            }
//        }
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
