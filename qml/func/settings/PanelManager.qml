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
    id: panelmanagerpage
    width: parent.width
    height: 476

    property int blur_mode

    property string actiontitle: qsTr("Dash & Panel")//搜索和面板
    property string actiontext: qsTr("Manage Dash and Panel menu settings.")//管理Dash搜索和面板菜单的设置
    property int default_time_index
    property int default_power_index
    property bool first_slider_value: false //系统初始化时会使value的值为0.2，需要过滤掉

    property bool battery_exists: false//判断是否存在电池

    ListModel { id: datechoices }
    ListModel { id: powerchoices }

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        panelmanagerpage.battery_exists = sessiondispatcher.judge_power_is_exists_qt();
        if(panelmanagerpage.battery_exists) {
            battery_icon.visible = true;
            battery_percentage.visible = true;
            battery_time.visible = true;
        }
        else {
            battery_icon.visible = false;
            battery_percentage.visible = false;
            battery_time.visible = false;
        }


        panelmanagerpage.blur_mode = sessiondispatcher.get_dash_blur_experimental_qt();
        var timelist = sessiondispatcher.get_all_time_format_qt();
        var cur_format = sessiondispatcher.get_time_format_qt();
        var default_format = sessiondispatcher.get_uk_default_setting_string("datetime", "time-format");
        var new_list = new Array();
        for(var i=0; i < timelist.length; i++) {
            if(timelist[i] !== cur_format) {
                new_list.push(timelist[i]);
            }
        }
        new_list.unshift(cur_format);
        datechoices.clear();
        for(var j=0; j < new_list.length; j++) {
            datechoices.append({"text": new_list[j]});
            if (default_format === new_list[j]) {
                panelmanagerpage.default_time_index = j;
            }
        }



        if (sessiondispatcher.get_show_seconds_qt()) {
            secondswitcher.switchedOn = true;
        }
        else {
            secondswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_show_week_qt()) {
            weekswitcher.switchedOn = true;
        }
        else {
            weekswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_show_date_qt()) {
            dateswitcher.switchedOn = true;

        }
        else {
            dateswitcher.switchedOn = false;
        }


        var powerlist = sessiondispatcher.get_all_power_icon_policy_qt();
        var cur_power = sessiondispatcher.get_power_icon_policy_qt();
        var default_power = sessiondispatcher.get_uk_default_setting_string("power", "icon-policy");
        var new_list2 = new Array();
        for(var m=0; m < powerlist.length; m++) {
            if(powerlist[m] !== cur_power) {
                new_list2.push(powerlist[m]);
            }
        }
        new_list2.unshift(cur_power);
        powerchoices.clear();
        for(var n=0; n < new_list2.length; n++) {
            powerchoices.append({"text": new_list2[n]});
            if (default_power === new_list2[n]) {
                panelmanagerpage.default_power_index = n;
            }
        }


        if (sessiondispatcher.get_show_power_percentage_qt()) {
            percentageswitcher.switchedOn = true;
        }
        else {
            percentageswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_show_power_time_qt()) {
            timeswitcher.switchedOn = true;
        }
        else {
            timeswitcher.switchedOn = false;
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
                 text: panelmanagerpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: panelmanagerpage.actiontext
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
            spacing: 83//230
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Common.Label {
                    width: 160
                    text: qsTr("Dash background blur type:")//搜索框背景模糊类型：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 134
                    Common.CheckBox {
                        id: smartbox
                        titleName: qsTr("Smart blur")//活动模糊
                        checked: (panelmanagerpage.blur_mode == 2) ? true : false
                        flag: "radio"
                        onClicked: {
                            if (smartbox.checked == true) {
                                if(panelmanagerpage.blur_mode != 2) {
                                    panelmanagerpage.blur_mode = 2;
                                    sessiondispatcher.set_dash_blur_experimental_qt(2);
                                }
                            }
                        }
                    }
                    Common.CheckBox {
                        id: staticbox
                        titleName: qsTr("Static blur")//静态模糊
                        checked: (panelmanagerpage.blur_mode == 1) ? true : false
                        flag: "radio"
                        onClicked: {
                            if (staticbox.checked == true) {
                                if(panelmanagerpage.blur_mode != 1) {
                                    panelmanagerpage.blur_mode = 1;
                                    sessiondispatcher.set_dash_blur_experimental_qt(1);
                                }
                            }
                        }
                    }
                    Common.CheckBox {
                        id: nonbox
                        titleName: qsTr("Clear")//非模糊
                        checked: (panelmanagerpage.blur_mode == 0) ? true : false
                        flag: "radio"
                        onClicked: {
                            if (nonbox.checked == true) {
                                if(panelmanagerpage.blur_mode != 0) {
                                    panelmanagerpage.blur_mode = 0;
                                    sessiondispatcher.set_dash_blur_experimental_qt(0);
                                }
                            }
                        }
                    }
                }
            }

            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    var cur_type;
                    if (smartbox.checked) {
                        cur_type = 2;
                    }
                    if (staticbox.checked) {
                        cur_type = 1;
                    }
                    if (nonbox.checked) {
                        cur_type = 0;
                    }
                    if (sessiondispatcher.get_uk_default_setting_int("unity", "dash-blur-experimental") !== cur_type) {
                        sessiondispatcher.restore_uk_default_setting("unity", "dash-blur-experimental");
                        panelmanagerpage.blur_mode = sessiondispatcher.get_dash_blur_experimental_qt();
                        if(panelmanagerpage.blur_mode === 2) {
                            smartbox.checked = true;
                        }
                        else if(panelmanagerpage.blur_mode === 1) {
                            staticbox.checked = true;
                        }
                        else {
                            nonbox.checked = true;
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Common.Label {
                    width: 160
                    text: qsTr("Panel Transparency:")//面板透明度：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: slider
                    value: sessiondispatcher.get_panel_transparency_qt()
                    onValueChanged: {
                        if(panelmanagerpage.first_slider_value ){  //系统初始化时会使value的值为0.2（最小值），需要过滤掉
                            sessiondispatcher.set_panel_transparency_qt(slider.value);
                        }
                        if(slider.value == 0.2) { //系统初始化时会使value的值为0.2（最小值），需要过滤掉
                            panelmanagerpage.first_slider_value = true;
                        }
                    }
                    width: 160
                    maximumValue: 8.0
                    minimumValue: 0.2
                    stepSize: 0.1
                    animated: true
                }
            }

            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if (sessiondispatcher.get_uk_default_setting_double("unity", "panel-opacity") !== slider.value) {
                        sessiondispatcher.restore_uk_default_setting("unity", "panel-opacity");
                        slider.value = sessiondispatcher.get_panel_transparency_qt();
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Date & time format:")//日期时间格式：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: datecombo
                    model: datechoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_time_format_qt(datecombo.selectedText);
                    }
                }
            }
            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    var default_format = sessiondispatcher.get_uk_default_setting_string("datetime", "time-format");
                    if(datecombo.selectedText !== default_format) {
                        sessiondispatcher.restore_uk_default_setting("datetime", "time-format");
                        datecombo.selectedIndex = panelmanagerpage.default_time_index;
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Display seconds:")//显示秒数：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: secondswitcher
                    width: 160
                    onSwitched: {
                        if (secondswitcher.switchedOn) {
                            sessiondispatcher.set_show_seconds_qt(true);
                        }
                        else if(!secondswitcher.switchedOn) {
                            sessiondispatcher.set_show_seconds_qt(false);
                        }
                    }
                }
            }

            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("datetime", "show-seconds") !== secondswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("datetime", "show-seconds");
                        if (sessiondispatcher.get_show_seconds_qt()) {
                            secondswitcher.switchedOn = true;
                        }
                        else {
                            secondswitcher.switchedOn = false;
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
                    text: qsTr("Display week:")//显示星期：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: weekswitcher
                    width: 160
                    onSwitched: {
                        if (weekswitcher.switchedOn) {
                            sessiondispatcher.set_show_week_qt(true);
                        }
                        else if(!weekswitcher.switchedOn) {
                            sessiondispatcher.set_show_week_qt(false);
                        }
                    }
                }
            }

            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("datetime", "show-day") !== weekswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("datetime", "show-day");
                        if (sessiondispatcher.get_show_week_qt()) {
                            weekswitcher.switchedOn = true;
                        }
                        else {
                            weekswitcher.switchedOn = false;
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Show date:")//显示日期：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: dateswitcher
                    width: 160
                    onSwitched: {
                        if (dateswitcher.switchedOn) {
                            sessiondispatcher.set_show_date_qt(true);
                        }
                        else if(!dateswitcher.switchedOn) {
                            sessiondispatcher.set_show_date_qt(false);
                        }
                    }
                }
            }

            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("datetime", "show-date") !== dateswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("datetime", "show-date");
                        if (sessiondispatcher.get_show_date_qt()) {
                            dateswitcher.switchedOn = true;
                        }
                        else {
                            dateswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }



        //# 电源
