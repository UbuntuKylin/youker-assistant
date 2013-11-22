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
    property string btn_text: qsTr("Start scanning")//开始扫描
    property string apt_title: qsTr("The package management depth cleaning")//包管理深度清理
    property string apt_description: qsTr("Deep cleaning package management of deb package, to save disk space")//深度清理包管理残留的deb包,节省磁盘空间
    property string apt_btn_flag: "apt_scan"
    property int apt_sub_num: 0
    property bool apt_check_flag: false//判断扫描后的实际内容是否为空的标记
    property bool apt_null_flag: false
    property int apt_num: apt_sub_num
    property int arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool position_flag: true//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    ListModel {
        id: mainModel
    }
    ListModel {
        id: subModel
    }
    //得到apt缓存
    function getData() {
        var apt_data = sessiondispatcher.scan_apt_cruft_qt();
        if (apt_data.length === 0) {
            root.apt_null_flag = true;
        }
        else {
            root.apt_null_flag = false;
        }
        root.apt_sub_num = apt_data.length;
        systemdispatcher.clear_apt_args();
        subModel.clear();
        var num = 0;
        for (var i=0; i< apt_data.length; i++) {
        //sina.com.cn<2_2>10
            var splitlist = apt_data[i].split("<2_2>");
            if (splitlist[0] == "") {
                num++;
            }
            else {
                subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
                systemdispatcher.set_apt_args(splitlist[0]);
            }
        }
        root.apt_sub_num -= num;
        apt_num = apt_sub_num
        if(apt_num != 0) {
            root.apt_check_flag = true;//扫描的实际有效内容存在
        }
        else {
            root.apt_check_flag = false;//扫描的实际有效内容不存在
        }
        mainModel.clear();
        //包管理清理        用户可以根据扫描结果选择性地清理包管理残留包,缓存路径为:/var/cache/apt/archives/
        mainModel.append({"itemTitle": qsTr("The package management cleaning"),
                         "picture": "../img/toolWidget/apt-min.png",
                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/"),
                         "flags": "clear_apt"})


        if(root.apt_check_flag == false) {
            root.state = "AptWorkEmpty";
            root.arrow_show = 0;
            if(root.flag == false) {
                //友情提示：      扫描内容为空，不再执行清理！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else {
                root.flag = false;
            }
        }
        else if(root.apt_check_flag == true) {
            if(flag == false) {
                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
            }
            else {
                root.flag = false;
            }
            root.arrow_show = 1;
            root.state = "AptWork";
            apt_bitButton.text = qsTr("Start cleaning");//开始清理
            root.apt_btn_flag = "apt_work";
            backBtn.visible = true;
            rescanBtn.visible = true;
        }
    }

    Connections
    {
        target: sessiondispatcher
        onFinishScanWork: {//扫描完成时收到的信号
            if(msg == "apt") {
                root.state = "AptWork";
            }
        }
    }
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (apt_btn_flag == "apt_work") {
                if (msg == "apt") {
                    root.state = "AptWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (apt_btn_flag == "apt_work") {
                if (msg == "") {
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "apt") {
                    root.state = "AptWorkFinish";
                    toolkits.alertMSG(qsTr("Cleared"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
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
        id: apt_titlebar
        spacing: 20
        width: parent.width
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
        Image {
            id: apt_refreshArrow
            source: "../img/toolWidget/apt.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: root.apt_title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: root.apt_description
                wrapMode: Text.WordWrap
//                wrapMode: Text.WrapAnywhere
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
                        subModel.clear();//内容清空
                        root.arrow_show = 0;//伸缩图标隐藏
                        root.state = "AptWorkAGAIN";//按钮的状态恢复初始值
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
                        apt_bitButton.text = qsTr("Start scanning");//开始扫描
                        root.apt_btn_flag = "apt_scan";
                        backBtn.visible = false;
                        rescanBtn.visible = false;
                        subModel.clear();//内容清空
                        root.arrow_show = 0;//伸缩图标隐藏
                        root.flag = false;
                        root.getData();//重新获取数据
                    }
                }
            }
        }
        Common.Button {
            id: apt_bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            fontsize: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if (root.apt_btn_flag == "apt_scan") {//扫描
                    root.flag = false;
                    root.getData();
                }
                else if (root.apt_btn_flag == "apt_work") {//清理
                    if(root.apt_check_flag) {//扫描得到的实际内容存在时
                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_apt_args(), "apt");
                        root.arrow_show = 1;
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
        id: apt_splitbar
        anchors {
            top: apt_titlebar.bottom
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
        anchors.top: apt_titlebar.bottom
        anchors.topMargin: 20//30
        anchors.left:parent.left
        anchors.leftMargin: 27
        height: root.height -apt_titlebar.height - 37//50
        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.apt_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: apt_listView
                height: parent.height
                model: mainModel
                delegate: Cleardelegate{
                    sub_num: apt_sub_num; sub_model: subModel; btn_flag: apt_btn_flag; arrow_display: root.arrow_show;
                    delegate_flag: root.position_flag
                    onSubpressed: {root.apt_num=hMark}
                    onCheckchanged: {root.apt_check_flag=checkchange}
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
        }//Item
    }//ScrollArea

    states: [
        State {
            name: "AptWork"
            PropertyChanges { target: apt_bitButton; text:qsTr("Start cleaning")}//开始清理
            PropertyChanges { target: root; apt_btn_flag: "apt_work" }
            PropertyChanges { target: backBtn; visible: true}
            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "AptWorkAGAIN"
            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkError"
            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkFinish"
            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkEmpty"
            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        }
    ]
}









//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string btn_text: qsTr("Start scanning")//开始扫描
//    property string apt_title: qsTr("The package management depth cleaning")//包管理深度清理
//    property string apt_description: qsTr("Deep cleaning package management of deb package, to save disk space")//深度清理包管理残留的deb包,节省磁盘空间
//    property string apt_btn_flag: "apt_scan"
//    property ListModel listmodel: apt_mainModel
//    property ListModel apt_submodel: apt_subModel
//    property int apt_sub_num: 0
//    property string apt_work_result: ""
//    property bool apt_check_flag: true
//    property bool apt_null_flag: false
//    property int apt_num: apt_sub_num
//    property int deleget_arrow :0

//    signal apt_signal(string apt_msg);
//    onApt_signal: {
//        if (apt_msg == "AptWork") {
//            //get data of cookies
//            var apt_data = sessiondispatcher.scan_apt_cruft_qt();
//            if (apt_data == "") {
//                root.apt_null_flag = true;
//                if(apt_statusImage.visible == true)
//                    apt_statusImage.visible = false;
//            }
//            else {
//                root.apt_null_flag = false;
//                apt_statusImage.visible = true;
//            }
//            root.apt_sub_num = apt_data.length;
//            systemdispatcher.clear_apt_args();
//            apt_subModel.clear();
//            var num = 0;
//            for (var i=0; i< apt_data.length; i++) {
//            //sina.com.cn<2_2>10
//                var splitlist = apt_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    apt_subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
//                    systemdispatcher.set_apt_args(splitlist[0]);
//                }
//            }
//            root.apt_sub_num -= num;
//            apt_num=apt_sub_num
//            if(apt_num!=0)
//                apt_check_flag=true;
//            apt_mainModel.clear();
//            //包管理清理        用户可以根据扫描结果选择性地清理包管理残留包,缓存路径为:/var/cache/apt/archives/
//            apt_mainModel.append({"itemTitle": qsTr("The package management cleaning"),
//                             "picture": "../img/toolWidget/apt-min.png",
//                             "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/"),
//                             "flags": "clear_apt",
//                            "attributes":
//                                 [{"subItemTitle": "Cookies1"},
//                                 {"subItemTitle": "Cookies2"},
//                                 {"subItemTitle": "Cookies3"},
//                                 {"subItemTitle": "Cookies4"}]
//                             })
//        }
//    }



//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
////             if (apt_btn_flag == "apt_scan") {
////                 titleBar.apt_work_result = msg;
////                 titleBar.state = "AptWork";
////             }
////         }
//        onFinishCleanWorkError: {
//            if (apt_btn_flag == "apt_work") {
//                if (msg == "apt") {
//                    root.apt_work_result = msg;
//                    root.state = "AptWorkError";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (apt_btn_flag == "apt_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "apt") {
//                    root.apt_work_result = msg;
//                    root.state = "AptWorkFinish";
//                    toolkits.alertMSG(qsTr("Cleared"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    apt_signal("AptWork");
//                }
//            }
//        }
//    }

//    ListModel {
//        id: apt_mainModel
//    }

//    ListModel {
//        id: apt_subModel
//    }

//    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }
//    //titlebar
//    Row {
//        id: apt_titlebar
//        spacing: 20
//        width: parent.width
////        height: 50
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: apt_refreshArrow
//            source: "../img/toolWidget/apt.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                width: 500
//                text: root.apt_title
//                wrapMode: Text.WrapAnywhere
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                width: 500
//                text: root.apt_description
//                wrapMode: Text.WrapAnywhere
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20

//        //status picture
////        Image {
////            id: apt_statusImage
////            source: "../img/toolWidget/unfinish.png"
////            fillMode: "PreserveAspectFit"
////            smooth: true
////            anchors.verticalCenter: parent.verticalCenter
////        }
//        Common.StatusImage {
//            id: apt_statusImage
//            visible: false
//            iconName: "yellow.png"
//            text: qsTr("Unfinished")//未完成
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Button {
//            id: apt_bitButton
//            width: 120
//            height: 39
//            hoverimage: "green1.png"
//            text: root.btn_text
//            fontsize: 15
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                if(apt_check_flag)
//                {
//                //apt cruft
//                 if (apt_btn_flag == "apt_scan") {
//                     apt_signal("AptWork");
//                     if(root.apt_null_flag == true) {
//                        root.state = "AptWorkEmpty";
//                         deleget_arrow=0;
//                         //友情提示：      扫描内容为空，不再执行清理！
//                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                     else if(root.apt_null_flag == false)
//                     {
//                        root.state = "AptWork";
//                         deleget_arrow=1;
//                         toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                     }
//                 }
//                 else if (apt_btn_flag == "apt_work") {
//                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_apt_args(), "apt");
//                     deleget_arrow=1;
//                 }
//                }
//                else
//                     sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//            }//友情提示：        对不起，您没有选择需要清理的项，请确认！
//        }

//        SetBtn {
//            id: resetBtn
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            visible: false
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                apt_subModel.clear();
//                root.state = "AptWorkAGAIN";
//            }
//        }
//    }
//    //分割条
//    Rectangle {
//        id: apt_splitbar
//        anchors {
//            top: apt_titlebar.bottom
//            topMargin: 18
//            left: parent.left
//            leftMargin: 2
//        }
//        width: parent.width - 4
//        height: 1
//        color: "#d8e0e6"
//    }

//    Common.ScrollArea {
//        frame:false
//        anchors.top: apt_titlebar.bottom
//        anchors.topMargin: 20//30
//        anchors.left:parent.left
//        anchors.leftMargin: 27
//        height: root.height -apt_titlebar.height - 37//50
//        width: parent.width - 27 -2
//        Item {
//            width: parent.width
//            height: (root.apt_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
//            //垃圾清理显示内容
//            ListView {
//                id: apt_listView
//                height: parent.height
//                model: apt_mainModel
//                delegate: Cleardelegate{
//                    sub_num: apt_sub_num;sub_model: apt_subModel;btn_flag: apt_btn_flag;arrow_display:deleget_arrow;
//                    delegate_flag: true
//                    onSubpressed: {root.apt_num=hMark}
//                    onCheckchanged: {root.apt_check_flag=checkchange}
//                  }
//                cacheBuffer: 1000
//                opacity: 1
//                spacing: 10
//                snapMode: ListView.NoSnap
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
//            }
//        }//Item
//    }//ScrollArea

//    states: [
//        State {
//            name: "AptWork"
//             PropertyChanges { target: apt_bitButton; text:qsTr("Start cleaning")}//开始清理
//            PropertyChanges { target: root; apt_btn_flag: "apt_work" }
//            PropertyChanges { target: apt_statusImage; visible: true; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
//        },
//        State {
//            name: "AptWorkAGAIN"
//            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
//            PropertyChanges { target: apt_statusImage; visible: false }
//        },
//        State {
//            name: "AptWorkError"
//            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
//            PropertyChanges { target: apt_statusImage; visible: true; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
//        },
//        State {
//            name: "AptWorkFinish"
//            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
//            PropertyChanges { target: apt_statusImage; visible: true; iconName: "green.png"; text: qsTr("Completed")}//已完成
//        },
//        State {
//            name: "AptWorkEmpty"
//            PropertyChanges { target: apt_bitButton; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
//            PropertyChanges { target: apt_statusImage;  visible: false}
//        }
//    ]
//}
