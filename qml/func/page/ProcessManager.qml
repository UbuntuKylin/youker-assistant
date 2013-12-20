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
import "../common" as Common

Rectangle {
    id: root
    width: parent.width
    height: 475
    SystemPalette {id: syspal}
    property string processId//记录鼠标所在那行的进程号，以便自动刷新时重新定位到原来那行

    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    //更新进程列表
    function updateProcessList() {
        largeModel.clear();//清空largeModel
        processmanager.clearMap();//清空qt中保存的进程序号和进程号组合的map
//        var list = processmanager.getProcess();//得到当前用户的进程
        var list = processmanager.getProcessAdvance();//得到所用用户的进程
        for (var i=0 ; i < list.length ; i++) {
            var splitlist = list[i].split(";");
            if(splitlist.length !== 7) {
                continue;
            }
            else {
                var num = i.toString();
                var user = splitlist[0];
                var id = splitlist[1];
                largeModel.append({/*"number": num, */ "user": user, "pid": id, "pcpu": splitlist[2], "pmem": splitlist[3], "started": splitlist[4], "content": splitlist[5], "command": splitlist[6]});
                processmanager.updateMap(num, id);//更新qt中保存的进程序号和进程号组合的map
                processmanager.updateUserMap(id, user);
            }
        }
        largeModel.append({"user": "user", "pid": "pid", "pcpu": "cpu", "pmem": "mem", "started": "time", "content": "ubuntukylin", "command": "test for TableView"});
    }

    Image {
        id: titleimage
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        source: "../../img/skin/note-bg.png"
    }
    Text {
        anchors {
            left: parent.left
            leftMargin: 50
            top: parent.top
            topMargin: titleimage.height/2 - 7
        }
        text: qsTr("The task manager to help you kill some process which you want.")//任务管理器帮助您结束一些您想关闭的进程。
        font.pixelSize: 12
        color: "#383838"
    }
    Row {
        anchors {
            right: parent.right
            rightMargin: 30
            top: parent.top
            topMargin: 5
        }
        spacing: 10
        Common.Button {
            id: listBtn
            width: 100
            height: 30
            text: qsTr("Refresh")//刷新
            hoverimage: "green1.png"
            fontsize: 15
            onClicked: {
                updateProcessList();
                toolkits.alertMSG(qsTr("Refresh Over!"), mainwindow.pos.x, mainwindow.pos.y);//刷新完毕！
            }
        }
        Common.Button {
            id: killBtn
            width: 100
            height: 30
            text: qsTr("Kill process")//结束进程
            hoverimage: "green1.png"
            fontsize: 15
            onClicked: {
                //根据鼠标激活的序号来获取对应的进程号
                var currentId = processmanager.getProcessId(tableView.currentIndex.toString());
                if(currentId.length !== 0) {
                    var currentUser = processmanager.getProcessUser(currentId);
//                    console.log(currentUser);
//                    console.log(processmanager.getCasualUser());
                    if(currentUser == processmanager.getCasualUser()) {//普通用户杀进程
                        if(processmanager.killProcess(currentId)) {
                            toolkits.alertMSG(qsTr("Kill successfully!"), mainwindow.pos.x, mainwindow.pos.y);//结束进程操作成功！
                            updateProcessList();
                        }
                        else {
                            toolkits.alertMSG(qsTr("Kill failed!"), mainwindow.pos.x, mainwindow.pos.y);//结束进程操作失败！
                        }
                    }
                    else {//root用户杀进程
                        systemdispatcher.kill_root_process_qt(currentId);
                        updateProcessList();
                    }
                }
                else {
                    toolkits.alertMSG(qsTr("Have no choice!"), mainwindow.pos.x, mainwindow.pos.y);//没有选择将要结束的进程！
                }
            }
        }
    }

    ListModel {
        id: largeModel
        Component.onCompleted: {
            updateProcessList();
        }
    }

    Common.TableView {
        id: tableView
        model: largeModel
        anchors {
            top: titleimage.bottom
            left: parent.left
        }
        anchors.margins: 5
        width: parent.width - 10
        height: parent.height - titleimage.height - 5*2
//        frame: false
        //标题栏内容列表
//        Common.TableColumn {
//            role: "number"
//            title: "序号"
//            width: 40
//        }
        Common.TableColumn {
            role: "user"
            title: qsTr("User")//用户
            width: 60
        }
        Common.TableColumn {
            role: "pid"
            title: qsTr("ID")//ID
            width: 50
        }
        Common.TableColumn {
            role: "pcpu"
            title: qsTr("Cpu%")//CPU占用%
            width: 70
        }
        Common.TableColumn {
            role: "pmem"
            title: qsTr("Memory%")//内存占用%
            width: 70
        }
        Common.TableColumn {
            role: "started"
            title: qsTr("Start time")//启动时间
            width: 80
        }
        Common.TableColumn {
            role: "content"
            title: qsTr("Process description")//进程说明
            width: 150
        }
        Common.TableColumn {
            role: "command"
            title: qsTr("Process name")//进程名
            width: parent.width - 60 - 70*2 - 50 - 80 - 150 - 30
        }

        //标题栏美化
        headerDelegate: BorderImage{
            source: "../../img/icons/gray1-hover.png"
            border{left:2;right:2;top:2;bottom:2}
            Text {
                text: itemValue
                anchors.centerIn:parent
//                font.bold: true
                font.pixelSize: 12
                color: "#383838"
            }
        }

        //选中项
        rowDelegate: Rectangle {
            color: itemSelected ? "#448" : (itemAlternateBackground ? "#eee" : "#fff")
            border.color:"#ccc"
            border.width: 1
            BorderImage{
                id:selected
                anchors.fill: parent
                source: "../../img/skin/progress-bg.png"
                visible: itemSelected
                border{left:2;right:2;top:2;bottom:2}
//                SequentialAnimation {
//                    running: true; loops: Animation.Infinite
//                    NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
//                    NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
//                }
            }
        }
        onClicked: {
            //得到选中的进程号
            root.processId = processmanager.getProcessId(tableView.currentIndex.toString());
        }
    }
    //每隔1分钟自动刷新
    Timer {
        interval: 60000; running: true; repeat: true
        onTriggered: {
            updateProcessList();
            var result = processmanager.getProcessIndex(root.processId);
            tableView.currentIndex = result;
        }
    }
}
