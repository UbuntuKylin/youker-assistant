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
    id: touchpadsetpage
    width: parent.width
    height: 476
    color: "#e4f2fc"

    property string scrollbars_mode: ""
    property string touchscrolling_mode: ""
    property string actiontitle: qsTr("Touchpad settings")//触摸板设置
    property string actiontext: qsTr("By setting the relevant properties of your touchpad, make the operation more convenient.")//通过调整您触摸板的相关设置，使操作更加便捷。
    //背景
//    Image {
//        source: "../../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }

    //使用云配置后，控件状态根据配置发生相应的变化
    Connections
    {
        target: sessiondispatcher
        onTellDownloadCloudConfToQML: {
            if(download == "touchpad_enable") {
                if (sessiondispatcher.get_touchpad_enable_qt()) {
                    touchpadswitcher.switchedOn = true;
                }
                else {
                    touchpadswitcher.switchedOn = false;
                }
            }
            else if(download == "touch_horizontal_scrolling") {
                if (sessiondispatcher.get_touchscrolling_use_horizontal_qt()) {
                    horizontalswitcher.switchedOn = true;
                }
                else {
                    horizontalswitcher.switchedOn = false;
                }
            }
            else if(download == "type_scroll_bar") {
                touchpadsetpage.scrollbars_mode = sessiondispatcher.get_scrollbars_mode_qt();
                if (touchpadsetpage.scrollbars_mode == "overlay-auto") {
                    overlay.checked = true;
                }
                else if(touchpadsetpage.scrollbars_mode == "normal") {
                    legacy.checked = true;
                }
            }
            else if(download == "touchpad_scrolling_mode") {
                touchpadsetpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();
                if (touchpadsetpage.touchscrolling_mode == "edge-scrolling") {
                    edge.checked = true;
                }
                else if(touchpadsetpage.touchscrolling_mode == "two-finger-scrolling") {
                    twofinger.checked = true;
                }
            }
        }
    }

    Component.onCompleted: {
        touchpadsetpage.scrollbars_mode = sessiondispatcher.get_scrollbars_mode_qt();
        touchpadsetpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();//edge-scrolling
        if (sessiondispatcher.get_touchpad_enable_qt()) {
            touchpadswitcher.switchedOn = true;
        }
        else {
            touchpadswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_touchscrolling_use_horizontal_qt()) {
            horizontalswitcher.switchedOn = true;
        }
        else {
            horizontalswitcher.switchedOn = false;
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
                pageStack.pop();
//                var num = sessiondispatcher.get_page_num();
//                if (num == 0) {
//                    pageStack.push(homepage);
//                }
//                else if (num == 1) {
//                    pageStack.push(systemmessage);
//                }
//                else if (num == 2) {
//                    pageStack.push(clearrubbish);
//                }
//                else if (num == 3) {
//                    pageStack.push(systemset);
//                }
//                else if (num == 4) {
//                    pageStack.push(functioncollection);
//                }
            }
        }
        Column {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                text: touchpadsetpage.actiontitle
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: touchpadsetpage.width - 80 - 20
                text: touchpadsetpage.actiontext
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
        spacing: 30
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 50
        }
        z: 11
        Row {
            spacing: 200
            z: 11
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
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Enable/Disable touchpad: ")//启用/禁用触摸板：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
                Common.Switch {
                    id: touchpadswitcher
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    onSwitched: {
                        if (touchpadswitcher.switchedOn) {
                            sessiondispatcher.set_touchpad_enable_qt(true);
                        }
                        else if(!touchpadswitcher.switchedOn) {
                            sessiondispatcher.set_touchpad_enable_qt(false);
                        }
                    }
                }
            }

            Common.Button {
    //            hoverimage: "blue.png"
                picNormal: "../../img/icons/button12-blue.png"
                picHover: "../../img/icons/button12-blue-hover.png"
                picPressed: "../../img/icons/button12-blue-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("touchpad", "touchpad-enabled") !== touchpadswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("touchpad", "touchpad-enabled");
                        if (sessiondispatcher.get_touchpad_enable_qt()) {
                            touchpadswitcher.switchedOn = true;
                        }
                        else {
                            touchpadswitcher.switchedOn = false;
                        }
                    }
