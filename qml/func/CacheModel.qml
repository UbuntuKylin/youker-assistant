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
//扫描后取消两个checkbox，此时点击返回，再点击扫描，都为true，再点击清理，则都为false



//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string apt_title: qsTr("The cruft management depth cleaning")//缓存管理深度清理
//    property string apt_description: qsTr("Deep cleaning cruft, to save disk space")//深度清理缓存,节省磁盘空间
//    property string btnFlag: "apt_scan"//扫描或者清理的标记：apt_scan/apt_work
//    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
//    property bool softresultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
//    property int aptsubNum: 0//扫描后得到的apt的项目总数
////    property int aptNum: aptsubNum//001
//    property int aptNum
//    property int softsubNum: 0//扫描后得到的apt的项目总数
//    property int softNum: softsubNum//001
//    property bool splitFlag: true//传递给ClearDelegate.qml,为true时切割字符串，为false时不切割字符串
//    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

//    property int spaceValue: 20
//    property int firefox_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
//    property int chromium_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
//    property bool firefox_expanded: false
//    property bool chromium_expanded: false

//    property bool maincheck1: true
//    property bool maincheck2: true
//    property bool showNum1: false
//    property bool showNum2: false
//    ListModel { id: mainModel }
//    ListModel { id: subModel }
//    ListModel { id: softmainModel }
//    ListModel { id: softsubModel }

//    Connections
//    {
//        target: sessiondispatcher
//        onAppendContentToCacheModel: {
//            //QString flag, QString path, QString fileFlag, QString sizeValue
//            if(flag == "apt") {
//                subModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue});
//                root.aptNum += 1;
//                systemdispatcher.set_cache_args(path);
//            }
//            else if(flag == "software-center") {
//                softsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue});
//                root.softNum += 1;
//                systemdispatcher.set_cache_args(path);
//            }
//        }
//        onTellQMLCaheOver: {
//            mainModel.clear();
//            softmainModel.clear();
//            mainModel.append({"mstatus": root.maincheck1 ? "true": "false",
//                             "itemTitle": qsTr("The package management cleaning"),
//                             "picture": "../img/toolWidget/apt-min.png",
//                             "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
//            softmainModel.append({"mstatus": root.maincheck2 ? "true": "false",
//                             "itemTitle": qsTr("Software Center buffer cleaning"),
//                             "picture": "../img/toolWidget/software-min.png",
//                             "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

//            if(root.aptNum != 0) {
//                root.resultFlag = true;//扫描的实际有效内容存在
//            }
//            else {
//                root.resultFlag = false;//扫描的实际有效内容不存在
//            }
//            if(root.softNum != 0) {
//                root.softresultFlag = true;//扫描的实际有效内容存在
//            }
//            else {
//                root.softresultFlag = false;//扫描的实际有效内容不存在
//            }



//            if(root.resultFlag == false) {
//                root.showNum1 = false;
//                root.firefox_expanded = false;//伸缩箭头不扩展
//                root.firefox_arrow_show = 0;//伸缩箭头不显示
//            }
//            else if(root.resultFlag == true) {
//                root.showNum1 = true;
//                root.firefox_expanded = true;//伸缩箭头扩展
//                root.firefox_arrow_show = 1;//伸缩箭头显示
//            }
//            if(root.softresultFlag == false) {
//                root.showNum2 = false;
//                root.chromium_expanded = false;//伸缩箭头不扩展
//                root.chromium_arrow_show = 0;//伸缩箭头不显示
//            }
//            else if(root.softresultFlag == true) {
//                root.showNum2 = true;
//                root.chromium_expanded = true;//伸缩箭头扩展
//                root.chromium_arrow_show = 1;//伸缩箭头显示
//            }

//            if(root.resultFlag == false && root.softresultFlag == false) {
//                root.state = "AptWorkEmpty";
//                if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
//                    //友情提示：      扫描内容为空，不再执行清理！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                }
//                else {//清理apt后的重新获取数据，此时不需要显示对话框
//                    root.flag = false;
//                }
//            }
//            else {
//                if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
//                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                }
//                else {//清理software后的重新获取数据，此时不需要显示对话框
//                    root.flag = false;
//                }
//                root.state = "AptWork";
//                actionBtn.text = qsTr("Start cleaning");//开始清理
//                root.btnFlag = "apt_work";
//                backBtn.visible = true;
////                rescanBtn.visible = true;
//            }
//            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
//        }
//    }

