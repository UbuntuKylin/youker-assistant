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
//sudo aptitude search ~i~nlinux-
Item {
    id:root
    width: parent.width
    height: 435
    property string title: qsTr("Uninstall old kernel packages")//卸载旧内核包
    property string description: qsTr("Clean old kernel, to free space for system")//清理旧内核，释放系统空间
    property string btnFlag: "kernel_scan"//扫描或者清理的标记：kernel_scan/kernel_work
    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int subNum: 0//扫描后得到的kernel的项目总数
    property int kernelNum: subNum//001
    property int arrowShow: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool positionFlag: false//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    ListModel { id: mainModel }
    ListModel { id: subModel }

    //得到old kernel package
    function getData() {
        var kernel_data = sessiondispatcher.scan_oldkernel_packages_qt();
        if (kernel_data.length === 0) {//扫描内容不存在
            root.resultFlag = false;
        }
        else {
            root.subNum = kernel_data.length;//001
            systemdispatcher.clear_kernel_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< kernel_data.length; i++) {
            //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
                var splitlist = kernel_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
                    systemdispatcher.set_kernel_args(splitlist[0]);
                }
            }
            root.subNum -= num;//001
            root.kernelNum = root.subNum;//001
            if(root.kernelNum != 0) {
                root.resultFlag = true;//扫描的实际有效内容存在
            }
            else {
                root.resultFlag = false;//扫描的实际有效内容不存在
            }
            mainModel.clear();
            //卸载旧内核包         用户可以根据扫描结果选择性地清理旧内核包,节省系统空间
            mainModel.append({"itemTitle": qsTr("Uninstall old kernel packages"),
                             "picture": "../img/toolWidget/deb-min.png",
                             "detailstr": qsTr("User can selectively clean old kernel packages according to the scan results, to save the system space")})
//            mainModel.append({"itemTitle": qsTr("Uninstall old kernel packages"),
//                             "picture": "../img/toolWidget/deb-min.png",
//                             "detailstr": qsTr("User can selectively clean old kernel packages according to the scan results, to save the system space"),
//                             "flags": "clear_kernel"})
        }


        if(root.resultFlag == false) {
            root.state = "KernelWorkEmpty";
            root.arrowShow = 0;
            if(root.flag == false) {
                //友情提示：      扫描内容为空，不再执行清理！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else {
                root.flag = false;
            }
        }
        else if(root.resultFlag == true) {
            if(root.flag == false) {
                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
            }
            else {
                root.flag = false;
            }
            root.arrowShow = 1;
            root.state = "KernelWork";
            actionBtn.text = qsTr("Start cleaning");//开始清理
            root.btnFlag = "kernel_work";
            backBtn.visible = true;
            rescanBtn.visible = true;
        }
    }

    Connections
    {
        target: sudodispatcher
        onFinishCleanDebError: {//清理出错时收到的信号
            if (msg == "kernel") {
                if (root.btnFlag == "kernel_work") {
                    //清理过程中发生错误，解禁按钮
                    actionBtn.enabled = true;
                    titleBar.state = "KernelWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
         }
        onFinishCleanDeb: {//清理成功时收到的信号
            if (msg == "") {
                //清理取消，解禁按钮
                actionBtn.enabled = true;
                toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
            }
            else if (msg == "kernel") {
                if (root.btnFlag == "kernel_work") {
                    //清理成功完成，解禁按钮
                    actionBtn.enabled = true;
                    root.state = "KernelWorkFinish";
                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                    root.flag = true;
                    root.getData();
                }
            }
        }
    }

    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    //titlebar
    Row {
        id: titlebar
        spacing: 20
        width: parent.width
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27}
        Image {
            id: refreshArrow
            source: "../img/toolWidget/deb-max.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: root.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: root.description
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    Row{
        anchors { top: parent.top; topMargin: 20;right: parent.right ; rightMargin: 40 }
        spacing: 20
        Row {
            spacing: 20
            Item {
                id: backBtn
                visible: false
                width: 60
                height: 29
                Text {
                    id:backText
                    height: 10
                    anchors.centerIn: parent
                    text: qsTr("Go back")//返回
                    font.pointSize: 10
                    color: "#318d11"
                }
                Rectangle {
                    id: btnImg
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: backText.width
                    height: 1
                    color: "transparent"
                }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: btnImg.color = "#318d11"
                    onPressed: btnImg.color = "#318d11"
                    onReleased: btnImg.color = "#318d11"
                    onExited: btnImg.color = "transparent"
                    onClicked: {
                        mainModel.clear();
                        subModel.clear();//内容清空
                        root.kernelNum = 0;//隐藏滑动条
                        root.arrowShow = 0;//伸缩图标隐藏
                        root.state = "KernelWorkAGAIN";//按钮的状态恢复初始值
                    }
                }
            }

            Item {
                id: rescanBtn
                visible: false
                width: 49
                height: 29
                Text {
                    id:rescanText
                    height: 10
                    anchors.centerIn: parent
                    text: qsTr("Scan again")//重新扫描
                    font.pointSize: 10
                    color: "#318d11"
                }
                Rectangle {
                    id: btnImg2
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: rescanText.width
                    height: 1
                    color: "transparent"
                }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: btnImg2.color = "#318d11"
                    onPressed: btnImg2.color = "#318d11"
                    onReleased: btnImg2.color = "#318d11"
                    onExited: btnImg2.color = "transparent"
                    onClicked: {
                        actionBtn.text = qsTr("Start scanning");//开始扫描
                        root.btnFlag = "kernel_scan";
                        backBtn.visible = false;
                        rescanBtn.visible = false;
                        subModel.clear();//内容清空
                        root.arrowShow = 0;//伸缩图标隐藏
                        root.flag = false;
                        root.getData();//重新获取数据
                    }
                }
            }
        }

        Common.Button {
            id: actionBtn
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: qsTr("Start scanning")//开始扫描
            fontsize: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {//sessiondbus服务已经成功启动了
                    if(!sudodispatcher.getUKSignalFlag()) {
                        sudodispatcher.setUKSignalFlag(true);
                        sudodispatcher.bind_signals_after_dbus_start();
                    }
                    if (root.btnFlag == "kernel_scan") {//扫描
                        root.flag = false;
                        root.getData();
                    }
                    else if (root.btnFlag == "kernel_work") {//清理
                        if(root.resultFlag) {//扫描得到的实际内容存在时
                            //开始清理时，禁用按钮，等到清理完成后解禁
                            actionBtn.enabled = false;
                            sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_kernel_args(), "kernel");
                            root.arrowShow = 1;
                        }
                        else {//扫描得到的实际内容不存在时
                            //友情提示：        对不起，您没有选择需要清理的项，请确认！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                        }
                    }
                }
                else {//sessiondbus服务还没有启动
                    sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                        if(!sudodispatcher.getUKSignalFlag()) {
                            if(!sudodispatcher.getUKSignalFlag()) {
                                sudodispatcher.setUKSignalFlag(true);
                                sudodispatcher.bind_signals_after_dbus_start();
                            }
                            if (root.btnFlag == "kernel_scan") {//扫描
                                root.flag = false;
                                root.getData();
                            }
                            else if (root.btnFlag == "kernel_work") {//清理
                                if(root.resultFlag) {//扫描得到的实际内容存在时
                                    //开始清理时，禁用按钮，等到清理完成后解禁
                                    actionBtn.enabled = false;
                                    sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_kernel_args(), "kernel");
                                    root.arrowShow = 1;
                                }
                                else {//扫描得到的实际内容不存在时
                                    //友情提示：        对不起，您没有选择需要清理的项，请确认！
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //分割条
    Rectangle {
        id: splitbar
        anchors {
            top: titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        height: 1
        color: "#d8e0e6"
    }

    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 20
        anchors.left:parent.left
        anchors.leftMargin: 27
        height: root.height -titlebar.height - 37
        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.kernelNum + 1) * 40
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: Cleardelegate{
                    sub_num: root.subNum//001
                    sub_model: subModel
                    btn_flag: root.btnFlag
                    arrow_display: root.arrowShow
                    delegate_flag: root.positionFlag
                    onSubpressed: { root.kernelNum = hMark }
                    onCheckchanged: { root.resultFlag = checkchange }
                }
                cacheBuffer: 1000
                opacity: 1
                spacing: 10
                snapMode: ListView.NoSnap
                boundsBehavior: Flickable.DragOverBounds
                currentIndex: 0
                preferredHighlightBegin: 0
                preferredHighlightEnd: preferredHighlightBegin
                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }
    }

    states: [
        State {
            name: "KernelWork"
            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning") }//开始清理
            PropertyChanges { target: root; btnFlag: "kernel_work" }
            PropertyChanges { target: backBtn; visible: true}
            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "KernelWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "kernel_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "KernelWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "kernel_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "KernelWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "kernel_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "KernelWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: root; btnFlag: "kernel_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        }
    ]
}
