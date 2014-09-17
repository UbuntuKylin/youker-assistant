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
import "../bars" as Bars

Item {
    id:packagepage
    width: parent.width; height: 437

    Rectangle {
        id: masklayer
        width: parent.width
        height: parent.height
        color: "#eeedf0"
        x: (parent.width * 1.5)
        //背景
//        Image {
//            source: "../../img/skin/bg-middle.png"
//            anchors.fill: parent
//        }
        Connections
        {
            target: systemdispatcher
            //得到数据，显示在进度条上
            onSendProgressToQML: {
                if(type == "apt_start") {
                    progress.value = 0;
                    packagepage.state = "MaskLayerState";
                }
                else if(type == "apt_pulse"){
                    progressTitle.text = qsTr("The ongoing: ") + info;//正在进行：
                    progress.value = ratio_sus;
                }
                else if(type == "apt_stop") {
//                    progress.value = 0;
                }
            }
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
//                background: "../../img/skin/progress-bg.png"
                color: "lightsteelblue"////"#086794"
                secondColor: "steelblue"//"#318d11"
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
                packagepage.state = "NormalState";
            }
        }
    }

    Rectangle {
        id:root
        width: parent.width
        height: parent.height
        color: "#eeedf0"
        property string title: qsTr("Uninstall unnecessary procedures, old kernel packages and configfile")//卸载不必要的程序、旧内核包和清除软件配置文件
        property string description: qsTr("Cleaning up the software that installed by other software bundled, old kernel packages and configfile, to improve system performance")//清理软件安装过程中捆绑安装的依赖程序、旧内核包和软件配置文件，提高系统性能
        property string btnFlag: "package_scan"//扫描或者清理的标记：package_scan/package_work
        property bool packageresultFlag: false//判断依赖包扫描后的实际内容是否为空，为空时为false，有内容时为true
        property bool kernelresultFlag: false//判断旧内核包扫描后的实际内容是否为空，为空时为false，有内容时为true
        property bool configresultFlag: false//判断软件配置扫描后的实际内容是否为空，为空时为false，有内容时为true
        property int packageNum//扫描后得到的依赖包的项目总数
        property int kernelNum//扫描后得到的旧内核包的项目总数
        property int configNum//扫描后得到的软件配置的项目总数
        property bool packageEmpty: false//决定是否显示扫描内容为空的状态图
        property bool kernelEmpty: false//决定是否显示扫描内容为空的状态图
        property bool configEmpty: false//决定是否显示扫描内容为空的状态图
        property int mode: 0//扫描模式：0表示两者都扫描，1表示只选中了package，2表示只选中了kernel，3表示只选中了config, 4表示只选中了package和kernel，5表示只选中了package和config, 6表示只选中了kernel和config
        property bool splitFlag: true//传递给CacheDelegate.qml,为true时切割字符串，为false时不切割字符串
        property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
        property int spaceValue: 20
        property int package_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property int kernel_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property int config_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
        property bool package_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
        property bool kernel_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
        property bool config_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
        property bool package_maincheck: true
        property bool kernel_maincheck: true
        property bool config_maincheck: true
        property bool package_showNum: false//决定依赖包的扫描结果数是否显示
        property bool kernel_showNum: false//决定旧内核包的扫描结果数是否显示
        property bool config_showNum: false//决定旧内核包的扫描结果数是否显示
        ListModel { id: packagemainModel }
        ListModel { id: packagesubModel }
        ListModel { id: kernelmainModel }
        ListModel { id: kernelsubModel }
        ListModel { id: configmainModel }
        ListModel { id: configsubModel }
        property int item_height: 30

        Component.onCompleted: {
            //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
            packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                             "itemTitle": qsTr("Uninstall unnecessary procedures"),
                             "picture": "../../img/toolWidget/deb-min.png"})
            //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
            kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                             "itemTitle": qsTr("Uninstall old kernel packages"),
                             "picture": "../../img/toolWidget/kernel.png"})
            //清除软件配置文件
            configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                             "itemTitle": qsTr("Cleanup software configfile"),
                             "picture": "../../img/toolWidget/configfile.png"})
        }

        Connections
        {
            target: sessiondispatcher
            onAppendPackageContentToCacheModel: {
                //QString flag, QString pkgName, QString description, QString sizeValue
                if(flag == "unneed") {
                    packagesubModel.append({"itemTitle": pkgName, "desc": description, "number": sizeValue, "index": root.packageNum, "checked": true});
                    root.packageNum += 1;
                }
                else if(flag == "oldkernel") {
                    kernelsubModel.append({"itemTitle": pkgName, "desc": description, "number": sizeValue, "index": root.kernelNum, "checked": true});
                    root.kernelNum += 1;
                }
                else if(flag == "configfile") {
                    configsubModel.append({"itemTitle": pkgName, "desc": description, "number": sizeValue, "index": root.configNum, "checked": true});
                    root.configNum += 1;
                }
            }
            onTellQMLPackageOver: {
                doingImage.visible = false;
                packagemainModel.clear();
                kernelmainModel.clear();
                configmainModel.clear();
                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                 "picture": "../../img/toolWidget/deb-min.png"})
                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                 "picture": "../../img/toolWidget/kernel.png"})
                //清除软件配置文件
                configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup software configfile"),
                                 "picture": "../../img/toolWidget/configfile.png"})

                if(root.packageNum != 0) {
                    root.packageresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(root.mode == 0 || root.mode == 1 || root.mode == 4 || root.mode == 5) {
                        root.packageEmpty = true;
                    }
                    root.packageresultFlag = false;//扫描的实际有效内容不存在
                }
                if(root.kernelNum != 0) {
                    root.kernelresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(root.mode == 0 || root.mode == 2 || root.mode == 4 || root.mode == 6) {
                        root.kernelEmpty = true;
                    }
                    root.kernelresultFlag = false;//扫描的实际有效内容不存在
                }
                if(root.configNum != 0) {
                    root.configresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(root.mode == 0 || root.mode == 3 || root.mode == 5 || root.mode == 6) {
                        root.configEmpty = true;
                    }
                    root.configresultFlag = false;//扫描的实际有效内容不存在
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
                if(root.configresultFlag == false) {
                    root.config_showNum = false;
                    root.config_expanded = false;//伸缩箭头不扩展
                    root.config_arrow_show = 0;//伸缩箭头不显示
                }
                else if(root.configresultFlag == true) {
                    root.config_showNum = true;
                    root.config_expanded = true;//伸缩箭头扩展
                    root.config_arrow_show = 1;//伸缩箭头显示
                }

                if(root.packageresultFlag == false && root.kernelresultFlag == false && root.configresultFlag == false) {
                    root.state = "PackageWorkEmpty";
                    if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        //友情提示：      扫描内容为空，无需清理！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                    }
                    else {//清理apt后的重新获取数据，此时不需要显示对话框
                        root.flag = false;
                    }
                }
                else {
                    if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
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
                scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 1) * root.item_height + (root.configNum + 1) * root.item_height + root.spaceValue*6;
                //扫描完成后恢复按钮的使能
                actionBtn.enabled = true;
            }
        }

        Connections
        {
            target: systemdispatcher
            onFinishCleanDebError: {//清理出错时收到的信号
                if (root.btnFlag == "package_work") {
                    if (msg == "package") {
                        packagepage.state = "NormalState";
                        //清理过程中发生错误，解禁按钮
                        actionBtn.enabled = true;
                        packagepage.state = "PackageWorkError";
                        toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                    }
                }
            }
            onFinishCleanDeb: {//清理成功时收到的信号
                if (root.btnFlag == "package_work") {
                    if (msg == "") {
                        //清理取消，解禁按钮
                        actionBtn.enabled = true;
                        packagepage.state = "NormalState";
                        toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
                    }
                    else if (msg == "package") {
                        root.state = "PackageWorkFinish";
                        toolkits.alertMSG(qsTr("Cleared"));//清理完毕
                        //清理完毕后重新获取数据
                        root.flag = true;
//                        root.getData();
                        if(root.package_maincheck && root.kernel_maincheck && root.config_maincheck) {
                            packagemainModel.clear();
                            kernelmainModel.clear();
                            configmainModel.clear();
                            //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                            packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                             "picture": "../../img/toolWidget/deb-min.png"})
                            //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                            kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Uninstall old kernel packages"),
                                             "picture": "../../img/toolWidget/kernel.png"})
                            //清除软件配置文件
                            configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup software configfile"),
                                             "picture": "../../img/toolWidget/configfile.png"})
                            packagesubModel.clear();//内容清空
                            kernelsubModel.clear();//内容清空
                            configsubModel.clear();//内容清空
                            root.packageNum = 0;//隐藏滑动条
                            root.kernelNum = 0;//隐藏滑动条
                            root.configNum = 0;//隐藏滑动条
                            root.mode = 0;
                            sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(0));
                        }
                        else {
                            if(root.package_maincheck && !root.kernel_maincheck && !root.config_maincheck) {
                                packagemainModel.clear();
                                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                                 "picture": "../../img/toolWidget/deb-min.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 1;
                                sessiondispatcher.package_scan_function_qt("unneed");
                            }
                            else if(!root.package_maincheck && root.kernel_maincheck && !root.config_maincheck) {
                                kernelmainModel.clear();
                                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                                 "picture": "../../img/toolWidget/kernel.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 2;
                                sessiondispatcher.package_scan_function_qt("oldkernel");
                            }
                            else if(!root.package_maincheck && !root.kernel_maincheck && root.config_maincheck) {
                                configmainModel.clear();
                                //清除软件配置文件
                                configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Cleanup software configfile"),
                                                 "picture": "../../img/toolWidget/configfile.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 3;
                                sessiondispatcher.package_scan_function_qt("configfile");
                            }
                            else if(root.package_maincheck && root.kernel_maincheck && !root.config_maincheck) {
                                packagemainModel.clear();
                                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                                 "picture": "../../img/toolWidget/deb-min.png"})
                                kernelmainModel.clear();
                                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                                 "picture": "../../img/toolWidget/kernel.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 4;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(4));
                            }
                            else if(root.package_maincheck && !root.kernel_maincheck && root.config_maincheck) {
                                packagemainModel.clear();
                                //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                                packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                                 "picture": "../../img/toolWidget/deb-min.png"})
                                configmainModel.clear();
                                //清除软件配置文件
                                configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Cleanup software configfile"),
                                                 "picture": "../../img/toolWidget/configfile.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 5;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(5));
                            }
                            else if(!root.package_maincheck && root.kernel_maincheck && root.config_maincheck) {
                                kernelmainModel.clear();
                                //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                                kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Uninstall old kernel packages"),
                                                 "picture": "../../img/toolWidget/kernel.png"})
                                configmainModel.clear();
                                //清除软件配置文件
                                configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                                 "itemTitle": qsTr("Cleanup software configfile"),
                                                 "picture": "../../img/toolWidget/configfile.png"})
                                packagesubModel.clear();//内容清空
                                kernelsubModel.clear();//内容清空
                                configsubModel.clear();//内容清空
                                root.packageNum = 0;//隐藏滑动条
                                root.kernelNum = 0;//隐藏滑动条
                                root.configNum = 0;//隐藏滑动条
                                root.mode = 6;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(6));
                            }
                        }
                        packagepage.state = "NormalState";
                        //清理成功完成，解禁按钮
                        actionBtn.enabled = true;
                    }
                }
            }
        }

        //背景