//    Component.onCompleted: {
//        mainModel.append({"mstatus": root.maincheck1 ? "true": "false",
//                         "itemTitle": qsTr("The package management cleaning"),
//                         "picture": "../img/toolWidget/apt-min.png",
//                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
//        softmainModel.append({"mstatus": root.maincheck2 ? "true": "false",
//                         "itemTitle": qsTr("Software Center buffer cleaning"),
//                         "picture": "../img/toolWidget/software-min.png",
//                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

//    }

//    //得到apt缓存
////    function getaptData() {
////        var apt_data = sessiondispatcher.scan_apt_cruft_qt();
////        if (apt_data.length === 0) {
////            root.resultFlag = false;//扫描内容不存在
////        }
////        else {
////            root.aptsubNum = apt_data.length;//001
////            systemdispatcher.clear_apt_args();
////            subModel.clear();
////            var num = 0;
////            for (var i=0; i< apt_data.length; i++) {
////            //sina.com.cn<2_2>10
////                var splitlist = apt_data[i].split("<2_2>");
////                if (splitlist[0] == "") {
////                    num++;
////                }
////                else {
////                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
////                    systemdispatcher.set_apt_args(splitlist[0]);
////                }
////            }
////            root.aptsubNum -= num;//001
////            root.aptNum = root.aptsubNum;//001
////            console.log("apt num:");
////            console.log(root.aptNum);
////            if(root.aptNum != 0) {
////                root.resultFlag = true;//扫描的实际有效内容存在
////                mainModel.clear();
////                mainModel.append({"mstatus": "true",
////                                 "itemTitle": qsTr("The package management cleaning"),
////                                 "picture": "../img/toolWidget/apt-min.png",
////                                 "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})

////            }
////            else {
////                root.resultFlag = false;//扫描的实际有效内容不存在
////            }
////        }

////        if(root.resultFlag == false) {
////            root.firefox_expanded = false;//伸缩箭头不扩展
////            root.firefox_arrow_show = 0;//伸缩箭头不显示
////        }
////        else if(root.resultFlag == true) {
////            root.firefox_expanded = true;//伸缩箭头扩展
////            root.firefox_arrow_show = 1;//伸缩箭头显示
////        }
////    }

////    //得到softcenter缓存
////    function getsoftData() {
////        var software_data = sessiondispatcher.scan_softwarecenter_cruft_qt();
////        if (software_data.length === 0) {
////            root.softresultFlag = false;//扫描内容不存在
////        }
////        else {
////            root.softsubNum = software_data.length;//001
////            systemdispatcher.clear_software_args();
////            softsubModel.clear();
////            var num = 0;
////            for (var i=0; i< software_data.length; i++) {
////            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
////                var splitlist = software_data[i].split("<2_2>");
////                if (splitlist[0] == "") {
////                    num++;
////                }
////                else {
////                    softsubModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
////                    systemdispatcher.set_software_args(splitlist[0]);
////                }
////            }
////            root.softsubNum -= num;//001
////            root.softNum = root.softsubNum;//001
////            console.log("soft num:");
////            console.log(root.softNum);
////            if(root.softNum != 0) {
////                root.softresultFlag = true;//扫描的实际有效内容存在
////                softmainModel.clear();
////                softmainModel.append({"mstatus": "true",
////                                 "itemTitle": qsTr("Software Center buffer cleaning"),
////                                 "picture": "../img/toolWidget/software-min.png",
////                                 "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})
////            }
////            else {
////                root.softresultFlag = false;//扫描的实际有效内容不存在
////            }
////        }

////        if(root.softresultFlag == false) {
////            root.chromium_expanded = false;//伸缩箭头不扩展
////            root.chromium_arrow_show = 0;//伸缩箭头不显示
////        }
////        else if(root.softresultFlag == true) {
////            root.chromium_expanded = true;//伸缩箭头扩展
////            root.chromium_arrow_show = 1;//伸缩箭头显示
////        }
////    }

////    function getData() {
////        root.aptNum = 0;
////        root.softNum =0;
////        root.getaptData();
////        root.getsoftData();
////        if(root.resultFlag == false && root.softresultFlag == false) {
////            root.state = "AptWorkEmpty";
////            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
////                //友情提示：      扫描内容为空，不再执行清理！
////                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
////            }
////            else {//清理apt后的重新获取数据，此时不需要显示对话框
////                root.flag = false;
////            }
////        }
////        else {
////            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
////                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
////            }
////            else {//清理software后的重新获取数据，此时不需要显示对话框
////                root.flag = false;
////            }
////            root.state = "AptWork";
////            actionBtn.text = qsTr("Start cleaning");//开始清理
////            root.btnFlag = "apt_work";
////            backBtn.visible = true;
//////            rescanBtn.visible = true;
////        }
////        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
////    }

