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
import SessionType 0.1
import SystemType 0.1
import "common" as Common
//坐边栏
Rectangle {
    id: leftbar
    width: 600; height: 460
    property string onekeypage: "first"

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkMain: {
            if (msg == "") {
                leftbar.state = "StatusEmpty";
            }
            else if (msg == "u") {
                unneedstatus.state = "StatusU";
            }
            else if (msg == "c") {
                cachestatus.state = "StatusC";
            }

            refreshArrow0.visible = true;
            refreshArrow.visible = false;

        }

        onFinishCleanWorkMainError: {
            if (msg == "ue") {
                unneedstatus.state = "StatusU1";
            }
            else if (msg == "ce") {
                cachestatus.state = "StatusC1";
            }
        }
    }

    Connections
    {
        target: sessiondispatcher
        onFinishCleanWorkMain: {
            if (msg == "") {
                leftbar.state = "StatusEmpty";
            }
            else if (msg == "h") {
                historystatus.state = "StatusH";
            }
            else if (msg == "k") {
               cookiestatus.state = "StatusK";
            }

            refreshArrow0.visible = true;
            refreshArrow.visible = false;

        }

        onFinishCleanWorkMainError: {
            if (msg == "he") {
                historystatus.state = "StatusH1";
            }
            else if (msg == "ke") {
               cookiestatus.state = "StatusK1";
            }
        }
    }


    //背景
    Image {
        source: "../img/skin/bg-left.png"
        anchors.fill: parent
    }
    Column {
        anchors.fill: parent
        Row {
            id: myrow
            spacing: 10
            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
            Image {
                id: refreshArrow0
                visible: true
                source: "../img/toolWidget/clear-logo.gif"
                width: 120
                height: 118
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            AnimatedImage {
                id: refreshArrow
                visible: false
                width: 120
                height: 118
                source: "../img/toolWidget/clear-logo.gif"
            }

            Column {
                spacing: 10
                id: mycolumn
                Text {
                    id: text0
                    width: 69
                    text: qsTr("一键清理系统垃圾，有效提高系统运行效率")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Text {
                    id: text1
                    width: 69
                    text: qsTr("     一键清理将会直接清理掉下面四个勾选项的内容,如果您不想直接清理掉某项")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
                Text {
                    id: text2
                    width: 69
                    text: qsTr("内容,请去掉该项的勾选框,进入系统清理页面进行更细致地选择性清理。")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
                SetBtn {
                    id: firstonekey
                    iconName: "onekeyBtn.png"
                    setbtn_flag: "onekey"
                    anchors {
                        top: text2.bottom; topMargin: 10
                        left: parent.left; leftMargin: 100
                    }
                    width: 186
                    height: 45
                    onSend_dynamic_picture: {
                        if (str == "onekey") {
                            refreshArrow0.visible = false;
                            refreshArrow.visible = true;
                        }
                    }
//如果没有选中任何清理项，提示警告框！
                    onClicked: {
                        if(!(checkboxe.checked||checkboxe2.checked||checkboxe3.checked||checkboxe4.checked))
                        {
                            firstonekey.check_flag=false;
//                            sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中清理项，请确认！");
                        }
                        else
                            firstonekey.check_flag=true;
                    }
                }
            }

        }//Row


        Column {
            anchors { top: myrow.bottom; topMargin: 20; left: parent.left; leftMargin: 20 }
            spacing:25
            Row{
                spacing: 10
                Common.Label {
                    id: itemtip
                    text: "一键清理项目"
                    font.bold: true
                    font.pixelSize: 14
                    color: "#008000"
                }
                Common.CheckBox {
                    id:chek
                    checked:true    //将所有选项都check
                    anchors.verticalCenter: parent.verticalCenter
                    onCheckedChanged: {
                        checkboxe.checked=chek.checked;
                        checkboxe2.checked=chek.checked;
                        checkboxe3.checked=chek.checked;
                        checkboxe4.checked=chek.checked;
                    }
                }
            }

            //---------------------------
                        Item {
                        property SessionDispatcher dis: sessiondispatcher
                        width: parent.width //clearDelegate.ListView.view.width
                        height:45 //65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe
                            //checkbox, picture and words
                            Row {
                                id: lineLayout
                                spacing: 10
                                anchors {
                                    fill: parent
                                    left: parent.left
                                    leftMargin: 50
                                }
                                Common.CheckBox {
                                    id: checkboxe
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if (checkboxe.checked) {
                                                    var rubbishlist = systemdispatcher.get_onekey_args();
                                                    var word_flag = "false";
                                                    for (var i=0; i<rubbishlist.length; i++) {
                                                        if (rubbishlist[i] == "cache") {
                                                            word_flag = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag == "false") {
                                                        systemdispatcher.set_onekey_args("cache");
                                                    }
                                        }
                                        else if (!checkboxe.checked) {
                                                systemdispatcher.del_onekey_args("cache");
                                            }
                                    }
                                }
                                Image {
                                    id: clearImage1
                                    width: 40; height: 42
                                    source:"../img/toolWidget/brush.png" //picturename
                                    anchors {
                                        left: checkboxe.right; leftMargin: 15
                                        verticalCenter: parent.verticalCenter
                                    }

                                }

                                Column {
                                    spacing: 5
                                    anchors {
                                        left: clearImage1.right; leftMargin: 15
                                        verticalCenter: parent.verticalCenter
                                    }
                                    Text {
                                        text: "清理垃圾"//titlename
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#383838"
                                    }
                                    Text {
                                        text: "清理系统中的垃圾文件，释放磁盘空间"//detailstr
                                        font.pixelSize: 12
                                        color: "#7a7a7a"
                                    }
                                }
                            }
                            Image {
                                id: cachestatus
                                source: "../img/toolWidget/unfinish.png"
                                anchors {
                                    top: itemtip.bottom; topMargin: 20
                                    left: parent.left; leftMargin: 500
                                }
                                states: [
                                        State {
                                        name: "StatusC"
                                        PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
                                    },

                                        State {
                                        name: "StatusC1"
                                        PropertyChanges { target: cachestatus; source: "../img/toolWidget/exception.png"}
                                    }

                                ]
                            }

                            Rectangle {  //分割条
                                width: parent.width; height: 1
                                anchors { top: lineLayout.bottom; topMargin: 5}
                                color: "gray"
                            }
                        }
                        }

            //----------------------------
                        Item {
                        property SessionDispatcher dis: sessiondispatcher
                        width: parent.width//clearDelegate.ListView.view.width
                        height: 45//65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe1
                            //checkbox, picture and words
                            Row {
                                id: lineLayout1
                                spacing: 10
                                anchors {
                                    fill: parent
                                    left: parent.left
                                    leftMargin: 50
                                }
                               Common.CheckBox {
                                    id: checkboxe2
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if (checkboxe2.checked) {
                                                    var historylist = systemdispatcher.get_onekey_args();
                                                    var word_flag1 = "false";
                                                    for (var j=0; j<historylist.length; j++) {
                                                        if (historylist[j] == "history") {
                                                            word_flag1 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag1 == "false") {
                                                        systemdispatcher.set_onekey_args("history");
                                                    }
                                        }
                                        else if (!checkboxe2.checked) {
                                                systemdispatcher.del_onekey_args("history");
                                            }
                                    }
                                }


                            Image {
                                id: clearImage2
                                width: 40; height: 42
                                source: "../img/toolWidget/history.png"//picturename
                                anchors {
                                    left: checkboxe.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }
                            }

                            Column {
                                spacing: 5
                                anchors {
                                    left: clearImage2.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }
                                Text {
                                    text: "清理历史记录"//titlename
                                    font.bold: true
                                    font.pixelSize: 14
                                    color: "#383838"
                                }
                                Text {
                                    text: "清理上网时留下的历史记录，保护您的个人隐私"//detailstr
                                    font.pixelSize: 12
                                    color: "#7a7a7a"
                                }
                            }
                           }
                            Image {
                                id: historystatus
                                source: "../img/toolWidget/unfinish.png"
                                anchors {
                                    top: cachestatus.bottom; topMargin: 45
                                    left: parent.left; leftMargin: 500
                                }
                                states: [
                                        State {
                                        name: "StatusH"
                                        PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
                                    },

                                        State {
                                        name: "StatusH1"
                                        PropertyChanges { target: historystatus; source: "../img/toolWidget/exception.png"}
                                    }

                                ]
                            }

                            Rectangle {  //分割条
                                width: parent.width; height: 1
                                anchors { top: lineLayout.bottom; topMargin: 5}
                                color: "gray"
                            }

                        }
                      }
            //----------------------------
                        Item {
                        property SessionDispatcher dis: sessiondispatcher
                        width: parent.width//clearDelegate.ListView.view.width
                        height: 45//65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe2
                            //checkbox, picture and words
                            Row {
                                id: lineLayout2
                                spacing: 10
                                anchors {
                                    fill: parent
                                    left: parent.left
                                    leftMargin: 50
                                }
                               Common.CheckBox {
                                    id: checkboxe3
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if (checkboxe3.checked) {
                                                    var cookieslist = systemdispatcher.get_onekey_args();
                                                    var word_flag2 = "false";
                                                    for (var k=0; k<cookieslist.length; k++) {
                                                        if (cookieslist[k] == "cookies") {
                                                            word_flag2 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag2 == "false") {
                                                        systemdispatcher.set_onekey_args("cookies");
                                                    }
                                        }
                                        else if (!checkboxe3.checked) {
                                                systemdispatcher.del_onekey_args("cookies");
                                            }
                                    }
                                }


                            Image {
                                id: clearImage3
                                width: 40; height: 42
                                source: "../img/toolWidget/cookies.png"//picturename
                                anchors {
                                    left: checkboxe.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }

                            }

                            Column {
                                spacing: 5
                                anchors {
                                    left: clearImage2.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }
                                Text {
                                    text: "清理Cookies"//titlename
                                    font.bold: true
                                    font.pixelSize: 14
                                    color: "#383838"
                                }
                                Text {
                                    text: "清理上网时产生的Cookies，还浏览器一片天空"//detailstr
                                    font.pixelSize: 12
                                    color: "#7a7a7a"
                                }
                            }
                           }

                            Image {
                                id: cookiestatus
                                source: "../img/toolWidget/unfinish.png"
                                anchors {
                                    top: historystatus.bottom; topMargin: 45
                                    left: parent.left; leftMargin: 500
                                }
                                states: [
                                        State {
                                        name: "StatusK"
                                        PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
                                    },

                                        State {
                                        name: "StatusK1"
                                        PropertyChanges { target: cookiestatus; source: "../img/toolWidget/exception.png"}
                                    }

                                ]
                            }

                            Rectangle {  //分割条
                                width: parent.width; height: 1
                                anchors { top: lineLayout.bottom; topMargin: 5}
                                color: "gray"
                            }

                        }
                      }
            //----------------------------
                        Item {
                        property SessionDispatcher dis: sessiondispatcher
                        width: parent.width//clearDelegate.ListView.view.width
                        height: 45//65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe3
                            //checkbox, picture and words
                            Row {
                                id: lineLayout3
                                spacing: 10
                                anchors {
                                    fill: parent
                                    left: parent.left
                                    leftMargin: 50
                                }
                               Common.CheckBox {
                                    id: checkboxe4
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if (checkboxe4.checked) {
                                                    var mylist = systemdispatcher.get_onekey_args();
                                                    var word_flag3 = "false";
                                                    for (var q=0; q<mylist.length; q++) {
                                                        if (mylist[q] == "unneed") {
                                                            word_flag3 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag3 == "false") {
                                                        systemdispatcher.set_onekey_args("unneed");
                                                    }
                                        }
                                        else if (!checkboxe4.checked) {
                                                systemdispatcher.del_onekey_args("unneed");
                                            }
                                    }
                                }


                            Image {
                                id: clearImage4
                                width: 40; height: 42
                                source: "../img/toolWidget/deb.png"//picturename
                                anchors {
                                    left: checkboxe.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }

                            }

                            Column {
                                spacing: 5
                                anchors {
                                    left: clearImage2.right; leftMargin: 15
                                    verticalCenter: parent.verticalCenter
                                }
                                Text {
                                    text: "卸载不必要的程序"//titlename
                                    font.bold: true
                                    font.pixelSize: 14
                                    color: "#383838"
                                }
                                Text {
                                    text: "清理软件安装过程中安装的依赖程序，提高系统性能"//detailstr
                                    font.pixelSize: 12
                                    color: "#7a7a7a"
                                }
                            }
                          }

                            Image {
                                id: unneedstatus
                                source: "../img/toolWidget/unfinish.png"
                                anchors {
                                    top: cookiestatus.bottom; topMargin: 45
                                    left: parent.left; leftMargin: 500
                                }
                                states: [
                                        State {
                                        name: "StatusU"
                                        PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
                                    },

                                        State {
                                        name: "StatusU1"
                                        PropertyChanges { target: unneedstatus; source: "../img/toolWidget/exception.png"}
                                    }

                                ]
                            }

                            Rectangle {  //分割条
                                width: parent.width; height: 1
                                anchors { top: lineLayout.bottom; topMargin: 5}
                                color: "gray"
                            }

                        }
                      }
            //----------------------------
                    }//Column
                }//Column

            }//坐边栏Rectangle
