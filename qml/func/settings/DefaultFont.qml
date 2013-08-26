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
    id: defaultfontpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

    property SessionDispatcher dis: sessiondispatcher
    property string current_font: "Helvetica"
    property string desktop_font: "Helvetica"
    property string monospace_font: "Helvetica"
    property double zoom: 1.0
    property bool current_font_flag: false
    property bool desktop_font_flag: false
    property bool monospace_font_flag: false
    property bool zoom_flag: false
    property string actiontitle: "默认字体设置"
    property string actiontext: "根据您的喜好设置系统默认字体，通过“使用默认设置”按钮，可以将对应的字体恢复到优客助手启动时的默认字体。"
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        defaultfontpage.current_font_flag = false;
        defaultfontpage.desktop_font_flag = false;
        defaultfontpage.monospace_font_flag = false;
        defaultfontpage.zoom_flag = false;

        defaultfontpage.current_font = sessiondispatcher.get_font_qt();
        defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        defaultfontpage.monospace_font = sessiondispatcher.get_monospace_font_qt();
        defaultfontpage.zoom = sessiondispatcher.get_font_zoom_qt();

        if (sessiondispatcher.get_desktop_font_qt() == "") {
            sessiondispatcher.set_desktop_font_qt_default();
            defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        }
    }

    //信号绑定，绑定qt的信号finishSetFont，该信号emit时触发onFinishSetFont
    Connections
    {
        target: sessiondispatcher
        onFinishSetFont: {
            if (font_style == "font") {
                defaultfontpage.current_font_flag = true;
                sysfont.text = sessiondispatcher.get_font_qt();
            }
            else if (font_style == "desktopfont") {
                defaultfontpage.desktop_font_flag = true;
                desktopfont.text = sessiondispatcher.get_desktop_font_qt();
            }
            else if (font_style == "monospacefont") {
                defaultfontpage.monospace_font_flag = true;
                monofont.text = sessiondispatcher.get_monospace_font_qt();
            }

            else if (font_style == "font_default") {
                defaultfontpage.current_font_flag = false;
                sysfont.text = sessiondispatcher.get_font_qt();
            }
            else if (font_style == "desktopfont_default") {
                defaultfontpage.desktop_font_flag = false;
                desktopfont.text = sessiondispatcher.get_desktop_font_qt()
            }
            else if (font_style == "monospacefont_default") {
                defaultfontpage.monospace_font_flag = false;
                monofont.text = sessiondispatcher.get_monospace_font_qt();
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
                 text: defaultfontpage.actiontitle
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
             text: defaultfontpage.actiontext
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
            text: "字体设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:700
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Column {
        id: fontcolumn
        spacing: 20
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10
        }

        Row {
            spacing: 130
            Row{
                spacing: 10
                Common.Label {
                    id: fontslabel
                    width: 130
                    text: "当前字体:"
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: sysfont
                    text: sessiondispatcher.get_font_qt()
        //                text: defaultfontpage.current_font
                    width: 200
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row{
                spacing: 10
                Common.Button {
                    id: fontBtn
                    hoverimage: "changefont.png"
                    width: 124
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("font");
                }
                Common.Button {
                    hoverimage: "use.png"
                    width: 124
                    height: 30
                    onClicked: {
                        if(defaultfontpage.current_font_flag == true) {
    //                        defaultfontpage.current_font_flag = false;
                            sessiondispatcher.set_font_qt_default(defaultfontpage.current_font);
                            sessiondispatcher.restore_default_font_signal("font_default");
                            statusImage.visible = true;
                        }
                        else
                            sessiondispatcher.send_warningdialog_msg("友情提示：", "您系统的当前字体已经为默认字体！");
                    }
                }
            }
        }

        Row {
            spacing: 130
            Row{
                spacing: 10
                Common.Label {
                    id: desktopfontlabel
                    width: 130
                    text: "当前桌面字体:"
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: desktopfont
                    text: sessiondispatcher.get_desktop_font_qt()
                    width: 200
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row{
                spacing: 10
                Common.Button {
                    id: desktopfontBtn
                    hoverimage: "changefont.png"
                    width: 124
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("desktopfont");
                }
                Common.Button {
                    hoverimage: "use.png"
                    width: 124
                    height: 30
                    onClicked: {
                        if(defaultfontpage.desktop_font_flag == true) {
    //                        defaultfontpage.desktop_font_flag = false;
                            sessiondispatcher.set_desktop_font_qt_default(defaultfontpage.desktop_font);
                            sessiondispatcher.restore_default_font_signal("desktopfont_default");
                            statusImage.visible = true;
                        }
                        else
                            sessiondispatcher.send_warningdialog_msg("友情提示：","您系统的当前桌面字体已经为默认字体！");
                    }
                }
            }
        }

        Row {
            spacing: 130
            Row{
                spacing: 10
                Common.Label {
                    id: monospacefontlabel
                    width: 130
                    text: "当前等宽字体:"  //monospace
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: monofont
                    text: sessiondispatcher.get_monospace_font_qt()
    //                text: defaultfontpage.monospace_font
                    width: 200
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row{
                spacing: 10
                Common.Button {
                    id: monofontBtn
                    hoverimage: "changefont.png"
                    width: 124
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("monospacefont");
                }
                Common.Button {
                    hoverimage: "use.png"
                    width: 124
                    height: 30
                    onClicked: {
                        if(defaultfontpage.monospace_font_flag == true) {
    //                        defaultfontpage.monospace_font_flag = false;
                            sessiondispatcher.set_monospace_font_qt_default(defaultfontpage.monospace_font);
                            sessiondispatcher.restore_default_font_signal("monospacefont_default");
                            statusImage.visible = true;
                        }
                        else
                            sessiondispatcher.send_warningdialog_msg("友情提示：","您系统的当前等宽字体已经为默认字体！");
                    }
                }
            }
        }

    }//Column





    Row {
        id: zoomtitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: fontcolumn.bottom
            topMargin: 30
        }
        spacing: 5
        Text{
            text: "缩放设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:700
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Row {
        anchors{
            left: parent.left
            leftMargin: 60
            top: zoomtitle.bottom
            topMargin: 10
        }
        spacing: 185
        Row{
            Common.Label {
                id: fontzoomlabel
                width: 130
                text: "全局字体缩放:"
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Slider {
                id: slider
                minimumValue: 0.1
                maximumValue: 2
                width: 150
                value: sessiondispatcher.get_font_zoom_qt()
                stepSize: 0.1
                animated: true
            }
            Text {
                id: displaynum
                text: slider.value
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row{
            spacing: 38
            Common.Button {
                id: okBtn
                width: 95;height: 30
                hoverimage: "ok.png"
                onClicked: {
                    sessiondispatcher.set_font_zoom_qt(slider.value);
                    statusImage.visible = true;
                    if (defaultfontpage.zoom != sessiondispatcher.get_font_zoom_qt())
                        defaultfontpage.zoom_flag = true
                }
            }
            Common.Button {
                hoverimage: "use.png"
                width: 124
                height: 30
                onClicked: {
                    if(defaultfontpage.zoom_flag == true) {
                        defaultfontpage.zoom_flag = false;
                        sessiondispatcher.set_font_zoom_qt(defaultfontpage.zoom);
                        slider.value = defaultfontpage.zoom;
                        statusImage.visible = true;
                    }
                    else
                        sessiondispatcher.send_warningdialog_msg("友情提示：", "您系统的全局字体缩放已经为默认设置！");
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
    Timer {
             interval: 5000; running: true; repeat: true
             onTriggered: statusImage.visible = false
         }

}