//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWorkError: {//清理出错时收到的信号
//            if (btnFlag == "apt_work") {
//                if (msg == "apt") {
//                    root.state = "AptWorkError";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//        }
//        onFinishCleanWork: {//清理成功时收到的信号
//            if (root.btnFlag == "apt_work") {
//                if (msg == "") {
//                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
//                }
//                else if (msg == "apt") {
//                    root.state = "AptWorkFinish";
//                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    //清理完毕后重新获取数据
//                    root.flag = true;
//                    if(root.maincheck1 && root.maincheck2) {//software-center
//                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
//                    }
//                    else {
//                        if(root.maincheck1) {
//                            sessiondispatcher.cache_scan_function_qt("apt");
//                        }
//                        else if(root.maincheck2) {
//                            sessiondispatcher.cache_scan_function_qt("software-center");
//                        }
//                    }
////                    root.getData();//清理完毕后重新获取数据
//                }
//            }
//        }
//    }

////    get_cache_arglist
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
//                wrapMode: Text.WordWrap
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                width: 500
//                text: root.apt_description
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
////                        if(root.maincheck1 == false) {
////                            root.maincheck1 = true;
////                        }
////                        if(root.maincheck2 == false) {
////                            root.maincheck2 = true;
////                        }
//                        systemdispatcher.clear_cache_args();
//                        root.showNum1 = false;
//                        root.showNum2 = false;
//                        mainModel.clear();
//                        softmainModel.clear();
//                        mainModel.append({"mstatus": "true",
//                                         "itemTitle": qsTr("The package management cleaning"),
//                                         "picture": "../img/toolWidget/apt-min.png",
//                                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
//                        softmainModel.append({"mstatus": "true",
//                                         "itemTitle": qsTr("Software Center buffer cleaning"),
//                                         "picture": "../img/toolWidget/software-min.png",
//                                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

//                        subModel.clear();//内容清空
//                        root.aptNum = 0;//隐藏滑动条
//                        root.firefox_arrow_show = 0;//伸缩图标隐藏
//                        softsubModel.clear();//内容清空
//                        root.softNum = 0;//隐藏滑动条
//                        root.chromium_arrow_show = 0;//伸缩图标隐藏
//                        scrollItem.height = 2 * 40 + root.spaceValue*2;
//                        root.state = "AptWorkAGAIN";//按钮的状态恢复初始值
//                    }
//                }
//            }
////            Item {
////                id: rescanBtn
////                visible: false
////                width: 49
////                height: 29
////                Text {
////                    id:rescanText
////                    height: 10
////                    anchors.centerIn: parent
////                    text: qsTr("Scan again")//重新扫描
////                    font.pointSize: 10
////                    color: "#318d11"
////                }
////                Rectangle {
////                    id: btnImg2
////                    anchors.top: parent.bottom
////                    anchors.horizontalCenter: parent.horizontalCenter
////                    width: rescanText.width
////                    height: 1
////                    color: "transparent"
////                }
////                MouseArea {
////                    hoverEnabled: true
////                    anchors.fill: parent
////                    onEntered: btnImg2.color = "#318d11"
////                    onPressed: btnImg2.color = "#318d11"
////                    onReleased: btnImg2.color = "#318d11"
////                    onExited: btnImg2.color = "transparent"
////                    onClicked: {
////                        if(root.maincheck1 == false) {
////                            root.maincheck1 = true;
////                        }
////                        if(root.maincheck2 == false) {
////                            root.maincheck2 = true;
////                        }
////                        systemdispatcher.clear_apt_args();
////                        systemdispatcher.clear_software_args();
////                        mainModel.clear();
////                        softmainModel.clear();
////                        mainModel.append({"mstatus": "true",
////                                         "itemTitle": qsTr("The package management cleaning"),
////                                         "picture": "../img/toolWidget/apt-min.png",
////                                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
////                        softmainModel.append({"mstatus": "true",
////                                         "itemTitle": qsTr("Software Center buffer cleaning"),
////                                         "picture": "../img/toolWidget/software-min.png",
////                                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})
////                        actionBtn.text = qsTr("Start scanning");//开始扫描
////                        root.btnFlag = "apt_scan";
////                        backBtn.visible = false;
////                        rescanBtn.visible = false;
////                        root.aptNum = 0;//隐藏滑动条
////                        root.softNum = 0;//隐藏滑动条
////                        subModel.clear();//内容清空
////                        softsubModel.clear();//内容清空
////                        root.firefox_arrow_show = 0;//伸缩图标隐藏
////                        root.chromium_arrow_show = 0;//伸缩图标隐藏
////                        root.flag = false;
////                        root.getData();//获取数据
////                    }
////                }
////            }
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
////                console.log("-----------");
////                console.log(root.maincheck1);
////                console.log(root.maincheck2);

