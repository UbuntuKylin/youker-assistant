/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
//import RegisterMyType 0.1
import SessionType 0.1
//import SystemType 0.1
import QtDesktop 0.1
import "../common" as Common

import AudioType 0.1

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

////        var soundlist = new Array()
////        soundlist.push("音乐2");
////        soundlist.push("Ubuntukylin默认");
////        var current_sound = "Ubuntukylin默认";

////        soundlist.unshift(current_sound);
////        choices.clear();
////        choices.append({"text": soundlist[0]});
////        choices.append({"text": soundlist[1]});


////        for(var i=0; i < soundlist.length; i++) {
////            choices.append({"text": soundlist[i]});
////            if (i!=0 && soundlist[i] == current_sound)
////                choices.remove(i);
////        }
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

//    QmlAudio{
//        id: song;
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

//    Column{     //声音主题
//        id:soundtheme
//        spacing: 10
//        anchors {
//            top: parent.top
//            topMargin: 120
//            left: parent.left
//            leftMargin: 60
//        }
//        Text{
//            text: qsTr("声音主题：")
//            font.bold:true
//            font.pointSize: 10
//        }
//        Row{
//            spacing: 10
//            ComboBox {
//                id: iconcombo
//                width : 345
//                model: choices
//                onSelectedTextChanged: console.log(selectedText)

//            }
//            Common.Button {
//                width: 95
//                height: 30
//                hoverimage: "saveas.png"
//                onClicked: {

//                }
//            }
//            Common.Button {
//                width: 95
//                height: 30
//                hoverimage: "delete.png"
//                onClicked: {

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
//            font.pointSize: 10
//        }
//        Rectangle{
//            border.color: "#b9c5cc"
//            width: 550; height: 125
//            clip:true
//            ListModel{
//                id:ukmodel
//                ListElement{name:"UbuntuKylin";image:"../../img/icons/book.png";onclicked:"UbuntuKylin";playclicked:"UbuntuKylin播放";nextclicked:"UbuntuKylin下一首";revokesclicked:"UbuntuKylin重播"}
//                ListElement{name:"UbuntuKylin登录"; image:"../../img/icons/broadcast.png";onclicked:"UbuntuKylin登录";playclicked:"登录的播放";nextclicked:"登录的下一首";revokesclicked:"登录的重播"}
//                ListElement{name:"UbuntuKylin注销"; image:"../../img/icons/broadcast.png"; onclicked:"UbuntuKylin注销";playclicked:"注销的播放";nextclicked:"注销的下一首";revokesclicked:"注销的重播"}
//                ListElement{name:"退出UbuntuKylin";image:"../../img/icons/broadcast.png"; onclicked:"退出UbuntuKylin";playclicked:"退出的播放";nextclicked:"退出的下一首";revokesclicked:"退出的重播"}
//                ListElement{name:"关键性停止";image:"../../img/icons/broadcast.png"; onclicked:"关键性停止";playclicked:"停止的播放";nextclicked:"停止的下一首";revokesclicked:"停止的重播"}
//                ListElement{name:"感叹号";image:"../../img/icons/broadcast.png"; onclicked:"感叹号";playclicked:"感叹号播放";nextclicked:"感叹号下一首";revokesclicked:"感叹号重播"}
//            }
//            ListModel{
//                id:sound2modle
//                ListElement{name:"音乐2";image:"../../img/icons/book.png";onclicked:"音乐2";playclicked:"音乐2播放";nextclicked:"音乐2下一首";revokesclicked:"音乐2重播"}
//                ListElement{name:"音乐2的登录"; image:"../../img/icons/broadcast.png";onclicked:"音乐2的登录";playclicked:"音乐2的登录播放";nextclicked:"音乐2的登录下一首";revokesclicked:"音乐2的登录重播"}
//                ListElement{name:"音乐2的注销"; image:"../../img/icons/broadcast.png"; onclicked:"音乐2的注销";playclicked:"音乐2的注销播放";nextclicked:"音乐2的注销下一首";revokesclicked:"音乐2的注销重播"}
//                ListElement{name:"退出音乐2";image:"../../img/icons/broadcast.png"; onclicked:"退出音乐2";playclicked:"退出音乐2播放";nextclicked:"退出音乐2下一首";revokesclicked:"退出音乐2重播"}
//                ListElement{name:"关键性停止音乐2";image:"../../img/icons/broadcast.png"; onclicked:"关键性停止音乐2";playclicked:"关键性停止音乐2播放";nextclicked:"关键性停止音乐2下一首";revokesclicked:"关键性停止音乐2重播"}
//                ListElement{name:"感叹号";image:"../../img/icons/broadcast.png"; onclicked:"感叹号";playclicked:"感叹号播放";nextclicked:"感叹号下一首";revokesclicked:"感叹号重播"}
//            }

