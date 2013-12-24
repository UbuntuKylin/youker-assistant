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
import "../bars" as Bars

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
            onSendProgressToQML: {//onSendDynamicSoftwareProgressQML
                if(type == "apt_start") {
                    progress.value = 0;
                    home.state = "MaskLayerState";
                }
                else if(type == "apt_pulse"){
                    progressTitle.text = qsTr("The ongoing: ") + info;//正在进行:
                    progress.value = ratio_sus;
                }
                else if(type == "apt_stop") {
//                    progress.value = 0;
                }
            }
        }

        //背景
        Image {
            source: "../../img/skin/bg-middle.png"
            anchors.fill: parent
        }

        Column {
            anchors.centerIn: parent
            spacing: 5
            AnimatedImage {
//                anchors.centerIn: parent
                width: 16
                height: 16
                source: "../../img/icons/move.gif"
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
        Common.SetBtn {
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
        id:root
        width: parent.width
        height: parent.height
        property string title: qsTr("Uninstall unnecessary procedures and old kernel packages")//卸载不必要的程序和旧内核包
        property string description: qsTr("Cleaning up the software that installed by other software bundled or old kernel packages, to improve system performance")//清理软件安装过程中捆绑安装的依赖程序或旧内核包，提高系统性能
        property string btnFlag: "package_scan"//扫描或者清理的标记：package_scan/package_work
        property bool packageresultFlag: false//判断依赖包扫描后的实际内容是否为空，为空时为false，有内容时为true
        property bool kernelresultFlag: false//判断旧内核包扫描后的实际内容是否为空，为空时为false，有内容时为true
        property int packageNum//扫描后得到的依赖包的项目总数
        property int kernelNum//扫描后得到的旧内核包的项目总数
        property bool packageEmpty: false//决定是否显示扫描内容为空的状态图
        property bool kernelEmpty: false//决定是否显示扫描内容为空的状态图
        property int mode: 0//扫描模式：0表示两者都扫描，1表示只选中了package，2表示只选中了kernel
        property bool splitFlag: true//传递给CacheDelegate.qml,为true时切割字符串，为false时不切割字符串
        property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
        property int spaceValue: 20
        property int package_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property int kernel_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property bool package_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
        property bool kernel_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
        property bool package_maincheck: true
        property bool kernel_maincheck: true
        property bool package_showNum: false//决定依赖包的扫描结果数是否显示
        property bool kernel_showNum: false//决定旧内核包的扫描结果数是否显示
        ListModel { id: packagemainModel }
        ListModel { id: packagesubModel }
        ListModel { id: kernelmainModel }
        ListModel { id: kernelsubModel }

        Component.onCompleted: {
            //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
            packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                             "itemTitle": qsTr("Uninstall unnecessary procedures"),
                             "picture": "../../img/toolWidget/deb-min.png",
                             "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
            //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
            kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                             "itemTitle": qsTr("Uninstall old kernel packages"),
                             "picture": "../../img/toolWidget/deb-min.png",
                            "detailstr": qsTr("Users can selectively clean installed old kernel packages according to the scanning results, to save the disk space.")})
        }

        Connections
        {
            target: sessiondispatcher
            onAppendPackageContentToCacheModel: {
                //QString flag, QString pkgName, QString description, QString sizeValue
                if(flag == "unneed") {
                    packagesubModel.append({"itemTitle": pkgName, "desc": description, "number": sizeValue});
                    root.packageNum += 1;
                    systemdispatcher.set_package_args(pkgName);
                }
                else if(flag == "oldkernel") {
                    kernelsubModel.append({"itemTitle": pkgName, "desc": description, "number": sizeValue});
                    root.kernelNum += 1;
                    systemdispatcher.set_package_args(pkgName);
                }
            }
            onTellQMLPackageOver: {
                packagemainModel.clear();
                kernelmainModel.clear();
                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                 "picture": "../../img/toolWidget/deb-min.png",
                                 "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                 "picture": "../../img/toolWidget/deb-min.png",
                                "detailstr": qsTr("Users can selectively clean installed old kernel packages according to the scanning results, to save the disk space.")})

                if(root.packageNum != 0) {
                    root.packageresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(root.mode == 0 || root.mode == 1) {
                        root.packageEmpty = true;
                    }
                    root.packageresultFlag = false;//扫描的实际有效内容不存在
                }
                if(root.kernelNum != 0) {
                    root.kernelresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(root.mode == 0 || root.mode == 2) {
                        root.kernelEmpty = true;
                    }
                    root.kernelresultFlag = false;//扫描的实际有效内容不存在
                }

                if(root.packageresultFlag == false) {
                    root.package_showNum = false;
                    root.package_expanded = false;//伸缩箭头不扩展
                    root.package_arrow_show = 0;//伸缩箭头不显示
                }
                else if(root.packageresultFlag == true) {
                    root.package_showNum = true;
                    root.package_expanded = true;//伸缩箭头扩展
                    root.package_arrow_show = 1;//伸缩箭头显示
                }
                if(root.kernelresultFlag == false) {
                    root.kernel_showNum = false;
                    root.kernel_expanded = false;//伸缩箭头不扩展
                    root.kernel_arrow_show = 0;//伸缩箭头不显示
                }
                else if(root.kernelresultFlag == true) {
                    root.kernel_showNum = true;
                    root.kernel_expanded = true;//伸缩箭头扩展
                    root.kernel_arrow_show = 1;//伸缩箭头显示
                }

                if(root.packageresultFlag == false && root.kernelresultFlag == false) {
                    root.state = "PackageWorkEmpty";
                    if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        //友情提示：      扫描内容为空，无需清理！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan results is empty, no need to clean up!"), mainwindow.pos.x, mainwindow.pos.y);
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
                    root.state = "PackageWork";
                    actionBtn.text = qsTr("Begin cleanup");//开始清理
                    root.btnFlag = "package_work";
                    backBtn.visible = true;
    //                rescanBtn.visible = true;
                }
                scrollItem.height = (root.packageNum + 1) * 40 + (root.kernelNum + 1) * 40 + root.spaceValue*2;
                //扫描完成后恢复按钮的使能
                actionBtn.enabled = true;
            }
        }


        //得到package
