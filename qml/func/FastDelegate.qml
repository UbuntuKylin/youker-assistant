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
import "common" as Common
import SessionType 0.1
Item {
    id: clearDelegate
    property SessionDispatcher dis: sessiondispatcher
    property string pagenum: ""
    width: parent.width//clearDelegate.ListView.view.width
    height: 65

//        function itemClicked() {
//            rotateDetails.title = "kobe111";
//            rotateDetails.description = "lixiang111";
//            scaleMe.state = "Details";
//        }

    //kobe: 'flag' comes from ListModel in FastclearModel.qml
    Component.onCompleted: {

    }

    Item {
        Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
        id: scaleMe
        //checkbox, picture and words
        Row {
            id: lineLayout
            spacing: 15
            anchors {
                fill: parent
                left: parent.left
                leftMargin: 50
            }
            Common.CheckBox {
                id: checkbox
//                    checked: true
                //清理历史记录时，chechbox默认为true，首页一键清理和系统清理页面的一键清理默认都为false
//                    checked: (pagenum == "history") ? true : false
                checked: true    //将所有选项都check
//                    width: 30
                anchors.verticalCenter: parent.verticalCenter
                onCheckedChanged: {
                    //kobe: wait for adding function
                    if (checkbox.checked) {
                        //----------------首页一键清理----------------
                        if (clearDelegate.pagenum == "first") {
                            if (clearflag == "cache") {
                                var rubbishlist = systemdispatcher.get_onekey_args();
                                var word_flag = "false";
                                for (var i=0; i<rubbishlist.length; i++) {
                                    if (rubbishlist[i] == clearflag) {
                                        word_flag = "true";
                                        break;
                                    }
                                }
                                if (word_flag == "false") {
                                    systemdispatcher.set_onekey_args(clearflag);
                                }
                            }
                            else if (clearflag == "history") {
                                var historylist = systemdispatcher.get_onekey_args();
                                var word_flag1 = "false";
                                for (var j=0; j<historylist.length; j++) {
                                    if (historylist[j] == clearflag) {
                                        word_flag1 = "true";
                                        break;
                                    }
                                }
                                if (word_flag1 == "false") {
                                    systemdispatcher.set_onekey_args(clearflag);
                                }
                            }
                            else if (clearflag == "cookies") {
                                var cookieslist = systemdispatcher.get_onekey_args();
                                var word_flag2 = "false";
                                for (var k=0; k<cookieslist.length; k++) {
                                    if (cookieslist[k] == clearflag) {
                                        word_flag2 = "true";
                                        break;
                                    }
                                }
                                if (word_flag2 == "false") {
                                    systemdispatcher.set_onekey_args(clearflag);
                                }
                            }
                            else if (clearflag == "unneed") {
                                var mylist = systemdispatcher.get_onekey_args();
                                var word_flag3 = "false";
                                for (var q=0; q<mylist.length; q++) {
                                    if (mylist[q] == clearflag) {
                                        word_flag3 = "true";
                                        break;
                                    }
                                }
                                if (word_flag3 == "false") {
                                    systemdispatcher.set_onekey_args(clearflag);
                                }
                            }
                        }

                        //----------------系统清理页面的一键清理----------------
                        else if (clearDelegate.pagenum == "second") {
                            if (clearflag == "cache") {
                                var rubbishlist2 = systemdispatcher.get_onekey_args2();
                                var second_flag = "false";
                                for (var x=0; x<rubbishlist2.length; x++) {
                                    if (rubbishlist2[x] == clearflag) {
                                        second_flag = "true";
                                        break;
                                    }
                                }
                                if (second_flag == "false") {
                                    systemdispatcher.set_onekey_args2(clearflag);
                                }
                            }
                            else if (clearflag == "history") {
                                var historylist2 = systemdispatcher.get_onekey_args2();
                                var second_flag2 = "false";
                                for (var y=0; y<historylist2.length; y++) {
                                    if (historylist2[y] == clearflag) {
                                        second_flag2 = "true";
                                        break;
                                    }
                                }
                                if (second_flag2 == "false") {
                                    systemdispatcher.set_onekey_args2(clearflag);
                                }
                            }
                            else if (clearflag == "cookies") {
                                var cookieslist2 = systemdispatcher.get_onekey_args2();
                                var second_flag3 = "false";
                                for (var z=0; z<cookieslist2.length; z++) {
                                    if (cookieslist2[z] == clearflag) {
                                        second_flag3 = "true";
                                        break;
                                    }
                                }
                                if (second_flag3 == "false") {
                                    systemdispatcher.set_onekey_args2(clearflag);
                                }
                            }
                            else if (clearflag == "unneed") {
                                var mylist2 = systemdispatcher.get_onekey_args2();
                                var second_flag4 = "false";
                                for (var w=0; w<mylist2.length; w++) {
                                    if (mylist2[w] == clearflag) {
                                        second_flag4 = "true";
                                        break;
                                    }
                                }
                                if (second_flag4 == "false") {
                                    systemdispatcher.set_onekey_args2(clearflag);
                                }
                            }
                        }

                        //----------------清理历史记录----------------
                        else if (clearDelegate.pagenum == "history") {
                            systemdispatcher.set_history_flag(true);
                        }

                    }



                    else if (!checkbox.checked) {
                        //----------------首页一键清理----------------
                        if (clearDelegate.pagenum == "first") {
                            if (clearflag == "cache") {
                                systemdispatcher.del_onekey_args(clearflag);
                            }
                            else if (clearflag == "history") {
                                systemdispatcher.del_onekey_args(clearflag);
                            }
                           else if (clearflag == "cookies") {

                                systemdispatcher.del_onekey_args(clearflag);
                            }
                            else if (clearflag == "unneed") {
                                systemdispatcher.del_onekey_args(clearflag);
                            }
                        }
                        //----------------系统清理页面的一键清理----------------c
                        else if (clearDelegate.pagenum == "second") {
                            if (clearflag == "cache") {
                                systemdispatcher.del_onekey_args2(clearflag);
                            }
                            else if (clearflag == "history") {
                                systemdispatcher.del_onekey_args2(clearflag);
                            }
                           else if (clearflag == "cookies") {

                                systemdispatcher.del_onekey_args2(clearflag);
                            }
                            else if (clearflag == "unneed") {
                                systemdispatcher.del_onekey_args2(clearflag);
                            }
                        }

                        //----------------清理历史记录----------------
                        else if (clearDelegate.pagenum == "history") {
                            systemdispatcher.set_history_flag(false);
                        }
                    }
                }
            }
            Image {
                id: clearImage
                width: 40; height: 42
                source: picturename
                anchors.verticalCenter: parent.verticalCenter
            }

            Column {
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    text: titlename
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Text {
                    text: detailstr
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
        Rectangle {  //分割条
            width: parent.width; height: 1
            anchors { top: lineLayout.bottom; topMargin: 5}
            color: "gray"
        }
    }
}

