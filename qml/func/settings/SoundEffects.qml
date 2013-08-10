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
        console.log("sound......................................");
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

//    Connections {strlist
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "SoundEffects") {
//                if (soundeffectspage.default_sound != soundcombo.selectedText) {
//                    console.log("111");
//                    soundeffectspage.default_sound = soundcombo.selectedText;
//                    sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
//                }
//                else
//                    console.log("222");
//            }
//        }
//    }


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
                hoverimage: "ok.png"
                onClicked: {
                    console.log("sound ok");
                    if (soundeffectspage.default_sound != iconcombo.selectedText) {
                        console.log("111");
                        soundeffectspage.default_sound = iconcombo.selectedText;
                        sessiondispatcher.set_sound_theme_qt(iconcombo.selectedText);
                        statusImage.visible = true;
                    }
                    else
                        console.log("222");

                    soundeffectspage.init_sound_flag = true;
                    musicmodel.clear();
                    var musiclist=systemdispatcher.get_sounds_qt();
                    console.log(musiclist);
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
                hoverimage: "use.png"
                width: 124
                height: 30
                onClicked: {
                    if (soundeffectspage.init_sound_flag == true) {
                        soundeffectspage.init_sound_flag = false;
                        systemdispatcher.restore_all_sound_file_qt(soundeffectspage.init_sound);
                        statusImage.visible = true;
                    }
                    else
                        sessiondispatcher.send_warningdialog_msg("友情提示：","当前主题已经为默认主题!");
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
                            width: play.width;height: play.height
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
                            width: next.width;height: next.height
                            Image {id:next;source: "../../img/icons/folder.png"}
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    wrapper.ListView.view.currentIndex = index;
                                    soundeffectspage.selectedmusic = systemdispatcher.show_file_dialog("soundeffects");
                                    systemdispatcher.get_music_path(soundeffectspage.selectedmusic);
                                    systemdispatcher.replace_sound_file_qt(soundeffectspage.selectedmusic, split_music_name(musicname));
                                }
                            }
                        }
                        Rectangle{
                            width: revoke.width;height: revoke.height
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
//                        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//                        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onExited: {btnImg.source = ""/*;soundz=0*/}
                        onClicked: {
//                            soundz=1
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
                width:5
                color: "lightgrey"
            }
            Rectangle{
                id: button
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 12
                z:scrollbar_z
                y: lisv.visibleArea.yPosition * scrollbar.height
                height: lisv.visibleArea.heightRatio * scrollbar.height;
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
                        lisv.contentY = button.y / scrollbar.height * lisv.contentHeight
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
                        console.log("系统登录音乐on---------------");
                        sessiondispatcher.set_login_music_enable_qt(true);
                    }
                    else if(!soundswitcher.switchedOn) {
                        console.log("系统登录音乐off---------------");
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
//            console.log("sound ok");
//            if (soundeffectspage.default_sound != soundcombo.selectedText) {
//                console.log("111");
//                soundeffectspage.default_sound = soundcombo.selectedText;
//                sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
//            }
//            else
//                console.log("222");
        }
    }
}





//Rectangle {
//    id: soundeffectspage
//    property bool on: true
//    width: parent.width
//    color:"transparent"
//    height: 475
//    property int soundz:0
//    property int play_pause:0
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property string default_sound: ""
//    property string actiontitle: "声音效果设置"
//    property string actiontext: "选择声音主题，点击“确定”按钮;选中列表框中的音乐文件名,进行对应程序事件的播放、更换和还原。"

//    property string selectedmusic: ""

//    Component.onCompleted: {

