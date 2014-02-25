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
import AudioType 0.1
Rectangle {
    id: soundeffectspage
    property bool on: true
    width: parent.width
    color:"transparent"
    height: 475
    property int scrollbar_z: 0
    property int play_pause: 0
    property int chooseyy_height: 200
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property string default_sound: ""
    property string actiontitle: qsTr("Sound effect")//声音效果
    property string actiontext: qsTr("Selected music file name in the list box, do something such as audition, substitution and reduction.")//选中列表框中的音乐文件名，进行对应程序事件的试听、替换和还原。
    property int musiclist_num: 0

    property int current_index//当前主题的索引
    property int default_index//系统默认主题的索引

    property string selectedmusic: ""
    property string selected_sound_theme: ""//存放用户选择确认后的主题


    function split_music_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    Component.onCompleted: {
        if (sessiondispatcher.get_login_music_enable_qt())
            soundswitcher.switchedOn = true;
        else
            soundswitcher.switchedOn = false;
        var soundlist = systemdispatcher.get_sound_themes_qt();
        var current_sound = sessiondispatcher.get_sound_theme_qt();
        var default_theme = sessiondispatcher.get_default_sound_string_qt("soundtheme");
        showText.text = qsTr("[ Current Sound Theme: ") + current_sound + " ]";//[ 当前音效主题是：
        soundeffectspage.selected_sound_theme = current_sound;
        choices.clear();
        if(current_sound == default_theme) {
            for(var i=0; i < soundlist.length; i++) {
                choices.append({"themetext": soundlist[i]});
                if (soundlist[i] == current_sound) {
                    soundeffectspage.current_index = i;
                    soundeffectspage.default_index = i;
                }
            }
        }
        else {
            for(var j=0; j < soundlist.length; j++) {
                choices.append({"themetext": soundlist[j]});
                if (soundlist[j] == current_sound) {
                    soundeffectspage.current_index = j;
                }
                else if (soundlist[j] == default_theme) {
                    soundeffectspage.default_index = j;
                }
            }
        }
        iconcombo.selectedIndex = soundeffectspage.current_index;
        musicmodel.clear();
        var musiclist=systemdispatcher.get_sounds_qt();
        musiclist_num = musiclist.length;
        for(var l=0; l < musiclist.length; l++) {
            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
        }
        if(30*musiclist.length<=chooseyy_height)
            scrollbar_z = -1;
        else
            scrollbar_z = 1;
    }


    ListModel { id: choices }
    ListModel { id: musicmodel }

    Image {     //背景图片
        id: background
        anchors.fill: parent
        source: "../../img/skin/bg-middle.png"
    }

    QmlAudio{
        id: song
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
            Text {
                id: showText
                text: ""
                font.pixelSize: 14
                color: "#318d11"
            }
            //status picture
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            width: 650 - 80 - 15//左边区域总宽度-左边space-右边space
            text: soundeffectspage.actiontext
            wrapMode: Text.WordWrap
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
            text: qsTr("Sound theme:")//声音主题：
            font.bold:true;color: "#383838"
            font.pointSize: 10
        }
        Row{
            spacing: 100
            Common.ComboBox {
                id: iconcombo
                width : 345
                model: choices
                onSelectedTextChanged: {
                    showText.text = qsTr("[ Current Sound Theme: ") + iconcombo.selectedText + " ]";//[ 当前音效主题是：
                    soundeffectspage.selected_sound_theme = iconcombo.selectedText;
                    sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
                    statusImage.visible = true;

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
//            Common.Button {
//                width: 95;height: 30
//                hoverimage: "green.png"
//                text: qsTr("OK")//确定
//                onClicked: {
//                    if (soundeffectspage.selected_sound_theme != iconcombo.selectedText) {
//                        soundeffectspage.selected_sound_theme = iconcombo.selectedText;
//                        showText.text = qsTr("[ Current Sound Theme: ") + iconcombo.selectedText + " ]";//[ 当前音效主题是：
//                        soundeffectspage.selected_sound_theme = iconcombo.selectedText;
//                        sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
//                        statusImage.visible = true;

//                        musicmodel.clear();
//                        var musiclist=systemdispatcher.get_sounds_qt();
//                        for(var l=0; l < musiclist.length; l++) {
//                            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
//                        }
//                        if(30*musiclist.length<=chooseyy_height) {
//                            scrollbar_z = -1
//                        }
//                        else {
//                            scrollbar_z = 1;
//                        }
//                    }
//                }
//            }
            Common.Button {
                hoverimage: "blue.png"
                text: qsTr("Restore")//恢复默认
                width: 105
                height: 30
                onClicked: {
                    sessiondispatcher.set_default_sound_qt("soundtheme");
                    var defaulttheme = sessiondispatcher.get_sound_theme_qt();
                    showText.text = qsTr("[ Current Sound Theme: ") + defaulttheme + " ]";//[ 当前音效主题是：
                    //attention：这里貌似combobox的顺序已经发生变化了。
                    iconcombo.selectedIndex = soundeffectspage.default_index;
//                    iconcombo.selectedText = defaulttheme;
//                    console.log("111");
//                    console.log(soundeffectspage.default_index);
                    statusImage.visible = true;
//                    sessiondispatcher.set_default_sound_qt("soundtheme");
//                    var defaulttheme = sessiondispatcher.get_sound_theme_qt();
//                    showText.text = qsTr("[ Current Sound Theme: ") + defaulttheme + " ]";//[ 当前音效主题是：
//                    iconcombo.selectedText = defaulttheme;
//                    statusImage.visible = true;
                }
            }
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
            spacing: 270
            Text{
                id: eventtitle
                width: 100
                text: qsTr("System event tone: ")//系统事件提示音：
                font.bold:true
                color: "#383838"
                font.pointSize: 10
            }
            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 2
                Text {
                    id: listen
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 50
                    text: qsTr("Listen")//试听
                }
                Text {
                    id: select
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 50
                    text: qsTr("Replace")//替换
                }
                Text {
                    id: revoke
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 50
                    text: qsTr("Restore")//还原
                }
            }

        }
        Rectangle{
            border.color: "#b9c5cc"
            width: 550; height: 205
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
                        spacing: 40
                        anchors{
                            right: parent.right
                            rightMargin: 30
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
                                    systemdispatcher.getMusicFileAbsolutePath(musicname);
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
                                    soundeffectspage.selectedmusic = systemdispatcher.showSelectFileDialog("soundeffects");
                                    systemdispatcher.getMusicFileAbsolutePath(soundeffectspage.selectedmusic);
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
                        width: 360//宽度不能超过360,否则会覆盖试听音乐等等的按钮响应区域
                        hoverEnabled: true
                        onClicked: {
                            wrapper.ListView.view.currentIndex = index;

                        }
                    }

                }
            }
            Common.ScrollArea {
                frame:false
                anchors{
                    top:parent.top
                    topMargin: 1
                    left:parent.left
                    leftMargin: 1
                }
                height: parent.height-1
                width: parent.width-1
                Item {
                    width: parent.width
                    height: musiclist_num * 30 //列表长度
                    //垃圾清理显示内容
                    ListView{
                        id:lisv
                        anchors.fill: parent
                        model:musicmodel
                        delegate: cdelegat
                        highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
                        focus:true
                    }
                }//Item
            }//ScrollArea
        }
    }

