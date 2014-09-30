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
    id: desktopiconsetpage
    width: parent.width
    height: 476
//    color: "#eeedf0"

    property string current_desktop
    property int default_index//系统默认主题的索引
    property string actiontitle: qsTr("Desktop Icons")//桌面图标设置
    property string actiontext: qsTr("Set the desktop icon theme and the visibility of desktop icons.")//设置桌面图标主题和桌面图标的可见性

    ListModel { id: choices }

    //使用云配置后，控件状态根据配置发生相应的变化
//    Connections
//    {
//        target: sessiondispatcher
//        onTellDownloadCloudConfToQML: {
//            if(download == "icon_theme") {
//                var iconlist = sessiondispatcher.get_icon_themes_qt();
//                var current_icon_theme = sessiondispatcher.get_icon_theme_qt();
//                var new_list = new Array();
//                for(var m=0; m < iconlist.length; m++) {
//                    if(iconlist[m] !== current_icon_theme) {
//                        new_list.push(iconlist[m]);
//                    }
//                }
//                new_list.unshift(current_icon_theme);
//                for(var j=0; j < new_list.length; j++) {
//                    if (current_icon_theme === new_list[j]) {
//                        iconcombo.selectedIndex  = j;
//                        break;
//                    }
//                }
//            }
//            else if(download == "show_desktop_icons") {
//                if (sessiondispatcher.get_show_desktop_icons_qt()) {
//                    iconswitcher.switchedOn = true;
//                }
//                else {
//                    iconswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "show_homefolder") {
//                if (sessiondispatcher.get_show_homefolder_qt()) {
//                    folderswitcher.switchedOn = true;
//                }
//                else {
//                    folderswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "show_network") {
//                if (sessiondispatcher.get_show_network_qt()) {
//                    networkswitcher.switchedOn = true;
//                }
//                else {
//                    networkswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "show_trash") {
//                if (sessiondispatcher.get_show_trash_qt()) {
//                    trashswitcher.switchedOn = true;
//                }
//                else {
//                    trashswitcher.switchedOn = false;
//                }
//            }
//            else if(download == "show_devices") {
//                if (sessiondispatcher.get_show_devices_qt()) {
//                    deviceswitcher.switchedOn = true;
//                }
//                else {
//                    deviceswitcher.switchedOn = false;
//                }
//            }
//        }
//    }

    Component.onCompleted: {
        desktopiconsetpage.current_desktop =  sessiondispatcher.access_current_desktop_qt();
        if (desktopiconsetpage.current_desktop == "Unity") {
            var iconlist = sessiondispatcher.get_icon_themes_qt();
            var current_icon_theme = sessiondispatcher.get_icon_theme_qt();
            var default_theme = sessiondispatcher.get_uk_default_setting_string("icon", "icon-theme");
            var new_list = new Array();
            for(var j=0; j < iconlist.length; j++) {
                if(iconlist[j] !== current_icon_theme) {
                    new_list.push(iconlist[j]);
                }
            }
            new_list.unshift(current_icon_theme);
            choices.clear();
            for(var k=0; k < new_list.length; k++) {
                choices.append({"text": new_list[k]});
                if (default_theme === new_list[k]) {
                    desktopiconsetpage.default_index = k;
                }
            }

            if (sessiondispatcher.get_show_desktop_icons_qt()) {
                iconswitcher.switchedOn = true;
            }
            else {
                iconswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_homefolder_qt()) {
                folderswitcher.switchedOn = true;
            }
            else {
                folderswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_network_qt()) {
                networkswitcher.switchedOn = true;
            }
            else {
                networkswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_trash_qt()) {
                trashswitcher.switchedOn = true;
            }
            else {
                trashswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_devices_qt()) {
                deviceswitcher.switchedOn = true;
            }
            else {
                deviceswitcher.switchedOn = false;
            }
        }
        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
            if (sessiondispatcher.get_show_cinnamon_desktop_icons_qt()) {
                iconswitcher.switchedOn = true;
            }
            else {
                iconswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_cinnamon_computer_qt()) {
                computerswitcher.switchedOn = true;
            }
            else {
                computerswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_cinnamon_homefolder_qt()) {
                folderswitcher.switchedOn = true;
            }
            else {
                folderswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_cinnamon_network_qt()) {
                networkswitcher.switchedOn = true;
            }
            else {
                networkswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_cinnamon_trash_qt()) {
                trashswitcher.switchedOn = true;
            }
            else {
                trashswitcher.switchedOn = false;
            }

            if (sessiondispatcher.get_show_cinnamon_devices_qt()) {
                deviceswitcher.switchedOn = true;
            }
            else {
                deviceswitcher.switchedOn = false;
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
                text: desktopiconsetpage.actiontitle
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: desktopiconsetpage.actiontext
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
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 40
        }
        spacing: 10
//        z: 11
        Row {
            visible: (desktopiconsetpage.current_desktop == "Unity") ? true : false
            spacing: 150
//            z: 11
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: iconthemelabel
                    width: 170
                    text: qsTr("Icon theme:")//图标主题：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Common.ComboBox {
                    id: iconcombo
                    model: choices
                    width: 220
                    onSelectedTextChanged: {
                        sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    var default_theme = sessiondispatcher.get_uk_default_setting_string("icon", "icon-theme");
                    if(iconcombo.selectedText !== default_theme) {
                        sessiondispatcher.restore_uk_default_setting("icon", "icon-theme");
                        iconcombo.selectedIndex = desktopiconsetpage.default_index;
                    }
                }
            }
        }

        Row {
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: desktopiconlabel
                    width: 170
                    text: qsTr("Show Desktop Icons: ")//显示桌面图标：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: iconswitcher
                    width: 220//desktopiconlabel.width
                    onSwitched: {
                        if (desktopiconsetpage.current_desktop == "Unity") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_desktop_icons_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_desktop_icons_qt(false);
                            }
                        }
                        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_desktop_icons_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_desktop_icons_qt(false);
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if (desktopiconsetpage.current_desktop == "Unity") {
                        if(sessiondispatcher.get_uk_default_setting_bool("icon", "show-desktop-icons") !== iconswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("icon", "show-desktop-icons");
                            if (sessiondispatcher.get_show_desktop_icons_qt()) {
                                iconswitcher.switchedOn = true;
                            }
                            else {
                                iconswitcher.switchedOn = false;
                            }
                        }
                    }
                    else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                        if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "show-desktop-icons") !== iconswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "show-desktop-icons");
                            if (sessiondispatcher.get_show_cinnamon_desktop_icons_qt()) {
                                iconswitcher.switchedOn = true;
                            }
                            else {
                                iconswitcher.switchedOn = false;
                            }
                        }
                    }
                }
            }
        }

        Row {
            visible: (desktopiconsetpage.current_desktop == "X-Cinnamon") ? true : false
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: computericonlabel
                    width: 170
                    text: qsTr("Computer: ")//计算机：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: computerswitcher
                    width: 220
                    onSwitched: {
                        if (computerswitcher.switchedOn) {
                            sessiondispatcher.set_show_cinnamon_computer_qt(true);
                        }
                        else if(!computerswitcher.switchedOn) {
                            sessiondispatcher.set_show_cinnamon_computer_qt(false);
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "computer-icon-visible") !== computerswitcher.switchedOn) {
                        sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "computer-icon-visible");
                        if (sessiondispatcher.get_show_cinnamon_computer_qt()) {
                            computerswitcher.switchedOn = true;
                        }
                        else {
                            computerswitcher.switchedOn = false;
                        }
                    }
                }
            }
        }


        Row {
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: homefolderlabel
                    width: 170
                    text: qsTr("Home Folder: ")//主文件夹：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: folderswitcher
                    width: 220//homefolderlabel.width
                    onSwitched: {
                        if (desktopiconsetpage.current_desktop == "Unity") {
                            if (folderswitcher.switchedOn) {
                                sessiondispatcher.set_show_homefolder_qt(true);
                            }
                            else if(!folderswitcher.switchedOn) {
                                sessiondispatcher.set_show_homefolder_qt(false);
                            }
                        }
                        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_homefolder_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_homefolder_qt(false);
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if (desktopiconsetpage.current_desktop == "Unity") {
                        if(sessiondispatcher.get_uk_default_setting_bool("icon", "home-icon-visible") !== folderswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("icon", "home-icon-visible");
                            if (sessiondispatcher.get_show_homefolder_qt()) {
                                folderswitcher.switchedOn = true;
                            }
                            else {
                                folderswitcher.switchedOn = false;
                            }
                        }
                    }
                    else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                        if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "home-icon-visible") !== folderswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "home-icon-visible");
                            if (sessiondispatcher.get_show_cinnamon_homefolder_qt()) {
                                folderswitcher.switchedOn = true;
                            }
                            else {
                                folderswitcher.switchedOn = false;
                            }
                        }
                    }
                }
            }
        }

        Row {
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: networklabel
                    width: 170
                    text: qsTr("Network: ")//网络：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: networkswitcher
                    width: 220//networklabel.width
                    onSwitched: {
                        if (desktopiconsetpage.current_desktop == "Unity") {
                            if (networkswitcher.switchedOn) {
                                sessiondispatcher.set_show_network_qt(true);
                            }
                            else if(!networkswitcher.switchedOn) {
                                sessiondispatcher.set_show_network_qt(false);
                            }
                        }
                        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_network_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_network_qt(false);
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if (desktopiconsetpage.current_desktop == "Unity") {
                        if(sessiondispatcher.get_uk_default_setting_bool("icon", "network-icon-visible") !== networkswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("icon", "network-icon-visible");
                            if (sessiondispatcher.get_show_network_qt()) {
                                networkswitcher.switchedOn = true;
                            }
                            else {
                                networkswitcher.switchedOn = false;
                            }
                        }
                    }
                    else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                        if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "network-icon-visible") !== networkswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "network-icon-visible");
                            if (sessiondispatcher.get_show_cinnamon_network_qt()) {
                                networkswitcher.switchedOn = true;
                            }
                            else {
                                networkswitcher.switchedOn = false;
                            }
                        }
                    }
                }
            }
        }

        Row {
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: trashlabel
                    width: 170
                    text: qsTr("Trash : ")//回收站：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: trashswitcher
                    width: 220//trashlabel.width
                    onSwitched: {
                        if (desktopiconsetpage.current_desktop == "Unity") {
                            if (trashswitcher.switchedOn) {
                                sessiondispatcher.set_show_trash_qt(true);
                            }
                            else if(!trashswitcher.switchedOn) {
                                sessiondispatcher.set_show_trash_qt(false);
                            }
                        }
                        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_trash_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_trash_qt(false);
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if (desktopiconsetpage.current_desktop == "Unity") {
                        if(sessiondispatcher.get_uk_default_setting_bool("icon", "trash-icon-visible") !== trashswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("icon", "trash-icon-visible");
                            if (sessiondispatcher.get_show_trash_qt()) {
                                trashswitcher.switchedOn = true;
                            }
                            else {
                                trashswitcher.switchedOn = false;
                            }
                        }
                    }
                    else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                        if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "trash-icon-visible") !== trashswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "trash-icon-visible");
                            if (sessiondispatcher.get_show_cinnamon_trash_qt()) {
                                trashswitcher.switchedOn = true;
                            }
                            else {
                                trashswitcher.switchedOn = false;
                            }
                        }
                    }
                }
            }
        }

        Row {
            spacing: 150
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }
//                Common.TipLabel {
//                    anchors.verticalCenter: parent.verticalCenter
//                    kflag: "yes"
//                    showImage: "../../img/icons/cloud-light.png"
//                }
                Common.Label {
                    id: devicelabel
                    width: 170
                    text: qsTr("Mounted Volumes: ")//已经挂载卷标：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: deviceswitcher
                    width: 220//devicelabel.width
                    onSwitched: {
                        if (desktopiconsetpage.current_desktop == "Unity") {
                            if (deviceswitcher.switchedOn) {
                                sessiondispatcher.set_show_devices_qt(true);
                            }
                            else if(!deviceswitcher.switchedOn) {
                                sessiondispatcher.set_show_devices_qt(false);
                            }
                        }
                        else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                            if (iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_devices_qt(true);
                            }
                            else if(!iconswitcher.switchedOn) {
                                sessiondispatcher.set_show_cinnamon_devices_qt(false);
                            }
                        }
                    }
                }
            }

            Common.Button {
                picNormal: "../../img/icons/button12-lightblue-long.png"
                picHover: "../../img/icons/button12-lightblue-long-hover.png"
                picPressed: "../../img/icons/button12-lightblue-long-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 100; height: 28
                text: qsTr("Restore")//恢复默认
                onClicked: {
                    if (desktopiconsetpage.current_desktop == "Unity") {
                        if(sessiondispatcher.get_uk_default_setting_bool("icon", "volumes-visible") !== deviceswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("icon", "volumes-visible");
                            if (sessiondispatcher.get_show_devices_qt()) {
                                deviceswitcher.switchedOn = true;
                            }
                            else {
                                deviceswitcher.switchedOn = false;
                            }
                        }
                    }
                    else if (desktopiconsetpage.current_desktop == "X-Cinnamon") {
                        if(sessiondispatcher.get_uk_default_setting_bool("cinnamon-icon", "volumes-visible") !== deviceswitcher.switchedOn) {
                            sessiondispatcher.restore_uk_default_setting("cinnamon-icon", "volumes-visible");
                            if (sessiondispatcher.get_show_cinnamon_devices_qt()) {
                                deviceswitcher.switchedOn = true;
                            }
                            else {
                                deviceswitcher.switchedOn = false;
                            }
                        }
                    }
                }
            }
        }
    }//Column
}