//        Image {
//            source: "../../img/skin/bg-middle.png"
//            anchors.fill: parent
//        }

        //titlebar
        Row {
            id: titlebar
            spacing: 20
            width: parent.width
            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
            Image {
                id: apt_refreshArrow
                source: "../../img/toolWidget/program.png"
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
            anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 20 }
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
                        actionBtn.visible = true;
                        actionBtn.enabled = true;
                        root.packageEmpty = false;
                        root.kernelEmpty = false;
                        root.configEmpty = false;
                        if(root.package_maincheck == false) {
                            root.package_maincheck = true;
                        }
                        if(root.kernel_maincheck == false) {
                            root.kernel_maincheck = true;
                        }
                        if(root.config_maincheck == false) {
                            root.config_maincheck = true;
                        }
                        root.package_showNum = false;
                        root.kernel_showNum = false;
                        root.config_showNum = false;
                        packagemainModel.clear();
                        kernelmainModel.clear();
                        configmainModel.clear();
                        //卸载不必要的程序         可以根据扫描结果选择性地清理安装程序，让系统更瘦。
                        packagemainModel.append({"mstatus": root.package_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Uninstall unnecessary procedures"),
                                         "picture": "../../img/toolWidget/deb-min.png"})
                        //卸载旧内核包        可以根据扫描结果选择性地清理旧内核包，让系统更瘦。
                        kernelmainModel.append({"mstatus": root.kernel_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Uninstall old kernel packages"),
                                         "picture": "../../img/toolWidget/kernel.png"})
                        //清除软件配置文件
                        configmainModel.append({"mstatus": root.config_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Cleanup software configfile"),
                                         "picture": "../../img/toolWidget/configfile.png"})
                        packagesubModel.clear();//内容清空
                        root.packageNum = 0;//隐藏滑动条
                        root.package_arrow_show = 0;//伸缩图标隐藏
                        kernelsubModel.clear();//内容清空
                        root.kernelNum = 0;//隐藏滑动条
                        root.kernel_arrow_show = 0;//伸缩图标隐藏
                        configsubModel.clear();//内容清空
                        root.configNum = 0;//隐藏滑动条
                        root.config_arrow_show = 0;//伸缩图标隐藏
                        scrollItem.height = 3 * root.item_height + root.spaceValue*6;
                        root.state = "PackageWorkAGAIN";//按钮的状态恢复初始值
                    }
                }
            }
            Common.Button {
                id: actionBtn
                picNormal: "../../img/icons/button16.png"
                picHover: "../../img/icons/button16-hover.png"
                picPressed: "../../img/icons/button16-hover.png"
                fontcolor:"#ffffff"
                fontsize: 16
                width: 120; height: 36
                text: qsTr("Start scanning")//开始扫描
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {

                    root.packageEmpty = false;
                    root.kernelEmpty = false;
                    root.configEmpty = false;

                    if (root.btnFlag == "package_scan") {//扫描
                        //扫描过程中禁用按钮
                        actionBtn.enabled = false;
                        root.flag = false;
//                            root.getData();
                        if(root.package_maincheck && root.kernel_maincheck && root.config_maincheck) {
                            root.mode = 0;
                            root.packageNum = 0;
                            root.kernelNum = 0;
                            root.configNum = 0;
                            doingImage.visible = true;
                            sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(0));
                        }
                        else {
                            if(root.package_maincheck && !root.kernel_maincheck && !root.config_maincheck) {
                                root.mode = 1;
                                root.packageNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt("unneed");
                            }
                            else if(!root.package_maincheck && root.kernel_maincheck && !root.config_maincheck) {
                                root.mode = 2;
                                root.kernelNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt("oldkernel");
                            }
                            else if(!root.package_maincheck && !root.kernel_maincheck && root.config_maincheck) {
                                root.mode = 3;
                                root.configNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt("configfile");
                            }
                            else if(root.package_maincheck && root.kernel_maincheck && !root.config_maincheck) {
                                root.mode = 4;
                                root.packageNum = 0;
                                root.kernelNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(4));
                            }
                            else if(root.package_maincheck && !root.kernel_maincheck && root.config_maincheck) {
                                root.mode = 5;
                                root.packageNum = 0;
                                root.configNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(5));
                            }
                            else if(!root.package_maincheck && root.kernel_maincheck && root.config_maincheck) {
                                root.mode = 6;
                                root.kernelNum = 0;
                                root.configNum = 0;
                                doingImage.visible = true;
                                sessiondispatcher.package_scan_function_qt(sessiondispatcher.get_package_arglist(6));
                            }
                            else{
                                doingImage.visible = false;
                                actionBtn.enabled = true;
                                //友情提示：        对不起，您没有选择需要扫描的内容，请确认！
                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be scanned, please confirm!"));
                            }
                        }
                    }
                    else if (root.btnFlag == "package_work") {//清理
                        if(root.packageresultFlag || root.kernelresultFlag || root.configresultFlag) {//扫描得到的实际内容存在时
                            if(!root.package_maincheck && !root.kernel_maincheck && !root.config_maincheck) {
                                //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"));
                            }
                            else {
//                                    packagepage.state = "MaskLayerState";

                                //test 0410
                                var packagelist = new Array();
                                for(var i=0; i<packagesubModel.count; i++) {
                                    if(packagesubModel.get(i).checked) {
                                        packagelist.push(packagesubModel.get(i).itemTitle);
                                    }
                                }
                                for(var j=0; j<kernelsubModel.count; j++) {
                                    if(kernelsubModel.get(j).checked) {
                                        packagelist.push(kernelsubModel.get(j).itemTitle);
                                    }
                                }
                                for(var k=0; k<configsubModel.count; k++) {
                                    if(configsubModel.get(k).checked) {
                                        packagelist.push(configsubModel.get(k).itemTitle);
                                    }
                                }
                                //开始清理时，禁用按钮，等到清理完成后解禁
                                actionBtn.enabled = false;
                                systemdispatcher.clean_package_cruft_qt(packagelist, "package");
                            }
                        }
                    }
                }
            }
            AnimatedImage {
                id: doingImage
                anchors.verticalCenter: parent.verticalCenter
                width: 16
                height: 16
                visible: false
                source: "../../img/icons/move.gif"
            }
        }

        //分割条
        Common.Separator {
            id: splitbar
            anchors {
                top: titlebar.bottom
                topMargin: 18
                left: parent.left
                leftMargin: 2
            }
            width: parent.width - 4
        }

        Common.ScrollArea {
            frame:false
            anchors.top: titlebar.bottom
            anchors.topMargin: 30
            anchors.left:parent.left
            height: root.height - titlebar.height - 47
            width: parent.width -2//parent.width - 27 -2
            Item {
                id: scrollItem
                width: parent.width
                height: root.item_height*3 + root.spaceValue*3*2
                Column {
                    spacing: root.spaceValue*2
                    //垃圾清理显示内容
                    ListView {
                        id: aptListView
                        width: parent.width
                        height: root.package_expanded ? (root.packageNum + 1) * root.item_height : root.item_height
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

                            //test 0410
                            onTransmitCacheItemMainCheckBoxStatus: {
                                if(flag == "package") {
                                    if(status) {
                                        for(var i=0; i<packagesubModel.count; i++) {
                                            packagesubModel.setProperty(i, "checked", true);
                                        }
                                    }
                                    else {
                                        for(var j=0; j<packagesubModel.count; j++) {
                                            packagesubModel.setProperty(j, "checked", false);
                                        }
                                    }
                                }
                            }

                            //test 0410
                            onTransmitCacheItemCheckBoxStatus: {
                                if(flag == "package") {
                                    if(status) {
                                        packagesubModel.setProperty(index, "checked", true);
                                    }
                                    else {
                                        packagesubModel.setProperty(index, "checked", false);
                                    }
                                }
                            }

                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                            onCheckchanged: {
    //                            root.packageresultFlag = checkchange;
                                root.package_maincheck = checkchange;
                            }
                            onArrowClicked: {
                                if(cacheFlag == "package") {//1212
                                    if(expand_flag == true) {
                                        root.package_expanded = true;
                                        if((root.kernel_expanded == true) && (root.config_expanded == true)) {
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 1) * root.item_height + (root.configNum + 1) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.kernel_expanded == true) && (root.config_expanded == false)){
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.kernel_expanded == false) && (root.config_expanded == true)){
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.configNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = (root.packageNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                    }
                                    else {
                                        root.package_expanded = false;
                                        if((root.kernel_expanded == true) && (root.config_expanded == true)) {
                                            scrollItem.height = (root.kernelNum + 1) * root.item_height + (root.configNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.kernel_expanded == true) && (root.config_expanded == false)){
                                            scrollItem.height = (root.kernelNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.kernel_expanded == false) && (root.config_expanded == true)){
                                            scrollItem.height = (root.configNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = 3 * root.item_height + root.spaceValue*6;
                                        }
                                    }
                                }
                            }
                        }
                        cacheBuffer: 1000
                        opacity: 1
//                        spacing: 10
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
                        height: root.kernel_expanded ? (root.kernelNum + 1) * root.item_height : root.item_height
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

                            //test 0410
                            onTransmitCacheItemMainCheckBoxStatus: {
                                if(flag == "kernel") {
                                    if(status) {
                                        for(var i=0; i<kernelsubModel.count; i++) {
                                            kernelsubModel.setProperty(i, "checked", true);
                                        }
                                    }
                                    else {
                                        for(var j=0; j<kernelsubModel.count; j++) {
                                            kernelsubModel.setProperty(j, "checked", false);
                                        }
                                    }
                                }
                            }

                            //test 0410
                            onTransmitCacheItemCheckBoxStatus: {
                                if(flag == "kernel") {
                                    if(status) {
                                        kernelsubModel.setProperty(index, "checked", true);
                                    }
                                    else {
                                        kernelsubModel.setProperty(index, "checked", false);
                                    }
                                }
                            }


                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                            onCheckchanged: {
    //                            root.kernelresultFlag = checkchange;
                                root.kernel_maincheck = checkchange;
                            }
                            onArrowClicked: {
                                if(cacheFlag == "kernel") {//1212
                                    if(expand_flag == true) {
                                        root.kernel_expanded = true;
                                        if((root.package_expanded == true) && (root.config_expanded == true)) {
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 1) * root.item_height + (root.configNum + 1) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == true) && (root.config_expanded == false)){
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == false) && (root.config_expanded == true)){
                                            scrollItem.height = (root.configNum + 1) * root.item_height + (root.kernelNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = (root.kernelNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                    }
                                    else {
                                        root.kernel_expanded = false;
                                        if((root.package_expanded == true) && (root.config_expanded == true)) {
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.configNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == true) && (root.config_expanded == false)){
                                            scrollItem.height = (root.packageNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == false) && (root.config_expanded == true)){
                                            scrollItem.height = (root.configNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = 3 * root.item_height + root.spaceValue*6;
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
                        id: configListView
                        width: parent.width
                        height: root.config_expanded ? (root.configNum + 1) * root.item_height : root.item_height
                        model: configmainModel
                        delegate: CacheDelegate{
                            sub_num: root.configNum
                            sub_model: configsubModel
                            btn_flag: root.btnFlag
                            showNum: root.config_showNum
                            arrowFlag: "configfile"
                            arrow_display: root.config_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                            expanded: root.config_expanded//kernel_expanded为true时，箭头向下，内容展开;kernel_expanded为false时，箭头向上，内容收缩
                            delegate_flag: root.splitFlag
                            emptyTip: root.configEmpty

                            //test 0410
                            onTransmitCacheItemMainCheckBoxStatus: {
                                if(flag == "configfile") {
                                    if(status) {
                                        for(var i=0; i<configsubModel.count; i++) {
                                            configsubModel.setProperty(i, "checked", true);
                                        }
                                    }
                                    else {
                                        for(var j=0; j<configsubModel.count; j++) {
                                            configsubModel.setProperty(j, "checked", false);
                                        }
                                    }
                                }
                            }

                            //test 0410
                            onTransmitCacheItemCheckBoxStatus: {
                                if(flag == "configfile") {
                                    if(status) {
                                        configsubModel.setProperty(index, "checked", true);
                                    }
                                    else {
                                        configsubModel.setProperty(index, "checked", false);
                                    }
                                }
                            }


                            //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                            onCheckchanged: {
    //                            root.kernelresultFlag = checkchange;
                                root.config_maincheck = checkchange;
                            }
                            onArrowClicked: {
                                if(cacheFlag == "configfile") {//1212
                                    if(expand_flag == true) {
                                        root.config_expanded = true;
                                        if((root.package_expanded == true) && (root.kernel_expanded == true)) {
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 1) * root.item_height + (root.configNum + 1) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == true) && (root.kernel_expanded == false)){
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.configNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == false) && (root.kernel_expanded == true)){
                                            scrollItem.height = (root.kernelNum + 1) * root.item_height + (root.configNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = (root.configNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                    }
                                    else {
                                        root.config_expanded = false;
                                        if((root.package_expanded == true) && (root.kernel_expanded == true)) {
                                            scrollItem.height = (root.packageNum + 1) * root.item_height + (root.kernelNum + 2) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == true) && (root.kernel_expanded == false)){
                                            scrollItem.height = (root.packageNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else if((root.package_expanded == false) && (root.kernel_expanded == true)){
                                            scrollItem.height = (root.kernelNum + 3) * root.item_height + root.spaceValue*6;
                                        }
                                        else {
                                            scrollItem.height = 3 * root.item_height + root.spaceValue*6;
                                        }
                                    }
                                }
                            }
                        }
                        cacheBuffer: 1000
                        opacity: 1
//                        spacing: 10
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
            },
            State {
                name: "PackageWorkAGAIN"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
            },
            State {
                name: "PackageWorkError"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
            },
            State {
                name: "PackageWorkFinish"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
            },
            State {
                name: "PackageWorkEmpty"
                PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
                PropertyChanges { target: root; btnFlag: "package_scan" }
                PropertyChanges { target: backBtn; visible: false}
            }
        ]
    }
    states: [
        State {
            name: "NormalState"
            PropertyChanges { target: root; x: 0 }
            PropertyChanges { target: masklayer; x: (parent.width * 1.5) }
        },

        State {
            name: "MaskLayerState"
            PropertyChanges { target: masklayer; x: 0 }
            PropertyChanges { target: progressTitle; text: qsTr("Software operation schedule") }//软件操作进度
            PropertyChanges { target: progress; value: 0 }
            PropertyChanges { target: root; x: (parent.width * 1.5) }
        }
    ]
}