//            Component{
//                id:cdelegat
//                Item{
//                    id:wrapper
//                    width: 530; height: 30
//                    Image {
//                        id:pickcher
//                        source: image
//                        anchors.verticalCenter: parent.verticalCenter
//                    }
//                    Text{
//                        id:listtext
//                        anchors.verticalCenter: parent.verticalCenter
//                        color: "grey"
//                        anchors.left: pickcher.right
//                        anchors.leftMargin: 5
//                        text:name
//                    }
//                    Row{
//                        spacing: 10
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
//                                    console.log(playclicked)
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: next.width;height: next.height
//                            Image {id:next;source: "../../img/icons/next.png"}
//                            MouseArea{
//                                anchors.fill:parent
//                                onClicked: {
//                                    console.log(nextclicked)
//                                }
//                            }
//                        }
//                        Rectangle{
//                            width: revoke.width;height: revoke.height
//                            Image {id:revoke;source: "../../img/icons/revoke.png"}
//                            MouseArea{
//                                anchors.fill:parent
//                                onClicked: {
//                                    console.log(revokesclicked)
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
//                        anchors.fill:parent
//                        hoverEnabled: true
//                        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//                        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                        onExited: {btnImg.source = "";soundz=0}
//                        onClicked: {
//                            console.log(onclicked)
//                            soundz=1
//                            wrapper.ListView.view.currentIndex = index;
//                        }
//                    }

//                }
//            }
//            ListView{
//                id:lisv
//                anchors.fill: parent
////                model:ukmodel
//                model: {
//                    if (iconcombo.selectedText == "音乐2")
//                        sound2modle
//                    else if(iconcombo.selectedText == "Ubuntukylin默认")
//                        ukmodel
//                }

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
//                        if(play_pause==0){ song.play();play_pause=1;}
//                        else if(play_pause==1){song.pause();play_pause=0;}
//                }
//            }
//            Common.Button {
//                width: 95
//                height: 30
//                hoverimage: "browser.png"
//                onClicked: {
//                    song.stop()
//                    song.play();play_pause=1
//                }
//            }
//        }
//    }

//    Rectangle{id:topline ; x:0; y: 420; width:parent.width ; height:1; color:"#b9c5cc"}
//    Rectangle{id:bottomline ; x:0;y:422 ;width:parent.width ; height:1; color:"#fafcfe"}



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