//左右分割线
    Rectangle{id:leftline ; x:650; y: 0; width:1 ; height:425; color:"#b9c5cc"}
    Rectangle{id:rightline ; x:652; y:0 ; width:1 ; height:425; color:"#fafcfe"}

    Row{
        spacing: 7
        anchors{
            left: parent.left
            top:parent.top
            leftMargin: 665
            topMargin: 25
        }
        Image {
            width: 52
            height: 52
            source: "../../img/icons/listen-pen.png"
        }
//        Column{
//            spacing: 5
        Text{
            anchors.verticalCenter: parent.verticalCenter
            text:qsTr("Custom Sound Theme")//自定义声音主题
            width: soundeffectspage.width- 665 - 52 - 15
            wrapMode: Text.WordWrap
            color: "#383838"
            font.pointSize: 10
            font.bold: true
        }
    }
    Rectangle{id:topline ; x:652; y: 110; width:parent.width ; height:1; color:"#b9c5cc"}
    Rectangle{id:bottomline ; x:652;y:111 ;width:parent.width ; height:1; color:"#fafcfe"}

    Column
    {
        anchors {
            top: parent.top
            topMargin: 150
            left: parent.left
            leftMargin: 665
        }
        spacing: 20
        Text {
            text:qsTr("Sound settings:")//声音设置：
            color: "#383838"
            font.pointSize: 10
            font.bold: true
        }
        Row {
            spacing: 20
            Text{
                text:qsTr("Login tone: ")//登录提示音：
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
