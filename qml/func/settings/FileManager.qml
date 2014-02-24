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
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property int cursor_size: 24

    property string actiontitle: qsTr("File Manager")//文件管理器
    property string actiontext: qsTr("Manage the Nautilus file manager.")//管理Nautilus文件管理器
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }
}

//Rectangle {
//    id: filemanagerpage
//    property bool on: true
//    width: parent.width
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property int cursor_size: 24

//    property string actiontitle: qsTr("File Manager")//文件管理器
//    property string actiontext: qsTr("Manage the Nautilus file manager.")//管理Nautilus文件管理器
//    //背景
//    Image {
//        source: "../../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }

//    Component.onCompleted: {
////        if (sessiondispatcher.get_location_replace_pathbar_qt()) {
////            pathbarswitcher.switchedOn = true;
////        }
////        else {
////            pathbarswitcher.switchedOn = false;
////        }

////        if (sessiondispatcher.get_auto_mount_media_qt()) {
////            mediaswitcher.switchedOn = true;
////        }
////        else {
////            mediaswitcher.switchedOn = false;
////        }

////        if (sessiondispatcher.get_auto_open_folder_qt()) {
////            folderswitcher.switchedOn = true;
////        }
////        else {
////            folderswitcher.switchedOn = false;
////        }

////        if (sessiondispatcher.get_prompt_autorun_programs_qt()) {
////            programsswitcher.switchedOn = true;
////        }
////        else {
////            programsswitcher.switchedOn = false;
////        }
//    }

//    Column {
//        spacing: 10
//        anchors.top: parent.top
//        anchors.topMargin: 44
//        anchors.left: parent.left
//        anchors.leftMargin: 80
//        Row{
//            spacing: 50
//            Text {
//                 text: filemanagerpage.actiontitle
//                 font.bold: true
//                 font.pixelSize: 14
//                 color: "#383838"
//             }
//            Text {
//                id: showText
//                text: ""
//                font.pixelSize: 14
//                color: "#318d11"
//            }
//        }
//        Text {
//            text: filemanagerpage.actiontext
//            font.pixelSize: 12
//            color: "#7a7a7a"
//        }
//    }

//    Row {
//        id: titlebar
//        anchors{
//            left: parent.left
//            leftMargin: 40
//            top: parent.top
//            topMargin: 120
//        }
//        Text{
//            id: showtitle
//            text: qsTr("File manage and control")//文件管理控制
//            font.bold: true
//            font.pixelSize: 12
//            color: "#383838"
//        }
//        //横线
//        Common.Separator {
//            anchors.verticalCenter: parent.verticalCenter
//            width: filemanagerpage.width - showtitle.width - 40 * 2
//        }
//    }