Rectangle {
    id: soundeffectspage
    property bool on: true
    width: parent.width
    color:"transparent"
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property SessionDispatcher dis: sessiondispatcher
    property string default_sound: ""
    property string actiontitle: "声音效果设置"
    property string actiontext: "单击一下列表中的程序事件，然后选择要应用的声音。您可以更改系统和程序事件的声音方案。"

    Component.onCompleted: {

        if (sessiondispatcher.get_login_music_enable_qt())
            soundswitcher.switchedOn = true;
        else
            soundswitcher.switchedOn = false;
        soundeffectspage.default_sound = sessiondispatcher.get_sound_theme_qt();
        var soundlist = sessiondispatcher.get_sound_themes_qt();
        var current_sound = sessiondispatcher.get_sound_theme_qt();
        soundlist.unshift(current_sound);
        choices.clear();
        for(var i=0; i < soundlist.length; i++) {
            choices.append({"text": soundlist[i]});
            if (i!=0 && soundlist[i] == current_sound)
                choices.remove(i);
        }
    }

    Connections {
        target: toolBar
        //按下确定按钮
        onOkBtnClicked: {
            if (settigsDetails.setTitle == "SoundEffects") {
                if (soundeffectspage.default_sound != soundcombo.selectedText) {
                    console.log("111");
                    soundeffectspage.default_sound = soundcombo.selectedText;
                    sessiondispatcher.set_sound_theme_qt(soundcombo.selectedText);
                }
                else
                    console.log("222");
            }
        }
    }

    ListModel {
        id: choices
        ListElement { text: "" }
    }

    Image {     //背景图片
        id: background
        anchors.fill: parent
        source: "../../img/skin/bg-left.png"
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: soundeffectspage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: soundeffectspage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    Column{//程序事件及选择框
        id:chooseyy
        spacing: 10
        anchors {
            top: parent.top
            topMargin: 120
            left: parent.left
            leftMargin: 60
        }
        Text{
            text: qsTr("程序事件：")
            font.bold:true
            font.pointSize: 10
        }
        Rectangle{
            border.color: "#b9c5cc"
            width: 550; height: 190
            clip:true
            ListModel{
                id:lmodel
                ListElement{name:"test1"}
                ListElement{name:"test2"}
                ListElement{name:"test3"}
                ListElement{name:"test4"}
            }
            Component{
                id:cdelegat
                Rectangle{
                    id:wrapper
                    width: 530; height: 30
                    color: "white"
//                    color:ListView.isCurrentItem?"lightgrey":"white"
                    Text{
                        id:listtext
                        anchors.verticalCenter: parent.verticalCenter
                        text:name+":"+name
                    }
                    MouseArea{
                        anchors.fill:parent
                        hoverEnabled: true
                        onEntered: {wrapper.color="lightgrey"}
                        onPressed: {wrapper.color="lightgrey"}
//                        onReleased: {wrapper.color="lightgrey"}
                        onExited: {wrapper.color="white"}
                        onClicked: {console.log("a.....")}
                    }

                }
            }
            ListView{
                id:lisv
                anchors.fill: parent
                model:lmodel
                delegate: cdelegat
//              highlight: Rectangle{color: "lightsteelblue"}
            }

            Rectangle{
                id:scrollbar
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

    Column {
        spacing: 5
        anchors {
            top: parent.top
            topMargin: 350
            left: parent.left
            leftMargin: 60
        }
        Text {
            text: "声音"
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }

        Row {
            spacing: 10
            ComboBox {
                id: comboBox
                width: 345
            }

            Common.Button {
                width: 95
                height: 30
                hoverimage: "listen.png"
                onClicked: {

                }
            }
            Common.Button {
                width: 95
                height: 30
                hoverimage: "browser.png"
                onClicked: {

                }
            }
        }
    }

//    Rectangle{id:topline ; x:0; y: 420; width:parent.width ; height:1; color:"#b9c5cc"}
//    Rectangle{id:bottomline ; x:0;y:422 ;width:parent.width ; height:1; color:"#fafcfe"}



        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
            anchors {
                top: parent.top
                topMargin: 280
                left: parent.left
                leftMargin: 620
//                horizontalCenter: parent.horizontalCenter
            }
            Label {
                id: soundlabel
                width: 110
                text: qsTr("系统登录音乐:")
                font {
                    family: soundeffectspage.fontName
                    pointSize: soundeffectspage.fontSize
                }
//                anchors.verticalCenter: parent.verticalCenter
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

        Row {
            anchors {
                top: parent.top
                topMargin: 320
                left: parent.left
                leftMargin: 620
            }
            Label {
                id: soundthemelabel
                width: 110
                text: qsTr("音乐主题:")
                font {
                    family: soundeffectspage.fontName
                    pointSize: soundeffectspage.fontSize
                }
//                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: soundcombo
                model: choices
                width: soundthemelabel.width
//                onSelectedTextChanged: console.log(selectedText)
            }
        }
}








//Rectangle {
//    id: soundeffectspage
//    property bool on: true
//    width: parent.width
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property string default_sound: ""

////    property Dispatcher dis: mydispather

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

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

//        var musiclist = sessiondispatcher.get_sound_themes_qt();
//        choices.clear();
//        for(var i=0; i < musiclist.length; i++) {
//            choices.append({"text": musiclist[i]});
//        }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "sound") {
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

//    Label {
//        id: sound
//        text: qsTr("声音设置>")
//        height: 30
//        font.bold: true
//        font.family: "Ubuntu"
//        elide: Text.ElideRight
//        font.pointSize: 20
//        anchors {
//            top: parent.top
//            topMargin: 10
//            left: parent.left
//            leftMargin: 15
//        }
//    }

//    Column {
//        spacing: 20
//        anchors {
//            top: sound.bottom
//            topMargin: 20
//            horizontalCenter: parent.horizontalCenter
//        }

////        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
//            Label {
//                id: soundlabel
//                width: 110
//                text: qsTr("系统登录音乐:")
//                font {
//                    family: soundeffectspage.fontName
//                    pointSize: soundeffectspage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            Common.Switch {
//                id: soundswitcher
////                width: soundlabel.width
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
//            Label {
//                id: soundthemelabel
//                width: 110
//                text: qsTr("音乐主题:")
//                font {
//                    family: soundeffectspage.fontName
//                    pointSize: soundeffectspage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: soundcombo
//                model: choices
//                width: soundthemelabel.width
////                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: music_theme
////                text: sessiondispatcher.get_sound_theme_qt()
////                width: soundthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//    }//Column
//}

















//import QtQuick 1.1
////import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
//import QtDesktop 0.1
//import "../common" as Common
//import "../common" as Common
//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
////    property Dispatcher dis: mydispather

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    Component.onCompleted: {
////        choices.clear();
////        choices.append({"text": mydispather.get_themes()[0]});
////        choices.append({"text": mydispather.get_themes()[1]});
////        choices.append({"text": mydispather.get_themes()[2]});
////        choices.append({"text": mydispather.get_themes()[3]});

////        streamModel.sync();
//    }

//    ListModel {
//        id: choices
//        ListElement { text: "theme" }
//        ListElement { text: "lixiang" }
//        ListElement { text: "ps" }
//        ListElement { text: "baby" }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onButton2Clicked: {
////            console.log("111111111111");
////            console.log(settigsDetails.setTitle);
//            if (settigsDetails.setTitle == "theme")
//                console.log(themelabel.text);
////            console.log("222222222222");
//        }
//    }

//    Column {
//        spacing: 20
//        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            Label {
//                id:themelabel
//                width: 110
//                text: qsTr("ps1-model")
//            }
//            ComboBox {
//                id: combobox
//                model: choices;
//                width: parent.width;
////                KeyNavigation.tab: t1
////                KeyNavigation.backtab: button2
////                onSelectedIndexChanged: console.log(selectedText)
//            }
//            Button {
//                id: button1
//                text: qsTr("确定")
//                width: 96
//                tooltip:"This is an interesting tool tip"
//                //                KeyNavigation.tab: button2
//                //                KeyNavigation.backtab: frame.tabBar
//                onClicked: {

//                }
//            }
//        }
//        Row {
//            Label {
//                id: modelabel1
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox2
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel3
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox4
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel5
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox6
//                x: 110
//            }
//        }


//    }//Column

//}





//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Column {
//        spacing: 20
//        anchors.top: parent.top
//        anchors.topMargin: 30
//        anchors.left: parent.left
//        anchors.leftMargin: 30

//        Row {
//            Label {
//                id: hidelabel
//                width: 110
//                text: qsTr("自动隐藏:")
//            }
//            CheckBox {
//                id: enabledCheck
//                text: qsTr("开启")
//                checked: false
//                onCheckedChanged: {}
//                onClicked: {
////                    enabledCheck.checked = !enabledCheck.checked;
////                    if (enabledCheck.checked == true) {
//////                        enabledCheck.checked = false;
////                        enabledCheck.text = qsTr("关闭");
////                    }
////                    else if (enabledCheck.checked == false){
//////                        enabledCheck.checked = true;
////                        enabledCheck.text = qsTr("开启");
////                    }
//                }
//            }

////            Common.Switch {
////                id: themeSwitch
////                anchors.right: parent.right
////                height: parent.height
////                spacing: 8
////                textOn: qsTr("On")
////                textOff: qsTr("Off")
////                fontColor: "#666666"
////                onSwitched: lancherpage.on = position
//////                id: switchLauncher
////////                checked: false
//////                x: 130
////////                onClicked: {
////////                    //kobe: wait for adding function
////////                    mydispather.set_launcher(switchLauncher.checked)
////////                }
////            }
//        }

//        Row {
//            Label {
//                id: sizelabel
//                width: 110
//                text: qsTr("图标大小:")
//            }
//            Slider {
//                id: slider
//                x: 130
////                function formatValue(v) { return v.toFixed(2) }
//                minimumValue: 0
//                maximumValue: 100
//                value: 0
////                live: true
////                onTouched: {
////                    console.log(slider.value)
////                }
//            }
//        }

//        Row {
//            Label {
//                id: locationlabel
//                width: 110
//                text: qsTr("位置:")
//            }
//            RadioButton {
//                id: radioleft
//                x: 130
////                text: "靠左"
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel1
//                width: 110
//                text: qsTr("输入用户名:")
//            }
//            TextField {
//                id: textfield1
//                placeholderText: qsTr("put your username")
//                echoMode: TextInput.Normal
////                hasClearButton: true
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield1.text)
//                }
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel2
//                width: 110
//                text: qsTr("输入密码:")
//            }
//            TextField {
//                id: textfield2
//                placeholderText: qsTr("put your password")
////                hasClearButton: true
//                echoMode: TextInput.Password
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield2.text)
//                }

//            }
//        }

//        Row {
//            Label {
//                id: progresslabel
//                width: 110
//                text: qsTr("进度显示:")
//            }
//            ProgressBar {
//                id: progressbar
////                indeterminate: true
//                value: 24
//                minimumValue: 0
//                maximumValue: 100

//            }
//        }

//        Row {
//            Label {
//                id: modelabel
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox
//                x: 110
////                titel1: "111111111"
////                titel2: "222222222"
////                titel3: "333333333"
////                flags: "launcher"
//            }

//        }
//    }
//}