//        function getpackageData() {
//            var unneed_data = sessiondispatcher.scan_unneed_packages_qt();
//            if (unneed_data.length == 0) {//扫描内容不存在
//                root.packageresultFlag = false;
//                root.packageNum = 0;
//            }
//            else {
//                root.packageNum = unneed_data.length;//001
//                systemdispatcher.clear_package_args();
//                packagesubModel.clear();
//                var num = 0;
//                for (var i=0; i< unneed_data.length; i++) {
//                //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//                    var splitlist = unneed_data[i].split("<2_2>");
//                    if (splitlist[0] == "") {
//                        num++;
//                    }
//                    else {
//                        packagesubModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
//                        systemdispatcher.set_package_args(splitlist[0]);
//                    }
//                }

//                root.packageNum -= num;//001
//                if(root.packageNum != 0) {
//                    root.packageresultFlag = true;//扫描的实际有效内容存在
//                    packagemainModel.clear();
////                    root.maincheck = true;//扫描到数据时默认把主checkbox勾上
//                    //卸载不必要的程序         用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦
//                    packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
//                                     "itemTitle": qsTr("Uninstall unnecessary procedures"),
//                                     "picture": "../../img/toolWidget/deb-min.png",
//                                     "detailstr": qsTr("User can selectively clean installed program no longer need according to the scan results, make the system more thin")})
//                }
//                else {
//                    root.packageresultFlag = false;//扫描的实际有效内容不存在
//                }
//            }

//            if(root.packageresultFlag == false) {
//                root.package_expanded = false;//伸缩箭头不扩展
//                root.package_arrow_show = 0;//伸缩箭头不显示
//            }
//            else if(root.packageresultFlag == true) {
//                root.package_expanded = true;//伸缩箭头扩展
//                root.package_arrow_show = 1;//伸缩箭头显示
//            }
//        }

        //得到old kernel package
