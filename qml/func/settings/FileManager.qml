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
    id: filemanagerpage
    width: parent.width
    height: 475

    property string actiontitle: qsTr("File Manager")//文件管理器
    property string actiontext: qsTr("Manage the Nautilus file manager.")//管理Nautilus文件管理器

    property bool first_icon_size: false
    property bool first_cache_time: false
    property bool first_cache_size: false
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    //使用云配置后，控件状态根据配置发生相应的变化
    Connections
    {
        target: sessiondispatcher
        onTellDownloadCloudConfToQML: {
            if(download == "location_replace_pathbar") {
                if (sessiondispatcher.get_location_replace_pathbar_qt()) {
                    pathbarswitcher.switchedOn = true;
                }
                else {
                    pathbarswitcher.switchedOn = false;
                }
            }
            else if(download == "auto_mount_media") {
                if (sessiondispatcher.get_auto_mount_media_qt()) {
                    mediaswitcher.switchedOn = true;
                }
                else {
                    mediaswitcher.switchedOn = false;
                }
            }
            else if(download == "auto_open_folder") {
                if (sessiondispatcher.get_auto_open_folder_qt()) {
                    folderswitcher.switchedOn = true;
                }
                else {
                    folderswitcher.switchedOn = false;
                }
            }
            else if(download == "prompt_autorun_programs") {
                if (sessiondispatcher.get_prompt_autorun_programs_qt()) {
                    programsswitcher.switchedOn = true;
                }
                else {
                    programsswitcher.switchedOn = false;
                }
            }
            else if(download == "thumbnail_icon_size") {
                iconsizeslider.value = sessiondispatcher.get_thumbnail_icon_size_qt();
            }
            else if(download == "thumbnail_cache_time") {
                cachetimeslider.value = sessiondispatcher.get_thumbnail_cache_time_qt();
            }
            else if(download == "thumbnail_cache_size") {
                maxcacheslider.value = sessiondispatcher.get_thumbnail_cache_size_qt();
            }
        }
    }

    Component.onCompleted: {
        if (sessiondispatcher.get_location_replace_pathbar_qt()) {
            pathbarswitcher.switchedOn = true;
        }
        else {
            pathbarswitcher.switchedOn = false;
        }

        if (sessiondispatcher.get_auto_mount_media_qt()) {
            mediaswitcher.switchedOn = true;
        }
        else {
            mediaswitcher.switchedOn = false;
        }

        if (sessiondispatcher.get_auto_open_folder_qt()) {
            folderswitcher.switchedOn = true;
        }
        else {
            folderswitcher.switchedOn = false;
        }

        if (sessiondispatcher.get_prompt_autorun_programs_qt()) {
            programsswitcher.switchedOn = true;
        }
        else {
            programsswitcher.switchedOn = false;
        }
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
                 text: filemanagerpage.actiontitle
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
            text: filemanagerpage.actiontext
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
            text: qsTr("File manage and control")//文件管理控制
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: filemanagerpage.width - showtitle.width - 40 * 2
        }
    }

    Column {
        anchors{
            left: parent.left
            leftMargin: 60
            top: titlebar.bottom
            topMargin: 10
        }
        spacing: 10
        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: pathbarlabel
                    width: 270
                    text: qsTr("Use the location entry instead of the pathbar: ")//路径输入框取代路径栏：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: pathbarswitcher
                    width: 200
                    onSwitched: {
                        if (pathbarswitcher.switchedOn) {
                            sessiondispatcher.set_location_replace_pathbar_qt(true);
                        }
                        else if(!pathbarswitcher.switchedOn) {
                            sessiondispatcher.set_location_replace_pathbar_qt(false);
                        }
                    }
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
                        sessiondispatcher.set_default_filemanager_qt("pathbar");
                        if (sessiondispatcher.get_location_replace_pathbar_qt()) {
                            pathbarswitcher.switchedOn = true;
                        }
                        else {
                            pathbarswitcher.switchedOn = false;
                        }
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: medialabel
                    width: 270
                    text: qsTr("Automatically mount media: ")//自动挂载媒体：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: mediaswitcher
                    width: 200
                    onSwitched: {
                        if (mediaswitcher.switchedOn) {
                            sessiondispatcher.set_auto_mount_media_qt(true);
                        }
                        else if(!mediaswitcher.switchedOn) {
                            sessiondispatcher.set_auto_mount_media_qt(false);
                        }
                    }
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
                        sessiondispatcher.set_default_filemanager_qt("media");
                        if (sessiondispatcher.get_auto_mount_media_qt()) {
                            mediaswitcher.switchedOn = true;
                        }
                        else {
                            mediaswitcher.switchedOn = false;
                        }
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: folderlabel
                    width: 270
                    text: qsTr("Automatically open a folder: ")//自动打开文件夹：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: folderswitcher
                    width: 200
                    onSwitched: {
                        if (folderswitcher.switchedOn) {
                            sessiondispatcher.set_auto_open_folder_qt(true);
                        }
                        else if(!folderswitcher.switchedOn) {
                            sessiondispatcher.set_auto_open_folder_qt(false);
                        }
                    }
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
                        sessiondispatcher.set_default_filemanager_qt("folder");
                        if (sessiondispatcher.get_auto_open_folder_qt()) {
                            folderswitcher.switchedOn = true;
                        }
                        else {
                            folderswitcher.switchedOn = false;
                        }
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: programslabel
                    width: 270
                    text: qsTr("Prompt or autorun/autostart programs: ")//提示自动运行的程序：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Switch {
                    id: programsswitcher
                    width: 200
                    onSwitched: {
                        if (programsswitcher.switchedOn) {
                            sessiondispatcher.set_prompt_autorun_programs_qt(true);
                        }
                        else if(!programsswitcher.switchedOn) {
                            sessiondispatcher.set_prompt_autorun_programs_qt(false);
                        }
                    }
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
                        sessiondispatcher.set_default_filemanager_qt("programs");
                        if (sessiondispatcher.get_prompt_autorun_programs_qt()) {
                            programsswitcher.switchedOn = true;
                        }
                        else {
                            programsswitcher.switchedOn = false;
                        }
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: thumbnailsizelabel
                    width: 270
                    text: qsTr("Thumbnail icon size (pixels): ")//缩略图图标尺寸（像素）：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: iconsizeslider
                    minimumValue: 16
                    maximumValue: 512
                    width: 200
                    value: sessiondispatcher.get_thumbnail_icon_size_qt()
                    onValueChanged: {
                        if(filemanagerpage.first_icon_size ) {
                            sessiondispatcher.set_thumbnail_icon_size_qt(iconsizeslider.value);
                        }
                        if(iconsizeslider.value == 16) {//系统初始化时value的值为16（最小值），需要过滤掉
                            filemanagerpage.first_icon_size = true;
                        }
                    }
                    stepSize: 16
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
                        sessiondispatcher.set_default_filemanager_qt("iconsize");
                        iconsizeslider.value = sessiondispatcher.get_thumbnail_icon_size_qt();
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: thumbnailtimelabel
                    width: 270
                    text: qsTr("Thumbnail cache time (days): ")//缩略图缓存时间（天数）：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: cachetimeslider
                    minimumValue: -1
                    maximumValue: 180
                    width: 200
                    value: sessiondispatcher.get_thumbnail_cache_time_qt()
                    onValueChanged: {
                        if(filemanagerpage.first_cache_time ) {
                            sessiondispatcher.set_thumbnail_cache_time_qt(cachetimeslider.value);
                        }
                        if(iconsizeslider.value == -1) {//系统初始化时value的值为16（最小值），需要过滤掉
                            filemanagerpage.first_cache_time = true;
                        }
                    }
                    stepSize: 1
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
                        sessiondispatcher.set_default_filemanager_qt("cachetime");
                        cachetimeslider.value = sessiondispatcher.get_thumbnail_cache_time_qt();
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }

        Row {
            spacing: 164
            Row {
                spacing: 20
                Common.Label {
                    id: thumbnailmaxsizelabel
                    width: 270
                    text: qsTr("Maximum thumbnail cache size (MB): ")//最大缩略图缓存尺寸（MB）：
                    font.pixelSize: 12
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.Slider {
                    id: maxcacheslider
                    minimumValue: -1
                    maximumValue: 512
                    width: 200
                    value: sessiondispatcher.get_thumbnail_cache_size_qt()
                    onValueChanged: {
                        if(filemanagerpage.first_cache_size ) {
                            sessiondispatcher.set_thumbnail_cache_size_qt(maxcacheslider.value);
                        }
                        if(iconsizeslider.value == -1) {//系统初始化时value的值为16（最小值），需要过滤掉
                            filemanagerpage.first_cache_size = true;
                        }
                    }
                    stepSize: 1
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
                        sessiondispatcher.set_default_filemanager_qt("maxsize");
                        maxcacheslider.value = sessiondispatcher.get_thumbnail_cache_size_qt();
                    }
                }
                Image {
                    width: 16; height: 16
                    source: "../../img/icons/cloud.png"
                }
            }
        }


    }//Column

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
