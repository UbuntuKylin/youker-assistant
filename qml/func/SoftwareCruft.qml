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

Item {
    id:root
    width: parent.width
    height: 435
    property string sof_title: qsTr("Software Center buffer depth cleaning")//软件中心缓存深度清理
    property string sof_description: qsTr("Deep cleaning software center cache, to save disk space")//深度清理软件中心缓存,节省磁盘空间
    property string btnFlag: "software_scan"//扫描或者清理的标记：software_scan/software_work
    property int subNum: 0//扫描后得到的software的项目总数
    property int softNum: subNum//001

    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int arrowShow: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool positionFlag: true//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    ListModel {
        id: mainModel
    }
    ListModel {
        id: subModel
    }

    function remove_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(0, need_str.lastIndexOf("/"));
        return need_str;
    }

    //得到softcenter缓存
    function getData() {
        var software_data = sessiondispatcher.scan_softwarecenter_cruft_qt();
        if (software_data.length === 0) {
            root.resultFlag = false;//扫描内容不存在
        }
        else {
            root.subNum = software_data.length;//001
            systemdispatcher.clear_software_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< software_data.length; i++) {
            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
                var splitlist = software_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
                    systemdispatcher.set_software_args(splitlist[0]);
                }
            }
            root.subNum -= num;//001
            root.softNum = root.subNum;//001
            if(root.softNum != 0) {
                root.resultFlag = true;//扫描的实际有效内容存在
                mainModel.clear();
                //软件中心缓存清理     用户可以根据扫描结果选择性地清理软件中心缓存,缓存路径为:
                mainModel.append({"itemTitle": qsTr("Software Center buffer cleaning"),
                                 "picture": "../img/toolWidget/software-min.png",
                                 "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/",
                                 "flags": "clear_software"})
            }
            else {
                root.resultFlag = false;//扫描的实际有效内容不存在
            }
        }

        if(root.resultFlag == false) {
            root.state = "SoftwareWorkEmpty";
            root.arrowShow = 0;
            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                //友情提示：      扫描内容为空，不再执行清理！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else {//清理software后的重新获取数据，此时不需要显示对话框
                root.flag = false;
            }
        }
        else if(root.resultFlag == true) {
            if(flag == false) {//点击扫描时的获取数据，此时显示该对话框
                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
            }
            else {//清理software后的重新获取数据，此时不需要显示对话框
                root.flag = false;
            }
            root.arrowShow = 1;
            root.state = "SoftwareWork";
            actionBtn.text = qsTr("Start cleaning");//开始清理
            root.btnFlag = "software_work";
            backBtn.visible = true;
            rescanBtn.visible = true;
        }
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (root.btnFlag == "software_work") {
                if (msg == "software") {
                    root.state = "SoftwareWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (root.btnFlag == "software_work") {
                if (msg == "") {
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "software") {
                    root.state = "SoftwareWorkFinish";
                    toolkits.alertMSG(qsTr("Cleaned!"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
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
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
        Image {
            id: refreshArrow
            source: "../img/toolWidget/software-max.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: root.sof_title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: root.sof_description
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
                        root.softNum = 0;//隐藏滑动条
                        root.arrowShow = 0;//伸缩图标隐藏
                        root.state = "SoftwareWorkAGAIN";//按钮的状态恢复初始值
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
                        root.btnFlag = "software_scan";
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
                if (root.btnFlag == "software_scan") {//扫描
                    root.flag = false;
                    root.getData();
                }
                else if (root.btnFlag == "software_work") {//清理
                    if(root.resultFlag) {//扫描得到的实际内容存在时
                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
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
        height: root.height - titlebar.height - 37
        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.softNum + 1) * 40
            //垃圾清理显示内容
            ListView {
                height: parent.height
                model: mainModel
                delegate: Cleardelegate{
                    sub_num: root.subNum//001
                    sub_model: subModel
                    btn_flag: root.btnFlag
                    arrow_display: root.arrowShow
                    delegate_flag: root.positionFlag
                    onSubpressed: {root.softNum = hMark}
                    //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                    onCheckchanged: {root.resultFlag = checkchange}
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
            name: "SoftwareWork"
            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning") }//开始清理
            PropertyChanges { target: root; btnFlag: "software_work" }
            PropertyChanges { target: backBtn; visible: true}
            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "SoftwareWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "software_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "SoftwareWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "software_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "SoftwareWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "software_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "SoftwareWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "software_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        }
    ]
}