//        if (sessiondispatcher.get_login_music_enable_qt())
//            soundswitcher.switchedOn = true;
//        else
//            soundswitcher.switchedOn = false;
//        soundeffectspage.default_sound = sessiondispatcher.get_sound_theme_qt();
//        var soundlist = sessiondispatcher.get_sound_themes_qt();
//        var current_sound = sessiondispatcher.get_sound_theme_qt();
//        soundlist.unshift(current_sound);
//        choices.clear();
//        for(var i=0; i < soundlist.length; i++) {
//            choices.append({"themetext": soundlist[i]});
//            if (i!=0 && soundlist[i] == current_sound)
//                choices.remove(i);
//        }
//        musicmodel.clear();
//        var musiclist=systemdispatcher.get_sounds_qt();
//        for(var l=0; l < musiclist.length; l++) {
//            musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
//        }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "SoundEffects") {
//                if (soundeffectspage.default_sound != soundcombo.selectedText) {
//                    console.log("111");
//                    soundeffectspage.default_sound = soundcombo.selectedText;
//                    sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
//                }
//                else
//                    console.log("222");
//            }
//        }
//    }


//    ListModel {
//        id: choices
//        ListElement { themetext: "" }
//    }
//    ListModel {
//        id: musicmodel
//        ListElement { musicname: ""; musicimage: "" }
//    }

//    Image {     //背景图片
//        id: background
//        anchors.fill: parent
//        source: "../../img/skin/bg-left.png"
//    }

//    QmlAudio{
//        id: song;
//    }

//    Column {
//        spacing: 10
//        anchors{
//            top: parent.top;topMargin: 44
//            left: parent.left;leftMargin: 80
//        }
//        Text {
//             text: soundeffectspage.actiontitle
//             font.bold: true
//             font.pixelSize: 14
//             color: "#383838"
//         }
//         Text {
//             text: soundeffectspage.actiontext
//             font.pixelSize: 12
//             color: "#7a7a7a"
//         }
//    }

