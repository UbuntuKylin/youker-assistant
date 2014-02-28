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
    id: defaultfontpage
    property bool on: true
    width: parent.width
    height: 475

    property string current_font: "Helvetica"
    property string desktop_font: "Helvetica"
    property string monospace_font: "Helvetica"
    property string document_font: "Helvetica"
    property string titlebar_font: "Helvetica"
    property double zoom: 1.0
    property bool first_slider_value: false //系统初始化时会使value的值为0.5，需要过滤掉
    property int current_smooth_index//当前平滑的索引
    property int default_smooth_index//系统默认平滑的索引
    property int current_antialiasing_index//当前锯齿的索引
    property int default_antialiasing_index//系统默认锯齿的索引

    property string actiontitle: qsTr("Default font settings")//默认字体设置
    property string actiontext: qsTr("According to personal preferences to set the system default font, click the  'Restore' button, can be restored to the state before the font settings. ")//根据个人喜好设置系统默认字体，单击＂恢复默认＂按钮，可以将对应的字体恢复到设置前状态。
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }
    ListModel { id: smoothchoices }
    ListModel { id: antialiasingchoices }


    Connections
    {
        target: sessiondispatcher
        onNotifyFontStyleToQML: {//字体更改后界面显示刷新
            if (font_style == "font") {
                fontBtn.text = sessiondispatcher.get_font_qt();
            }
            else if (font_style == "desktopfont") {
                desktopfontBtn.text = sessiondispatcher.get_desktop_font_qt();
            }
            else if (font_style == "monospacefont") {
                monofontBtn.text = sessiondispatcher.get_monospace_font_qt();
            }
            else if (font_style == "documentfont") {
                docufontBtn.text = sessiondispatcher.get_document_font_qt();
            }
            else if (font_style == "titlebarfont") {//弹出字体对话框更改好字体后
                titlefontBtn.text = sessiondispatcher.get_window_title_font_qt();
            }
        }

        onTellDownloadCloudConfToQML: {//使用云配置后，控件状态根据配置发生相应的变化
            if(download == "default_font") {
                fontBtn.text = sessiondispatcher.get_font_qt();
            }
            else if(download == "desktop_font") {
                desktopfontBtn.text = sessiondispatcher.get_desktop_font_qt();
            }
            else if(download == "document_font") {
                monofontBtn.text = sessiondispatcher.get_monospace_font_qt();
            }
            else if(download == "monospace_font") {
                docufontBtn.text = sessiondispatcher.get_document_font_qt();
            }
            else if(download == "window_title_font") {
                titlefontBtn.text = sessiondispatcher.get_window_title_font_qt();
            }
            else if(download == "font_zoom") {
                slider.value = sessiondispatcher.get_font_zoom_qt();
            }
            else if(download == "font_hinting") {
                var smooth_list = sessiondispatcher.get_smooth_style_list_qt();
                var cur_smooth = sessiondispatcher.get_smooth_style_qt();
                for(var m=0; m < smooth_list.length; m++) {
                    if (smooth_list[m] == cur_smooth) {
                        defaultfontpage.current_smooth_index = m;
                        break;
                    }
                }
                smoothcombo.selectedIndex = defaultfontpage.current_smooth_index;
            }
            else if(download == "font_antialiasing") {
                var antialiasinglist = sessiondispatcher.get_antialiasing_style_list_qt();
                var current_antialiasing = sessiondispatcher.get_antialiasing_style_qt();
                for(var n=0; n < antialiasinglist.length; n++) {
                    if (antialiasinglist[n] == current_antialiasing) {
                        defaultfontpage.current_antialiasing_index = n;
                        break;
                    }
                }
                antialiasingcombo.selectedIndex = defaultfontpage.current_antialiasing_index;
            }
        }
    }

    Component.onCompleted: {
        defaultfontpage.current_font = sessiondispatcher.get_font_qt();
        defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        if (defaultfontpage.desktop_font == "") {
            sessiondispatcher.set_desktop_font_qt_default();
            defaultfontpage.desktop_font = sessiondispatcher.get_desktop_font_qt();
        }
        defaultfontpage.monospace_font = sessiondispatcher.get_monospace_font_qt();
        defaultfontpage.document_font = sessiondispatcher.get_document_font_qt();
        defaultfontpage.titlebar_font = sessiondispatcher.get_window_title_font_qt();

        defaultfontpage.zoom = sessiondispatcher.get_font_zoom_qt();
        var smoothlist = sessiondispatcher.get_smooth_style_list_qt();
        var current_smooth = sessiondispatcher.get_smooth_style_qt();
        var default_smooth = sessiondispatcher.get_default_theme_sring_qt("smoothstyle");
        smoothchoices.clear();
        if(current_smooth == default_smooth) {
            for(var m=0; m < smoothlist.length; m++) {
                smoothchoices.append({"text": smoothlist[m]});
                if (smoothlist[m] == current_smooth) {
                    defaultfontpage.current_smooth_index = m;
                    defaultfontpage.default_smooth_index = m;
                }
            }
        }
        else {
            for(var i=0; i < smoothlist.length; i++) {
                smoothchoices.append({"text": smoothlist[i]});
                if (smoothlist[i] == current_smooth) {
                    defaultfontpage.current_smooth_index = i;
                }
                else if (smoothlist[i] == default_smooth) {
                    defaultfontpage.default_smooth_index = i;
                }
            }
        }
        smoothcombo.selectedIndex = defaultfontpage.current_smooth_index;

        var antialiasinglist = sessiondispatcher.get_antialiasing_style_list_qt();
        var current_antialiasing = sessiondispatcher.get_antialiasing_style_qt();
        var default_antialiasing = sessiondispatcher.get_default_theme_sring_qt("antialiasingstyle");
        antialiasingchoices.clear();
        if(current_antialiasing == default_antialiasing) {
            for(var n=0; n < antialiasinglist.length; n++) {
                antialiasingchoices.append({"text": antialiasinglist[n]});
                if (antialiasinglist[n] == current_antialiasing) {
                    defaultfontpage.current_antialiasing_index = n;
                    defaultfontpage.default_antialiasing_index = n;
                }
            }
        }
        else {
            for(var j=0; j < antialiasinglist.length; j++) {
                antialiasingchoices.append({"text": antialiasinglist[j]});
                if (antialiasinglist[j] == current_antialiasing) {
                    defaultfontpage.current_antialiasing_index = j;
                }
                else if (antialiasinglist[j] == default_antialiasing) {
                    defaultfontpage.default_antialiasing_index = j;
                }
            }
        }
        antialiasingcombo.selectedIndex = defaultfontpage.current_antialiasing_index;
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
            text: defaultfontpage.actiontitle
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
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
            topMargin: 105

        }
        Text{
            id: fonttitle
            text: qsTr("Font Settings")//字体设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: defaultfontpage.width - fonttitle.width - 40 * 2
        }
    }

    Column {
        id: fontcolumn
        spacing: 3
        anchors{
            left: parent.left
            leftMargin: 80
            top: settitle.bottom
            topMargin: 10
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: fontslabel
                    width: 150
                    text: qsTr("Default Font: ")//默认字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Button {
                    id: fontBtn
                    hoverimage: "fontbtn.png"
                    fontcolor: "#086794"
                    text: sessiondispatcher.get_font_qt()
                    width: 250
                    height: 29
                    fontsize: 13
                    onClicked: sessiondispatcher.show_font_dialog("font");
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("defaultfont");
                        fontBtn.text = sessiondispatcher.get_font_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: desktopfontlabel
                    width: 150
                    text: qsTr("Desktop Font: ")//桌面字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Button {
                    id: desktopfontBtn
                    hoverimage: "fontbtn.png"
                    text: sessiondispatcher.get_desktop_font_qt()
                    fontcolor: "#086794"
                    width: 250
                    height: 29
                    fontsize: 13
                    onClicked: sessiondispatcher.show_font_dialog("desktopfont");
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("desktopfont");
                        desktopfontBtn.text = sessiondispatcher.get_desktop_font_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: monospacefontlabel
                    width: 150
                    text: qsTr("Monospace Font: ")  //等宽字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Button {
                    id: monofontBtn
                    hoverimage: "fontbtn.png"
                    text: sessiondispatcher.get_monospace_font_qt()
                    fontcolor: "#086794"
                    width: 250
                    height: 29
                    fontsize: 13
                    onClicked: sessiondispatcher.show_font_dialog("monospacefont");
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("monospacefont");
                        monofontBtn.text = sessiondispatcher.get_monospace_font_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: documentfontlabel
                    width: 150
                    text: qsTr("Document font: ")//文档字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Button {
                    id: docufontBtn
                    hoverimage: "fontbtn.png"
                    text: defaultfontpage.document_font
                    fontcolor: "#086794"
                    width: 250
                    height: 29
                    fontsize: 13
                    onClicked: sessiondispatcher.show_font_dialog("documentfont");
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("documentfont");
                        docufontBtn.text = sessiondispatcher.get_document_font_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: windowtitlefontlabel
                    width: 150
                    text: qsTr("Titlebar font: ")//标题栏字体：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Button {
                    id: titlefontBtn
                    hoverimage: "fontbtn.png"
                    text: defaultfontpage.titlebar_font
                    fontcolor: "#086794"
                    width: 250
                    height: 29
                    fontsize: 13
                    onClicked: sessiondispatcher.show_font_dialog("titlebarfont");
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("titlebarfont");
                        titlefontBtn.text = sessiondispatcher.get_window_title_font_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }
    }//Column

    Row {
        id: zoomrow
        anchors{
            left: parent.left
            leftMargin: 40
            top: fontcolumn.bottom
            topMargin: 10
        }
        Text{
            id: zoomtitle
            text: qsTr("Style Settings")//风格设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: defaultfontpage.width - zoomtitle.width - 40 * 2
        }
    }
    Column {
        id: stylecolumn
        spacing: 3
        anchors{
            left: parent.left
            leftMargin: 80
            top: zoomrow.bottom
            topMargin: 5
        }
        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: fontzoomlabel
                    width: 150
                    text: qsTr("Global Font Scaling: ")//全局字体缩放：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: slider
                    minimumValue: 0.5
                    maximumValue: 3.0
                    width: 250
                    value: sessiondispatcher.get_font_zoom_qt()
                    onValueChanged: {
                        if(defaultfontpage.first_slider_value ){  //系统初始化时会使value的值为0.5（最小值），需要过滤掉
                            sessiondispatcher.set_font_zoom_qt(slider.value);
                        }
                        if(slider.value == 0.5) { //系统初始化时会使value的值为0.5（最小值），需要过滤掉
                            defaultfontpage.first_slider_value = true;
                        }
                    }
                    stepSize: 0.1
                    animated: true
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("globalfontscaling");
                        slider.value = sessiondispatcher.get_font_zoom_qt();
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }

        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: smoothlabel
                    width: 150
                    text: qsTr("Global Font Scaling: ")//平滑：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: smoothcombo
                    model: smoothchoices
                    width: 250
                    onSelectedTextChanged: {
                        sessiondispatcher.set_smooth_style_qt(smoothcombo.selectedText);
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("smoothstyle");
                        smoothcombo.selectedIndex = defaultfontpage.default_smooth_index;
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
            }
        }

        Row {
            spacing: 234 - 16 - 40
            Row{
                spacing: 20
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    id: antialiasinglabel
                    width: 150
                    text: qsTr("Global Font Scaling: ")//反锯齿：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: antialiasingcombo
                    model: antialiasingchoices
                    width: 250
                    onSelectedTextChanged: {
                        sessiondispatcher.set_antialiasing_style_qt(antialiasingcombo.selectedText);
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row {
                Common.Button {
                    hoverimage: "blue.png"
                    text: qsTr("Restore")//恢复默认
                    width: 94
                    height: 29
                    fontsize: 13
                    onClicked: {
                        sessiondispatcher.set_default_theme_qt("antialiasingstyle");
                        antialiasingcombo.selectedIndex = defaultfontpage.default_antialiasing_index;
                    }
                }
//                Image {
//                    width: 16; height: 16
//                    source: "../../img/icons/cloud-light.png"
//                }
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
