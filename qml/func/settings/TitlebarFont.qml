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
    id: titlebarfontpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property string titlebar_font: "Helvetica"
//    property string selected_font: ""//存放用户选择确认后的字体
    property string actiontitle: qsTr("Titlebar font settings")//标题栏字体设置
    property string actiontext: qsTr("According to personal preferences to set titlebar fonts, click the 'Restore' button, can be restored to the state before the font settings.")//根据个人喜好设置标题栏字体，单击＂恢复默认＂按钮，可以将对应的字体恢复到设置前状态。
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        titlebarfontpage.titlebar_font = sessiondispatcher.get_window_title_font_qt();
//        titlebarfontpage.selected_font = titlebarfontpage.titlebar_font;
        //将系统初始的标题栏字体写入QSetting配置文件
//        sessiondispatcher.write_default_configure_to_qsetting_file("font", "titlebarfont", titlebarfontpage.titlebar_font);
    }

    Connections
    {
        target: sessiondispatcher
        onNotifyFontStyleToQML: {
            if (font_style == "titlebarfont") {//弹出字体对话框更改好字体后
                titlefont.text = sessiondispatcher.get_window_title_font_qt();
//                titlebarfontpage.selected_font = titlefont.text;
            }
//            else if (font_style == "titlebarfont_default") {//恢复默认时
//                titlefont.text = sessiondispatcher.get_window_title_font_qt();
//                titlebarfontpage.selected_font = titlefont.text;
//            }
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
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            width: titlebarfontpage.width - 80 - 20
            text: titlebarfontpage.actiontext
            wrapMode: Text.WordWrap
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
            id: fonttitle
            text: qsTr("Titlebar font settings")//标题栏字体设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Rectangle{
            width: titlebarfontpage.width - fonttitle.width - 40 * 2
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
            text: qsTr("Titlebar font: ")//标题栏字体：
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            id: titlefont
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
            leftMargin: 490
            top: settitle.bottom
            topMargin: 10
        }
        spacing: 26
        Common.Button {
            id: titlefontBtn
            hoverimage: "blue4.png"
            text: qsTr("Change fonts")//更换字体
            fontcolor: "#086794"
            width: 105
            height: 30
            onClicked: sessiondispatcher.show_font_dialog("titlebarfont");
        }
        Common.Button {
            hoverimage: "blue2.png"
            text: qsTr("Restore")//恢复默认
            width: 105
            height: 30
            onClicked: {
                //20140219
                sessiondispatcher.set_default_theme_qt("titlebarfont");
                titlefont.text = sessiondispatcher.get_window_title_font_qt();
//                sessiondispatcher.set_default_theme_qt("org.gnome.desktop.wm.preferences", "titlebar-font", "string");
//                var defaultfont = sessiondispatcher.read_default_configure_from_qsetting_file("font", "titlebarfont");
//                if(defaultfont == titlebarfontpage.selected_font) {
//                    //友情提示：        您系统的窗体标题栏字体已经为默认字体！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips: "), qsTr("Your system's titlebar font is the default font!"), mainwindow.pos.x, mainwindow.pos.y);//您系统的标题栏字体已经为默认字体！
//                }
//                else {
//                    sessiondispatcher.set_window_title_font_qt_default(defaultfont);
//                    titlebarfontpage.selected_font = defaultfont;
//                    sessiondispatcher.restore_default_font_signal("titlebarfont_default");
//                    statusImage.visible = true;
//                }
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
        onOkBtnClicked: {}
    }
}
