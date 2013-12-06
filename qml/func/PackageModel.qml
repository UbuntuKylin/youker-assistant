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
import "./bars" as Bars
Item {
    id:home
    width: parent.width
    height: 435

    Rectangle {
        id: masklayer2
        width: parent.width
        height: parent.height
        x: (parent.width * 1.5)
        Connections
        {
            target: sudodispatcher
            //得到数据，显示在进度条上
            onSendProgressToQML: {
                progressTitle.text = msg;
            }
        }
        //背景
        Image {
            source: "../img/skin/bg-middle.png"
            anchors.fill: parent
        }

        Column {
            anchors.centerIn: parent
            spacing: 5
            AnimatedImage {
//                anchors.centerIn: parent
                width: 16
                height: 16
                source: "../img/icons/move.gif"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: progressTitle
                text: qsTr("Software operation schedule")//软件操作进度
                color: "#318d11"
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Bars.Progress {
                id: progress
                value: 0
                background: "../../img/skin/progress-bg.png"
                color: "#086794"//"#383838"
                secondColor: "#318d11"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        SetBtn {
            id: resetBtn2
            width: 12
            height: 15
            iconName: "revoke.png"
            anchors {
                left: parent.left
                leftMargin: 10
                top: parent.top
                topMargin: 10
            }
            onClicked: {
                home.state = "NormalState";
            }
        }
    }

    Rectangle {
        id: root
        width: parent.width
        height: parent.height
//        x: (parent.width * 1.5)
        property string title: qsTr("Uninstall unnecessary procedures")//卸载不必要的程序
        property string description: qsTr("Clean installed dependent program, to improve system performance")//清理软件安装过程中安装的依赖程序，提高系统性能
        property string btnFlag: "package_scan"//扫描或者清理的标记：package_scan/package_work
        property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
        property int subNum: 0//扫描后得到的deb的项目总数
        property int debNum: subNum//001
        property int arrowShow: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property bool positionFlag: false//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
        property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

        ListModel { id: mainModel }
        ListModel { id: subModel }

        //得到package
        function getData() {
            var unneed_data = sessiondispatcher.scan_unneed_packages_qt();
            if (unneed_data.length === 0) {//扫描内容不存在
                root.resultFlag = false;
            }
            else {
                root.subNum = unneed_data.length;//001
                systemdispatcher.clear_package_args();
                subModel.clear();
                var num = 0;
                for (var i=0; i< unneed_data.length; i++) {
                //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
                    var splitlist = unneed_data[i].split("<2_2>");
                    if (splitlist[0] == "") {
                        num++;
                    }
                    else {
                        subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
                        systemdispatcher.set_package_args(splitlist[0]);
                    }
                }
                root.subNum -= num;//001
                root.debNum = root.subNum;//001
                if(root.debNum != 0) {
                    root.resultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    root.resultFlag = false;//扫描的实际有效内容不存在
                }
                mainModel.clear();
                //卸载不必要的程序         用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦
                mainModel.append({"itemTitle": qsTr("Uninstall unnecessary procedures"),
                                 "picture": "../img/toolWidget/deb-min.png",
                                 "detailstr": qsTr("User can selectively clean installed program no longer need according to the scan results, make the system more thin")})
            }


            if(root.resultFlag == false) {
                root.state = "UnneedWorkEmpty";
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
                root.state = "UnneedWork";
                actionBtn.text = qsTr("Start cleaning");//开始清理
                root.btnFlag = "package_work";
                backBtn.visible = true;
                rescanBtn.visible = true;
            }
        }

        Connections
        {
            target: sudodispatcher
            onFinishCleanDebError: {//清理出错时收到的信号
                if (msg == "package") {
                    if (root.btnFlag == "package_work") {
                        home.state = "NormalState";
                        //清理过程中发生错误，解禁按钮
                        actionBtn.enabled = true;
                        titleBar.state = "UnneedWorkError";
                        toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                    }
                }
            }
            onFinishCleanDeb: {//清理成功时收到的信号
                if (msg == "") {
                    //清理取消，解禁按钮
                    actionBtn.enabled = true;
                    home.state = "NormalState";
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "package") {
                    if (root.btnFlag == "package_work") {
                        //清理成功完成，解禁按钮
                        actionBtn.enabled = true;
                        root.state = "UnneedWorkFinish";
                        toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                        root.flag = true;
                        root.getData();
                        home.state = "NormalState";
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
                            root.debNum = 0;//隐藏滑动条
                            root.arrowShow = 0;//伸缩图标隐藏
                            root.state = "UnneedWorkAGAIN";//按钮的状态恢复初始值
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
                            root.btnFlag = "package_scan";
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
                        if (root.btnFlag == "package_scan") {//扫描
                            root.flag = false;
                            root.getData();
                        }
                        else if (root.btnFlag == "package_work") {//清理
                            if(root.resultFlag) {//扫描得到的实际内容存在时
                                home.state = "MaskLayerState";
                                //开始清理时，禁用按钮，等到清理完成后解禁
                                actionBtn.enabled = false;
                                sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
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
                                if (root.btnFlag == "package_scan") {//扫描
                                    root.flag = false;
                                    root.getData();
                                }
                                else if (root.btnFlag == "package_work") {//清理
                                    if(root.resultFlag) {//扫描得到的实际内容存在时
                                        home.state = "MaskLayerState";
                                        //开始清理时，禁用按钮，等到清理完成后解禁
                                        actionBtn.enabled = false;
                                        sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
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
                height: (root.debNum + 1) * 40
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
                        onSubpressed: { root.debNum = hMark }
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
                name: "UnneedWork"
                PropertyChanges { target: actionBtn; text:qsTr("Start cleaning") }//开始清理
                PropertyChanges { target: root; btnFlag: "package_work" }
                PropertyChanges { target: backBtn; visible: true}
                PropertyChanges { target: rescanBtn; visible: true}
            },
            State {
                name: "UnneedWorkAGAIN"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
                PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "UnneedWorkError"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
                PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "UnneedWorkFinish"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
                PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "UnneedWorkEmpty"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
                PropertyChanges { target: rescanBtn; visible: false}
            }
        ]
    }


    states: [
        State {
            name: "NormalState"
            PropertyChanges { target: root; x: 0 }
            PropertyChanges { target: masklayer2; x: (parent.width * 1.5) }
        },

        State {
            name: "MaskLayerState"
            PropertyChanges { target: masklayer2; x: 0 }
            PropertyChanges { target: progressTitle; text: qsTr("Software operation schedule") }//软件操作进度
            PropertyChanges { target: progress; value: 0 }
            PropertyChanges { target: root; x: (parent.width * 1.5) }
        }
    ]
}









//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string title: qsTr("Uninstall unnecessary procedures")//卸载不必要的程序
//    property string description: qsTr("Clean installed dependent program, to improve system performance")//清理软件安装过程中安装的依赖程序，提高系统性能
//    property string btnFlag: "package_scan"//扫描或者清理的标记：package_scan/package_work
//    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
//    property int subNum: 0//扫描后得到的deb的项目总数
//    property int debNum: subNum//001
//    property int arrowShow: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
//    property bool positionFlag: false//传递给ClearDelegate.qml,为true时伸缩图标指向上方，为false时伸缩图标指向下方
//    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

//    ListModel { id: mainModel }
//    ListModel { id: subModel }

//    //得到package
//    function getData() {
//        var unneed_data = sessiondispatcher.scan_unneed_packages_qt();
//        if (unneed_data.length === 0) {//扫描内容不存在
//            root.resultFlag = false;
//        }
//        else {
//            root.subNum = unneed_data.length;//001
//            systemdispatcher.clear_package_args();
//            subModel.clear();
//            var num = 0;
//            for (var i=0; i< unneed_data.length; i++) {
//            //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//                var splitlist = unneed_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
//                    systemdispatcher.set_package_args(splitlist[0]);
//                }
//            }
//            root.subNum -= num;//001
//            root.debNum = root.subNum;//001
//            if(root.debNum != 0) {
//                root.resultFlag = true;//扫描的实际有效内容存在
//            }
//            else {
//                root.resultFlag = false;//扫描的实际有效内容不存在
//            }
//            mainModel.clear();
//            //卸载不必要的程序         用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦
//            mainModel.append({"itemTitle": qsTr("Uninstall unnecessary procedures"),
//                             "picture": "../img/toolWidget/deb-min.png",
//                             "detailstr": qsTr("User can selectively clean installed program no longer need according to the scan results, make the system more thin")})
////            mainModel.append({"itemTitle": qsTr("Uninstall unnecessary procedures"),
////                             "picture": "../img/toolWidget/deb-min.png",
////                             "detailstr": qsTr("User can selectively clean installed program no longer need according to the scan results, make the system more thin"),
////                             "flags": "clear_package"})
//        }


//        if(root.resultFlag == false) {
//            root.state = "UnneedWorkEmpty";
//            root.arrowShow = 0;
//            if(root.flag == false) {
//                //友情提示：      扫描内容为空，不再执行清理！
//                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//            }
//            else {
//                root.flag = false;
//            }
//        }
//        else if(root.resultFlag == true) {
//            if(root.flag == false) {
//                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//            }
//            else {
//                root.flag = false;
//            }
//            root.arrowShow = 1;
//            root.state = "UnneedWork";
//            actionBtn.text = qsTr("Start cleaning");//开始清理
//            root.btnFlag = "package_work";
//            backBtn.visible = true;
//            rescanBtn.visible = true;
//        }
//    }

//    Connections
//    {
//        target: sudodispatcher
//        onFinishCleanDebError: {//清理出错时收到的信号
//            if (msg == "package") {
//                if (root.btnFlag == "package_work") {
//                    //清理过程中发生错误，解禁按钮
//                    actionBtn.enabled = true;
//                    titleBar.state = "UnneedWorkError";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//        }
//        onFinishCleanDeb: {//清理成功时收到的信号
//            if (msg == "") {
//                //清理取消，解禁按钮
//                actionBtn.enabled = true;
//                toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
//            }
//            else if (msg == "package") {
//                if (root.btnFlag == "package_work") {
//                    //清理成功完成，解禁按钮
//                    actionBtn.enabled = true;
//                    root.state = "UnneedWorkFinish";
//                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    root.flag = true;
//                    root.getData();
//                }
//            }
//        }
//    }

//    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }

//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 20
//        width: parent.width
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27}
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/deb-max.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                width: 500
//                text: root.title
//                wrapMode: Text.WordWrap
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                width: 500
//                text: root.description
//                wrapMode: Text.WordWrap
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }

//    Row{
//        anchors { top: parent.top; topMargin: 20;right: parent.right ; rightMargin: 40 }
//        spacing: 20
//        Row {
//            spacing: 20
//            Item {
//                id: backBtn
//                visible: false
//                width: 60
//                height: 29
//                Text {
//                    id:backText
//                    height: 10
//                    anchors.centerIn: parent
//                    text: qsTr("Go back")//返回
//                    font.pointSize: 10
//                    color: "#318d11"
//                }
//                Rectangle {
//                    id: btnImg
//                    anchors.top: parent.bottom
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    width: backText.width
//                    height: 1
//                    color: "transparent"
//                }
//                MouseArea {
//                    hoverEnabled: true
//                    anchors.fill: parent
//                    onEntered: btnImg.color = "#318d11"
//                    onPressed: btnImg.color = "#318d11"
//                    onReleased: btnImg.color = "#318d11"
//                    onExited: btnImg.color = "transparent"
//                    onClicked: {
//                        mainModel.clear();
//                        subModel.clear();//内容清空
//                        root.debNum = 0;//隐藏滑动条
//                        root.arrowShow = 0;//伸缩图标隐藏
//                        root.state = "UnneedWorkAGAIN";//按钮的状态恢复初始值
//                    }
//                }
//            }

//            Item {
//                id: rescanBtn
//                visible: false
//                width: 49
//                height: 29
//                Text {
//                    id:rescanText
//                    height: 10
//                    anchors.centerIn: parent
//                    text: qsTr("Scan again")//重新扫描
//                    font.pointSize: 10
//                    color: "#318d11"
//                }
//                Rectangle {
//                    id: btnImg2
//                    anchors.top: parent.bottom
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    width: rescanText.width
//                    height: 1
//                    color: "transparent"
//                }
//                MouseArea {
//                    hoverEnabled: true
//                    anchors.fill: parent
//                    onEntered: btnImg2.color = "#318d11"
//                    onPressed: btnImg2.color = "#318d11"
//                    onReleased: btnImg2.color = "#318d11"
//                    onExited: btnImg2.color = "transparent"
//                    onClicked: {
//                        actionBtn.text = qsTr("Start scanning");//开始扫描
//                        root.btnFlag = "package_scan";
//                        backBtn.visible = false;
//                        rescanBtn.visible = false;
//                        subModel.clear();//内容清空
//                        root.arrowShow = 0;//伸缩图标隐藏
//                        root.flag = false;
//                        root.getData();//重新获取数据
//                    }
//                }
//            }
//        }

//        Common.Button {
//            id: actionBtn
//            width: 120
//            height: 39
//            hoverimage: "green1.png"
//            text: qsTr("Start scanning")//开始扫描
//            fontsize: 15
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {//sessiondbus服务已经成功启动了
//                    if(!sudodispatcher.getUKSignalFlag()) {
//                        sudodispatcher.setUKSignalFlag(true);
//                        sudodispatcher.bind_signals_after_dbus_start();
//                    }
//                    if (root.btnFlag == "package_scan") {//扫描
//                        root.flag = false;
//                        root.getData();
//                    }
//                    else if (root.btnFlag == "package_work") {//清理
//                        if(root.resultFlag) {//扫描得到的实际内容存在时
//                            //开始清理时，禁用按钮，等到清理完成后解禁
//                            actionBtn.enabled = false;
//                            sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
//                            root.arrowShow = 1;
//                        }
//                        else {//扫描得到的实际内容不存在时
//                            //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                        }
//                    }
//                }
//                else {//sessiondbus服务还没有启动
//                    sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
//                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
//                        if(!sudodispatcher.getUKSignalFlag()) {
//                            if(!sudodispatcher.getUKSignalFlag()) {
//                                sudodispatcher.setUKSignalFlag(true);
//                                sudodispatcher.bind_signals_after_dbus_start();
//                            }
//                            if (root.btnFlag == "package_scan") {//扫描
//                                root.flag = false;
//                                root.getData();
//                            }
//                            else if (root.btnFlag == "package_work") {//清理
//                                if(root.resultFlag) {//扫描得到的实际内容存在时
//                                    //开始清理时，禁用按钮，等到清理完成后解禁
//                                    actionBtn.enabled = false;
//                                    sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
//                                    root.arrowShow = 1;
//                                }
//                                else {//扫描得到的实际内容不存在时
//                                    //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }

//    //分割条
//    Rectangle {
//        id: splitbar
//        anchors {
//            top: titlebar.bottom
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
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 20
//        anchors.left:parent.left
//        anchors.leftMargin: 27
//        height: root.height -titlebar.height - 37
//        width: parent.width - 27 -2
//        Item {
//            width: parent.width
//            height: (root.debNum + 1) * 40
//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height
//                model: mainModel
//                delegate: Cleardelegate{
//                    sub_num: root.subNum//001
//                    sub_model: subModel
//                    btn_flag: root.btnFlag
//                    arrow_display: root.arrowShow
//                    delegate_flag: root.positionFlag
//                    onSubpressed: { root.debNum = hMark }
//                    onCheckchanged: { root.resultFlag = checkchange }
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
//        }
//    }

//    states: [
//        State {
//            name: "UnneedWork"
//            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning") }//开始清理
//            PropertyChanges { target: root; btnFlag: "package_work" }
//            PropertyChanges { target: backBtn; visible: true}
//            PropertyChanges { target: rescanBtn; visible: true}
//        },
//        State {
//            name: "UnneedWorkAGAIN"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "package_scan" }
//            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "UnneedWorkError"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "package_scan" }
//            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "UnneedWorkFinish"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "package_scan" }
//            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "UnneedWorkEmpty"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: root; btnFlag: "package_scan" }
//            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
//        }
//    ]
//}
