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
//左边栏
Rectangle {
    id: leftbar
    width: 600; height: 460
    property string onekeypage: "first"
    property int num: 3     //checkbox num
    property int check_num: num

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkMain: {
            if (msg == "") {
                if (cachestatus.visible == true)
                    cachestatus.visible = false;
                if (historystatus.visible == true)
                    historystatus.visible = false;
                if (cookiestatus.visible == true)
                    cookiestatus.visible = false;
                if (cachedes.visible == true)
                    cachedes.visible = false;
                if (historydes.visible == true)
                    historydes.visible = false;
                if (cookiedes.visible == true)
                    cookiedes.visible = false;
            }
            else if (msg == "c") {
                cachestatus.state = "StatusC";
            }
            else if (msg == "h") {
                historystatus.state = "StatusH";
            }
            else if (msg == "k") {
               cookiestatus.state = "StatusK";
            }
            else if (msg == "o") {
                toolkits.alertMSG(qsTr("A Key cleared!"), mainwindow.pos.x, mainwindow.pos.y);//一键清理完毕！
            }
            refreshArrow0.visible = true;
            refreshArrow.visible = false;
        }

        onFinishCleanWorkMainError: {
            if (msg == "ce") {
                cachestatus.state = "StatusC1";
                if (cachedes.visible == true)
                    cachedes.visible = false;
            }
            else if (msg == "he") {
                historystatus.state = "StatusH1";
                if (historydes.visible == true)
                    historydes.visible = false;
            }
            else if (msg == "ke") {
               cookiestatus.state = "StatusK1";
                if (cookiedes.visible == true)
                    cookiedes.visible = false;
            }
        }
        onFinishCleanDataMain: {
            if (type == "c") {
                cachedes.visible = true;
                cachedes.text = qsTr("(totally cleared") + msg + qsTr("garbage");//（共清理掉      垃圾）
            }
            else if (type == "h") {
                historydes.visible = true;
                historydes.text = qsTr("(totally cleared") + msg + qsTr("historical records");//（共清理掉     条历史记录）
            }
            else if (type == "k") {
                cookiedes.visible = true;
                cookiedes.text = qsTr("(totally cleared") + msg + qsTr("Cookies）");//（共清理掉    条Cookies）
            }
        }
    }

    onCheck_numChanged: {
        if(check_num==0)
            chek.checked="false"
        else if(check_num==leftbar.num)
            chek.checked="true"
        else
            chek.checked="mid"
    }
    //背景
    Image {
        source: "../img/skin/bg-left.png"
        anchors.fill: parent
    }
