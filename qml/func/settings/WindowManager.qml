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
    height: 476

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
    property string actiontext: qsTr("Manage Window Manager settings.")//管理窗口管理器的设置
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
    Connections
    {
        target: sessiondispatcher
        onTellDownloadCloudConfToQML: {
            if(download == "window_button") {
                windowmanagerpage.position_mode = sessiondispatcher.get_window_button_align_qt();
                if (windowmanagerpage.position_mode == "left") {
                    leftbox.checked = true;
                }
                else if(windowmanagerpage.position_mode == "right") {
                    rightbox.checked = true;
                }
            }
            else if(download == "menus_have_icons") {
                if (sessiondispatcher.get_menus_have_icons_qt()) {
                    menuswitcher.switchedOn = true;
                }
                else {
                    menuswitcher.switchedOn = false;
                }
            }
            else if(download == "titlebar_wheel") {
                var wheellist = sessiondispatcher.get_titlebar_wheel_qt();
                var current_wheel_type = sessiondispatcher.get_current_titlebar_wheel_qt();
                for(var i=0; i < wheellist.length; i++) {
                    if (wheellist[i] == current_wheel_type) {
                        windowmanagerpage.wheel_current_index = i;
                        break;
                    }
                }
                wheelcombo.selectedIndex = windowmanagerpage.wheel_current_index;
            }
            else if(download == "titlebar_double") {
                var doublelist = sessiondispatcher.get_titlebar_double_qt();
                var current_double_type = sessiondispatcher.get_current_titlebar_double_qt();
                for(var k=0; k < doublelist.length; k++) {
                    if (doublelist[k] == current_double_type) {
                        windowmanagerpage.double_current_index = k;
                        break;
                    }
                }
                doublecombo.selectedIndex = windowmanagerpage.double_current_index;
            }
            else if(download == "titlebar_middle") {
                var middlelist = sessiondispatcher.get_titlebar_middle_qt();
                var current_middle_type = sessiondispatcher.get_current_titlebar_middle_qt();
                for(var n=0; n < middlelist.length; n++) {
                    if (middlelist[n] == current_middle_type) {
                        windowmanagerpage.middle_current_index = n;
                        break;
                    }
                }
                middlecombo.selectedIndex = windowmanagerpage.middle_current_index;
            }
            else if(download == "titlebar_right") {
                var rightlist = sessiondispatcher.get_titlebar_right_qt();
                var current_right_type = sessiondispatcher.get_current_titlebar_right_qt();
                for(var l=0; l < rightlist.length; l++) {
                    if (rightlist[l] == current_right_type) {
                        windowmanagerpage.right_current_index = l;
                        break;
                    }
                }
                rightcombo.selectedIndex = windowmanagerpage.right_current_index;
            }
        }
    }

    Component.onCompleted: {
        windowmanagerpage.position_mode = sessiondispatcher.get_window_button_align_qt();
        if (sessiondispatcher.get_menus_have_icons_qt()) {
            menuswitcher.switchedOn = true;
        }
        else {
            menuswitcher.switchedOn = false;
        }

        //wheel action
//        var wheellist = sessiondispatcher.get_titlebar_wheel_qt();
//        var current_wheel_type = sessiondispatcher.get_current_titlebar_wheel_qt();
//        var default_wheel_type = sessiondispatcher.get_default_system_sring_qt("wheel-action");
//        wheelchoices.clear();
//        if(current_wheel_type == default_wheel_type) {
//            for(var i=0; i < wheellist.length; i++) {
//                wheelchoices.append({"text": wheellist[i]});
//                if (wheellist[i] == current_wheel_type) {
//                    windowmanagerpage.wheel_current_index = i;
//                    windowmanagerpage.wheel_default_index = i;
//                }
//            }
//        }
//        else {
//            for(var j=0; j < wheellist.length; j++) {
//                wheelchoices.append({"text": wheellist[j]});
//                if (wheellist[j] == current_wheel_type) {
//                    windowmanagerpage.wheel_current_index = j;
//                }
//                else if (wheellist[j] == default_wheel_type) {
//                    windowmanagerpage.wheel_default_index = j;
//                }
//            }
//        }
//        wheelcombo.selectedIndex = windowmanagerpage.wheel_current_index;



        var index = 0;
        var i = 0;
        var j = 0;
        var k = 0;
        var wheellist = sessiondispatcher.get_titlebar_wheel_qt();
        var current_wheel_type = sessiondispatcher.get_current_titlebar_wheel_qt();
        var default_wheel_type = sessiondispatcher.get_default_system_sring_qt("wheel-action");
        for(i=0; i < wheellist.length; i++) {
            if (current_wheel_type == wheellist[i]) {
                index = i;
                windowmanagerpage.wheel_current_index = i;
            }
            if (default_wheel_type == wheellist[i]) {
                windowmanagerpage.wheel_default_index = i;
            }
        }
        wheelchoices.clear();
        if (index == 0) {
            for(j=0; j < wheellist.length; j++) {
                wheelchoices.append({"text": wheellist[j]});
            }
        }
        else {
            wheellist.unshift(current_wheel_type);
            for(k=0; k < wheellist.length; k++) {
                wheelchoices.append({"text": wheellist[k]});
                if (k!=0 && wheellist[k] == current_wheel_type){
                    wheelchoices.remove(k);
                }
            }
        }


        //double click
//        var doublelist = sessiondispatcher.get_titlebar_double_qt();
//        var current_double_type = sessiondispatcher.get_current_titlebar_double_qt();
//        var default_double_type = sessiondispatcher.get_default_system_sring_qt("double-click");
//        doublechoices.clear();
//        if(current_double_type == default_double_type) {
//            for(var k=0; k < doublelist.length; k++) {
//                doublechoices.append({"text": doublelist[k]});
//                if (doublelist[k] == current_double_type) {
//                    windowmanagerpage.double_current_index = k;
//                    windowmanagerpage.double_default_index = k;
//                }
//            }
//        }
//        else {
//            for(var m=0; m < doublelist.length; m++) {
//                doublechoices.append({"text": doublelist[m]});
//                if (doublelist[m] == current_double_type) {
//                    windowmanagerpage.double_current_index = m;
//                }
//                else if (doublelist[m] == default_double_type) {
//                    windowmanagerpage.double_default_index = m;
//                }
//            }
//        }
//        doublecombo.selectedIndex = windowmanagerpage.double_current_index;



        index = 0;
        var doublelist = sessiondispatcher.get_titlebar_double_qt();
        var current_double_type = sessiondispatcher.get_current_titlebar_double_qt();
        var default_double_type = sessiondispatcher.get_default_system_sring_qt("double-click");
        for(i=0; i < doublelist.length; i++) {
            if (current_double_type == doublelist[i]) {
                index = i;
                windowmanagerpage.double_current_index = i;

            }
            if (default_double_type == doublelist[i]) {
                windowmanagerpage.double_default_index = i;
            }
        }
        doublechoices.clear();
        if (index == 0) {
            for(j=0; j < doublelist.length; j++) {
                doublechoices.append({"text": doublelist[j]});
            }
        }
        else {
            doublelist.unshift(current_double_type);
            for(k=0; k < doublelist.length; k++) {
                doublechoices.append({"text": doublelist[k]});
                if (k!=0 && doublelist[k] == current_double_type){
                    doublechoices.remove(k);
                }
            }
        }


        //middle click
//        var middlelist = sessiondispatcher.get_titlebar_middle_qt();
//        var current_middle_type = sessiondispatcher.get_current_titlebar_middle_qt();
//        var default_middle_type = sessiondispatcher.get_default_system_sring_qt("middle-click");
//        middlechoices.clear();
//        if(current_middle_type == default_middle_type) {
//            for(var n=0; n < middlelist.length; n++) {
//                middlechoices.append({"text": middlelist[n]});
//                if (middlelist[n] == current_middle_type) {
//                    windowmanagerpage.middle_current_index = n;
//                    windowmanagerpage.middle_default_index = n;
//                }
//            }
//        }
//        else {
//            for(var p=0; p < middlelist.length; p++) {
//                middlechoices.append({"text": middlelist[p]});
//                if (middlelist[p] == current_middle_type) {
//                    windowmanagerpage.middle_current_index = p;
//                }
//                else if (middlelist[p] == default_middle_type) {
//                    windowmanagerpage.middle_default_index = p;
//                }
//            }
//        }
//        middlecombo.selectedIndex = windowmanagerpage.middle_current_index;


        index = 0;
        var middlelist = sessiondispatcher.get_titlebar_middle_qt();
        var current_middle_type = sessiondispatcher.get_current_titlebar_middle_qt();
        var default_middle_type = sessiondispatcher.get_default_system_sring_qt("middle-click");
        for(i=0; i < middlelist.length; i++) {
            if (current_middle_type == middlelist[i]) {
                index = i;
                windowmanagerpage.middle_current_index = i;

            }
            if (default_middle_type == middlelist[i]) {
                windowmanagerpage.middle_default_index = i;
            }
        }
        middlechoices.clear();
        if (index == 0) {
            for(j=0; j < middlelist.length; j++) {
                middlechoices.append({"text": middlelist[j]});
            }
        }
        else {
            middlelist.unshift(current_middle_type);
            for(k=0; k < middlelist.length; k++) {
                middlechoices.append({"text": middlelist[k]});
                if (k!=0 && middlelist[k] == current_middle_type){
                    middlechoices.remove(k);
                }
            }
        }


        //right click
//        var rightlist = sessiondispatcher.get_titlebar_right_qt();
//        var current_right_type = sessiondispatcher.get_current_titlebar_right_qt();
//        var default_right_type = sessiondispatcher.get_default_system_sring_qt("right-click");
//        rightchoices.clear();
//        if(current_right_type == default_right_type) {
//            for(var l=0; l < rightlist.length; l++) {
//                rightchoices.append({"text": rightlist[l]});
//                if (rightlist[l] == current_right_type) {
//                    windowmanagerpage.right_current_index = l;
//                    windowmanagerpage.right_default_index = l;
//                }
//            }
//        }
//        else {
//            for(var q=0; q < rightlist.length; q++) {
//                rightchoices.append({"text": rightlist[q]});
//                if (rightlist[q] == current_right_type) {
//                    windowmanagerpage.right_current_index = q;
//                }
//                else if (rightlist[q] == default_right_type) {
//                    windowmanagerpage.right_default_index = q;
//                }
//            }
//        }
//        rightcombo.selectedIndex = windowmanagerpage.right_current_index;



        index = 0;
        var rightlist = sessiondispatcher.get_titlebar_right_qt();
        var current_right_type = sessiondispatcher.get_current_titlebar_right_qt();
        var default_right_type = sessiondispatcher.get_default_system_sring_qt("right-click");
        for(i=0; i < rightlist.length; i++) {
            if (current_right_type == rightlist[i]) {
                index = i;
                windowmanagerpage.right_current_index = i;

            }
            if (default_right_type == rightlist[i]) {
                windowmanagerpage.right_default_index = i;
            }
        }
        rightchoices.clear();
        if (index == 0) {
            for(j=0; j < rightlist.length; j++) {
                rightchoices.append({"text": rightlist[j]});
            }
        }
        else {
            rightlist.unshift(current_right_type);
            for(k=0; k < rightlist.length; k++) {
                rightchoices.append({"text": rightlist[k]});
                if (k!=0 && rightlist[k] == current_right_type){
                    rightchoices.remove(k);
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
        y: 60
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
            topMargin: 50
        }
        z: 11
        Row {
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
                    text: qsTr("Window control btn position:")//窗口控制按钮位置：
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    sessiondispatcher.set_default_system_qt("control-button-position");
                    var default_type = sessiondispatcher.get_window_button_align_qt();
                    windowmanagerpage.position_mode = default_type;
                    if(default_type == "left") {
                        leftbox.checked = true;
                    }
                    else if(default_type == "right") {
                        rightbox.checked = true;
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    sessiondispatcher.set_default_system_qt("menu-with-icons");
                    if (sessiondispatcher.get_menus_have_icons_qt()) {
                        menuswitcher.switchedOn = true;
                    }
                    else {
                        menuswitcher.switchedOn = false;
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    sessiondispatcher.set_default_system_qt("wheel-action");
                    wheelcombo.selectedIndex = windowmanagerpage.wheel_default_index;
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    sessiondispatcher.set_default_system_qt("double-action");
                    doublecombo.selectedIndex = windowmanagerpage.double_default_index;
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    sessiondispatcher.set_default_system_qt("middle-action");
                    middlecombo.selectedIndex = windowmanagerpage.middle_default_index;
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
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    sessiondispatcher.set_default_system_qt("right-action");
                    rightcombo.selectedIndex = windowmanagerpage.right_default_index;
                }
            }
        }
    }
}