//    Column{     //声音主题
//        id:soundtheme
//        spacing: 10
//        anchors {
//            top: parent.top;topMargin: 120
//            left: parent.left;leftMargin: 60
//        }
//        Text{
//            text: qsTr("声音主题：")
//            font.bold:true;color: "#383838"
//            font.pointSize: 10
//        }
//        Row{
//            spacing: 10
//            ComboBox {
//                id: iconcombo
//                width : 345
//                model: choices
//                onSelectedTextChanged: soundeffectspage.default_sound = selectedText
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Button {
//                width: 95;height: 30
//                hoverimage: "ok.png"
//                onClicked: {
//                    musicmodel.clear();
//                    var musiclist=systemdispatcher.get_sounds_qt();
//                    console.log(musiclist);
//                    for(var l=0; l < musiclist.length; l++) {
//                        musicmodel.append({"musicname": musiclist[l], "musicimage": "../../img/icons/broadcast.png"});
//                    }
//                }
//            }

//        }

//    }


//    Column{     //程序事件及选择框
//        id:chooseyy
//        spacing: 10
//        anchors {
//            top: parent.top
//            topMargin: 185
//            left: parent.left
//            leftMargin: 60
//        }
//        Text{
//            text: qsTr("程序事件：")
//            font.bold:true
//            color: "#383838"
//            font.pointSize: 10
//        }
//        Rectangle{
//            border.color: "#b9c5cc"
//            width: 550; height: 200
//            clip:true

//            Component{
//                id:cdelegat
//                Item{
//                    id:wrapper
//                    width: 530; height: 30
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
//                        text: musicname
//                    }
//                    Row{
//                        spacing: 20
//                        anchors{
//                            right: parent.right
//                            rightMargin: 40
//                            verticalCenter: parent.verticalCenter
//                        }

//                        z:soundz
//                        Rectangle{
//                            width: play.width;height: play.height
//                            Image {id:play;source: "../../img/icons/play.png"}
//                            MouseArea{
//                                anchors.fill:parent
//                                onClicked: {
//                                    console.log("lixiaing...........");
//                                    systemdispatcher.get_music_path("/usr/share/youker-assistant-daemon/sound-theme/" + soundeffectspage.default_sound + "/stereo/" + musicname);
//                                    if(play_pause==0){
//                                        console.log("lixiaing111...........");
//                                        song.play();
//                                        play_pause=1;
//                                    }
//                                    else if(play_pause == 1)
//                                    {
//                                        console.log("lixiaing222...........");
//                                        song.pause();
//                                        play_pause=0;
//                                    }
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: next.width;height: next.height
//                            Image {id:next;source: "../../img/icons/folder.png"}
//                            MouseArea{
//                                anchors.fill:parent
//                                onClicked: {
//                                    soundeffectspage.selectedmusic = systemdispatcher.show_file_dialog("soundeffects");
////                                    systemdispatcher.get_music_path(soundeffectspage.selectedmusic);
//                                    systemdispatcher.get_music_path("/home/kobe/下载/qc.mp3");
//                                    systemdispatcher.replace_sound_file(soundeffectspage.selectedmusic, musicname);
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: revoke.width;height: revoke.height
//                            Image {id:revoke;source: "../../img/icons/revoke.png"}
//                            MouseArea{
//                                anchors.fill:parent
//                                onClicked: {
//                                    systemdispatcher.restore_sound_file(musicname);
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
//                        anchors.fill:listtext
//                        hoverEnabled: true
//                        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//                        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onExited: {btnImg.source = "";soundz=0}
//                        onClicked: {
//                            soundz=1
//                            wrapper.ListView.view.currentIndex = index;
//                        }
//                    }

//                }
//            }
//            ListView{
//                id:lisv
//                anchors.fill: parent
//                model:musicmodel
//                delegate: cdelegat
//                highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue";radius:5 }
//                focus:true
//            }

//            Rectangle{
//                id:scrollbar
//                anchors.right: parent.right
//                anchors.rightMargin: 8
//                height: parent.height
//                width:5
//                color: "lightgrey"
//            }
//            Rectangle{
//                id: button
//                anchors.right: parent.right
//                anchors.rightMargin: 5
//                width: 12
//                y: lisv.visibleArea.yPosition * scrollbar.height
//                height: lisv.visibleArea.heightRatio * scrollbar.height;
//                radius: 3
//                smooth: true
//                color: "white"
//                border.color: "lightgrey"
//                Column{
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 2
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                }
//                MouseArea {
//                    id: mousearea
//                    anchors.fill: button
//                    drag.target: button
//                    drag.axis: Drag.YAxis
//                    drag.minimumY: 0
//                    drag.maximumY: scrollbar.height - button.height
//                    onMouseYChanged: {
//                        lisv.contentY = button.y / scrollbar.height * lisv.contentHeight
//                    }
//                }
//            }
//        }
//    }

////左右分割线
//    Rectangle{id:leftline ; x:650; y: 0; width:1 ; height:425; color:"#b9c5cc"}
//    Rectangle{id:rightline ; x:652; y:0 ; width:1 ; height:425; color:"#fafcfe"}

//    Row{
//        spacing: 5
//        anchors{
//            left: parent.left
//            top:parent.top
//            leftMargin: 665
//            topMargin: 25
//        }
//        Image {
//            source: "../../img/icons/listen-pen.png"
//        }
//        Column{
//            spacing: 5
//            Text{
//                text:qsTr("自定义声音主题")
//                color: "#383838"
//                font.pointSize: 10
//                font.bold: true
//            }
//            Text{
//                text:qsTr("您能根据喜好组合")
//                font.pointSize: 10
//                color: "#7a7a7a"
//            }
//            Text{
//                text:qsTr("成专属声音主题")
//                font.pointSize: 10
//                color: "#7a7a7a"
//            }
//        }

//    }
//    Rectangle{id:topline ; x:652; y: 115; width:parent.width ; height:1; color:"#b9c5cc"}
//    Rectangle{id:bottomline ; x:652;y:116 ;width:parent.width ; height:1; color:"#fafcfe"}

