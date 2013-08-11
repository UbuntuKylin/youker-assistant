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
//import SessionType 0.1
//import SystemType 0.1
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
            else if (msg == "h") {
                console.log("new test..............");
                historystatus.state = "StatusH";
                console.log("new test11..............");
            }
            else if (msg == "k") {
               cookiestatus.state = "StatusK";
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
            if (msg == "he") {
                historystatus.state = "StatusH1";
            }
            else if (msg == "ke") {
               cookiestatus.state = "StatusK1";
            }
            else if (msg == "ue") {
                unneedstatus.state = "StatusU1";
            }
            else if (msg == "ce") {
                cachestatus.state = "StatusC1";
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
                }
            }

        }//Row


        Column {
            anchors { top: myrow.bottom; topMargin: 20; left: parent.left; leftMargin: 20 }
            Common.Label {
                id: itemtip
                text: "一键清理项目"
                font.bold: true
                font.pixelSize: 14
                color: "#008000"
            }

            Item {
                id: views
                width: parent.width ////ListView不会随鼠标上下移动
                height: leftbar.height - 118 - itemtip.height - 10*2 - 20 -10
                anchors.top: itemtip.bottom
                anchors.topMargin: 30

                ListModel {
                    id: clearModel
                    ListElement {
                        titlename: "清理垃圾"
                        picturename: "../img/toolWidget/brush.png"
                        detailstr: "清理系统中的垃圾文件，释放磁盘空间"
                        clearflag: "cache"
                    }
                    ListElement {
                        titlename: "清理历史记录"
                        picturename: "../img/toolWidget/history.png"
                        detailstr: "清理上网时留下的历史记录，保护您的个人隐私"
                        clearflag: "history"
                    }
                    ListElement {
                        titlename: "清理Cookies"
                        picturename: "../img/toolWidget/cookies.png"
                        detailstr: "清理上网时产生的Cookies，还浏览器一片天空"
                        clearflag: "cookies"
                    }
                    ListElement {
                        titlename: "卸载不必要的程序"
                        picturename: "../img/toolWidget/deb.png"
                        detailstr: "清理软件安装过程中安装的依赖程序，提高系统性能"
                        clearflag: "unneed"
                    }
                }

                ListView {
                    id: listView
                    height: parent.height
                    width: parent.width
                    anchors.top: parent.top
//                    anchors.topMargin: titlebar.height + 45
                    model: clearModel
                    delegate: FastDelegate {pagenum: leftbar.onekeypage} //"first"
                    cacheBuffer: 1000
                }
            }



            //status picture
            Image {
                id: cachestatus
                source: "../img/toolWidget/unfinish.png"
                anchors {
                    top: itemtip.bottom; topMargin: 20
                    left: parent.left; leftMargin: 500
//                    left: parent.right; leftMargin: 400
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


        }//Column
    }//Column

}//坐边栏Rectangle
