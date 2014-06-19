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
    property bool first_slider_value: false //系统初始化时会使value的值为0.2，需要过滤掉

    ListModel { id: datechoices }
    ListModel { id: powerchoices }
    property int dateindex: 0

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        panelmanagerpage.blur_mode = sessiondispatcher.get_dash_blur_experimental_qt();
        var index = 0;
        var timelist = sessiondispatcher.get_all_time_format_qt();
        var cur_format = sessiondispatcher.get_time_format_qt();
        for(var i=0; i < timelist.length; i++) {
            if (cur_format == timelist[i]) {
                index = i;
            }
        }
        datechoices.clear();
        if (index == 0) {
            for(var j=0; j < timelist.length; j++) {
                datechoices.append({"text": timelist[j]});
            }
        }
        else {
            timelist.unshift(cur_format);
            for(var k=0; k < timelist.length; k++) {
                datechoices.append({"text": timelist[k]});
                if (k!=0 && timelist[k] == cur_format){
                    datechoices.remove(k);
                }
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


        var index2 = 0;
        var powerlist = sessiondispatcher.get_all_power_icon_policy_qt();
        var cur_power = sessiondispatcher.get_power_icon_policy_qt();
        for(var x=0; x < powerlist.length; x++) {
            if (cur_power == powerlist[x]) {
                index2 = x;
            }
        }
        powerchoices.clear();
        if (index2 == 0) {
            for(var y=0; y < powerlist.length; y++) {
                powerchoices.append({"text": powerlist[y]});
            }
        }
        else {
            powerlist.unshift(cur_power);
            for(var z=0; z < powerlist.length; z++) {
                powerchoices.append({"text": powerlist[z]});
                if (z!=0 && cur_power == powerlist[z]){
                    powerchoices.remove(z);
                }
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

//            Common.Button {
////                hoverimage: "blue.png"
//                picNormal: "../../img/icons/button12.png"
//                picHover: "../../img/icons/button12-hover.png"
//                picPressed: "../../img/icons/button12-hover.png"
//                fontcolor:"#ffffff"
//                fontsize: 12
//                width: 100; height: 28
//                text: qsTr("Restore")//恢复默认
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: {
//                    sessiondispatcher.set_default_system_qt("control-button-position");
//                    var default_type = sessiondispatcher.get_window_button_align_qt();
//                    windowmanagerpage.position_mode = default_type;
//                    if(default_type == "left") {
//                        leftbox.checked = true;
//                    }
//                    else if(default_type == "right") {
//                        rightbox.checked = true;
//                    }
//                }
//            }
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

//            Common.Button {
////                hoverimage: "blue.png"
//                picNormal: "../../img/icons/button12.png"
//                picHover: "../../img/icons/button12-hover.png"
//                picPressed: "../../img/icons/button12-hover.png"
//                fontcolor:"#ffffff"
//                fontsize: 12
//                width: 100; height: 28
//                text: qsTr("Restore")//恢复默认
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: {
//                    sessiondispatcher.set_default_system_qt("menu-with-icons");
//                    if (sessiondispatcher.get_menus_have_icons_qt()) {
//                        menuswitcher.switchedOn = true;
//                    }
//                    else {
//                        menuswitcher.switchedOn = false;
//                    }
//                }
//            }
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

//            Common.Button {
////                hoverimage: "blue.png"
//                picNormal: "../../img/icons/button12.png"
//                picHover: "../../img/icons/button12-hover.png"
//                picPressed: "../../img/icons/button12-hover.png"
//                fontcolor:"#ffffff"
//                fontsize: 12
//                width: 100; height: 28
//                text: qsTr("Restore")//恢复默认
//                onClicked: {
//                    sessiondispatcher.set_default_system_qt("double-action");
//                    doublecombo.selectedIndex = windowmanagerpage.double_default_index;
//                }
//            }
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

//            Common.Button {
////                hoverimage: "blue.png"
//                picNormal: "../../img/icons/button12.png"
//                picHover: "../../img/icons/button12-hover.png"
//                picPressed: "../../img/icons/button12-hover.png"
//                fontcolor:"#ffffff"
//                fontsize: 12
//                width: 100; height: 28
//                text: qsTr("Restore")//恢复默认
//                onClicked: {
//                    sessiondispatcher.set_default_system_qt("middle-action");
//                    middlecombo.selectedIndex = windowmanagerpage.middle_default_index;
//                }
//            }
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

//            Common.Button {
////                hoverimage: "blue.png"
//                picNormal: "../../img/icons/button12.png"
//                picHover: "../../img/icons/button12-hover.png"
//                picPressed: "../../img/icons/button12-hover.png"
//                fontcolor:"#ffffff"
//                fontsize: 12
//                width: 100; height: 28
//                text: qsTr("Restore")//恢复默认
//                onClicked: {
//                    sessiondispatcher.set_default_system_qt("right-action");
//                    rightcombo.selectedIndex = windowmanagerpage.right_default_index;
//                }
//            }
        }



        //# 电源
//        # present:电源总是可见     charge:当机器充电/放电时可见         never:总是不可见
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
        }
    }
}
