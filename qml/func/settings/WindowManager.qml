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
    id: windowmanagerpage
    width: parent.width
    height: 476
    color: "#eeedf0"

    property string position_mode: ""
    property int wheel_current_index//当前的索引
    property int wheel_default_index//系统默认的索引
    property int double_current_index//当前的索引
    property int double_default_index//系统默认的索引
    property int middle_current_index//当前的索引
    property int middle_default_index//系统默认的索引
    property int right_current_index//当前的索引
    property int right_default_index//系统默认的索引

    property string actiontitle: qsTr("Window")//窗口
    property string actiontext: qsTr("Window Manager settings.")//管理窗口管理器的设置
    //背景
//    Image {
//        source: "../../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }

    ListModel { id: wheelchoices }
    ListModel { id: doublechoices }
    ListModel { id: middlechoices }
    ListModel { id: rightchoices }

    //使用云配置后，控件状态根据配置发生相应的变化
//    Connections
//    {
//        target: sessiondispatcher
//        onTellDownloadCloudConfToQML: {
//            if(download == "window_button") {
//                windowmanagerpage.position_mode = sessiondispatcher.get_window_button_align_qt();
//                if (windowmanagerpage.position_mode == "left") {
//                    leftbox.checked = true;
//                }
//                else if(windowmanagerpage.position_mode == "right") {
//                    rightbox.checked = true;
//                }
//            }
//            else if(download == "menus_have_icons") {
//                if (sessiondispatcher.get_menus_have_icons_qt()) {
//                    menuswitcher.switchedOn = true;
//                }
//                else {
//                    menuswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "titlebar_wheel") {
//                var wheellist = sessiondispatcher.get_titlebar_wheel_qt();
//                var current_wheel_type = sessiondispatcher.get_current_titlebar_wheel_qt();
//                var new_list = new Array();
//                for(var m=0; m < wheellist.length; m++) {
//                    if(wheellist[m] !== current_wheel_type) {
//                        new_list.push(wheellist[m]);
//                    }
//                }
//                new_list.unshift(current_wheel_type);
//                for(var j=0; j < new_list.length; j++) {
//                    if (current_wheel_type === new_list[j]) {
//                        wheelcombo.selectedIndex  = j;
//                        break;
//                    }
//                }
//            }
//            else if(download == "titlebar_double") {
//                var doublelist = sessiondispatcher.get_titlebar_double_qt();
//                var current_double_type = sessiondispatcher.get_current_titlebar_double_qt();
//                var new_list = new Array();
//                for(var m=0; m < doublelist.length; m++) {
//                    if(doublelist[m] !== current_double_type) {
//                        new_list.push(doublelist[m]);
//                    }
//                }
//                new_list.unshift(current_double_type);
//                for(var j=0; j < new_list.length; j++) {
//                    if (current_double_type === new_list[j]) {
//                        doublecombo.selectedIndex  = j;
//                        break;
//                    }
//                }
//            }
//            else if(download == "titlebar_middle") {
//                var middlelist = sessiondispatcher.get_titlebar_middle_qt();
//                var current_middle_type = sessiondispatcher.get_current_titlebar_middle_qt();
//                var new_list = new Array();
//                for(var m=0; m < middlelist.length; m++) {
//                    if(middlelist[m] !== current_middle_type) {
//                        new_list.push(middlelist[m]);
//                    }
//                }
//                new_list.unshift(current_middle_type);
//                for(var j=0; j < new_list.length; j++) {
//                    if (current_middle_type === new_list[j]) {
//                        middlecombo.selectedIndex  = j;
//                        break;
//                    }
//                }
//            }
//            else if(download == "titlebar_right") {
//                var rightlist = sessiondispatcher.get_titlebar_right_qt();
//                var current_right_type = sessiondispatcher.get_current_titlebar_right_qt();
//                var new_list = new Array();
//                for(var m=0; m < rightlist.length; m++) {
//                    if(rightlist[m] !== current_right_type) {
//                        new_list.push(rightlist[m]);
//                    }
//                }
//                new_list.unshift(current_right_type);
//                for(var j=0; j < new_list.length; j++) {
//                    if (current_right_type === new_list[j]) {
//                        rightcombo.selectedIndex  = j;
//                        break;
//                    }
//                }
//            }
//        }
//    }

    Component.onCompleted: {
        if (sessiondispatcher.judge_desktop_is_unity_qt() == "Unity") {
            toolboxpositon.visible = false;
        }
        else {
            toolboxpositon.visible = true;
        }

        windowmanagerpage.position_mode = sessiondispatcher.get_window_button_align_qt();
        if (sessiondispatcher.get_menus_have_icons_qt()) {
            menuswitcher.switchedOn = true;
        }
        else {
            menuswitcher.switchedOn = false;
        }

        var i = 0;
        var j = 0;
        var wheellist = sessiondispatcher.get_titlebar_wheel_qt();
        var current_wheel_type = sessiondispatcher.get_current_titlebar_wheel_qt();
        var default_wheel_type = sessiondispatcher.get_uk_default_setting_string("window", "mouse-wheel-action");

        var new_list = new Array();
        for(i=0; i < wheellist.length; i++) {
            if(wheellist[i] !== current_wheel_type) {
                new_list.push(wheellist[i]);
            }
        }
        new_list.unshift(current_wheel_type);
        wheelchoices.clear();
        for(j=0; j < new_list.length; j++) {
            wheelchoices.append({"text": new_list[j]});
            if (default_wheel_type === new_list[j]) {
                windowmanagerpage.wheel_default_index = j;
            }
        }

        var doublelist = sessiondispatcher.get_titlebar_double_qt();
        var current_double_type = sessiondispatcher.get_current_titlebar_double_qt();
        var default_double_type = sessiondispatcher.get_uk_default_setting_string("window", "action-double-click-titlebar");
        var new_list2 = new Array();
        for(i=0; i < doublelist.length; i++) {
            if(doublelist[i] !== current_double_type) {
                new_list2.push(doublelist[i]);
            }
        }
        new_list2.unshift(current_double_type);
        doublechoices.clear();
        for(j=0; j < new_list2.length; j++) {
            doublechoices.append({"text": new_list2[j]});
            if (default_double_type === new_list2[j]) {
                windowmanagerpage.double_default_index = j;
            }
        }

        var middlelist = sessiondispatcher.get_titlebar_middle_qt();
        var current_middle_type = sessiondispatcher.get_current_titlebar_middle_qt();
        var default_middle_type = sessiondispatcher.get_uk_default_setting_string("window", "action-middle-click-titlebar");
        var new_list3 = new Array();
        for(i=0; i < middlelist.length; i++) {
            if(middlelist[i] !== current_middle_type) {
                new_list3.push(middlelist[i]);
            }
        }
        new_list3.unshift(current_middle_type);
        middlechoices.clear();
        for(j=0; j < new_list3.length; j++) {
            middlechoices.append({"text": new_list3[j]});
            if (default_middle_type === new_list3[j]) {
                windowmanagerpage.middle_default_index = j;
            }
        }

        var rightlist = sessiondispatcher.get_titlebar_right_qt();
        var current_right_type = sessiondispatcher.get_current_titlebar_right_qt();
        var default_right_type = sessiondispatcher.get_uk_default_setting_string("window", "action-right-click-titlebar");
        var new_list4 = new Array();
        for(i=0; i < rightlist.length; i++) {
            if(rightlist[i] !== current_right_type) {
                new_list4.push(rightlist[i]);
            }
        }
        new_list4.unshift(current_right_type);
        rightchoices.clear();
        for(j=0; j < new_list4.length; j++) {
            rightchoices.append({"text": new_list4[j]});
            if (default_right_type === new_list4[j]) {
                windowmanagerpage.right_default_index = j;
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
                 text: windowmanagerpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: windowmanagerpage.actiontext
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
        spacing: 10
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 40
        }
        z: 11
        Row {
            id: toolboxpositon
            spacing: 230
            Row {
                id: workmode
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    width: 160
                    text: qsTr("Window function button:")//窗口控制按钮位置：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 134
                    Common.CheckBox {
                        id: leftbox
                        titleName: qsTr("Left Side")//左边
                        checked: (windowmanagerpage.position_mode == "left") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (leftbox.checked == true) {
                                if(windowmanagerpage.position_mode != "left") {
                                    sessiondispatcher.set_window_button_align_left_qt();
                                    windowmanagerpage.position_mode = "left";
                                }
                            }
                        }
                    }
                    Common.CheckBox {
                        id: rightbox
                        titleName: qsTr("Right Side")//右边
                        checked: (windowmanagerpage.position_mode == "right") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (rightbox.checked == true) {
                                if(windowmanagerpage.position_mode != "right") {
                                    sessiondispatcher.set_window_button_align_right_qt();
                                    windowmanagerpage.position_mode = "right";
                                }
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    var cur_type;
                    if (leftbox.checked) {
                        cur_type = "left";
                    }
                    else {
                        cur_type = "right";
                    }

                    if (sessiondispatcher.get_uk_default_setting_string("window", "button-layout") !== cur_type) {
                        sessiondispatcher.restore_uk_default_setting("window", "button-layout");
                        var current_type = sessiondispatcher.get_window_button_align_qt();
                        windowmanagerpage.position_mode = current_type;
                        if(current_type === "left") {
                            leftbox.checked = true;
                        }
                        else if(current_type === "right") {
                            rightbox.checked = true;
                        }
                    }
                }
            }
        }

        Row {
            spacing: 230
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Common.Label {
                    width: 160
                    text: qsTr("Menu with icons: ")//菜单项旁显示图标：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: menuswitcher
                    width: 160
                    onSwitched: {
                        if (menuswitcher.switchedOn) {
                            sessiondispatcher.set_menus_have_icons_qt(true);
                        }
                        else if(!menuswitcher.switchedOn) {
                            sessiondispatcher.set_menus_have_icons_qt(false);
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("window", "menus-have-icons") !== menuswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("window", "menus-have-icons");
                        if (sessiondispatcher.get_menus_have_icons_qt()) {
                            menuswitcher.switchedOn = true;
                        }
                        else {
                            menuswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }

        Row {
            spacing: 230
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Text {
                    width: 160
                    text: qsTr("Titlebar mouse wheel action:")//标题栏鼠标滚轮动作：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: wheelcombo
                    model: wheelchoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_titlebar_wheel_qt(wheelcombo.selectedText);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var default_theme = sessiondispatcher.get_uk_default_setting_string("window", "mouse-wheel-action");
                    if(wheelcombo.selectedText !== default_theme) {
                        sessiondispatcher.restore_uk_default_setting("window", "mouse-wheel-action");
                        wheelcombo.selectedIndex = windowmanagerpage.wheel_default_index;
                    }
                }
            }
        }

        Row {
            spacing: 230
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Text {
                    width: 160
                    text: qsTr("Titlebar double-click action:")//标题栏双击动作：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: doublecombo
                    model: doublechoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_titlebar_double_qt(doublecombo.selectedText);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var default_theme = sessiondispatcher.get_uk_default_setting_string("window", "action-double-click-titlebar");
                    if(doublecombo.selectedText !== default_theme) {
                        sessiondispatcher.restore_uk_default_setting("window", "action-double-click-titlebar");
                        doublecombo.selectedIndex = windowmanagerpage.double_default_index;
                    }
                }
            }
        }

        Row {
            spacing: 230
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Text {
                    width: 160
                    text: qsTr("Titlebar middle-click action:")//标题栏中键动作：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: middlecombo
                    model: middlechoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_titlebar_middle_qt(middlecombo.selectedText);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var default_theme = sessiondispatcher.get_uk_default_setting_string("window", "action-middle-click-titlebar");
                    if(middlecombo.selectedText !== default_theme) {
                        sessiondispatcher.restore_uk_default_setting("window", "action-middle-click-titlebar");
                        middlecombo.selectedIndex = windowmanagerpage.middle_default_index;
                    }
                }
            }
        }

        Row {
            spacing: 230
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "yes"
                    showImage: "../../img/icons/cloud-light.png"
                }
                Text {
                    width: 160
                    text: qsTr("Titlebar right-click action:")//标题栏右键动作：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: rightcombo
                    model: rightchoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_titlebar_right_qt(rightcombo.selectedText);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var default_theme = sessiondispatcher.get_uk_default_setting_string("window", "action-right-click-titlebar");
                    if(rightcombo.selectedText !== default_theme) {
                        sessiondispatcher.restore_uk_default_setting("window", "action-right-click-titlebar");
                        rightcombo.selectedIndex = windowmanagerpage.right_default_index;
                    }
                }
            }
        }
    }
}