//        # present:电源总是可见     charge:当机器充电/放电时可见         never:总是不可见
        Row {
            id: battery_icon
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Display battery icon:")//显示电池图标：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: powercombo
                    model: powerchoices
                    width: 160
                    onSelectedTextChanged: {
                        sessiondispatcher.set_power_icon_policy_qt(powercombo.selectedText);
                    }
                }
            }
            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(panelmanagerpage.battery_exists) {
                        var default_power = sessiondispatcher.get_uk_default_setting_string("power", "icon-policy");
                        if(powercombo.selectedText !== default_power) {
                            sessiondispatcher.restore_uk_default_setting("power", "icon-policy");
                            powercombo.selectedIndex = panelmanagerpage.default_power_index;
                        }
                    }
                }
            }
        }

        Row {
            id: battery_percentage
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Display battery percentage:")//显示电池百分比：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: percentageswitcher
                    width: 160
                    onSwitched: {
                        if (percentageswitcher.switchedOn) {
                            sessiondispatcher.set_show_power_percentage_qt(true);
                        }
                        else if(!percentageswitcher.switchedOn) {
                            sessiondispatcher.set_show_power_percentage_qt(false);
                        }
                    }
                }
            }
            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("power", "show-percentage") !== percentageswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("power", "show-percentage");
                        if (sessiondispatcher.get_show_power_percentage_qt()) {
                            percentageswitcher.switchedOn = true;
                        }
                        else {
                            percentageswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }

        Row {
            id: battery_time
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
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    width: 160
                    text: qsTr("Display battery remaining time:")//显示电池电量时间：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: timeswitcher
                    width: 160
                    onSwitched: {
                        if (timeswitcher.switchedOn) {
                            sessiondispatcher.set_show_power_time_qt(true);
                        }
                        else if(!timeswitcher.switchedOn) {
                            sessiondispatcher.set_show_power_time_qt(false);
                        }
                    }
                }
            }
            Common.Button {
//                hoverimage: "blue.png"
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("power", "show-time") !== timeswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("power", "show-time");
                        if (sessiondispatcher.get_show_power_time_qt()) {
                            timeswitcher.switchedOn = true;
                        }
                        else {
                            timeswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }
    }
}
