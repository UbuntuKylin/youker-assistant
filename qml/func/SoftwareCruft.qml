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
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435//420//340
    property string sof_title: qsTr("Software Center buffer depth cleaning")//软件中心缓存深度清理
    property string sof_description: qsTr("Deep cleaning software center cache, to save disk space")//深度清理软件中心缓存,节省磁盘空间
    property string sof_btn_flag: "software_scan"
    property string btn_text: qsTr("Start scanning")//开始扫描
    property int sof_sub_num: 0
    property string sof_work_result: ""
    property int sof_num:sof_sub_num
    property bool sof_null_flag: false
    property bool sof_check_flag: false
    property int arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool position_flag: true//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
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
            root.sof_null_flag = true;
        }
        else {
            root.sof_null_flag = false;
        }

        root.sof_sub_num = software_data.length;
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
        root.sof_sub_num -= num;
        sof_num = sof_sub_num;
        if(sof_num != 0) {
            root.sof_check_flag = true;//扫描的实际有效内容存在
        }
        else {
            root.sof_check_flag = false;//扫描的实际有效内容不存在
        }
        mainModel.clear();
        //软件中心缓存清理     用户可以根据扫描结果选择性地清理软件中心缓存,缓存路径为:
        mainModel.append({"itemTitle": qsTr("Software Center buffer cleaning"),
                         "picture": "../img/toolWidget/software-min.png",
                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/",
                         "flags": "clear_software"})

        if(root.sof_check_flag == false) {
            root.state = "SoftwareWorkEmpty";
            root.arrow_show = 0;
            if(root.flag == false) {
                //友情提示：      扫描内容为空，不再执行清理！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else {
                root.flag = false;
            }
        }
        else if(root.sof_check_flag == true) {
            if(flag == false) {
                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
            }
            else {
                root.flag = false;
            }
            root.arrow_show = 1;
            root.state = "SoftwareWork";
            sof_bitButton.text = qsTr("Start cleaning");//开始清理
            root.sof_btn_flag = "software_work";
            backBtn.visible = true;
            rescanBtn.visible = true;
        }
    }

    Connections
    {
        target: sessiondispatcher
        onFinishScanWork: {//扫描完成时收到的信号
            if(msg == "softwarecenter") {
                root.state = "SoftwareWork";
            }
        }
    }
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (sof_btn_flag == "software_work") {
                if (msg == "software") {
                    root.sof_work_result = msg;
                    root.state = "SoftwareWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (sof_btn_flag == "software_work") {
                if (msg == "") {
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "software") {
                    root.sof_work_result = msg;
                    root.state = "SoftwareWorkFinish";
                    toolkits.alertMSG(qsTr("Cleared!"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                    root.flag = true;
                    root.getData();
                }
            }
        }
    }

//    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }


    //sof_titlebar
    Row {
        id: sof_titlebar
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
                wrapMode: Text.WrapAnywhere
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: root.sof_description
                wrapMode: Text.WrapAnywhere
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
                        sof_bitButton.text = qsTr("Start scanning");//开始扫描
                        root.sof_btn_flag = "software_scan";
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
            id: sof_bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            fontsize: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if (root.sof_btn_flag == "software_scan") {//扫描
                    root.flag = false;
                    root.getData();
                }
                else if (root.sof_btn_flag == "software_work") {//清理
                    if(root.sof_check_flag) {//扫描得到的实际内容存在时
                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
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
        id: splitbar
        anchors {
            top: sof_titlebar.bottom
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
        anchors.top: sof_titlebar.bottom
        anchors.topMargin: 20//30
        anchors.left:parent.left
        anchors.leftMargin: 27
        height: root.height -sof_titlebar.height - 37//50
        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.sof_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: sof_listView
                height: parent.height
                model: mainModel
                delegate: Cleardelegate{
                    sub_num: sof_sub_num; sub_model: subModel;btn_flag: sof_btn_flag; arrow_display: root.arrow_show;
                    delegate_flag: root.position_flag
                    onSubpressed: {root.sof_num=hMark}
                    onCheckchanged: {root.sof_check_flag=checkchange}
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
            name: "SoftwareWork"
            PropertyChanges { target: sof_bitButton; text:qsTr("Start cleaning") }//开始清理
            PropertyChanges { target: root; sof_btn_flag: "software_work" }
            PropertyChanges { target: backBtn; visible: true}
            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "SoftwareWorkAGAIN"
            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
            PropertyChanges { target: backBtn; visible: false}
            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "SoftwareWorkError"
            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
        },
        State {
            name: "SoftwareWorkFinish"
            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
        },
        State {
            name: "SoftwareWorkEmpty"
            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
        }
    ]
}



//Item {
//    id:root
//    width: parent.width
//    height: 435//420//340
//    property string sof_title: qsTr("Software Center buffer depth cleaning")//软件中心缓存深度清理
//    property string sof_description: qsTr("Deep cleaning software center cache, to save disk space")//深度清理软件中心缓存,节省磁盘空间
//    property string sof_btn_flag: "software_scan"
//    property string btn_text: qsTr("Start scanning")//开始扫描
//    property int sof_sub_num: 0
//    property string sof_work_result: ""
//    property int sof_num:sof_sub_num
//    property bool sof_null_flag: false
//    property bool sof_check_flag:true
//    property int deleget_arrow :0

//    function remove_last_name(str)
//    {
//        var need_str = str;
//        need_str = need_str.substr(0, need_str.lastIndexOf("/"));
//        return need_str;
//    }

//    signal software_signal(string software_msg);
//    onSoftware_signal: {
//        if (software_msg == "SoftwareWork") {
//            //get data of cookies
////            var software_data = systemdispatcher.scan_softwarecenter_cruft_qt();
//            var software_data = sessiondispatcher.scan_softwarecenter_cruft_qt();
//            if (software_data == "") {
//                root.sof_null_flag = true;
//                if(sof_statusImage.visible == true)
//                    sof_statusImage.visible = false;
//            }
//            else {
//                root.sof_null_flag = false;
//                sof_statusImage.visible == true
//            }
//            root.sof_sub_num = software_data.length;
//            systemdispatcher.clear_software_args();
//            sof_subModel.clear();
//            var num = 0;
//            for (var i=0; i< software_data.length; i++) {
//            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
//                var splitlist = software_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    sof_subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
//                    systemdispatcher.set_software_args(splitlist[0]);
//                }
//            }
//            root.sof_sub_num -= num;
//            sof_num = sof_sub_num;
//            if(sof_num!=0)
//                sof_check_flag=true;
//            sof_mainModel.clear();
//            //软件中心缓存清理     用户可以根据扫描结果选择性地清理软件中心缓存,缓存路径为:
//            sof_mainModel.append({"itemTitle": qsTr("Software Center buffer cleaning"),
//                             "picture": "../img/toolWidget/software-min.png",
//                             "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/",
//                             "flags": "clear_software",
//                             "attributes":
//                                 [{"subItemTitle": "Cookies1"},
//                                 {"subItemTitle": "Cookies2"},
//                                 {"subItemTitle": "Cookies3"},
//                                 {"subItemTitle": "Cookies4"}]
//                             })
//        }
//    }

//    ListModel {
//        id: sof_mainModel
//    }

//    ListModel {
//        id: sof_subModel
//    }

//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
//        //             if (sof_btn_flag == "software_scan") {
//        //                 sof_titlebar.work_result = msg;
//        //                 sof_titlebar.state = "SoftwareWork";
//        //             }

////         }
//        onFinishCleanWorkError: {
//            if (sof_btn_flag == "software_work") {
//                if (msg == "software") {
//                    root.sof_work_result = msg;
//                    root.state = "SoftwareWorkError";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (sof_btn_flag == "software_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "software") {
//                    root.sof_work_result = msg;
//                    root.state = "SoftwareWorkFinish";
//                    toolkits.alertMSG(qsTr("Cleared!"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    software_signal("SoftwareWork");
//                }
//            }
//        }
//    }

////    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }


//    //sof_titlebar
//    Row {
//        id: sof_titlebar
//        spacing: 20
//        width: parent.width
////        height: 50
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/software-max.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                width: 500
//                text: root.sof_title
//                wrapMode: Text.WrapAnywhere
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                width: 500
//                text: root.sof_description
//                wrapMode: Text.WrapAnywhere
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20

//        Common.StatusImage {
//            id: sof_statusImage
//            visible: false
//            iconName: "yellow.png"
//            text: qsTr("Unfinished")//未完成
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Button {
//            id: sof_bitButton
//            width: 120
//            height: 39
//            hoverimage: "green1.png"
//            text: root.btn_text
//            fontsize: 15
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                if(root.sof_check_flag)
//                {
//                //software cruft
//                 if (sof_btn_flag == "software_scan") {
//                     software_signal("SoftwareWork");
//                     if(root.sof_null_flag == true) {
//                        root.state = "SoftwareWorkEmpty";
//                         deleget_arrow=0;
//                         //友情提示：         扫描内容为空，不再执行清理！
//                         sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                     else if(root.sof_null_flag == false)
//                     {
//                        root.state = "SoftwareWork";
//                         deleget_arrow=1;
//                         toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                     }
//                 }
//                 else if (sof_btn_flag == "software_work") {
//                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
//                     deleget_arrow=1;
//                 }
//                }
//                else {
//                    //友情提示：           对不起，您没有选择需要清理的项，请确认！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                }
//            }
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
//                sof_subModel.clear();
//                root.state = "SoftwareWorkAGAIN";
//            }
//        }
//    }
//    //分割条
//    Rectangle {
//        id: splitbar
//        anchors {
//            top: sof_titlebar.bottom
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
//        anchors.top: sof_titlebar.bottom
//        anchors.topMargin: 20//30
//        anchors.left:parent.left
//        anchors.leftMargin: 27
//        height: root.height -sof_titlebar.height - 37//50
//        width: parent.width - 27 -2
//        Item {
//            width: parent.width
//            height: (root.sof_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
//            //垃圾清理显示内容
//            ListView {
//                id: sof_listView
//                height: parent.height
//                model: sof_mainModel
//                delegate: Cleardelegate{
//                    sub_num: sof_sub_num;sub_model: sof_subModel;btn_flag: sof_btn_flag;arrow_display:deleget_arrow;
//                    delegate_flag: true
//                    onSubpressed: {root.sof_num=hMark}
//                    onCheckchanged: {root.sof_check_flag=checkchange}
//                }
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
//            name: "SoftwareWork"
//             PropertyChanges { target: sof_bitButton; text:qsTr("Start cleaning") }//开始清理
//            PropertyChanges { target: root; sof_btn_flag: "software_work" }
//            PropertyChanges { target: sof_statusImage; visible: true; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
//        },
//        State {
//            name: "SoftwareWorkAGAIN"
//            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
//            PropertyChanges { target: sof_statusImage; visible: false }
//        },
//        State {
//            name: "SoftwareWorkError"
//            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
//            PropertyChanges { target: sof_statusImage; visible: true; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
//        },
//        State {
//            name: "SoftwareWorkFinish"
//            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
//            PropertyChanges { target: sof_statusImage; visible: true; iconName: "green.png"; text: qsTr("Completed")}//已完成
//        },
//        State {
//            name: "SoftwareWorkEmpty"
//            PropertyChanges { target: sof_bitButton; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
//            PropertyChanges { target: sof_statusImage; visible: false}
//        }
//    ]
//}
