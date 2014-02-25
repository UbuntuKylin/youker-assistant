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
    id: windowmanagerpage
    width: parent.width
    height: 475

    property string actiontitle: qsTr("Window")//窗口
    property string actiontext: qsTr("Manage Window Manager settings.")//管理窗口管理器的设置
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    ListModel { id: choices1 }
    ListModel { id: choices2 }
    ListModel { id: choices3 }
    ListModel { id: choices4 }
    Component.onCompleted: {

    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row{
            spacing: 50
            Text {
                 text: windowmanagerpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            Text {
                id: showText
                text: ""
                font.pixelSize: 14
                color: "#318d11"
            }
        }
        Text {
            text: windowmanagerpage.actiontext
            font.pixelSize: 12
            color: "#7a7a7a"
        }
    }

    Row {
        id: titlebar
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120
        }
        Text{
            id: showtitle
            text: qsTr("Window settings")//窗口设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: windowmanagerpage.width - showtitle.width - 40 * 2
        }
    }

    Column {
        spacing: 10
        anchors{
            left: parent.left
            leftMargin: 60
            top: titlebar.bottom
            topMargin: 30
        }

        Row {
            spacing: 200
            Row {
                id: workmode
                spacing: 40
                Common.Label {
                    width: 130
                    text: qsTr("Scrollbar type: ")//滚动条类型：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 100
                    Common.CheckBox {
                        id:overlay
                        titleName: qsTr("Features Type") //特色类型
//                        checked: (touchpadsetpage.scrollbars_mode == "overlay-auto") ? true : false
                        flag: "radio"
                        onClicked: {
//                            if (overlay.checked == true) {
//                                if(touchpadsetpage.scrollbars_mode != "overlay-auto") {
//                                    sessiondispatcher.set_scrollbars_mode_overlay_qt();
//                                    touchpadsetpage.scrollbars_mode = "overlay-auto";
//                                    statusImage.visible = true;
//                                }
//                            }
                        }
                    }
                    Common.CheckBox {
                        id: legacy
                        titleName: qsTr("Standard Type")  //标准类型
//                        checked: (touchpadsetpage.scrollbars_mode == "normal") ? true : false
                        flag: "radio"
                        onClicked: {
//                            if (legacy.checked == true) {
//                                if(touchpadsetpage.scrollbars_mode != "normal") {
//                                    sessiondispatcher.set_scrollbars_mode_legacy_qt();
//                                    touchpadsetpage.scrollbars_mode = "normal";
//                                    statusImage.visible = true;
//                                }
//                            }
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
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
//                    sessiondispatcher.set_default_system_qt("scrollbar-mode");//滚动条类型
//                    var default_type = sessiondispatcher.get_scrollbars_mode_qt();
//                    if(default_type == "overlay-auto") {
//                        overlay.checked = true;
//                    }
//                    else if(default_type == "normal") {
//                        legacy.checked = true;
//                    }
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 40
                Common.Label {
                    width: 130
                    text: qsTr("Touchpad horizontal scroll: ")//触摸板横向滚动：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: horizontalswitcher
                    width: 125
                    onSwitched: {
//                        if (horizontalswitcher.switchedOn) {
//                            sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
//                        }
//                        else if(!horizontalswitcher.switchedOn) {
//                            sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
//                        }
                    }
                }
            }
            Common.Button {
                hoverimage: "blue.png"
                text: qsTr("Restore")//恢复默认
                width: 94
                height: 29
                fontsize: 13
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
//                    sessiondispatcher.set_default_system_qt("horiz-scroll-enabled");//触摸板横向滚动
//                    if (sessiondispatcher.get_touchscrolling_use_horizontal_qt()) {
//                        horizontalswitcher.switchedOn = true;
//                    }
//                    else {
//                        horizontalswitcher.switchedOn = false;
//                    }
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 40
                Text {
                    width: 130
                    text: qsTr("Icon theme")//图标主题
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: iconcombo1
                    model: choices1
                    width: 125
                    onSelectedTextChanged: {
//                            sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                            //[ 当前图标主题是：
//                            showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                            statusImage.visible = true;
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
//                    sessiondispatcher.set_default_theme_qt("icontheme");
//                    iconcombo.selectedIndex = desktopiconsetpage.default_index;
//                    showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                    statusImage.visible = true;
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 40
                Text {
                    width: 130
                    text: qsTr("Icon theme")//图标主题
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: iconcombo2
                    model: choices2
                    width: 125
                    onSelectedTextChanged: {
//                            sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                            //[ 当前图标主题是：
//                            showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                            statusImage.visible = true;
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
//                    sessiondispatcher.set_default_theme_qt("icontheme");
//                    iconcombo.selectedIndex = desktopiconsetpage.default_index;
//                    showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                    statusImage.visible = true;
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 40
                Text {
                    width: 130
                    text: qsTr("Icon theme")//图标主题
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: iconcombo3
                    model: choices3
                    width: 125
                    onSelectedTextChanged: {
//                            sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                            //[ 当前图标主题是：
//                            showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                            statusImage.visible = true;
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
//                    sessiondispatcher.set_default_theme_qt("icontheme");
//                    iconcombo.selectedIndex = desktopiconsetpage.default_index;
//                    showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                    statusImage.visible = true;
                }
            }
        }

        Row {
            spacing: 200
            Row {
                spacing: 40
                Text {
                    width: 130
                    text: qsTr("Icon theme")//图标主题
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: iconcombo4
                    model: choices4
                    width: 125
                    onSelectedTextChanged: {
//                            sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                            //[ 当前图标主题是：
//                            showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                            statusImage.visible = true;
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
//                    sessiondispatcher.set_default_theme_qt("icontheme");
//                    iconcombo.selectedIndex = desktopiconsetpage.default_index;
//                    showText.text = qsTr("[ Current icon theme is: ") + iconcombo.selectedText + " ]";//[ 当前图标主题是：
//                    statusImage.visible = true;
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
