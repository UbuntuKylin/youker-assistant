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
    id: launcherthemepage
    width: parent.width
    height: 476
//    color: "#e4f2fc"

    property bool first_slider_value: false //系统初始化时会使value的值为32（最小值），需要过滤掉
    property bool first_transparency_value: false //系统初始化时会使value的值为0.2（最小值），需要过滤掉
    property string actiontitle: qsTr("Launcher settings")//启动器设置
    property string actiontext: qsTr("Setting the Launcher display mode, Icon size.")//设置启动器的显示模式、图标尺寸。
    property int default_bg_index//系统默认图标背景模式的索引

    ListModel { id: backgroundchoices }

    //使用云配置后，控件状态根据配置发生相应的变化
//    Connections
//    {
//        target: sessiondispatcher
//        onTellDownloadCloudConfToQML: {
//            if(download == "launcher_autohide") {
//                if (sessiondispatcher.get_launcher_autohide_qt()) {
//                    launcherswitcher.switchedOn = true;
//                }
//                else {
//                    launcherswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "launcher_icon_size") {
//                slider.value = sessiondispatcher.get_launcher_icon_size_qt();
//            }
//        }
//    }

    Component.onCompleted: {
        if (sessiondispatcher.get_launcher_autohide_qt()) {
            launcherswitcher.switchedOn = true;
        }
        else {
            launcherswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_launcher_have_showdesktopicon_qt()) {
            showdesktopswitcher.switchedOn = true;
        }
        else {
            showdesktopswitcher.switchedOn = false;
        }

        var colourlist = sessiondispatcher.get_all_launcher_icon_colourings_qt();
        var cur_index = sessiondispatcher.get_launcher_icon_colouring_qt();
        var default_bg = sessiondispatcher.get_uk_default_setting_string("unity", "backlight-mode");
        var cur_colour;
        if (cur_index === 0) {
            cur_colour = "all programs";
        }
        else if (cur_index === 1) {
            cur_colour = "only run app";
        }
        else if (cur_index === 2) {
            cur_colour = "no coloring";
        }
        else if (cur_index === 3) {
            cur_colour = "edge coloring";
        }
        else if (cur_index === 4) {
            cur_colour = "each workspace alternating coloring";
        }
        var new_list = new Array();
        for(var j=0; j < colourlist.length; j++) {
            if(colourlist[j] !== cur_colour) {
                new_list.push(colourlist[j]);
            }
        }
        new_list.unshift(cur_colour);
        backgroundchoices.clear();
        for(var k=0; k < new_list.length; k++) {
            backgroundchoices.append({"text": new_list[k]});
            if (default_bg === new_list[k]) {
                launcherthemepage.default_bg_index = k;
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
                text: launcherthemepage.actiontitle
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: launcherthemepage.width - 80 - 20
                text: launcherthemepage.actiontext
                wrapMode: Text.WordWrap
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
        spacing: 20
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 50
        }
        z: 11
        Row {
            spacing: 210
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
                    id: iconsizelabel
                    width: 170
                    text: qsTr("Launcher icon size: ")//启动器图标尺寸：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: slider
                    value: sessiondispatcher.get_launcher_icon_size_qt()
                    onValueChanged: {
                        if(launcherthemepage.first_slider_value ){  //系统初始化时会使value的值为32（最小值），需要过滤掉
                            sessiondispatcher.set_launcher_icon_size_qt(slider.value);
                        }
                        if(slider.value == 32) { //系统初始化时会使value的值为32（最小值），需要过滤掉
                            launcherthemepage.first_slider_value = true;
                        }
                    }
                    width: iconsizelabel.width
                    maximumValue: 64
                    minimumValue: 32
    //                tickmarksEnabled: true
                    stepSize: 1
                    animated: true
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
                    if (sessiondispatcher.get_uk_default_setting_int("unity", "icon-size") !== slider.value) {
                        sessiondispatcher.restore_uk_default_setting("unity", "icon-size");
                        slider.value = sessiondispatcher.get_launcher_icon_size_qt();
                    }
                }
            }
        }

        Row {
            spacing: 210
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
                    id: launcherlabel
                    width: 170
                    text: qsTr("Launcher hide mode:")//启动器自动隐藏：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: launcherswitcher
                    width: launcherlabel.width
                    onSwitched: {
                        if (launcherswitcher.switchedOn) {
                            sessiondispatcher.set_launcher_autohide_qt(true);
                        }
                        else if(!launcherswitcher.switchedOn) {
                            sessiondispatcher.set_launcher_autohide_qt(false);
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
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("unity", "launcher-hide-mode") !== launcherswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("unity", "launcher-hide-mode");
                        if(sessiondispatcher.get_launcher_autohide_qt()) {
                            launcherswitcher.switchedOn = true;
                        }
                        else {
                            launcherswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }

        Row {
            spacing: 210
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Common.Label {
                    id: showdesktoplabel
                    width: 170
                    text: qsTr("Display desktop icon: ")//显示桌面图标：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: showdesktopswitcher
                    width: showdesktoplabel.width
                    onSwitched: {
                        if (showdesktopswitcher.switchedOn) {
                            sessiondispatcher.set_launcher_have_showdesktopicon_qt(true);
                        }
                        else if(!showdesktopswitcher.switchedOn) {
                            sessiondispatcher.set_launcher_have_showdesktopicon_qt(false);
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
                onClicked: {
                    sessiondispatcher.set_default_launcher_have_showdesktopicon_qt();
                    if (sessiondispatcher.get_launcher_have_showdesktopicon_qt()) {
                        showdesktopswitcher.switchedOn = true;
                    }
                    else {
                        showdesktopswitcher.switchedOn = false;
                    }
                }
            }
        }


        Row {
            spacing: 210
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Common.Label {
                    width: 170
                    text: qsTr("Launcher Transparency:")//启动器透明度：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: opacityslider
                    value: sessiondispatcher.get_launcher_transparency_qt()
                    onValueChanged: {
                        if(launcherthemepage.first_transparency_value ){  //系统初始化时会使value的值为0.2（最小值），需要过滤掉
                            sessiondispatcher.set_launcher_transparency_qt(opacityslider.value);
                        }
                        if(slider.value == 0.2) { //系统初始化时会使value的值为0.2（最小值），需要过滤掉
                            launcherthemepage.first_transparency_value = true;
                        }
                    }
                    width: 170
                    maximumValue: 8.0
                    minimumValue: 0.2
                    stepSize: 0.1
                    animated: true
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
                    if (sessiondispatcher.get_uk_default_setting_double("unity", "launcher-opacity") !== opacityslider.value) {
                        sessiondispatcher.restore_uk_default_setting("unity", "launcher-opacity");
                        opacityslider.value = sessiondispatcher.get_launcher_transparency_qt();
                    }
                }
            }
        }

        Row {
            spacing: 210
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.TipLabel {
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 170
                    text: qsTr("Icon Background:")//图标背景：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: backgroundcommbo
                    model: backgroundchoices
                    width: 170
                    onSelectedTextChanged: {
                        if (backgroundcommbo.selectedText == "all programs") {
                            sessiondispatcher.set_launcher_icon_colouring_qt(0);
                        }
                        else if (backgroundcommbo.selectedText == "only run app") {
                            sessiondispatcher.set_launcher_icon_colouring_qt(1);
                        }
                        else if (backgroundcommbo.selectedText == "no coloring") {
                            sessiondispatcher.set_launcher_icon_colouring_qt(2);
                        }
                        else if (backgroundcommbo.selectedText == "edge coloring") {
                            sessiondispatcher.set_launcher_icon_colouring_qt(3);
                        }
                        else if (backgroundcommbo.selectedText == "each workspace alternating coloring") {
                            sessiondispatcher.set_launcher_icon_colouring_qt(4);
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
                onClicked: {
                    var default_bg = sessiondispatcher.get_uk_default_setting_string("unity", "backlight-mode");
                    if(backgroundcommbo.selectedText !== default_bg) {
                        sessiondispatcher.restore_uk_default_setting("unity", "backlight-mode");
                        backgroundcommbo.selectedIndex = launcherthemepage.default_bg_index;
                    }
                }
            }
        }
    }//Column
}
