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
import SystemType 0.1
import "common" as Common
Rectangle {
    id: fastmode
    width: parent.width
    height: 435
    property string onekeypage: "second"

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkSecond: {
            if (msg == "") {
                onekeybtn.enabled=true;
            }
            else if (msg == "u") {
                unneedstatus.state = "StatusU";
                onekeybtn.enabled=true;
            }
            else if (msg == "c") {
                cachestatus.state = "StatusC";
                onekeybtn.enabled=true;
            }

        }

        onFinishCleanWorkSecondError: {
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
        onFinishCleanWorkSecond: {
            if (msg == "") {
                onekeybtn.enabled=true;
            }
            else if (msg == "h") {
                historystatus.state = "StatusH";
                onekeybtn.enabled=true;
            }
            else if (msg == "k") {
               cookiestatus.state = "StatusK";
                onekeybtn.enabled=true;
            }

        }
        onFinishCleanWorkSecondError: {
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
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    //上下分割条
    Rectangle {id: splitbar1; x: 2; y: 80; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar2; x: 2; y: 82; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar11; x: 2; y: 110; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar12; x: 2; y: 112; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar3; x: 2; y: 166; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar4; x: 2; y: 168; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar5; x: 2; y: 234; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar6; x: 2; y: 236; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar7; x: 2; y: 304; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar8; x: 2; y: 306; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar9; x: 2; y: 374; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar10; x: 2; y: 376; width: parent.width-4; height: 1; color: "#fafcfe" }


//    Row {

        Column {
            width: parent.width
            Row {
                id: myrow
                spacing: 10
                anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
                AnimatedImage {
                    id: refreshArrow
                    source: "../img/toolWidget/clear-movie.gif"
                }
                Column {
                    spacing: 10
                    id: mycolumn
                    Text {
                        id: text0
                        width: 69
                        text: qsTr("全面清理电脑中的垃圾、缓存和痕迹，只需要一个按键！")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Text {
                        id: text
                        width: 69
    //                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
                        text: qsTr("一键帮您节省磁盘空间，清理电脑中的垃圾，让系统运行更加快速。")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                SetBtn {
                    id: onekeybtn
                    iconName: "onekey.png"
                    setbtn_flag: "smallonekey"
                    anchors {
                        left: parent.left; leftMargin: 680
                    }
                    width: 120
                    height: 39
////如果没有选中任何清理项，提示警告框！
                    onClicked: {
                        if(!(checkboxe.checked||checkboxe2.checked||checkboxe3.checked||checkboxe4.checked))
                        {
                            onekeybtn.check_flag=false;

//                            sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中清理项，请确认！");
                        }
                        else
                            onekeybtn.check_flag=true;
//                            select.state="middlestate";
//                            if(checkboxe.checked&&checkboxe2.checked&&checkboxe3.checked&&checkboxe4.checked)
//                            {
//                                select.state="middlestate1";
//                            }

                    }
                }

            }//Row
//------begin new Layout
            Column {
                anchors.top: parent.top
                anchors.topMargin: 90
                anchors.left: parent.left
                anchors.leftMargin: 25
                spacing:25
                Item {
                    id: views
                    width: parent.width ////ListView不会随鼠标上下移动
        //                width:fastmode.width -10 //ListView会随鼠标上下移动
                    height: fastmode.height - refreshArrow.height - 10*2 - 20 -10

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
//                            background: red
                            anchors.verticalCenter: parent.verticalCenter
                            onCheckedChanged: {
                                checkboxe.checked=chek.checked;
                                checkboxe2.checked=chek.checked;
                                checkboxe3.checked=chek.checked;
                                checkboxe4.checked=chek.checked;
                            }
                        }
//                        Image {
//                            id:select
//                            source: "../img/toolWidget/unfinish.png"
//                            states: [
//                                State {
//                                    name: "middlestate"
//                                    PropertyChanges { target: select; source: "../img/toolWidget/finish.png"  }
//                                },

//                                State {
//                                    name: "middlestate1"
//                                    PropertyChanges { target: select; source: "../img/toolWidget/exception.png"  }
//                                }
//                            ]
//                        }
                    }
                    Column {
                        anchors.top: parent.top
                        anchors.topMargin: 50   //110
                        anchors.left: parent.left
                        anchors.leftMargin: 45
                        spacing:25
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
                                                    var rubbishlist = systemdispatcher.get_onekey_args2();
                                                    var word_flag = "false";
                                                    for (var i=0; i<rubbishlist.length; i++) {
                                                        if (rubbishlist[i] == "cache") {
                                                            word_flag = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag == "false") {
                                                        console.log("no word_flag1");
                                                        systemdispatcher.set_onekey_args2("cache");
                                                        console.log(systemdispatcher.get_package_args());
                                                    }
                                        }
                                        else if (!checkboxe.checked) {
                                                systemdispatcher.del_onekey_args2("cache");
                                                console.log(systemdispatcher.get_onekey_args2());
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
                                        PropertyChanges { target: cachestatus; source:"../img/toolWidget/finish.png"}
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
                                                    var historylist = systemdispatcher.get_onekey_args2();
                                                    console.log("this is a test!!!!!!!")
                                                    console.log(systemdispatcher.get_onekey_args2());
                                                    var word_flag1 = "false";
                                                    for (var j=0; j<historylist.length; j++) {
                                                        if (historylist[j] == "history") {
                                                            word_flag1 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag1 == "false") {
                                                        console.log("no word_flag2");
                                                        systemdispatcher.set_onekey_args2("history");
                                                        console.log(systemdispatcher.get_package_args());
                                                    }
                                        }
                                        else if (!checkboxe2.checked) {
                                                systemdispatcher.del_onekey_args2("history");
                                                console.log(systemdispatcher.get_onekey_args2());
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
                                                    var cookieslist = systemdispatcher.get_onekey_args2();
                                                    var word_flag2 = "false";
                                                    for (var k=0; k<cookieslist.length; k++) {
                                                        if (cookieslist[k] == "cookies") {
                                                            word_flag2 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag2 == "false") {
                                                        console.log("no word_flag3");
                                                        systemdispatcher.set_onekey_args2("cookies");
                                                        console.log(systemdispatcher.get_package_args());
                                                    }
                                        }
                                        else if (!checkboxe3.checked) {
                                                systemdispatcher.del_onekey_args2("cookies");
                                                console.log(systemdispatcher.get_onekey_args2());
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
                                                    var mylist = systemdispatcher.get_onekey_args2();
                                                    var word_flag3 = "false";
                                                    for (var q=0; q<mylist.length; q++) {
                                                        if (mylist[q] == "unneed") {
                                                            word_flag3 = "true";
                                                            break;
                                                        }
                                                    }
                                                    if (word_flag3 == "false") {
                                                        console.log("no word_flag4");
                                                        systemdispatcher.set_onekey_args2("unneed");
                                                        console.log(systemdispatcher.get_package_args());
                                                    }
                                        }
                                        else if (!checkboxe4.checked) {
                                                systemdispatcher.del_onekey_args2("unneed");
                                                console.log(systemdispatcher.get_onekey_args2());
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
                   }//Column
                }//Item
            }//Column
//------end new layout
    }//Row
}