//    Column {
//        anchors{
//            left: parent.left
//            leftMargin: 60
//            top: titlebar.bottom
//            topMargin: 10
//        }
//        spacing: 10
//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: pathbarlabel
//                    width: 250
//                    text: qsTr("Use the location entry instead of the pathbar: ")//路径输入框取代路径栏：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Switch {
//                    id: pathbarswitcher
//                    width: pathbarlabel.width
//                    onSwitched: {
//                        if (pathbarswitcher.switchedOn) {
//                            sessiondispatcher.set_location_replace_pathbar_qt(true);
//                        }
//                        else if(!pathbarswitcher.switchedOn) {
//                            sessiondispatcher.set_location_replace_pathbar_qt(false);
//                        }
//                    }
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("pathbar");
//                    if (sessiondispatcher.get_location_replace_pathbar_qt()) {
//                        pathbarswitcher.switchedOn = true;
//                    }
//                    else {
//                        pathbarswitcher.switchedOn = false;
//                    }
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: medialabel
//                    width: 250
//                    text: qsTr("Automatically mount media: ")//自动挂载媒体：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Switch {
//                    id: mediaswitcher
//                    width: medialabel.width
//                    onSwitched: {
//                        if (mediaswitcher.switchedOn) {
//                            sessiondispatcher.set_auto_mount_media_qt(true);
//                        }
//                        else if(!mediaswitcher.switchedOn) {
//                            sessiondispatcher.set_auto_mount_media_qt(false);
//                        }
//                    }
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("media");
//                    if (sessiondispatcher.get_auto_mount_media_qt()) {
//                        mediaswitcher.switchedOn = true;
//                    }
//                    else {
//                        mediaswitcher.switchedOn = false;
//                    }
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: folderlabel
//                    width: 250
//                    text: qsTr("Automatically open a folder: ")//自动打开文件夹：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Switch {
//                    id: folderswitcher
//                    width: folderlabel.width
//                    onSwitched: {
//                        if (folderswitcher.switchedOn) {
//                            sessiondispatcher.set_auto_open_folder_qt(true);
//                        }
//                        else if(!folderswitcher.switchedOn) {
//                            sessiondispatcher.set_auto_open_folder_qt(false);
//                        }
//                    }
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("folder");
//                    if (sessiondispatcher.get_auto_open_folder_qt()) {
//                        folderswitcher.switchedOn = true;
//                    }
//                    else {
//                        folderswitcher.switchedOn = false;
//                    }
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: programslabel
//                    width: 250
//                    text: qsTr("Prompt or autorun/autostart programs: ")//提示自动运行的程序：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Switch {
//                    id: programsswitcher
//                    width: programslabel.width
//                    onSwitched: {
//                        if (programsswitcher.switchedOn) {
//                            sessiondispatcher.set_prompt_autorun_programs_qt(true);
//                        }
//                        else if(!programsswitcher.switchedOn) {
//                            sessiondispatcher.set_prompt_autorun_programs_qt(false);
//                        }
//                    }
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("programs");
//                    if (sessiondispatcher.get_prompt_autorun_programs_qt()) {
//                        programsswitcher.switchedOn = true;
//                    }
//                    else {
//                        programsswitcher.switchedOn = false;
//                    }
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: thumbnailsizelabel
//                    width: 250
//                    text: qsTr("Thumbnail icon size (pixels): ")//缩略图图标尺寸（像素）：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Slider {
//                    id: iconsizeslider
//                    minimumValue: 16
//                    maximumValue: 512
//                    width: thumbnailsizelabel.width
//                    value: sessiondispatcher.get_thumbnail_icon_size_qt()
//                    onValueChanged: {
//                        sessiondispatcher.set_font_zoom_qt(iconsizeslider.value);
//                    }
//                    stepSize: 16
//                    animated: true
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("iconsize");
//                    iconsizeslider.value = sessiondispatcher.get_thumbnail_icon_size_qt();
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: thumbnailtimelabel
//                    width: 250
//                    text: qsTr("Thumbnail cache time (days): ")//缩略图缓存时间（天数）：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Slider {
//                    id: cachetimeslider
//                    minimumValue: -1
//                    maximumValue: 180
//                    width: thumbnailtimelabel.width
//                    value: sessiondispatcher.get_thumbnail_cache_time_qt()
//                    onValueChanged: {
//                        sessiondispatcher.set_font_zoom_qt(cachetimeslider.value);
//                    }
//                    stepSize: 1
//                    animated: true
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("cachetime");
//                    cachetimeslider.value = sessiondispatcher.get_thumbnail_cache_time_qt();
//                }
//            }
//        }

//        Row {
//            spacing: 200
//            Row {
//                spacing: 20
//                Common.Label {
//                    id: thumbnailmaxsizelabel
//                    width: 250
//                    text: qsTr("Maximum thumbnail cache size (MB): ")//最大缩略图缓存尺寸（MB）：
//                    font.pixelSize: 12
//                    color: "#383838"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Common.Slider {
//                    id: maxcacheslider
//                    minimumValue: -1
//                    maximumValue: 512
//                    width: thumbnailmaxsizelabel.width
//                    value: sessiondispatcher.get_thumbnail_cache_size_qt()
//                    onValueChanged: {
//                        sessiondispatcher.set_font_zoom_qt(maxcacheslider.value);
//                    }
//                    stepSize: 1
//                    animated: true
//                }
//            }
//            Common.Button {
//                hoverimage: "blue.png"
//                text: qsTr("Restore")//恢复默认
//                width: 94
//                height: 29
//                fontsize: 13
//                onClicked: {
//                    sessiondispatcher.set_default_filemanager_qt("maxsize");
//                    maxcacheslider.value = sessiondispatcher.get_thumbnail_cache_size_qt();
//                }
//            }
//        }


//    }//Column

//    //顶层工具栏
//    Bars.TopBar {
//        id: topBar
//        width: 28
//        height: 26
//        anchors.top: parent.top
//        anchors.topMargin: 40
//        anchors.left: parent.left
//        anchors.leftMargin: 40
//        opacity: 0.9
//        onButtonClicked: {
//            var num = sessiondispatcher.get_page_num();
//            if (num == 0) {
//                pageStack.push(homepage);
//            }
//            else if (num == 3) {
//                pageStack.push(systemset);
//            }
//            else if (num == 4) {
//                pageStack.push(functioncollection);
//            }
//        }
//    }
//    //底层工具栏
//    Bars.ToolBar {
//        id: toolBar
//        showok: false
//        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//        onQuitBtnClicked: {
//            var num = sessiondispatcher.get_page_num();
//            if (num == 0) {
//                pageStack.push(homepage);
//            }
//            else if (num == 3) {
//                pageStack.push(systemset);
//            }
//            else if (num == 4) {
//                pageStack.push(functioncollection);
//            }
//        }
//    }
//}
