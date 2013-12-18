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
    id: defaultfontpage
    property bool on: true
    width: parent.width
    height: 475

    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

    property string current_font: "Helvetica"
    property string desktop_font: "Helvetica"
    property string monospace_font: "Helvetica"
    property double zoom: 1.0

    property string selected_current_font: ""//存放用户选择确认后的当前字体
    property string selected_desktop_font: ""//存放用户选择确认后的桌面字体
    property string selected_monospace_font: ""//存放用户选择确认后的等宽字体
    property double selected_zoom //存放用户选择确认后的缩放值

    property string actiontitle: qsTr("Default font settings")//默认字体设置
    property string actiontext: qsTr("According to personal preferences to set the system default font, click the 'restore default' button, can be restored to the state before the font settings.")//根据个人喜好设置系统默认字体，单击“恢复默认”按钮，可以将对应的字体恢复到设置前状态。
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        defaultfontpage.current_font = sessiondispatcher.get_font_qt();
        defaultfontpage.selected_current_font = defaultfontpage.current_font;
        //将系统初始的当前字体写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("font", "currentfont", defaultfontpage.current_font);

        defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        if (defaultfontpage.desktop_font == "") {
            sessiondispatcher.set_desktop_font_qt_default();
            defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        }
        defaultfontpage.selected_desktop_font = defaultfontpage.desktop_font;
        //将系统初始的当前桌面字体写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("font", "desktopfont", defaultfontpage.desktop_font);

        defaultfontpage.monospace_font = sessiondispatcher.get_monospace_font_qt();
        defaultfontpage.selected_monospace_font = defaultfontpage.monospace_font;
        //将系统初始的当前等宽字体写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("font", "monospacefont", defaultfontpage.monospace_font);

        defaultfontpage.zoom = sessiondispatcher.get_font_zoom_qt();
        defaultfontpage.selected_zoom = defaultfontpage.zoom;
        //将系统初始的全局字体缩放写入QSetting配置文件
        sessiondispatcher.write_default_configure_to_qsetting_file("font", "zoom", defaultfontpage.zoom);
    }

    Connections
    {
        target: sessiondispatcher
        onNotifyFontStyleToQML: {
            if (font_style == "font") {
                sysfont.text = sessiondispatcher.get_font_qt();
                defaultfontpage.selected_current_font = sysfont.text;
            }
            else if (font_style == "desktopfont") {
                desktopfont.text = sessiondispatcher.get_desktop_font_qt();
                defaultfontpage.selected_desktop_font = desktopfont.text;
            }
            else if (font_style == "monospacefont") {
                monofont.text = sessiondispatcher.get_monospace_font_qt();
                defaultfontpage.selected_monospace_font = monofont.text;
            }

            else if (font_style == "font_default") {
                sysfont.text = sessiondispatcher.get_font_qt();
                defaultfontpage.selected_current_font = sysfont.text;
            }
            else if (font_style == "desktopfont_default") {
                desktopfont.text = sessiondispatcher.get_desktop_font_qt();
                defaultfontpage.selected_desktop_font = desktopfont.text;
            }
            else if (font_style == "monospacefont_default") {
                monofont.text = sessiondispatcher.get_monospace_font_qt();
                defaultfontpage.selected_monospace_font = monofont.text;
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
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             width: defaultfontpage.width - 80 - 20
             text: defaultfontpage.actiontext
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
        Text{
            id: fonttitle
            text: qsTr("Font Settings")//字体设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Rectangle{
            width: defaultfontpage.width - fonttitle.width - 40 * 2
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
            leftMargin: 80
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
                    text: qsTr("Default Font:")//默认字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: sysfont
                    text: sessiondispatcher.get_font_qt()
                    width: 200
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row{
                spacing: 26

                Common.Button {
                    id: fontBtn
                    hoverimage: "blue4.png"
                    fontcolor: "#086794"
                    text: qsTr("Change Font")//更换字体
                    width: 105
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("font");
                }
                Common.Button {
                    hoverimage: "blue2.png"
                    text: qsTr("Reset Font")//恢复默认
                    width: 105
                    height: 30
                    onClicked: {
                        var defaultfont = sessiondispatcher.read_default_configure_from_qsetting_file("font", "currentfont");
                        if(defaultfont == defaultfontpage.selected_current_font) {
                            //友情提示：    已经恢复为默认字体！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Has been restored to the default font!"), mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else {
                            sessiondispatcher.set_font_qt_default(defaultfont);
                            defaultfontpage.selected_current_font = defaultfont;
                            sessiondispatcher.restore_default_font_signal("font_default");
                            statusImage.visible = true;
                        }
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
                    text: qsTr("Desktop Font:")//桌面字体:
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
                spacing: 26

                Common.Button {
                    id: desktopfontBtn
                    hoverimage: "blue4.png"
                    text: qsTr("Change Font")//更换字体
                    fontcolor: "#086794"
                    width: 105
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("desktopfont");
                }
                Common.Button {
                    hoverimage: "blue2.png"
                    text: qsTr("Reset Font")//恢复默认
                    width: 105
                    height: 30
                    onClicked: {
                        var defaultfont = sessiondispatcher.read_default_configure_from_qsetting_file("font", "desktopfont");
                        if(defaultfont == defaultfontpage.selected_desktop_font) {
                            //友情提示： 您系统的桌面字体已经恢复为默认字体！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Your system's desktop font is the default font!"), mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else {
                            sessiondispatcher.set_desktop_font_qt_default(defaultfont);
                            defaultfontpage.selected_desktop_font = defaultfont;
                            sessiondispatcher.restore_default_font_signal("desktopfont_default");
                            statusImage.visible = true;
                        }
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
                    text: qsTr("Monospace Font:")  //等宽字体:
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
                spacing: 26
                Common.Button {
                    id: monofontBtn
                    hoverimage: "blue4.png"
                    text: qsTr("Change Font")//更换字体
                    fontcolor: "#086794"
                    width: 105
                    height: 30
                    onClicked: sessiondispatcher.show_font_dialog("monospacefont");
                }
                Common.Button {
                    hoverimage: "blue2.png"
                    text: qsTr("Reset Font")//恢复默认
                    width: 105
                    height: 30
                    onClicked: {
                        var defaultfont = sessiondispatcher.read_default_configure_from_qsetting_file("font", "monospacefont");
                        if(defaultfont == defaultfontpage.selected_monospace_font) {
                            //友情提示： 您系统的等宽字体已经恢复为默认字体！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Your system's monospace font is the default font!"), mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else {
                            sessiondispatcher.set_monospace_font_qt_default(defaultfont);
                            defaultfontpage.selected_monospace_font = defaultfont;
                            sessiondispatcher.restore_default_font_signal("monospacefont_default");
                            statusImage.visible = true;
                        }
                    }
                }
            }
        }

    }//Column

    Row {
        id: zoomrow
        anchors{
            left: parent.left
            leftMargin: 40
            top: fontcolumn.bottom
            topMargin: 30
        }
        Text{
            id: zoomtitle
            text: qsTr("Zoom Mode")//缩放设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Rectangle{
            width: defaultfontpage.width - zoomtitle.width - 40 * 2
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Row {
        anchors{
            left: parent.left
            leftMargin: 80
            top: zoomrow.bottom
            topMargin: 10
        }
        spacing: 185
        Row{
            Common.Label {
                id: fontzoomlabel
                width: 130
                text: qsTr("Global Font Scaling:")//全局字体缩放:
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
            spacing: 26
            Common.Button {
                id: okBtn
                width: 105;height: 30
                hoverimage: "green2.png"
                text: qsTr("OK")//确定
                onClicked: {
                    sessiondispatcher.set_font_zoom_qt(slider.value);
                    defaultfontpage.selected_zoom = slider.value;
                    statusImage.visible = true;
                }
            }
            Common.Button {
                hoverimage: "blue2.png"
                text: qsTr("Reset Font")//恢复默认
                width: 105
                height: 30
                onClicked: {
                    var defaultvalue = sessiondispatcher.read_default_configure_from_qsetting_file("font", "zoom");
                    if(defaultvalue == defaultfontpage.selected_zoom) {
                        //友情提示：       您系统的全局字体缩放已经为默认设置！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Your system's current global font scaling is the default!"), mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {
                        sessiondispatcher.set_font_zoom_qt(defaultvalue);
                        defaultfontpage.selected_zoom = defaultvalue;
                        slider.value = defaultvalue;
                        statusImage.visible = true;
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
