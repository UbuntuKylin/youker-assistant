/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SessionType 0.1
//import SystemType 0.1
import "../common" as Common
import "../bars" as Bars
import AudioType 0.1
Rectangle {
    id: soundeffectspage
    property bool on: true
    width: parent.width
    color:"transparent"
    height: 475
//    property int soundz:0
    property int scrollbar_z: 0
    property int play_pause: 0
    property int chooseyy_height: 200
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property string default_sound: ""
    property string init_sound: ""
    property bool init_sound_flag: false
    property string actiontitle: "声音效果设置"
    property string actiontext: "选择声音主题，点击“确定”按钮;选中列表框中的音乐文件名,进行对应程序事件的试听、替换和还原。"

    property string selectedmusic: ""


    function split_music_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    Component.onCompleted: {
        soundeffectspage.init_sound_flag = false;
        if (sessiondispatcher.get_login_music_enable_qt())
            soundswitcher.switchedOn = true;
        else
            soundswitcher.switchedOn = false;
        soundeffectspage.default_sound = sessiondispatcher.get_sound_theme_qt();
        soundeffectspage.init_sound = soundeffectspage.default_sound;
        var soundlist = systemdispatcher.get_sound_themes_qt();
        var current_sound = sessiondispatcher.get_sound_theme_qt();
        soundlist.unshift(current_sound);
        choices.clear();
        for(var i=0; i < soundlist.length; i++) {
            choices.append({"themetext": soundlist[i]});
            if (i!=0 && soundlist[i] == current_sound)
                choices.remove(i);
        }
        musicmodel.clear();
        var musiclist=systemdispatcher.get_sounds_qt();
        for(var l=0; l < musiclist.length; l++) {
            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
        }
        if(30*musiclist.length<=chooseyy_height)
            scrollbar_z = -1;
        else
            scrollbar_z = 1;
    }


    ListModel {
        id: choices
        ListElement { themetext: "" }
    }
    ListModel {
        id: musicmodel
        ListElement { musicname: ""; musicimage: "" }
    }

    Image {     //背景图片
        id: background
        anchors.fill: parent
        source: "../../img/skin/bg-bottom-tab.png"
    }

    QmlAudio{
        id: song;
    }

    Column {
        spacing: 10
        anchors{
            top: parent.top;topMargin: 44
            left: parent.left;leftMargin: 80
        }
        Row {
            spacing: 50

            Text {
                 text: soundeffectspage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            //status picture
            Image {
                id: statusImage
                visible: false
                source: "../../img/toolWidget/finish.png"
                fillMode: "PreserveAspectFit"
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             text: soundeffectspage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    Column{     //声音主题
        id:soundtheme
        spacing: 10
        anchors {
            top: parent.top;topMargin: 120
            left: parent.left;leftMargin: 60
        }
        Text{
            text: qsTr("声音主题：")
            font.bold:true;color: "#383838"
            font.pointSize: 10
        }
        Row{
            spacing: 10
            Common.ComboBox {
                id: iconcombo
                width : 345
                model: choices
                onSelectedTextChanged: soundeffectspage.default_sound = selectedText
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Button {
                width: 95;height: 30
                hoverimage: "green2.png"
                text: "确定"
                onClicked: {
                    if (soundeffectspage.default_sound != iconcombo.selectedText) {
                        soundeffectspage.default_sound = iconcombo.selectedText;
                        sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
                        statusImage.visible = true;
                    }

                    soundeffectspage.init_sound_flag = true;
                    musicmodel.clear();
                    var musiclist=systemdispatcher.get_sounds_qt();
                    for(var l=0; l < musiclist.length; l++) {
                        musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
                    }
                    if(30*musiclist.length<=chooseyy_height)
                    {
                        scrollbar_z=-1
                    }
                    else scrollbar_z=1
                }
            }
            Common.Button {
                hoverimage: "blue2.png"
                text: "使用默认设置"
                width: 124
                height: 30
                onClicked: {
                    if (soundeffectspage.init_sound_flag == true) {
                        soundeffectspage.init_somainwindowund_flag = false;
                        systemdispatcher.restore_all_sound_file_qt(soundeffectspage.init_sound);
                        statusImage.visible = true;
                    }
                    else
                        sessiondispatcher.send_warningdialog_msg("友情提示：","当前主题已经为默认主题!");
                }
            }
//            Common.Button {
//                width: 95;height: 30
////                hoverimage: "ok.png"
//                text:"确定"
//                onClicked: {
//                    if (soundeffectspage.default_sound != iconcombo.selectedText) {
//                        soundeffectspage.default_sound = iconcombo.selectedText;
//                        sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
//                        statusImage.visible = true;
//                    }

//                    soundeffectspage.init_sound_flag = true;
//                    musicmodel.clear();
//                    var musiclist=systemdispatcher.get_sounds_qt();
//                    for(var l=0; l < musiclist.length; l++) {
//                        musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
//                    }
//                    if(30*musiclist.length<=chooseyy_height)
//                    {
//                        scrollbar_z=-1
//                    }
//                    else scrollbar_z=1
//                }
//            }
//            Common.Button {
////                hoverimage: "use.png"
//                text:"使用默认设置"
//                color1: "#57bffc"
//                color2: "#2384c8"
//                bordercolor: "#31a0ee"
//                width: 124
//                height: 30
//                onClicked: {
//                    if (soundeffectspage.init_sound_flag == true) {
//                        soundeffectspage.init_sound_flag = false;
//                        systemdispatcher.restore_all_sound_file_qt(soundeffectspage.init_sound);
//                        statusImage.visible = true;
//                    }
//                    else
//                        sessiondispatcher.send_warningdialog_msg("友情提示：","当前主题已经为默认主题!");
//                }
//            }

            Timer {
                     interval: 5000; running: true; repeat: true
                     onTriggered: statusImage.visible = false
                 }

        }

    }


    Column{     //程序事件及选择框
        id:chooseyy
        spacing: 10
        anchors {
            top: parent.top
            topMargin: 185
            left: parent.left
            leftMargin: 60
        }
        Row {
            spacing: 340
            Text{
                text: "程序事件："
                font.bold:true
                color: "#383838"
                font.pointSize: 10
            }
            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10
                Text {
                    id: listen
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text: "试听"
                }
                Text {
                    id: select
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text: "替换"
                }
                Text {
                    id: revoke
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text: "还原"
                }
            }

        }
        Rectangle{
            border.color: "#b9c5cc"
            width: 550; height: 200
            clip:true

            Component{
                id:cdelegat

                Item{
                    id:wrapper
                    width: 530; height: 30
                    Image {
                        id:pickcher
                        source: musicimage
                        anchors {
                            left: parent.left
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                    }
                    Text{
                        id:listtext
                        anchors.verticalCenter: parent.verticalCenter
                        color: "grey"
                        anchors.left: pickcher.right
                        anchors.leftMargin: 5
                        text: split_music_name(musicname)
                    }
                    Row{
                        spacing: 20
                        anchors{
                            right: parent.right
                            rightMargin: 40
                            verticalCenter: parent.verticalCenter
                        }

//                        z:soundz
                        Rectangle{
                            width: play.width;height: play.height; color: "transparent"
                            Image {id:play;source: "../../img/icons/play.png"}
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    wrapper.ListView.view.currentIndex = index;
                                    systemdispatcher.get_music_path(musicname);
//                                    systemdispatcher.get_music_path("/usr/share/youker-assistant-daemon/sound-theme/" + soundeffectspage.default_sound + "/stereo/" + musicname);
                                    if(play_pause==0){
                                        song.play();
                                        play_pause=1;
                                    }
                                    else if(play_pause == 1)
                                    {
                                        song.stop()
                                        song.play()
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: next.width;height: next.height; color: "transparent"
                            Image {id:next;source: "../../img/icons/folder.png"}
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    wrapper.ListView.view.currentIndex = index;
                                    soundeffectspage.selectedmusic = systemdispatcher.show_file_dialog("soundeffects");
                                    systemdispatcher.get_music_path(soundeffectspage.selectedmusic);
                                    systemdispatcher.set_homedir_qt();
                                    systemdispatcher.replace_sound_file_qt(soundeffectspage.selectedmusic, split_music_name(musicname));
                                }
                            }
                        }
                        Rectangle{
                            width: revoke.width;height: revoke.height; color: "transparent"
                            Image {id:revoke;source: "../../img/icons/revoke.png"}
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    wrapper.ListView.view.currentIndex = index;
                                    systemdispatcher.restore_sound_file_qt(split_music_name(musicname));
                                }
                            }
                        }
                    }
                    Image {
                        id: btnImg
                        anchors.fill: parent
                        source: ""
                    }
                    MouseArea{
//                        anchors.fill:parent
                        height: parent.height
                        width: 405
                        hoverEnabled: true
                        onClicked: {
                            wrapper.ListView.view.currentIndex = index;

                        }
                    }

                }
            }
            ListView{
                id:lisv
                anchors.fill: parent
                model:musicmodel
                delegate: cdelegat
                highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
                focus:true
            }


            Rectangle{
                id:scrollbar
                z:scrollbar_z
                anchors.right: parent.right
                anchors.rightMargin: 8
                height: parent.height
                width:4
                color: "lightgrey"
            }
            Rectangle{
                id: button
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 10
                z:scrollbar_z
                y: lisv.visibleArea.yPosition * (scrollbar.height+button.height)
//                height: lisv.visibleArea.heightRatio * scrollbar.height;
                height:45
                radius: 3
                smooth: true
                color: "white"
                border.color: "lightgrey"
                Column{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                }
                MouseArea {
                    id: mousearea
                    anchors.fill: button
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height
                    onMouseYChanged: {
                        lisv.contentY = button.y / (scrollbar.height+lisv.visibleArea.heightRatio * (scrollbar.height-lisv.visibleArea.heightRatio * scrollbar.height))* lisv.contentHeight
                    }
                }
            }
        }
    }

//左右分割线
    Rectangle{id:leftline ; x:650; y: 0; width:1 ; height:425; color:"#b9c5cc"}
    Rectangle{id:rightline ; x:652; y:0 ; width:1 ; height:425; color:"#fafcfe"}

    Row{
        spacing: 5
        anchors{
            left: parent.left
            top:parent.top
            leftMargin: 665
            topMargin: 25
        }
        Image {
            source: "../../img/icons/listen-pen.png"
        }
        Column{
            spacing: 5
            Text{
                text:qsTr("自定义声音主题")
                color: "#383838"
                font.pointSize: 10
                font.bold: true
            }
            Text{
                text:qsTr("您能根据喜好组合")
                font.pointSize: 10
                color: "#7a7a7a"
            }
            Text{
                text:qsTr("成专属声音主题")
                font.pointSize: 10
                color: "#7a7a7a"
            }
        }

    }
    Rectangle{id:topline ; x:652; y: 115; width:parent.width ; height:1; color:"#b9c5cc"}
    Rectangle{id:bottomline ; x:652;y:116 ;width:parent.width ; height:1; color:"#fafcfe"}

    Column
    {
        anchors {
            top: parent.top
            topMargin: 130
            left: parent.left
            leftMargin: 665
        }
        spacing: 20
        Text {
            text:qsTr("声音设置:")
            color: "#383838"
            font.pointSize: 10
            font.bold: true
        }
        Row {
            spacing: 20
            Text{
                text:qsTr("系统登录:")
                font.pointSize: 10
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: soundswitcher
                onSwitched: {
                    if (soundswitcher.switchedOn) {
                        sessiondispatcher.set_login_music_enable_qt(true);
                    }
                    else if(!soundswitcher.switchedOn) {
                        sessiondispatcher.set_login_music_enable_qt(false);
                    }
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
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        showok: false
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("返回")
//            button2Label: qsTr("确定")
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {
//            if (soundeffectspage.default_sound != soundcombo.selectedText) {
//                soundeffectspage.default_sound = soundcombo.selectedText;
//                sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
//            }
        }
    }
}
