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
import ProcessType 0.1
import "common" as Common

Rectangle {
    width: parent.width
    height: 475
    SystemPalette {id: syspal}
    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    //更新进程列表
    function updateProcessList() {
        largeModel.clear();//清空largeModel
        processmanager.clearMap();//清空qt中保存的进程序号和进程号组合的map
        var list = processmanager.getProcess();
        for (var i=0 ; i < list.length ; i++) {
            var splitlist = list[i].split(";");
            if(splitlist.length !== 6) {
                continue;
            }
            else {
                var num = i.toString();
                var id = splitlist[1];
                largeModel.append({"user": splitlist[0], "pid": id, "pcpu": splitlist[2], "pmem": splitlist[3], "started": splitlist[4], "content": "ubuntukylin", "command": splitlist[5]});
                processmanager.updateMap(num, id);//更新qt中保存的进程序号和进程号组合的map
            }
        }
        largeModel.append({"user": "kobe", "pid": "pid", "pcpu": "cpu", "pmem": "mem", "started": "time", "content": "ubuntukylin", "command": "test for TableView"});
    }

    Image {
        id: titleimage
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        source: "../img/skin/note-bg.png"
    }
    Text {
        anchors {
            left: parent.left
            leftMargin: 50
            top: parent.top
            topMargin: titleimage.height/2 - 7
        }
        text: "任务管理器帮助您结束一些您想关闭的进程。"
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
            text: "刷新"
            hoverimage: "green1.png"
            fontsize: 15
            onClicked: {
                updateProcessList();
                toolkits.alertMSG("刷新完毕！", mainwindow.pos.x, mainwindow.pos.y);
            }
        }
        Common.Button {
            id: killBtn
            width: 100
            height: 30
            text: "结束进程"
            hoverimage: "green1.png"
            fontsize: 15
            onClicked: {
                //根据鼠标激活的序号来获取对应的进程号
                var currentId = processmanager.getProcessId(tableView.currentIndex.toString());
                if(currentId.length !== 0) {
                    if(processmanager.killProcess(currentId)) {
                        toolkits.alertMSG("结束进程操作成功！", mainwindow.pos.x, mainwindow.pos.y);
                        updateProcessList();
                    }
                    else {
                        toolkits.alertMSG("结束进程操作失败！", mainwindow.pos.x, mainwindow.pos.y);
                    }
                }
                else {
                    toolkits.alertMSG("没有选择将要结束的进程！", mainwindow.pos.x, mainwindow.pos.y);
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
            title: "用户"
            width: 60
        }
        Common.TableColumn {
            role: "pid"
            title: "ID"
            width: 50
        }
        Common.TableColumn {
            role: "pcpu"
            title: "CPU占用%"
            width: 70
        }
        Common.TableColumn {
            role: "pmem"
            title: "内存占用%"
            width: 70
        }
        Common.TableColumn {
            role: "started"
            title: "启动时间"
            width: 80
        }
        Common.TableColumn {
            role: "content"
            title: "进程说明"
            width: 150
        }
        Common.TableColumn {
            role: "command"
            title: "进程名"
            width: parent.width - 60 - 70*2 - 50 - 80 - 150 - 30
        }

        //标题栏美化
        headerDelegate: BorderImage{
            source: "../img/skin/progress-bg.png"
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
                source: "../img/skin/progress-bg.png"
                visible: itemSelected
                border{left:2;right:2;top:2;bottom:2}
//                SequentialAnimation {
//                    running: true; loops: Animation.Infinite
//                    NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
//                    NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
//                }
            }
        }
    }
    //每隔10秒自动刷新
//    Timer {
//        interval: 10000; running: true; repeat: true
//        onTriggered: {
//            updateProcessList();
//        }
//    }
}