//                    sessiondispatcher.set_default_system_qt("touchpad-enabled");//启用禁用触摸板
//                    if (sessiondispatcher.get_touchpad_enable_qt()) {
//                        touchpadswitcher.switchedOn = true;
//                    }
//                    else {
//                        touchpadswitcher.switchedOn = false;
//                    }
                }
            }
        }

        Row {
            spacing: 200
            Row {
                id: horizontalscroll
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
                    text: qsTr("Touchpad horizontal scroll: ")//触摸板横向滚动：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: horizontalswitcher
                    width: 160
                    anchors.verticalCenter: parent.verticalCenter
                    onSwitched: {
                        if (horizontalswitcher.switchedOn) {
                            sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
                        }
                        else if(!horizontalswitcher.switchedOn) {
                            sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
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
                    if(sessiondispatcher.get_uk_default_setting_bool("touchpad", "horiz-scroll-enabled") !== horizontalswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("touchpad", "horiz-scroll-enabled");
                        if (sessiondispatcher.get_touchscrolling_use_horizontal_qt()) {
                            horizontalswitcher.switchedOn = true;
                        }
                        else {
                            horizontalswitcher.switchedOn = false;
                        }
                    }
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
                    text: qsTr("Scrollbar type: ")//滚动条类型：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
        //        GroupBox {
        //            anchors.verticalCenter: parent.verticalCenter
        //                title: qsTr("触摸板滚动条触发方式:")
        //            adjustToContentSize: true
                    Common.ButtonRow {
                        exclusive: true//控制是否联动
                        spacing: 134
                        Common.CheckBox {
                            id:overlay
                            titleName: qsTr("Features Type") //特色类型
                            checked: (touchpadsetpage.scrollbars_mode == "overlay-auto") ? true : false
                            flag: "radio"
                            onClicked: {
                                if (overlay.checked == true) {
                                    if(touchpadsetpage.scrollbars_mode != "overlay-auto") {
                                        sessiondispatcher.set_scrollbars_mode_overlay_qt();
                                        touchpadsetpage.scrollbars_mode = "overlay-auto";
                                    }
                                }
                            }
                        }
                        Common.CheckBox {
                            id: legacy
                            titleName: qsTr("Standard Type")  //标准类型
                            checked: (touchpadsetpage.scrollbars_mode == "normal") ? true : false
                            flag: "radio"
                            onClicked: {
                                if (legacy.checked == true) {
                                    if(touchpadsetpage.scrollbars_mode != "normal") {
                                        sessiondispatcher.set_scrollbars_mode_legacy_qt();
                                        touchpadsetpage.scrollbars_mode = "normal";
                                    }
                                }
                            }
                        }
        //            }
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
                    var cur_type;
                    if (overlay.checked) {
                        cur_type = "overlay-auto";
                    }
                    else {
                        cur_type = "normal";
                    }
                    if (sessiondispatcher.get_uk_default_setting_string("touchpad", "scrollbar-mode") !== cur_type) {
                        sessiondispatcher.restore_uk_default_setting("touchpad", "scrollbar-mode");
                        var default_type = sessiondispatcher.get_scrollbars_mode_qt();
                        if(default_type === "overlay-auto") {
                            overlay.checked = true;
                        }
                        else if(default_type === "normal") {
                            legacy.checked = true;
                        }
                    }
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
                id: scrollstyle
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
                    text: qsTr("Touchpad scroll trigger mode: ")//触摸板滚动触发方式：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
        //        GroupBox {
        //            anchors.verticalCenter: parent.verticalCenter
        //                title: qsTr("触摸板滚动模式:")
        //            adjustToContentSize: true
                    Common.ButtonRow {
                        exclusive: true//控制是否联动
                        spacing: 134
                        Common.CheckBox {
                            id:edge
                            titleName: qsTr("Edgemotion")//边缘触发
                            checked: (touchpadsetpage.touchscrolling_mode == "edge-scrolling") ? true : false
                            flag: "radio"
                            onClicked: {
                                if (edge.checked == true) {
                                    if(touchpadsetpage.touchscrolling_mode != "edge-scrolling") {
                                        sessiondispatcher.set_touchscrolling_mode_edge_qt();
                                        touchpadsetpage.touchscrolling_mode = "edge-scrolling";
                                    }
                                }
                            }
                        }
                        Common.CheckBox {
                            id: twofinger
                            titleName: qsTr("Twofinger Scroll")//双指触发
                            checked: (touchpadsetpage.touchscrolling_mode == "two-finger-scrolling") ? true : false
                            flag: "radio"
                            onClicked: {
                                if (twofinger.checked == true) {
                                    if(touchpadsetpage.touchscrolling_mode != "two-finger-scrolling") {
                                        sessiondispatcher.set_touchscrolling_mode_twofinger_qt();
                                        touchpadsetpage.touchscrolling_mode = "two-finger-scrolling";
                                    }
                                }
                            }
                        }
        //            }
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
                    var cur_mode;
                    if (edge.checked) {
                        cur_mode = "edge-scrolling";
                    }
                    else {
                        cur_mode = "two-finger-scrolling";
                    }
                    if (sessiondispatcher.get_uk_default_setting_string("touchpad", "scroll-method") !== cur_mode) {
                        sessiondispatcher.restore_uk_default_setting("touchpad", "scroll-method");
                        var default_mode = sessiondispatcher.get_touchscrolling_mode_qt();
                        if(default_mode === "edge-scrolling") {
                            edge.checked = true;
                        }
                        else if(default_mode === "two-finger-scrolling") {
                            twofinger.checked = true;
                        }
                    }
//                    sessiondispatcher.set_default_system_qt("scroll-method");//触摸板滚动条触发方式
//                    var default_mode = sessiondispatcher.get_touchscrolling_mode_qt();
//                    if(default_mode == "edge-scrolling") {
//                        edge.checked = true;
//                    }
//                    else if(default_mode == "two-finger-scrolling") {
//                        twofinger.checked = true;
//                    }
                }
            }
        }
    }
}