//    Column
//    {
//        anchors {
//            top: parent.top
//            topMargin: 130
//            left: parent.left
//            leftMargin: 665
//        }
//        spacing: 20
//        Text {
//            text:qsTr("声音设置:")
//            color: "#383838"
//            font.pointSize: 10
//            font.bold: true
//        }
//        Row {
//            spacing: 20
//            Text{
//                text:qsTr("系统登录:")
//                font.pointSize: 10
//                color: "#7a7a7a"
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: soundswitcher
//                onSwitched: {
//                    if (soundswitcher.switchedOn) {
//                        console.log("系统登录音乐on---------------");
//                        sessiondispatcher.set_login_music_enable_qt(true);
//                    }
//                    else if(!soundswitcher.switchedOn) {
//                        console.log("系统登录音乐off---------------");
//                        sessiondispatcher.set_login_music_enable_qt(false);
//                    }
//                }
//            }
//        }
//    }
//}






//Rectangle {
//    id: soundeffectspage
//    property bool on: true
//    width: parent.width
//    color:"transparent"
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property string default_sound: ""
//    property string actiontitle: "声音效果设置"
//    property string actiontext: "单击一下列表中的程序事件，然后选择要应用的声音。您可以更改系统和程序事件的声音方案。"

//    Component.onCompleted: {

//        if (sessiondispatcher.get_login_music_enable_qt())
//            soundswitcher.switchedOn = true;
//        else
//            soundswitcher.switchedOn = false;
//        soundeffectspage.default_sound = sessiondispatcher.get_sound_theme_qt();
//        var soundlist = sessiondispatcher.get_sound_themes_qt();
//        var current_sound = sessiondispatcher.get_sound_theme_qt();
//        soundlist.unshift(current_sound);
//        choices.clear();
//        for(var i=0; i < soundlist.length; i++) {
//            choices.append({"text": soundlist[i]});
//            if (i!=0 && soundlist[i] == current_sound)
//                choices.remove(i);
//        }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "SoundEffects") {
//                if (soundeffectspage.default_sound != soundcombo.selectedText) {
//                    console.log("111");
//                    soundeffectspage.default_sound = soundcombo.selectedText;
//                    sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
//                }
//                else
//                    console.log("222");
//            }
//        }
//    }

//    ListModel {
//        id: choices
//        ListElement { text: "" }
//    }

//    Image {     //背景图片
//        id: background
//        anchors.fill: parent
//        source: "../../img/skin/bg-left.png"
//    }

//    Column {
//        spacing: 10
//        anchors.top: parent.top
//        anchors.topMargin: 44
//        anchors.left: parent.left
//        anchors.leftMargin: 80
//        Text {
//             text: soundeffectspage.actiontitle
//             font.bold: true
//             font.pixelSize: 14
//             color: "#383838"
//         }
//         Text {
//             text: soundeffectspage.actiontext
//             font.pixelSize: 12
//             color: "#7a7a7a"
//         }
//    }

//    Column{//程序事件及选择框
//        id:chooseyy
//        spacing: 10
//        anchors {
//            top: parent.top
//            topMargin: 120
//            left: parent.left
//            leftMargin: 60
//        }
//        Text{
//            text: qsTr("程序事件：")
//            font.bold:true
//            font.pointSize: 10
//        }
//        Rectangle{
//            border.color: "#b9c5cc"
//            width: 550; height: 190
//            clip:true
//            ListModel{
//                id:lmodel
//                ListElement{name:"test1"}
//                ListElement{name:"test2"}
//                ListElement{name:"test3"}
//                ListElement{name:"test4"}
//            }
//            Component{
//                id:cdelegat
//                Rectangle{
//                    id:wrapper
//                    width: 530; height: 30
//                    color: "white"
////                    color:ListView.isCurrentItem?"lightgrey":"white"
//                    Text{
//                        id:listtext
//                        anchors.verticalCenter: parent.verticalCenter
//                        text:name+":"+name
//                    }
//                    MouseArea{
//                        anchors.fill:parent
//                        hoverEnabled: true
//                        onEntered: {wrapper.color="lightgrey"}
//                        onPressed: {wrapper.color="lightgrey"}
////                        onReleased: {wrapper.color="lightgrey"}
//                        onExited: {wrapper.color="white"}
//                        onClicked: {console.log("a.....")}
//                    }

