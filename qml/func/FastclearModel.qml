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
            console.log("begin LeftPage Second onOneKeyFinishCleanWork..............");
            console.log(msg);
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
            else if (msg == "u") {
                unneedstatus.state = "StatusU";
                onekeybtn.enabled=true;
            }
            else if (msg == "c") {
                cachestatus.state = "StatusC";
                onekeybtn.enabled=true;
            }

            else if (msg == "he") {
                historystatus.state = "StatusH1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ke") {
                cookiestatus.state = "StatusK1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ue") {
                unneedstatus.state = "StatusU1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ce") {
                cachestatus.state = "StatusC1";
                onekeybtn.enabled=true;
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

    Rectangle {id: splitbar3; x: 2; y: 140; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar4; x: 2; y: 142; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar5; x: 2; y: 204; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar6; x: 2; y: 206; width: parent.width-4; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar7; x: 2; y: 268; width: parent.width-4; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar8; x: 2; y: 270; width: parent.width-4; height: 1; color: "#fafcfe" }


//    Row {

        Column {
            width: parent.width
            Row {
                id: myrow
                spacing: 10
                anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//                Image {
//                    id: refreshArrow
//                    source: "../img/toolWidget/ubuntukylin.png"
//                    width: 50; height: 50
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
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
                }

            }//Row


            Column {
                anchors.top: parent.top
                anchors.topMargin: 110
                Item {
                    id: views
                    width: parent.width ////ListView不会随鼠标上下移动
        //                width:fastmode.width -10 //ListView会随鼠标上下移动
                    height: fastmode.height - refreshArrow.height - 10*2 - 20 -10

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
                            picturename: "../img/toolWidget/eraser.png"
                            detailstr: "清理上网时留下的历史记录，保护您的个人隐私"
                            clearflag: "history"
                        }
                        ListElement {
                            titlename: "清理Cookies"
                            picturename: "../img/toolWidget/firefox.png"
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
                        delegate: FastDelegate {pagenum: fastmode.onekeypage}//"second"
                        cacheBuffer: 1000
                    }
                }
            }

//        }//Column

        Image {
            id: cachestatus
            source: "../img/toolWidget/unfinish.png"
            anchors {
                top: parent.top; topMargin: 100
                left: parent.left; leftMargin: 700
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
                top: parent.top; topMargin: 164
                left: parent.left; leftMargin: 700
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
                top: parent.top; topMargin: 228
                left: parent.left; leftMargin: 700
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
                top: parent.top; topMargin: 290
                left: parent.left; leftMargin: 700
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
    }//Row
}