//    Column {
//        anchors.fill: parent
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
                    width: leftbar.width-180
                    text: qsTr("A key to clean common system junk, effectively improve the efficiency of the system")//一键清理系统垃圾，有效提高系统运行效率
                    font.bold: true
                    wrapMode: Text.WordWrap
                    font.pixelSize: 14
                    color: "#383838"
                }
                Text {
                    id: text1
                    width: leftbar.width-180
                    text: qsTr("        A key to clean up will be directly removed the following three hook option, if you do not want to directly remove an item, please remove the tick, enter the system clean page for more detailed cleaning.")//        一键清理将会直接清理掉下面三个勾选项的内容,如果您不想直接清理掉某项内容,请去掉该项的勾选框,进入系统清理页面进行更细致地选择性清理。
                    wrapMode: Text.WordWrap
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
                Common.Button{
                    id: firstonekey
                    hoverimage: "green3.png"
                    setbtn_flag: "onekey"
                    text:qsTr("Clean Quickly")//一键清理
                    fontsize: 17
                    anchors {
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
                        if(checkboxe1.checked) {
                            cachestatus.visible = true;
                            cachestatus.state = "StatusCF";
                        }
                        else
                            cachestatus.visible = false;
                        if(checkboxe2.checked) {
                            historystatus.visible = true;
                            historystatus.state = "StatusHF";
                        }
                        else
                            historystatus.visible = false;
                        if(checkboxe3.checked) {
                            cookiestatus.visible = true;
                            cookiestatus.state = "StatusKF";
                        }
                        else
                            cookiestatus.visible = false;

                        if(!(checkboxe1.checked||checkboxe2.checked||checkboxe3.checked))
                        {
                            firstonekey.check_flag=false;
                        }
                        else
                            firstonekey.check_flag=true;

                    }
                }
            }

        }//Row


        Column {
            anchors { top: myrow.bottom; topMargin: 30; left: parent.left; leftMargin: 20 }
            spacing:45
            Row{
                spacing: 10
                Common.Label {
                    id: itemtip
                    text: qsTr("A key Clean Items")//一键清理项目
                    font.bold: true
                    font.pixelSize: 14
                    color: "#008000"
                }
                Common.MainCheckBox {
                    id:chek
                    checked:"true"    //将所有选项都check
                    onCheckedboolChanged: {
                        checkboxe1.checked = chek.checkedbool;
                        checkboxe2.checked = chek.checkedbool;
                        checkboxe3.checked = chek.checkedbool;
                    }
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 45
                spacing:30

            //---------------------------
                        Item {
                            width: parent.width //clearDelegate.ListView.view.width
                            height:45 //65

                            Item {
                                Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                                id: scaleMe
                                //checkbox, picture and words
                                Row {
                                    id: lineLayout
                                    spacing: 15
                                    anchors.verticalCenter: parent.verticalCenter
                                    Common.CheckBox {
                                        id: checkboxe1
                                        checked:true    //将所有选项都check
                                        anchors.verticalCenter: parent.verticalCenter
                                        onCheckedChanged: {
                                            if(checkboxe1.checked)
                                                leftbar.check_num=leftbar.check_num+1;
                                            else leftbar.check_num=leftbar.check_num-1;

                                            if (checkboxe1.checked) {
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
                                            else if (!checkboxe1.checked) {
                                                    systemdispatcher.del_onekey_args("cache");
                                                }
                                        }
                                    }
                                    Image {
                                        id: clearImage1
                                        width: 40; height: 42
                                        source:"../img/toolWidget/brush.png" //picturename
                                    }

                                    Column {
                                        spacing: 5
                                        Row {
                                            spacing: 20
                                            Text {
                                                text: qsTr("Clean up the garbage")//清理垃圾
                                                font.bold: true
                                                font.pixelSize: 14
                                                color: "#383838"
                                            }
                                            Text {
                                                id: cachedes
                                                color: "green"
                                                text: ""
                                                visible: false
                                            }
                                        }
                                        Text {
                                            text: qsTr("Clean up system junk files, free disk space")//清理系统中的垃圾文件，释放磁盘空间
                                            font.pixelSize: 12
                                            color: "#7a7a7a"
                                        }
                                    }
                                }
                                Common.StatusImage {
                                    id: cachestatus
                                    visible: false
                                    iconName: "yellow.png"
                                    text: qsTr("Unfinished")//未完成
                                    anchors {
//                                        top: itemtip.bottom; topMargin: 20
                                        left: parent.left; leftMargin: 450
                                    }
                                    states: [
                                            State {
                                            name: "StatusC"
                                            PropertyChanges { target: cachestatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                                        },

                                            State {
                                            name: "StatusC1"
                                            PropertyChanges { target: cachestatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                                        },
                                        State {
                                            name: "StatusCF"
                                            PropertyChanges { target: cachestatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
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
                        width: parent.width//clearDelegate.ListView.view.width
                        height: 45//65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe1
                            //checkbox, picture and words
                            Row {
                                id: lineLayout1
                                spacing: 15
                                anchors.verticalCenter: parent.verticalCenter
                               Common.CheckBox {
                                    id: checkboxe2
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if(checkboxe2.checked)
                                            leftbar.check_num=leftbar.check_num+1;
                                        else leftbar.check_num=leftbar.check_num-1;

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
                            }

                            Column {
                                spacing: 5
                                Row {
                                    spacing: 20
                                    Text {
                                        text: qsTr("Clean history")//清理历史记录
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#383838"
                                    }
                                    Text {
                                        id: historydes
                                        color: "green"
                                        text: ""
                                        visible: false
                                    }
                                }
                                Text {
                                    text: qsTr("Clean up the Internet histories, and protect your privacy")//清理上网时留下的历史记录，保护您的个人隐私
                                    font.pixelSize: 12
                                    color: "#7a7a7a"
                                }
                            }
                           }
                            Common.StatusImage {
                                id: historystatus
                                visible: false
                                iconName: "yellow.png"
                                text: qsTr("Unfinished")//未完成
                                anchors {
                                    left: parent.left; leftMargin: 450
                                }
                                states: [
                                        State {
                                        name: "StatusH"
                                        PropertyChanges { target: historystatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                                    },

                                        State {
                                        name: "StatusH1"
                                        PropertyChanges { target: historystatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                                    },
                                        State {
                                        name: "StatusHF"
                                        PropertyChanges { target: historystatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
                                    }

                                ]
                            }
                        }
                      }
            //----------------------------
                        Item {
                        width: parent.width//clearDelegate.ListView.view.width
                        height: 45//65

                        Item {
                            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                            id: scaleMe2
                            //checkbox, picture and words
                            Row {
                                id: lineLayout2
                                spacing: 15
                                anchors.verticalCenter: parent.verticalCenter
                               Common.CheckBox {
                                    id: checkboxe3
                                    checked:true    //将所有选项都check
                                    anchors.verticalCenter: parent.verticalCenter
                                    onCheckedChanged: {
                                        if(checkboxe3.checked)
                                            leftbar.check_num=leftbar.check_num+1;
                                        else leftbar.check_num=leftbar.check_num-1;

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
                            }

                            Column {
                                spacing: 5
                                Row {
                                    spacing: 20
                                    Text {
                                        text: qsTr("Clean Cookies")//清理Cookies
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#383838"
                                    }
                                    Text {
                                        id: cookiedes
                                        color: "green"
                                        text: ""
                                        visible: false
                                    }
                                }
                                Text {
                                    text: qsTr("Clean up the Internet Cookies, and give a piece of the sky to browser.")//清理上网时产生的Cookies，还浏览器一片天空
                                    font.pixelSize: 12
                                    color: "#7a7a7a"
                                }
                            }
                           }

                            Common.StatusImage {
                                id: cookiestatus
                                visible: false
                                iconName: "yellow.png"
                                text: qsTr("Unfinished")//未完成
                                anchors {
                                    left: parent.left; leftMargin: 450
                                }
                                states: [
                                        State {
                                        name: "StatusK"
                                        PropertyChanges { target: cookiestatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                                    },

                                        State {
                                        name: "StatusK1"
                                        PropertyChanges { target: cookiestatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                                    },
                                        State {
                                        name: "StatusKF"
                                        PropertyChanges { target: cookiestatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
                                    }

                                ]
                            }
                        }
                      }
        }//Column
    }//Column
}//左边栏Rectangle
