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
import AudioType 0.1

Rectangle {
    id: soundeffectspage
    width: parent.width
//    color:"transparent"
//    color: "#e4f2fc"
    height: 476

    property int scrollbar_z: 0
    property int play_pause: 0
    property int chooseyy_height: 200
    property string actiontitle: qsTr("Sound effect")//声音效果
    property string actiontext: qsTr("Selected music file name in the list box, do something such as audition, substitution and reduction.")//选中列表框中的音乐文件名，进行对应程序事件的试听、替换和还原。
    property int musiclist_num: 0
    property int current_index//当前主题的索引
//    property int default_index//系统默认主题的索引

    ListModel { id: choices }
    ListModel { id: musicmodel }

    function split_music_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    Component.onCompleted: {
        if (sessiondispatcher.get_login_music_enable_qt()) {
            soundswitcher.switchedOn = true;
        }
        else {
            soundswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_sound_event_enable_qt()) {
            eventswitcher.switchedOn = true;
        }
        else {
            eventswitcher.switchedOn = false;
        }
        if (sessiondispatcher.get_input_feedback_sounds_enable_qt()) {
            feedbackswitcher.switchedOn = true;
        }
        else {
            feedbackswitcher.switchedOn = false;
        }

        var index = 0;
        var soundlist = systemdispatcher.get_sound_themes_qt();
        var current_sound = sessiondispatcher.get_sound_theme_qt();
        var default_theme = sessiondispatcher.get_default_sound_string_qt("soundtheme");
        for(var i=0; i < soundlist.length; i++) {
            if (current_sound == soundlist[i]) {
                index = i;
                soundeffectspage.current_index = i;
            }
            if (default_theme == soundlist[i]) {
//                soundeffectspage.default_index = i;
            }
        }
        choices.clear();
        if (index == 0) {
            for(var j=0; j < soundlist.length; j++) {
                choices.append({"themetext": soundlist[j]});
            }
        }
        else {
            soundlist.unshift(current_sound);
            for(var k=0; k < soundlist.length; k++) {
                choices.append({"themetext": soundlist[k]});
                if (k!=0 && soundlist[k] == current_sound){
                    choices.remove(k);
                }
            }
        }

        musicmodel.clear();
        var musiclist=systemdispatcher.get_sounds_qt();
        musiclist_num = musiclist.length;
        for(var l=0; l < musiclist.length; l++) {
            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
        }
        if(30*musiclist.length<=chooseyy_height) {
            scrollbar_z = -1;
        }
        else {
            scrollbar_z = 1;
        }
    }


    QmlAudio{ id: song }

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
                 text: soundeffectspage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: soundeffectspage.actiontext
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

    Column{     //声音主题
        id:soundtheme
        spacing: 10
        z: 11
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 20
        }
        Row{
            spacing: 210
            Row {
                spacing: 20
                Image {
                    source: "../../img/icons/dot.png"
                    width: 14; height: 14
                    anchors.verticalCenter: parent.verticalCenter
                }

                Common.TipLabel {
                    z: 11
                    anchors.verticalCenter: parent.verticalCenter
                    kflag: "no"
                    showImage: "../../img/icons/cloud-gray.png"
                }
                Text {
                    id: trashlabel
                    width: 160
                    text: qsTr("Sound theme:")//声音主题：
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Common.ComboBox {
                    id: iconcombo
                    width : trashlabel.width//345
                    model: choices
                    onSelectedTextChanged: {
                        sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
                        musicmodel.clear();
                        var musiclist=systemdispatcher.get_sounds_qt();
                        for(var l=0; l < musiclist.length; l++) {
                            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
                        }
                        if(30*musiclist.length <= chooseyy_height) {
                            scrollbar_z = -1
                        }
                        else {
                            scrollbar_z = 1;
                        }
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        Row {
            spacing: 20
            Image {
                source: "../../img/icons/dot.png"
                width: 14; height: 14
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.TipLabel {
                z: 11
                anchors.verticalCenter: parent.verticalCenter
                kflag: "no"
                showImage: "../../img/icons/cloud-gray.png"
            }

            Text{
                text:qsTr("Login tone: ")//登录提示音：
                width: 160
                font.pixelSize: 12
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

        Row {
            spacing: 20
            Image {
                source: "../../img/icons/dot.png"
                width: 14; height: 14
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.TipLabel {
                z: 11
                anchors.verticalCenter: parent.verticalCenter
                kflag: "no"
                showImage: "../../img/icons/cloud-gray.png"
            }

            Text{
                text:qsTr("Event sounds:")//事件声音：
                width: 160
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: eventswitcher
                onSwitched: {
                    if (eventswitcher.switchedOn) {
                        sessiondispatcher.set_sound_event_enable_qt(true);
                    }
                    else if(!eventswitcher.switchedOn) {
                        sessiondispatcher.set_sound_event_enable_qt(false);
                    }
                }
            }
        }

        Row {
            spacing: 20
            Image {
                source: "../../img/icons/dot.png"
                width: 14; height: 14
                anchors.verticalCenter: parent.verticalCenter
            }

            Common.TipLabel {
                z: 11
                anchors.verticalCenter: parent.verticalCenter
                kflag: "no"
                showImage: "../../img/icons/cloud-gray.png"
            }

            Text{
                text:qsTr("Input feedback sounds:")//输入反馈声音：
                width: 160
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: feedbackswitcher
                onSwitched: {
                    if (feedbackswitcher.switchedOn) {
                        sessiondispatcher.set_input_feedback_sounds_enable_qt(true);
                    }
                    else if(!feedbackswitcher.switchedOn) {
                        sessiondispatcher.set_input_feedback_sounds_enable_qt(false);
                    }
                }
            }
        }
    }

//    Row {
//        spacing: 2
//        anchors {
//            top: soundtheme.bottom
//            topMargin: 20
//            right: parent.right
//            rightMargin: 95
//        }
//        Text {
//            id: listen
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            width: 50
//            text: qsTr("Listen")//试听
//        }
//        Text {
//            id: select
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            width: 50
//            text: qsTr("Replace")//替换
//        }
//        Text {
//            id: revoke
//            font.pixelSize: 12
//            color: "#7a7a7a"
//            width: 50
//            text: qsTr("Restore")//还原
//        }
//    }

//    Column{     //程序事件及选择框
//        id:chooseyy
//        spacing: 10
//        anchors {
//            top: soundtheme.bottom
//            topMargin: 20
//            left: parent.left
//            leftMargin: 60
//        }
//        Text{
//            id: eventtitle
//            width: 100
//            text: qsTr("System event tone: ")//系统事件提示音：
//            font.bold:true
//            color: "#383838"
//            font.pointSize: 10
//        }
//        Rectangle{
//            border.color: "#b9c5cc"
//            width: 720; height: 270
//            clip:true

//            Component{
//                id:cdelegat

//                Item{
//                    id:wrapper
//                    width: 700; height: 30
//                    Image {
//                        id:pickcher
//                        source: musicimage
//                        anchors {
//                            left: parent.left
//                            leftMargin: 10
//                            verticalCenter: parent.verticalCenter
//                        }
//                    }
//                    Text{
//                        id:listtext
//                        anchors.verticalCenter: parent.verticalCenter
//                        color: "grey"
//                        anchors.left: pickcher.right
//                        anchors.leftMargin: 5
//                        text: split_music_name(musicname)
//                    }
//                    Row{
//                        spacing: 40
//                        anchors{
//                            right: parent.right
//                            rightMargin: 30
//                            verticalCenter: parent.verticalCenter
//                        }

////                        z:soundz
//                        Rectangle{
//                            width: play.width;height: play.height; color: "transparent"
//                            Image {id:play;source: "../../img/icons/play.png"}
//                            Image {
//                                id: btnImg1
//                                anchors.fill: parent
//                                source: ""
//                            }
//                            MouseArea{
//                                anchors.fill:parent
//                                hoverEnabled: true
//                                onEntered: {
//                                    btnImg1.source = "../../img/icons/play_hover.png";
//                                }
//                                onPressed: {
//                                    btnImg1.source = "../../img/icons/play_hover.png";
//                                }
//                                //要判断松开是鼠标位置
//                                onReleased: {
//                                    btnImg1.source = "";
//                                }
//                                onExited: {
//                                    btnImg1.source = ""
//                                }
//                                onClicked: {
//                                    wrapper.ListView.view.currentIndex = index;
//                                    systemdispatcher.getMusicFileAbsolutePath(musicname);
//                                    if(play_pause==0){
//                                        song.play();
//                                        play_pause=1;
//                                    }
//                                    else if(play_pause == 1)
//                                    {
//                                        song.stop();
//                                        song.play();
//                                    }
////                                    systemdispatcher.listen_music(musicname);
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: next.width;height: next.height; color: "transparent"
//                            Image {id:next;source: "../../img/icons/folder.png"}
//                            Image {
//                                id: btnImg2
//                                anchors.fill: parent
//                                source: ""
//                            }
//                            MouseArea{
//                                anchors.fill:parent
//                                hoverEnabled: true
//                                onEntered: {
//                                    btnImg2.source = "../../img/icons/folder_hover.png";
//                                }
//                                onPressed: {
//                                    btnImg2.source = "../../img/icons/folder_hover.png";
//                                }
//                                //要判断松开是鼠标位置
//                                onReleased: {
//                                    btnImg2.source = "";
//                                }
//                                onExited: {
//                                    btnImg2.source = ""
//                                }
//                                onClicked: {
//                                    wrapper.ListView.view.currentIndex = index;
//                                    var selectedmusic = systemdispatcher.showSelectFileDialog("soundeffects");
//                                    systemdispatcher.getMusicFileAbsolutePath(selectedmusic);
//                                    systemdispatcher.set_homedir_qt();
//                                    systemdispatcher.replace_sound_file_qt(selectedmusic, split_music_name(musicname));
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: revoke.width;height: revoke.height; color: "transparent"
//                            Image {id:revoke;source: "../../img/icons/revoke.png"}
//                            Image {
//                                id: btnImg3
//                                anchors.fill: parent
//                                source: ""
//                            }
//                            MouseArea{
//                                anchors.fill:parent
//                                hoverEnabled: true
//                                onEntered: {
//                                    btnImg3.source = "../../img/icons/revoke_hover.png";
//                                }
//                                onPressed: {
//                                    btnImg3.source = "../../img/icons/revoke_hover.png";
//                                }
//                                //要判断松开是鼠标位置
//                                onReleased: {
//                                    btnImg3.source = "";
//                                }
//                                onExited: {
//                                    btnImg3.source = ""
//                                }
//                                onClicked: {
//                                    wrapper.ListView.view.currentIndex = index;
//                                    systemdispatcher.restore_sound_file_qt(split_music_name(musicname));
//                                }
//                            }
//                        }
//                    }
//                    Image {
//                        id: btnImg
//                        anchors.fill: parent
//                        source: ""
//                    }
//                    MouseArea{
//                        height: parent.height
//                        width: 360//宽度不能超过360,否则会覆盖试听音乐等等的按钮响应区域
//                        hoverEnabled: true
//                        onClicked: {
//                            wrapper.ListView.view.currentIndex = index;

//                        }
//                    }

//                }
//            }
//            Common.ScrollArea {
//                frame:false
//                anchors{
//                    top:parent.top
//                    topMargin: 1
//                    left:parent.left
//                    leftMargin: 1
//                }
//                height: parent.height-1
//                width: parent.width-1
//                Item {
//                    width: parent.width
//                    height: musiclist_num * 30 //列表长度
//                    //垃圾清理显示内容
//                    ListView{
//                        id:lisv
//                        anchors.fill: parent
//                        model:musicmodel
//                        delegate: cdelegat
//                        highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
//                        focus:true
//                    }
//                }//Item
//            }//ScrollArea
//        }
//    }
}