//                if (root.btnFlag == "apt_scan") {//扫描
//                    root.flag = false;
////                    root.getData();//获取数据
//                    if(root.maincheck1 && root.maincheck2) {//software-center
//                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
//                    }
//                    else {
//                        if(root.maincheck1) {
//                            sessiondispatcher.cache_scan_function_qt("apt");
//                        }
//                        else if(root.maincheck2) {
//                            sessiondispatcher.cache_scan_function_qt("software-center");
//                        }
//                    }
//                }
//                else if (root.btnFlag == "apt_work") {//清理
//                    if(root.resultFlag || root.softresultFlag) {//扫描得到的实际内容存在时
//                        console.log(systemdispatcher.get_cache_args());
////                        console.log("--------");
////                        console.log(systemdispatcher.get_software_args());
////                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_apt_args(), "apt");
////                        root.firefox_arrow_show = 1;
//                    }
//                    else {//扫描得到的实际内容不存在时
//                        //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                    }
//                }
//            }
//        }
//    }

//    //分割条
//    Rectangle {
//        id: apt_splitbar
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
//            id: scrollItem
//            width: parent.width
//            height: 40*2 + root.spaceValue*2
//            Column {
//                spacing: root.spaceValue
//                //垃圾清理显示内容
//                ListView {
//                    id: aptListView
//                    width: parent.width
//                    height: root.firefox_expanded ? (root.aptNum + 1) * 40 : 40
//                    model: mainModel
//                    delegate: CruftDelegate{
//                        sub_num: root.aptNum//root.aptsubNum//1212
//                        sub_model: subModel
//                        btn_flag: root.btnFlag
//                        arrowFlag: "apt"
//                        showNum: root.showNum1
//                        arrow_display: root.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
//                        expanded: root.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
//                        delegate_flag: root.splitFlag
////                        controlMain: root.maincheck1
////                        onSubpressed: {root.aptNum=hMark}
//                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
//                        onCheckchanged: {
////                            root.resultFlag = checkchange;
//                            root.maincheck1 = checkchange;
//                        }
////                        onArrowClicked: {
//////                            console.lmaincheck1og("111");
//////                            console.log(str);
//////                            console.log(expand_flag);
//////                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
////                            if(cacheFlag == "apt") {//1212

////                                if(expand_flag == true) {
////                                    root.firefox_expanded = true;
////                                    if(root.chromium_expanded == true) {
////                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
////                                    }
////                                    else {
////                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
////                                    }
////                                }
////                                else {
////                                    root.firefox_expanded = false;
////                                    if(root.chromium_expanded == true) {
////                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
////                                    }
////                                    else {
////                                        scrollItem.height = 2* 40 + root.spaceValue*2;
////                                    }
////                                }
////                            }
////                        }
//                    }
//                    cacheBuffer: 1000
//                    opacity: 1
//                    spacing: 10
//                    snapMode: ListView.NoSnap
//                    boundsBehavior: Flickable.DragOverBounds
//                    currentIndex: 0
//                    preferredHighlightBegin: 0
//                    preferredHighlightEnd: preferredHighlightBegin
//                    highlightRangeMode: ListView.StrictlyEnforceRange
//                }
//                //垃圾清理显示内容
//                ListView {
//                    id: softListView
//                    width: parent.width
//                    height: root.chromium_expanded ? (root.softNum + 1) * 40 : 40
//                    model: softmainModel
//                    delegate: CruftDelegate{
//                        sub_num: root.softNum//root.softsubNum//1212
//                        sub_model: softsubModel
//                        btn_flag: root.btnFlag
//                        showNum: root.showNum2
//                        arrowFlag: "soft"
//                        arrow_display: root.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
//                        expanded: root.chromium_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
//                        delegate_flag: root.splitFlag
////                        controlMain: root.maincheck2
//                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
//                        onCheckchanged: {
////                            root.softresultFlag = checkchange;
//                            root.maincheck2 = checkchange;
//                        }
////                        onArrowClicked: {
//////                            console.log("222");
//////                            console.log(str);
//////                            console.log(expand_flag);
//////                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
////                            if(cacheFlag == "soft") {//1212
////                                if(expand_flag == true) {
////                                    root.chromium_expanded = true;
////                                    if(root.firefox_expanded == true) {
////                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
////                                    }
////                                    else {
////                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
////                                    }
////                                }
////                                else {
////                                    root.chromium_expanded = false;
////                                    if(root.firefox_expanded == true) {
////                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
////                                    }
////                                    else {
////                                        scrollItem.height = 2* 40 + root.spaceValue*2;
////                                    }
////                                }
////                            }
////                        }
//                    }
//                    cacheBuffer: 1000
//                    opacity: 1
//                    spacing: 10
//                    snapMode: ListView.NoSnap
//                    boundsBehavior: Flickable.DragOverBounds
//                    currentIndex: 0
//                    preferredHighlightBegin: 0
//                    preferredHighlightEnd: preferredHighlightBegin
//                    highlightRangeMode: ListView.StrictlyEnforceRange
//                }
//            }
//        }
//    }