//        function getkernelData() {
//            var kernel_data = sessiondispatcher.scan_oldkernel_packages_qt();
//            if (kernel_data.length === 0) {//扫描内容不存在
//                root.kernelresultFlag = false;
//            }
//            else {
//                root.kernelNum = kernel_data.length;//001
//                systemdispatcher.clear_kernel_args();
//                kernelsubModel.clear();
//                var num = 0;
//                for (var i=0; i< kernel_data.length; i++) {
//                //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//                    var splitlist = kernel_data[i].split("<2_2>");
//                    if (splitlist[0] == "") {
//                        num++;
//                    }
//                    else {
//                        kernelsubModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
//                        systemdispatcher.set_kernel_args(splitlist[0]);
//                    }
//                }
//                root.kernelNum -= num;
//                if(root.kernelNum != 0) {
//                    root.kernelresultFlag = true;//扫描的实际有效内容存在
//                }
//                else {
//                    root.kernelresultFlag = false;//扫描的实际有效内容不存在
//                }
//                kernelmainModel.clear();
//                //卸载旧内核包         用户可以根据扫描结果选择性地清理旧内核包,节省系统空间
//                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
//                                 "itemTitle": qsTr("Uninstall old kernel packages"),
//                                 "picture": "../../img/toolWidget/deb-min.png",
//                                "detailstr": qsTr("According to the results of the scanning ，selectively clean up the old kernel to save the disk space")})
//            }
//            if(root.kernelresultFlag == false) {
//                root.kernel_expanded = false;//伸缩箭头不扩展
//                root.kernel_arrow_show = 0;//伸缩箭头不显示
//            }
//            else if(root.kernelresultFlag == true) {
//                root.kernel_expanded = true;//伸缩箭头扩展
//                root.kernel_arrow_show = 1;//伸缩箭头显示
//            }
//        }
//        function getData() {
//            root.packageNum = 0;
//            root.kernelNum =0;
//            root.getpackageData();
//            root.getkernelData();
//            if(root.packageresultFlag == false && root.kernelresultFlag == false) {
//                root.state = "PackageWorkEmpty";
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
//                root.state = "PackageWork";
//                actionBtn.text = qsTr("Begin Cleanup");//开始清理
//                root.btnFlag = "package_work";
//                backBtn.visible = true;
//    //            rescanBtn.visible = true;
//            }
//            scrollItem.height = (root.packageNum + 1) * 40 + (root.kernelNum + 1) * 40 + root.spaceValue*2;
//        }

        Connections
        {
            target: sudodispatcher
            onFinishCleanDebError: {//清理出错时收到的信号
                if (root.btnFlag == "package_work") {
                    if (msg == "package") {
                        home.state = "NormalState";
                        //清理过程中发生错误，解禁按钮
                        actionBtn.enabled = true;
                        titleBar.state = "PackageWorkError";
                        toolkits.alertMSG(qsTr("Cleanup abnormal!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                    }
                }
            }
            onFinishCleanDeb: {//清理成功时收到的信号
                if (root.btnFlag == "package_work") {
                    if (msg == "") {
                        //清理取消，解禁按钮
                        actionBtn.enabled = true;
                        home.state = "NormalState";
                        toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断！
                    }
                    else if (msg == "package") {
                        root.state = "PackageWorkFinish";
                        toolkits.alertMSG(qsTr("Cleared"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                        //清理完毕后重新获取数据
                        root.flag = true;
//                        root.getData();
                        if(root.package_maincheck && root.kernel_maincheck) {
                            packagemainModel.clear();
                            kernelmainModel.clear();
                            //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                            packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                             "picture": "../../img/toolWidget/deb-min.png",
                                             "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
                            //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                            kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Uninstall old kernel packages"),
                                             "picture": "../../img/toolWidget/deb-min.png",
                                            "detailstr": qsTr("Users can selectively clean installed old kernel packages according to the scanning results, to save the disk space.")})
                            systemdispatcher.clear_package_args();
                            packagesubModel.clear();//内容清空
                            kernelsubModel.clear();//内容清空
                            root.packageNum = 0;//隐藏滑动条
                            root.kernelNum = 0;//隐藏滑动条
                            root.mode = 0;
                            sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist());
                        }
                        else {
                            if(root.package_maincheck) {
                                packagemainModel.clear();
                                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                                 "picture": "../../img/toolWidget/deb-min.png",
                                                 "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
                                systemdispatcher.clear_package_args();
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.mode = 1;
                                sessiondispatcher.package_scan_function_qt("unneed");
                            }
                            else if(root.kernel_maincheck) {
                                kernelmainModel.clear();
                                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                                 "picture": "../../img/toolWidget/deb-min.png",
                                                 "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
                                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                                 "picture": "../../img/toolWidget/deb-min.png",
                                                "detailstr": qsTr("Users can selectively clean installed old kernel packages according to the scanning results, to save the disk space.")})
                                systemdispatcher.clear_package_args();
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.mode = 2;
                                sessiondispatcher.package_scan_function_qt("oldkernel");
                            }
                        }
                        home.state = "NormalState";
                        //清理成功完成，解禁按钮
                        actionBtn.enabled = true;
                    }
                }
            }
        }

        //背景
        Image {
            source: "../../img/skin/bg-bottom-tab.png"
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
                source: "../../img/toolWidget/apt.png"
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
                anchors.verticalCenter: parent.verticalCenter
                Common.StyleButton {
                    id: backBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Back")//返回
                    width: 40
                    height: 20
                    onClicked: {
                        root.packageEmpty = false;
                        root.kernelEmpty = false;
                        if(root.package_maincheck == false) {
                            root.package_maincheck = true;
                        }
                        if(root.kernel_maincheck == false) {
                            root.kernel_maincheck = true;
                        }
                        systemdispatcher.clear_package_args();
                        root.package_showNum = false;
                        root.kernel_showNum = false;
                        packagemainModel.clear();
                        kernelmainModel.clear();
                        //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                        packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                         "picture": "../../img/toolWidget/deb-min.png",
                                         "detailstr": qsTr("Users can selectively clean installed program according to the scanning results, to save the disk space.")})
                        //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                        kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Uninstall old kernel packages"),
                                         "picture": "../../img/toolWidget/deb-min.png",
                                        "detailstr": qsTr("Users can selectively clean installed old kernel packages according to the scanning results, to save the disk space.")})
                        packagesubModel.clear();//内容清空
                        root.packageNum = 0;//隐藏滑动条
                        root.package_arrow_show = 0;//伸缩图标隐藏
                        kernelsubModel.clear();//内容清空
                        root.kernelNum = 0;//隐藏滑动条
                        root.kernel_arrow_show = 0;//伸缩图标隐藏
                        scrollItem.height = 2 * 40 + root.spaceValue*2;
                        root.state = "PackageWorkAGAIN";//按钮的状态恢复初始值
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

                    root.packageEmpty = false;
                    root.kernelEmpty = false;
                    //                console.log("-----------");
                    //                console.log(root.package_maincheck);
                    //                console.log(root.kernel_maincheck);
                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {//sessiondbus服务已经成功启动了
                        if(!sudodispatcher.getUKSignalFlag()) {
                            sudodispatcher.setUKSignalFlag(true);
                            sudodispatcher.bind_signals_after_dbus_start();
                        }
                        if (root.btnFlag == "package_scan") {//扫描
                            //扫描过程中禁用按钮
                            actionBtn.enabled = false;
                            root.flag = false;
//                            root.getData();
                            if(root.package_maincheck && root.kernel_maincheck) {
                                root.mode = 0;
                                root.packageNum = 0;
                                root.kernelNum = 0;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist());
                            }
                            else {
                                if(root.package_maincheck) {
                                    root.mode = 1;
                                    root.packageNum = 0;
                                    sessiondispatcher.package_scan_function_qt("unneed");
                                }
                                else if(root.kernel_maincheck) {
                                    root.mode = 2;
                                    root.kernelNum = 0;
                                    sessiondispatcher.package_scan_function_qt("oldkernel");
                                }
                                else{
                                    actionBtn.enabled = true;
                                    //友情提示：        对不起，您没有选择需要扫描的内容，请确认！
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be scanned, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                }
                            }
                        }
                        else if (root.btnFlag == "package_work") {//清理
                            if(root.packageresultFlag || root.kernelresultFlag) {//扫描得到的实际内容存在时
                                if(!root.package_maincheck && !root.kernel_maincheck) {
                                    //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                }
                                else {
//                                    home.state = "MaskLayerState";
                                    //开始清理时，禁用按钮，等到清理完成后解禁
                                    actionBtn.enabled = false;
                                    console.log(systemdispatcher.get_package_args());
                                    sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
                                }
                            }
                        }
                    }
                    else {//sessiondbus服务还没有启动
                        if(!root.package_maincheck && !root.kernel_maincheck) {
                            if (root.btnFlag == "package_scan") {//扫描
                                //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                            }
                            else if (root.btnFlag == "package_work") {//清理
                                //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                            }
                        }
                        else {
                            sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
                            if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                                if(!sudodispatcher.getUKSignalFlag()) {
                                    if(!sudodispatcher.getUKSignalFlag()) {
                                        sudodispatcher.setUKSignalFlag(true);
                                        sudodispatcher.bind_signals_after_dbus_start();
                                    }
                                    if (root.btnFlag == "package_scan") {//扫描
                                        //扫描过程中禁用按钮
                                        actionBtn.enabled = false;
                                        root.flag = false;
    //                                    root.getData();

                                        if(root.package_maincheck && root.kernel_maincheck) {
                                            root.mode = 0;
                                            root.packageNum = 0;
                                            root.kernelNum = 0;
                                            sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist());
                                        }
                                        else {
                                            if(root.package_maincheck) {
                                                root.mode = 1;
                                                root.packageNum = 0;
                                                sessiondispatcher.package_scan_function_qt("unneed");
                                            }
                                            else if(root.kernel_maincheck) {
                                                root.mode = 2;
                                                root.kernelNum = 0;
                                                sessiondispatcher.package_scan_function_qt("oldkernel");
                                            }
//                                            else{
//                                                actionBtn.enabled = true;
//                                                //友情提示：        对不起，您没有选择需要扫描的项，请确认！
//                                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be scanned, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                            }
                                        }
                                    }
                                    else if (root.btnFlag == "package_work") {//清理
                                        if(root.packageresultFlag || root.kernelresultFlag) {//扫描得到的实际内容存在时
//                                            if(!root.package_maincheck && !root.kernel_maincheck) {
//                                                //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                            }
//                                            else {
    //                                            home.state = "MaskLayerState";
                                            //开始清理时，禁用按钮，等到清理完成后解禁
                                            actionBtn.enabled = false;
//                                            console.log(systemdispatcher.get_package_args());
                                            sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
//                                            }
                                        }
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
            anchors.topMargin: 30
            anchors.left:parent.left
            anchors.leftMargin: 27
            height: root.height - titlebar.height - 47
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
                        height: root.package_expanded ? (root.packageNum + 1) * 40 : 40
                        model: packagemainModel
                        delegate: CacheDelegate{
                            sub_num: root.packageNum//root.aptsubNum//1212
                            sub_model: packagesubModel
                            btn_flag: root.btnFlag
                            arrowFlag: "package"
                            showNum: root.package_showNum
                            arrow_display: root.package_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                            expanded: root.package_expanded//package_expanded为true时，箭头向下，内容展开;package_expanded为false时，箭头向上，内容收缩
                            delegate_flag: root.splitFlag
                            emptyTip: root.packageEmpty
                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                            onCheckchanged: {
    //                            root.packageresultFlag = checkchange;
                                root.package_maincheck = checkchange;
                            }
                            onArrowClicked: {
                                if(cacheFlag == "package") {//1212
                                    if(expand_flag == true) {
                                        root.package_expanded = true;
                                        if(root.kernel_expanded == true) {
                                            scrollItem.height = (root.packageNum + 1) * 40 + (root.kernelNum + 1) * 40 + root.spaceValue*2;
                                        }
                                        else {
                                            scrollItem.height = (root.packageNum + 2) * 40 + root.spaceValue*2;
                                        }
                                    }
                                    else {
                                        root.package_expanded = false;
                                        if(root.kernel_expanded == true) {
                                            scrollItem.height = (root.kernelNum + 2) * 40 + root.spaceValue*2;
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
                        height: root.kernel_expanded ? (root.kernelNum + 1) * 40 : 40
                        model: kernelmainModel
                        delegate: CacheDelegate{
                            sub_num: root.kernelNum
                            sub_model: kernelsubModel
                            btn_flag: root.btnFlag
                            showNum: root.kernel_showNum
                            arrowFlag: "kernel"
                            arrow_display: root.kernel_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                            expanded: root.kernel_expanded//kernel_expanded为true时，箭头向下，内容展开;kernel_expanded为false时，箭头向上，内容收缩
                            delegate_flag: root.splitFlag
                            emptyTip: root.kernelEmpty
                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                            onCheckchanged: {
    //                            root.kernelresultFlag = checkchange;
                                root.kernel_maincheck = checkchange;
                            }
                            onArrowClicked: {
                                if(cacheFlag == "kernel") {//1212
                                    if(expand_flag == true) {
                                        root.kernel_expanded = true;
                                        if(root.package_expanded == true) {
                                            scrollItem.height = (root.packageNum + 1) * 40 + (root.kernelNum + 1) * 40 + root.spaceValue*2;
                                        }
                                        else {
                                            scrollItem.height = (root.kernelNum + 2) * 40 + root.spaceValue*2;
                                        }
                                    }
                                    else {
                                        root.kernel_expanded = false;
                                        if(root.package_expanded == true) {
                                            scrollItem.height = (root.packageNum + 2) * 40 + root.spaceValue*2;
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
                name: "PackageWork"
                PropertyChanges { target: actionBtn; text:qsTr("Begin cleanup")}//开始清理
                PropertyChanges { target: root; btnFlag: "package_work" }
                PropertyChanges { target: backBtn; visible: true}
    //            PropertyChanges { target: rescanBtn; visible: true}
            },
            State {
                name: "PackageWorkAGAIN"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
    //            PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "PackageWorkError"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
    //            PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "PackageWorkFinish"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
    //            PropertyChanges { target: rescanBtn; visible: false}
            },
            State {
                name: "PackageWorkEmpty"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
    //            PropertyChanges { target: rescanBtn; visible: false}
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














//-------------------单独清理不需要的包的模块-----------------------
//Item {
//    id:home
//    width: parent.width
//    height: 435
//    Rectangle {
//        id: masklayer2
//        width: parent.width
//        height: parent.height
//        x: (parent.width * 1.5)
//        Connections
//        {
//            target: sudodispatcher
//            //得到数据，显示在进度条上
//            onSendProgressToQML: {//onSendDynamicSoftwareProgressQML
//                if(type == "apt_start") {
//                    progress.value = 0;
//                    home.state = "MaskLayerState";
//                }
//                else if(type == "apt_pulse"){
//                    progressTitle.text = qsTr("The ongoing: ") + info;//正在进行:
//                    progress.value = ratio_sus;
//                }
//                else if(type == "apt_stop") {
////                    progress.value = 0;
//                }
//            }
//        }

//        //背景
//        Image {
//            source: "../img/skin/bg-middle.png"
//            anchors.fill: parent
//        }

//        Column {
//            anchors.centerIn: parent
//            spacing: 5
//            AnimatedImage {
////                anchors.centerIn: parent
//                width: 16
//                height: 16
//                source: "../img/icons/move.gif"
//                anchors.horizontalCenter: parent.horizontalCenter
//            }
//            Text {
//                id: progressTitle
//                text: qsTr("Software operation schedule")//软件操作进度
//                color: "#318d11"
//                wrapMode: Text.WordWrap
//                font.pixelSize: 12
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Bars.Progress {
//                id: progress
//                value: 0
//                background: "../../img/skin/progress-bg.png"
//                color: "#086794"//"#383838"
//                secondColor: "#318d11"
//                anchors.horizontalCenter: parent.horizontalCenter
//            }
//        }
//        Common.SetBtn {
//            id: resetBtn2
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            anchors {
//                left: parent.left
//                leftMargin: 10
//                top: parent.top
//                topMargin: 10
//            }
//            onClicked: {
//                home.state = "NormalState";
//            }
//        }
//    }

//    Rectangle {
//        id:root
//        width: parent.width
//        height: parent.height
//        property string title: qsTr("Uninstall unnecessary procedures")//卸载不必要的程序
//        property string description: qsTr("Clean installed dependent program, to improve system performance")//清理软件安装过程中安装的依赖程序，提高系统性能
//        property string btnFlag: "package_scan"//扫描或者清理的标记：package_scan/package_work
//        property bool resultFlag: false//判断apt扫描后的实际内容是否为空，为空时为false，有内容时为true
//        property int debNum//扫描后得到的apt的项目总数
//        property bool splitFlag: true//传递给CacheDelegate.qml,为true时切割字符串，为false时不切割字符串
//        property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
//        property int spaceValue: 20
//        property int arrowShow: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
//        property bool package_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
//        property bool maincheck: true
//        property bool showNum: false//决定apt的扫描结果数是否显示
//        ListModel { id: mainModel }
//        ListModel { id: subModel }

//        //得到package
//        function getData() {
//            var unneed_data = sessiondispatcher.scan_unneed_packages_qt();
//            if (unneed_data.length == 0) {//扫描内容不存在
//                root.resultFlag = false;
//                root.debNum = 0;
//            }
//            else {
//                root.debNum = unneed_data.length;//001
//                systemdispatcher.clear_package_args();
//                subModel.clear();
//                var num = 0;
//                for (var i=0; i< unneed_data.length; i++) {
//                //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//                    var splitlist = unneed_data[i].split("<2_2>");
//                    if (splitlist[0] == "") {
//                        num++;
//                    }
//                    else {
//                        subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
//                        systemdispatcher.set_package_args(splitlist[0]);
//                    }
//                }

//                root.debNum -= num;//001
//                if(root.debNum != 0) {
//                    root.resultFlag = true;//扫描的实际有效内容存在
//                    mainModel.clear();
//                    root.maincheck = true;//扫描到数据时默认把主checkbox勾上
//                    //卸载不必要的程序         用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦
//                    mainModel.append({"mstatus": root.maincheck ? "true": "false",
//                                     "itemTitle": qsTr("Uninstall unnecessary procedures"),
//                                     "picture": "../img/toolWidget/deb-min.png",
//                                     "detailstr": qsTr("User can selectively clean installed program no longer need according to the scan results, make the system more thin")})
//                }
//                else {
//                    root.resultFlag = false;//扫描的实际有效内容不存在
//                }
//            }


//            if(root.resultFlag == false) {
//                root.state = "UnneedWorkEmpty";
//    //                root.package_expanded = false;//伸缩箭头不扩展
//    //                root.arrowShow = 0;//伸缩箭头不显示
//    //                root.showNum = false;
//    //                root.btnFlag = "package_scan";
//                if(root.flag == false) {
//                    //友情提示：      扫描内容为空，不再执行清理！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                }
//                else {
//                    root.flag = false;
//                }
//            }
//            else if(root.resultFlag == true) {
//                if(root.flag == false) {
//                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                }
//                else {
//                    root.flag = false;
//                }
//                //这里有奇怪的现在，下面三个量在state中设置无效 kobe
//                root.arrowShow = 1;
//                root.package_expanded = true;
//                root.showNum = true;

//                root.state = "UnneedWork";
//                actionBtn.text = qsTr("Begin Cleanup");//开始清理
//                root.btnFlag = "package_work";
//                backBtn.visible = true;
//                rescanBtn.visible = true;
//            }
//            scrollItem.height = (root.debNum + 1) * 40;
//        }

//        Connections
//        {
//            target: sudodispatcher
//            onFinishCleanDebError: {//清理出错时收到的信号
//                if (root.btnFlag == "package_work") {
//                    if (msg == "package") {
//                        home.state = "NormalState";
//                        //清理过程中发生错误，解禁按钮
//                        actionBtn.enabled = true;
//                        titleBar.state = "UnneedWorkError";
//                        toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                    }
//                }
//            }
//            onFinishCleanDeb: {//清理成功时收到的信号
//                if (root.btnFlag == "package_work") {
//                    if (msg == "") {
//                        //清理取消，解禁按钮
//                        actionBtn.enabled = true;
//                        home.state = "NormalState";
//                        toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
//                    }
//                    else if (msg == "package") {
//                        //清理成功完成，解禁按钮
//                        actionBtn.enabled = true;
//                        root.state = "UnneedWorkFinish";
//                        toolkits.alertMSG(qsTr("Cleared"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                        root.flag = true;
//                        root.getData();
//                        home.state = "NormalState";
//                    }
//                }
//            }
//        }
//        //背景
//        Image {
//            source: "../img/skin/bg-bottom-tab.png"
//            anchors.fill: parent
//        }

//        //titlebar
//        Row {
//            id: titlebar
//            spacing: 20
//            width: parent.width
//            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//            Image {
//                id: apt_refreshArrow
//                source: "../img/toolWidget/apt.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Column {
//                anchors.verticalCenter: parent.verticalCenter
//                spacing: 10
//                Text {
//                    width: 500
//                    text: root.title
//                    wrapMode: Text.WordWrap
//                    font.bold: true
//                    font.pixelSize: 14
//                    color: "#383838"
//                }
//                Text {
//                    width: 500
//                    text: root.description
//                    wrapMode: Text.WordWrap
//                    font.pixelSize: 12
//                    color: "#7a7a7a"
//                }
//            }
//        }

//        Row{
//            anchors { top: parent.top; topMargin: 20;right: parent.right ; rightMargin: 40 }
//            spacing: 20
//            Row {
//                spacing: 20
//                anchors.verticalCenter: parent.verticalCenter
//                Common.StyleButton {
//                    id: backBtn
//                    visible: false
//                    anchors.verticalCenter: parent.verticalCenter
//                    wordname: qsTr("Go back")//返回
//                    width: 40
//                    height: 20
//                    onClicked: {
//                        if(root.maincheck == false) {
//                            root.maincheck = true;
//                        }
//                        mainModel.clear();
//                        subModel.clear();//内容清空
//                        systemdispatcher.clear_package_args();
//                        root.debNum = 0;//隐藏滑动条
//                        root.resultFlag = false;
//                        scrollItem.height = 0;
//    //                        root.arrowShow = 0;//伸缩图标隐藏
//    //                        root.expandFlag = false;
//    //                        root.showNum = false;
//                        root.state = "UnneedWorkAGAIN";//按钮的状态恢复初始值
//                    }
//                }
//                Common.StyleButton {
//                    id: rescanBtn
//                    visible: false
//                    anchors.verticalCenter: parent.verticalCenter
//                    wordname: qsTr("Scan again")//重新扫描
//                    width: 40
//                    height: 20
//                    onClicked: {
//                        actionBtn.text = qsTr("Start scanning");//开始扫描
//                        root.maincheck = true;
//                        root.btnFlag = "package_scan";
//                        backBtn.visible = false;
//                        rescanBtn.visible = false;
//                        subModel.clear();//内容清空
//                        root.arrowShow = 0;//伸缩图标隐藏
//                        scrollItem.height = 0;
//                        root.arrowShow = 0;//伸缩图标隐藏
//                        root.package_expanded = false;
//                        root.showNum = false;
//                        root.flag = false;
//                        root.getData();//重新获取数据
//                    }
//                }
//            }

//            Common.Button {
//                id: actionBtn
//                width: 120
//                height: 39
//                hoverimage: "green1.png"
//                text: qsTr("Start scanning")//开始扫描
//                fontsize: 15
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: {
//                    if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {//sessiondbus服务已经成功启动了
//                        if(!sudodispatcher.getUKSignalFlag()) {
//                            sudodispatcher.setUKSignalFlag(true);
//                            sudodispatcher.bind_signals_after_dbus_start();
//                        }
//                        if (root.btnFlag == "package_scan") {//扫描
//                            root.flag = false;
//                            root.getData();
//                        }
//                        else if (root.btnFlag == "package_work") {//清理
//                            if(root.resultFlag) {//扫描得到的实际内容存在时
//                                //开始清理时，禁用按钮，等到清理完成后解禁
//                                actionBtn.enabled = false;
//                                console.log(systemdispatcher.get_package_args());
//                                sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
//                                root.arrowShow = 1;
//                            }
//                            else {//扫描得到的实际内容不存在时
//                                //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                            }
//                        }
//                    }
//                    else {//sessiondbus服务还没有启动
//                        sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
//                        if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
//                            if(!sudodispatcher.getUKSignalFlag()) {
//                                if(!sudodispatcher.getUKSignalFlag()) {
//                                    sudodispatcher.setUKSignalFlag(true);
//                                    sudodispatcher.bind_signals_after_dbus_start();
//                                }
//                                if (root.btnFlag == "package_scan") {//扫描
//                                    root.flag = false;
//                                    root.getData();
//                                }
//                                else if (root.btnFlag == "package_work") {//清理
//                                    if(root.resultFlag) {//扫描得到的实际内容存在时
//                                        home.state = "MaskLayerState";
//                                        //开始清理时，禁用按钮，等到清理完成后解禁
//                                        actionBtn.enabled = false;
//                                        console.log(systemdispatcher.get_package_args());
//                                        sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args(), "package");
//                                        root.arrowShow = 1;
//                                    }
//                                    else {//扫描得到的实际内容不存在时
//                                        //友情提示：        对不起，您没有选择需要清理的项，请确认！
//                                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        //分割条
//        Rectangle {
//            id: splitbar
//            anchors {
//                top: titlebar.bottom
//                topMargin: 18
//                left: parent.left
//                leftMargin: 2
//            }
//            width: parent.width - 4
//            height: 1
//            color: "#d8e0e6"
//        }

//        Common.ScrollArea {
//            frame:false
//            anchors.top: titlebar.bottom
//            anchors.topMargin: 20
//            anchors.left:parent.left
//            anchors.leftMargin: 27
//            height: root.height - titlebar.height - 37
//            width: parent.width - 27 -2
//            Item {
//                id: scrollItem
//                width: parent.width
//                height: 0//40*2 + root.spaceValue*2
//                Column {
//                    spacing: root.spaceValue
//                    //垃圾清理显示内容
//                    ListView {
//                        id: aptListView
//                        width: parent.width
//                        height: root.package_expanded ? (root.debNum + 1) * 40 : 0
//                        model: mainModel
//                        delegate: CacheDelegate{
//                            sub_num: root.debNum
//                            sub_model: subModel
//                            btn_flag: root.btnFlag
//                            arrowFlag: "package"
//                            showNum: root.showNum
//                            arrow_display: root.arrowShow//为0时隐藏伸缩图标，为1时显示伸缩图标
//                            expanded: root.package_expanded//apt_expanded为true时，箭头向下，内容展开;apt_expanded为false时，箭头向上，内容收缩
//                            delegate_flag: root.splitFlag
//                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
//                            onCheckchanged: {
//                                root.maincheck = checkchange;
//                            }
//                            onArrowClicked: {
//                                if(cacheFlag == "package") {
//                                    if(expand_flag == true) {
//                                        root.package_expanded = true;
//                                        scrollItem.height = (root.debNum + 1) * 40;
//                                    }
//                                    else {
//                                        root.package_expanded = false;
//                                        scrollItem.height = 0;
//                                    }
//                                }
//                            }
//                        }
//                        cacheBuffer: 1000
//                        opacity: 1
//                        spacing: 10
//                        snapMode: ListView.NoSnap
//                        boundsBehavior: Flickable.DragOverBounds
//                        currentIndex: 0
//                        preferredHighlightBegin: 0
//                        preferredHighlightEnd: preferredHighlightBegin
//                        highlightRangeMode: ListView.StrictlyEnforceRange
//                    }
//                }
//            }
//        }

//        states: [
//            State {
//                name: "UnneedWork"
//                PropertyChanges { target: actionBtn; text:qsTr("Begin cleanup") }//开始清理
//                PropertyChanges { target: root; btnFlag: "package_work" }
//                PropertyChanges { target: backBtn; visible: true}
//                PropertyChanges { target: rescanBtn; visible: true}
//                PropertyChanges { target: root; package_expanded: true }//伸缩箭扩展
//                PropertyChanges { target: root; arrowShow: 1}//伸缩箭头显示
//                PropertyChanges { target: root; showNum: true}
//            },
//            State {
//                name: "UnneedWorkAGAIN"
//                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//                PropertyChanges { target: root; btnFlag: "package_scan" }
//                PropertyChanges { target: backBtn; visible: false}
//                PropertyChanges { target: rescanBtn; visible: false}
//                PropertyChanges { target: root; package_expanded: false }//伸缩箭头不扩展
//                PropertyChanges { target: root; arrowShow: 0}//伸缩箭头不显示
//                PropertyChanges { target: root; showNum: false}
//            },
//            State {
//                name: "UnneedWorkError"
//                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//                PropertyChanges { target: root; btnFlag: "package_scan" }
//                PropertyChanges { target: backBtn; visible: false}
//                PropertyChanges { target: rescanBtn; visible: false}
//            },
//            State {
//                name: "UnneedWorkFinish"
//                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
//                PropertyChanges { target: root; btnFlag: "package_scan" }
//                PropertyChanges { target: backBtn; visible: false}
//                PropertyChanges { target: rescanBtn; visible: false}
//            },
//            State {
//                name: "UnneedWorkEmpty"
//                PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
//                PropertyChanges { target: root; btnFlag: "package_scan" }
//                PropertyChanges { target: backBtn; visible: false}
//                PropertyChanges { target: rescanBtn; visible: false}
//                PropertyChanges { target: root; package_expanded: false }//伸缩箭头不扩展
//                PropertyChanges { target: root; arrowShow: 0}//伸缩箭头不显示
//                PropertyChanges { target: root; showNum: false}
//            }
//        ]
//    }
//    states: [
//        State {
//            name: "NormalState"
//            PropertyChanges { target: root; x: 0 }
//            PropertyChanges { target: masklayer2; x: (parent.width * 1.5) }
//        },

//        State {
//            name: "MaskLayerState"
//            PropertyChanges { target: masklayer2; x: 0 }
//            PropertyChanges { target: progressTitle; text: qsTr("Software operation schedule") }//软件操作进度
//            PropertyChanges { target: progress; value: 0 }
//            PropertyChanges { target: root; x: (parent.width * 1.5) }
//        }
//    ]
//}