//                }
//            }
//            ListView{
//                id:lisv
//                anchors.fill: parent
//                model:lmodel
//                delegate: cdelegat
////              highlight: Rectangle{color: "lightsteelblue"}
//            }

//            Rectangle{
//                id:scrollbar
//                anchors.right: parent.right
//                anchors.rightMargin: 8
//                height: parent.height
//                width:5
//                color: "lightgrey"
//            }
//            Rectangle{
//                id: button
//                anchors.right: parent.right
//                anchors.rightMargin: 5
//                width: 12
//                y: lisv.visibleArea.yPosition * scrollbar.height
//                height: lisv.visibleArea.heightRatio * scrollbar.height;
//                radius: 3
//                smooth: true
//                color: "white"
//                border.color: "lightgrey"
//                Column{
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 2
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                }
//                MouseArea {
//                    id: mousearea
//                    anchors.fill: button
//                    drag.target: button
//                    drag.axis: Drag.YAxis
//                    drag.minimumY: 0
//                    drag.maximumY: scrollbar.height - button.height
//                    onMouseYChanged: {
//                        lisv.contentY = button.y / scrollbar.height * lisv.contentHeight
//                    }
//                }
//            }
//        }
//    }

//    Column {
//        spacing: 5
//        anchors {
//            top: parent.top
//            topMargin: 350
//            left: parent.left
//            leftMargin: 60
//        }
//        Text {
//            text: "声音"
//            font.bold: true
//            font.pixelSize: 14
//            color: "#383838"
//        }

//        Row {
//            spacing: 10
//            ComboBox {
//                id: comboBox
//                width: 345
//            }

//            Common.Button {
//                width: 95
//                height: 30
//                hoverimage: "listen.png"
//                onClicked: {

//                }
//            }
//            Common.Button {
//                width: 95
//                height: 30
//                hoverimage: "browser.png"
//                onClicked: {

//                }
//            }
//        }
//    }

////    Rectangle{id:topline ; x:0; y: 420; width:parent.width ; height:1; color:"#b9c5cc"}
////    Rectangle{id:bottomline ; x:0;y:422 ;width:parent.width ; height:1; color:"#fafcfe"}



//        Row {
////            anchors.horizontalCenter: parent.horizontalCenter
//            anchors {
//                top: parent.top
//                topMargin: 280
//                left: parent.left
//                leftMargin: 620
////                horizontalCenter: parent.horizontalCenter
//            }
//            Label {
//                id: soundlabel
//                width: 110
//                text: qsTr("系统登录音乐:")
//                font {
//                    family: soundeffectspage.fontName
//                    pointSize: soundeffectspage.fontSize
//                }
////                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: soundswitcher
//                onSwitched: {
//                    if (soundswitcher.switchedOn) {
//                        console.log("系统登录音乐on---------------");
//                        sessiondispatcher.set_login_music_enable_qt(true);
//                    }
//                    else if(!soundswitcher.switchedOn) {
//                        console.log("系统登录音乐off---------------");
//                        sessiondispatcher.set_login_music_enable_qt(false);
//                    }
//                }
//            }
//        }

//        Row {
//            anchors {
//                top: parent.top
//                topMargin: 320
//                left: parent.left
//                leftMargin: 620
//            }
//            Label {
//                id: soundthemelabel
//                width: 110
//                text: qsTr("音乐主题:")
//                font {
//                    family: soundeffectspage.fontName
//                    pointSize: soundeffectspage.fontSize
//                }
////                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: soundcombo
//                model: choices
//                width: soundthemelabel.width
////                onSelectedTextChanged: console.log(selectedText)
//            }
//        }
//}