//    states: [
//        State {
//            name: "AptWork"
//            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning")}//开始清理
//            PropertyChanges { target: root; btnFlag: "apt_work" }
//            PropertyChanges { target: backBtn; visible: true}
////            PropertyChanges { target: rescanBtn; visible: true}
//        },
//        State {
//            name: "AptWorkAGAIN"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "apt_scan" }
//            PropertyChanges { target: backBtn; visible: false}
////            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "AptWorkError"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "apt_scan" }
//            PropertyChanges { target: backBtn; visible: false}
////            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "AptWorkFinish"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: root; btnFlag: "apt_scan" }
//            PropertyChanges { target: backBtn; visible: false}
////            PropertyChanges { target: rescanBtn; visible: false}
//        },
//        State {
//            name: "AptWorkEmpty"
//            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: root; btnFlag: "apt_scan" }
//            PropertyChanges { target: backBtn; visible: false}
////            PropertyChanges { target: rescanBtn; visible: false}
//        }
//    ]
//}























Item {
    id:root
    width: parent.width
    height: 435
    property string apt_title: qsTr("The cruft management depth cleaning")//缓存管理深度清理
    property string apt_description: qsTr("Deep cleaning cruft, to save disk space")//深度清理缓存,节省磁盘空间
    property string btnFlag: "apt_scan"//扫描或者清理的标记：apt_scan/apt_work
    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool softresultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int aptsubNum: 0//扫描后得到的apt的项目总数
//    property int aptNum: aptsubNum//001
    property int aptNum
    property int softsubNum: 0//扫描后得到的apt的项目总数
    property int softNum: softsubNum//001
    property bool splitFlag: true//传递给ClearDelegate.qml,为true时切割字符串，为false时不切割字符串
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    property int spaceValue: 20
    property int firefox_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int chromium_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool firefox_expanded: false
    property bool chromium_expanded: false

    property bool maincheck1: true
    property bool maincheck2: true
    property bool showNum1: false
    property bool showNum2: false
    ListModel { id: mainModel }
    ListModel { id: subModel }
    ListModel { id: softmainModel }
    ListModel { id: softsubModel }

    Connections
    {
        target: sessiondispatcher
        onAppendContentToCacheModel: {
            //QString flag, QString path, QString fileFlag, QString sizeValue
            if(flag == "apt") {
                subModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue});
                root.aptNum += 1;
                systemdispatcher.set_cache_args(path);
            }
            else if(flag == "software-center") {
                softsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue});
                root.softNum += 1;
                systemdispatcher.set_cache_args(path);
            }
        }
        onTellQMLCaheOver: {
            mainModel.clear();
            softmainModel.clear();
            mainModel.append({"mstatus": root.maincheck1 ? "true": "false",
                             "itemTitle": qsTr("The package management cleaning"),
                             "picture": "../img/toolWidget/apt-min.png",
                             "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
            softmainModel.append({"mstatus": root.maincheck2 ? "true": "false",
                             "itemTitle": qsTr("Software Center buffer cleaning"),
                             "picture": "../img/toolWidget/software-min.png",
                             "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

            if(root.aptNum != 0) {
                root.resultFlag = true;//扫描的实际有效内容存在
            }
            else {
                root.resultFlag = false;//扫描的实际有效内容不存在
            }
            if(root.softNum != 0) {
                root.softresultFlag = true;//扫描的实际有效内容存在
            }
            else {
                root.softresultFlag = false;//扫描的实际有效内容不存在
            }



            if(root.resultFlag == false) {
                root.showNum1 = false;
                root.firefox_expanded = false;//伸缩箭头不扩展
                root.firefox_arrow_show = 0;//伸缩箭头不显示
            }
            else if(root.resultFlag == true) {
                root.showNum1 = true;
                root.firefox_expanded = true;//伸缩箭头扩展
                root.firefox_arrow_show = 1;//伸缩箭头显示
            }
            if(root.softresultFlag == false) {
                root.showNum2 = false;
                root.chromium_expanded = false;//伸缩箭头不扩展
                root.chromium_arrow_show = 0;//伸缩箭头不显示
            }
            else if(root.softresultFlag == true) {
                root.showNum2 = true;
                root.chromium_expanded = true;//伸缩箭头扩展
                root.chromium_arrow_show = 1;//伸缩箭头显示
            }

            if(root.resultFlag == false && root.softresultFlag == false) {
                root.state = "AptWorkEmpty";
                if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                    //友情提示：      扫描内容为空，不再执行清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
                }
                else {//清理apt后的重新获取数据，此时不需要显示对话框
                    root.flag = false;
                }
            }
            else {
                if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
                }
                else {//清理software后的重新获取数据，此时不需要显示对话框
                    root.flag = false;
                }
                root.state = "AptWork";
                actionBtn.text = qsTr("Start cleaning");//开始清理
                root.btnFlag = "apt_work";
                backBtn.visible = true;
//                rescanBtn.visible = true;
            }
            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
        }
    }

    Component.onCompleted: {
        mainModel.append({"mstatus": root.maincheck1 ? "true": "false",
                         "itemTitle": qsTr("The package management cleaning"),
                         "picture": "../img/toolWidget/apt-min.png",
                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
        softmainModel.append({"mstatus": root.maincheck2 ? "true": "false",
                         "itemTitle": qsTr("Software Center buffer cleaning"),
                         "picture": "../img/toolWidget/software-min.png",
                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

    }

    //得到apt缓存
//    function getaptData() {
//        var apt_data = sessiondispatcher.scan_apt_cruft_qt();
//        if (apt_data.length === 0) {
//            root.resultFlag = false;//扫描内容不存在
//        }
//        else {
//            root.aptsubNum = apt_data.length;//001
//            systemdispatcher.clear_apt_args();
//            subModel.clear();
//            var num = 0;
//            for (var i=0; i< apt_data.length; i++) {
//            //sina.com.cn<2_2>10
//                var splitlist = apt_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
//                    systemdispatcher.set_apt_args(splitlist[0]);
//                }
//            }
//            root.aptsubNum -= num;//001
//            root.aptNum = root.aptsubNum;//001
//            console.log("apt num:");
//            console.log(root.aptNum);
//            if(root.aptNum != 0) {
//                root.resultFlag = true;//扫描的实际有效内容存在
//                mainModel.clear();
//                mainModel.append({"mstatus": "true",
//                                 "itemTitle": qsTr("The package management cleaning"),
//                                 "picture": "../img/toolWidget/apt-min.png",
//                                 "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})

//            }
//            else {
//                root.resultFlag = false;//扫描的实际有效内容不存在
//            }
//        }

//        if(root.resultFlag == false) {
//            root.firefox_expanded = false;//伸缩箭头不扩展
//            root.firefox_arrow_show = 0;//伸缩箭头不显示
//        }
//        else if(root.resultFlag == true) {
//            root.firefox_expanded = true;//伸缩箭头扩展
//            root.firefox_arrow_show = 1;//伸缩箭头显示
//        }
//    }

//    //得到softcenter缓存
//    function getsoftData() {
//        var software_data = sessiondispatcher.scan_softwarecenter_cruft_qt();
//        if (software_data.length === 0) {
//            root.softresultFlag = false;//扫描内容不存在
//        }
//        else {
//            root.softsubNum = software_data.length;//001
//            systemdispatcher.clear_software_args();
//            softsubModel.clear();
//            var num = 0;
//            for (var i=0; i< software_data.length; i++) {
//            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
//                var splitlist = software_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    softsubModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
//                    systemdispatcher.set_software_args(splitlist[0]);
//                }
//            }
//            root.softsubNum -= num;//001
//            root.softNum = root.softsubNum;//001
//            console.log("soft num:");
//            console.log(root.softNum);
//            if(root.softNum != 0) {
//                root.softresultFlag = true;//扫描的实际有效内容存在
//                softmainModel.clear();
//                softmainModel.append({"mstatus": "true",
//                                 "itemTitle": qsTr("Software Center buffer cleaning"),
//                                 "picture": "../img/toolWidget/software-min.png",
//                                 "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})
//            }
//            else {
//                root.softresultFlag = false;//扫描的实际有效内容不存在
//            }
//        }

//        if(root.softresultFlag == false) {
//            root.chromium_expanded = false;//伸缩箭头不扩展
//            root.chromium_arrow_show = 0;//伸缩箭头不显示
//        }
//        else if(root.softresultFlag == true) {
//            root.chromium_expanded = true;//伸缩箭头扩展
//            root.chromium_arrow_show = 1;//伸缩箭头显示
//        }
//    }

//    function getData() {
//        root.aptNum = 0;
//        root.softNum =0;
//        root.getaptData();
//        root.getsoftData();
//        if(root.resultFlag == false && root.softresultFlag == false) {
//            root.state = "AptWorkEmpty";
//            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
//                //友情提示：      扫描内容为空，不再执行清理！
//                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//            }
//            else {//清理apt后的重新获取数据，此时不需要显示对话框
//                root.flag = false;
//            }
//        }
//        else {
//            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
//                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//            }
//            else {//清理software后的重新获取数据，此时不需要显示对话框
//                root.flag = false;
//            }
//            root.state = "AptWork";
//            actionBtn.text = qsTr("Start cleaning");//开始清理
//            root.btnFlag = "apt_work";
//            backBtn.visible = true;
////            rescanBtn.visible = true;
//        }
//        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
//    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (btnFlag == "apt_work") {
                if (msg == "cache") {
                    root.state = "AptWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (root.btnFlag == "apt_work") {
                if (msg == "") {
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "cache") {
                    console.log("12--------");
                    root.state = "AptWorkFinish";
                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！



//                    systemdispatcher.clear_cache_args();
//                    subModel.clear();//内容清空
//                    softsubModel.clear();//内容清空
//                    root.aptNum = 0;//隐藏滑动条
//                    root.softNum = 0;//隐藏滑动条

                    //清理完毕后重新获取数据
                    root.flag = true;
                    if(root.maincheck1 && root.maincheck2) {//software-center
                        console.log("123--------");
                        mainModel.clear();
                        softmainModel.clear();
                        mainModel.append({"mstatus": "true",
                                         "itemTitle": qsTr("The package management cleaning"),
                                         "picture": "../img/toolWidget/apt-min.png",
                                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
                        softmainModel.append({"mstatus": "true",
                                         "itemTitle": qsTr("Software Center buffer cleaning"),
                                         "picture": "../img/toolWidget/software-min.png",
                                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})
                        systemdispatcher.clear_cache_args();
                        subModel.clear();//内容清空
                        softsubModel.clear();//内容清空
                        root.aptNum = 0;//隐藏滑动条
                        root.softNum = 0;//隐藏滑动条
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
                    }
                    else {
                        if(root.maincheck1) {
                            console.log("1234--------");
                            mainModel.clear();
                            mainModel.append({"mstatus": "true",
                                             "itemTitle": qsTr("The package management cleaning"),
                                             "picture": "../img/toolWidget/apt-min.png",
                                             "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
                            systemdispatcher.clear_cache_args();
                            subModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            root.aptNum = 0;//隐藏滑动条
                            root.softNum = 0;//隐藏滑动条
                            sessiondispatcher.cache_scan_function_qt("apt");
                        }
                        else if(root.maincheck2) {
                            console.log("12345--------");
                            softmainModel.clear();
                            softmainModel.append({"mstatus": "true",
                                             "itemTitle": qsTr("Software Center buffer cleaning"),
                                             "picture": "../img/toolWidget/software-min.png",
                                             "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})
                            systemdispatcher.clear_cache_args();
                            subModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            root.aptNum = 0;//隐藏滑动条
                            root.softNum = 0;//隐藏滑动条
                            sessiondispatcher.cache_scan_function_qt("software-center");
                        }
                    }
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
                        if(root.maincheck1 == false) {
                            root.maincheck1 = true;
                        }
                        if(root.maincheck2 == false) {
                            root.maincheck2 = true;
                        }
                        systemdispatcher.clear_cache_args();
                        root.showNum1 = false;
                        root.showNum2 = false;
                        mainModel.clear();
                        softmainModel.clear();
                        mainModel.append({"mstatus": "true",
                                         "itemTitle": qsTr("The package management cleaning"),
                                         "picture": "../img/toolWidget/apt-min.png",
                                         "detailstr": qsTr("User can according to the scan results selectively clean residual package, cache path is:/var/cache/apt/archives/")})
                        softmainModel.append({"mstatus": "true",
                                         "itemTitle": qsTr("Software Center buffer cleaning"),
                                         "picture": "../img/toolWidget/software-min.png",
                                         "detailstr": qsTr("User can selectively cleaning software center cache according to the scanning result, cache path:") + sessiondispatcher.getHomePath() + "/.cache/software-center/"})

                        subModel.clear();//内容清空
                        root.aptNum = 0;//隐藏滑动条
                        root.firefox_arrow_show = 0;//伸缩图标隐藏
                        softsubModel.clear();//内容清空
                        root.softNum = 0;//隐藏滑动条
                        root.chromium_arrow_show = 0;//伸缩图标隐藏
                        scrollItem.height = 2 * 40 + root.spaceValue*2;
                        root.state = "AptWorkAGAIN";//按钮的状态恢复初始值
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
//                console.log("-----------");
//                console.log(root.maincheck1);
//                console.log(root.maincheck2);

                if (root.btnFlag == "apt_scan") {//扫描
                    root.flag = false;
                    if(root.maincheck1 && root.maincheck2) {//software-center
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
                    }
                    else {
                        if(root.maincheck1) {
                            sessiondispatcher.cache_scan_function_qt("apt");
                        }
                        else if(root.maincheck2) {
                            sessiondispatcher.cache_scan_function_qt("software-center");
                        }
                    }
                }
                else if (root.btnFlag == "apt_work") {//清理
                    if(root.resultFlag || root.softresultFlag) {//扫描得到的实际内容存在时
                        console.log(systemdispatcher.get_cache_args());
                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_cache_args(), "cache");
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
            id: scrollItem
            width: parent.width
            height: 40*2 + root.spaceValue*2
            Column {
                spacing: root.spaceValue
                //垃圾清理显示内容
                ListView {
                    id: aptListView
                    width: parent.width
                    height: root.firefox_expanded ? (root.aptNum + 1) * 40 : 40
                    model: mainModel
                    delegate: CacheDelegate{
                        sub_num: root.aptNum//root.aptsubNum//1212
                        sub_model: subModel
                        btn_flag: root.btnFlag
                        arrowFlag: "apt"
                        showNum: root.showNum1
                        arrow_display: root.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: root.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: root.splitFlag
//                        controlMain: root.maincheck1
//                        onSubpressed: {root.aptNum=hMark}
                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
//                            root.resultFlag = checkchange;
                            root.maincheck1 = checkchange;
                        }
                        onArrowClicked: {
//                            console.lmaincheck1og("111");
//                            console.log(str);
//                            console.log(expand_flag);
//                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                            if(cacheFlag == "apt") {//1212
                                if(expand_flag == true) {
                                    root.firefox_expanded = true;
                                    if(root.chromium_expanded == true) {
                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
                                    }
                                }
                                else {
                                    root.firefox_expanded = false;
                                    if(root.chromium_expanded == true) {
                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = 2* 40 + root.spaceValue*2;
                                    }
                                }
                            }
                        }
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
                //垃圾清理显示内容
                ListView {
                    id: softListView
                    width: parent.width
                    height: root.chromium_expanded ? (root.softNum + 1) * 40 : 40
                    model: softmainModel
                    delegate: CacheDelegate{
                        sub_num: root.softNum//root.softsubNum//1212
                        sub_model: softsubModel
                        btn_flag: root.btnFlag
                        showNum: root.showNum2
                        arrowFlag: "soft"
                        arrow_display: root.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: root.chromium_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: root.splitFlag
//                        controlMain: root.maincheck2
                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
//                            root.softresultFlag = checkchange;
                            root.maincheck2 = checkchange;
                        }
                        onArrowClicked: {
//                            console.log("222");
//                            console.log(str);
//                            console.log(expand_flag);
//                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                            if(cacheFlag == "soft") {//1212
                                if(expand_flag == true) {
                                    root.chromium_expanded = true;
                                    if(root.firefox_expanded == true) {
                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
                                    }
                                }
                                else {
                                    root.chromium_expanded = false;
                                    if(root.firefox_expanded == true) {
                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = 2* 40 + root.spaceValue*2;
                                    }
                                }
                            }
                        }
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
    }

    states: [
        State {
            name: "AptWork"
            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning")}//开始清理
            PropertyChanges { target: root; btnFlag: "apt_work" }
            PropertyChanges { target: backBtn; visible: true}
//            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "AptWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        }
    ]
}
