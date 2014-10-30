/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
    id: processpage
    width: parent.width; height: 476

    SystemPalette {id: syspal}
    property string processId//记录鼠标所在那行的进程号，以便自动刷新时重新定位到原来那行
    property bool flag: true//判断选中当前用户还是全部用户，当前用户为true，全部用户为false

    property string actiontitle: qsTr("Task Manager")//任务管理器
    property string actiontext: qsTr("Help you learn more about the program running on the system.")//帮助您了解系统上运行程序的详细信息。

    //更新进程列表
    function updateProcessList() {
        largeModel.clear();//清空largeModel
        processmanager.clearMap();//清空qt中保存的进程序号和进程号组合的map
        processmanager.clearUserMap();//清空qt中保存的进程号和用户名组合的map

        var list = processmanager.getProcess();//得到当前用户的进程
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
    //更新进程列表
    function updateAllProcessList() {
        largeModel.clear();//清空largeModel
        processmanager.clearMap();//清空qt中保存的进程序号和进程号组合的map
        processmanager.clearUserMap();//清空qt中保存的进程号和用户名组合的map
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


    Row {
        spacing: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 20
        }
        Common.Button {
            id: backBtn
            anchors.verticalCenter: parent.verticalCenter
            picNormal: "../../img/icons/button12-gray.png"
            picHover: "../../img/icons/button12-gray-hover.png"
            picPressed: "../../img/icons/button12-gray-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 70; height: 28
            text: qsTr("Back")//返回
            onClicked: {
                pageStack.pop();
            }
        }

        Column {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                 text: processpage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            Text {
                text: processpage.actiontext
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    Row {
        spacing: 70
        anchors {
            top: parent.top
            topMargin: 20
            right: parent.right
            rightMargin: 20
        }
        Common.ButtonRow {
            anchors.verticalCenter: parent.verticalCenter
            exclusive: true//控制是否联动
            spacing: 80
            Common.CheckBox {
                id:currentUser
                titleName: qsTr("Current User") //当前用户
                checked: (processpage.flag == true) ? true : false
                flag: "radio"
                onClicked: {
                    if (currentUser.checked == true) {
                        if(processpage.flag == false) {
                            processpage.flag = true;
                            processpage.updateProcessList();
                        }
                    }
                }
            }
            Common.CheckBox {
                id: allUser
                titleName: qsTr("All Users")//所有用户
                checked: (processpage.flag == false) ? true : false
                flag: "radio"
                onClicked: {
                    if (allUser.checked == true) {
                        if(processpage.flag == true) {
                            processpage.flag = false;
                            processpage.updateAllProcessList();
                        }
                    }
                }
            }
        }
        Row {
            spacing: 20
            Common.StyleButton {
                id: listBtn
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Refresh")//刷新
                width: 40
                height: 20
                onClicked: {
                    if(processpage.flag == true) {
                        processpage.updateProcessList();
                    }
                    else if(processpage.flag == false) {
                        processpage.updateAllProcessList();
                    }
                    toolkits.alertMSG(qsTr("Refresh completed!"));//刷新完成！
                }
            }
            Common.StyleButton {
                id: killBtn
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("End process")//结束进程
                width: 40
                height: 20
                onClicked: {
                    //根据鼠标激活的序号来获取对应的进程号
                    var currentId = processmanager.getProcessId(tableView.currentIndex.toString());
                    if(currentId.length !== 0) {
                        var currentUser = processmanager.getProcessUser(currentId);
                        if(currentUser == processmanager.getCasualUser()) {//普通用户杀进程
                            if(processmanager.killProcess(currentId)) {
                                toolkits.alertMSG(qsTr("The end of the process operation is successful!"));//结束进程操作成功！
                                if(processpage.flag == true) {
                                    processpage.updateProcessList();
                                }
                                else if(processpage.flag == false) {
                                    processpage.updateAllProcessList();
                                }
                            }
                            else {
                                toolkits.alertMSG(qsTr("The end of the process operation failed!"));//结束进程操作失败！
                            }
                        }
                        else {//root用户杀进程
                            systemdispatcher.kill_root_process_qt(currentId);
                            if(processpage.flag == true) {
                                processpage.updateProcessList();
                            }
                            else if(processpage.flag == false) {
                                processpage.updateAllProcessList();
                            }
                        }
                    }
                    else {
                        toolkits.alertMSG(qsTr("Sorry,  You did not choose the process to be killed!"));//对不起，您没有选择想要结束的进程！
                    }
                }
            }
        }
    }

    //分割条
    Common.Separator {
        id: top_splitbar
        y: 70
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
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
            top: top_splitbar.bottom
            left: parent.left
        }
        anchors.margins: 5
        width: parent.width - 10
        height: parent.height - 60 - 5*2
//        frame: false
        //标题栏内容列表
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
            title: qsTr("CPU %")//CPU占用 %
            width: 70
        }
        Common.TableColumn {
            role: "pmem"
            title: qsTr("Memory %")//内存占用 %
            width: 70
        }
        Common.TableColumn {
            role: "started"
            title: qsTr("Start Time")//启动时间
            width: 80
        }
        Common.TableColumn {
            role: "content"
            title: qsTr("Process Description")//进程说明
            width: 150
        }
        Common.TableColumn {
            role: "command"
            title: qsTr("Process Name")//进程名
            width: parent.width - 60 - 70*2 - 50 - 80 - 150 - 30
        }

        //标题栏美化
        headerDelegate: BorderImage{
            source: "../../img/icons/gray-hover.png"
            border{left:2;right:2;top:2;bottom:2}
            Text {
                text: itemValue
                anchors.centerIn:parent
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
            processpage.processId = processmanager.getProcessId(tableView.currentIndex.toString());
        }
    }
    //每隔1分钟自动刷新
    Timer {
        interval: 60000; running: true; repeat: true
        onTriggered: {
            if(processpage.flag == true) {
                processpage.updateProcessList();
            }
            else if(processpage.flag == false) {
                processpage.updateAllProcessList();
            }
            var result = processmanager.getProcessIndex(processpage.processId);
            tableView.currentIndex = result;
        }
    }
}
