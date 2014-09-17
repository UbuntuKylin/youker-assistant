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
    id:cachepage
    width: parent.width; height: 437
    color: "#eeedf0"

    property string title: qsTr("Cleaning up the system cache")//深度清理系统缓存
    property string description: qsTr("Deep cleaning up the system cache, to save disk space")//深度清理系统缓存，节省磁盘空间！
    property string btnFlag: "cache_scan"//扫描或者清理的标记：cache_scan/cache_work
    property bool aptresultFlag: false//判断apt扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool softresultFlag: false//判断soft扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool thumbresultFlag: false//判断thumbnails扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int aptNum//扫描后得到的apt的项目总数
    property int softNum//扫描后得到的soft的项目总数
    property int thumbNum//扫描后得到的thumbnails的项目总数
    property bool splitFlag: true//传递给CacheDelegate.qml,为true时切割字符串，为false时不切割字符串
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
    property int spaceValue: 20
    property int apt_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int soft_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int thumb_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool apt_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool soft_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool thumb_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool apt_maincheck: true
    property bool soft_maincheck: true
    property bool thumb_maincheck: true
    property bool apt_showNum: false//决定apt的扫描结果数是否显示
    property bool soft_showNum: false//决定soft的扫描结果数是否显示
    property bool thumb_showNum: false//决定thumbnails的扫描结果数是否显示
    property bool aptEmpty: false//决定是否显示扫描内容为空的状态图
    property bool softEmpty: false//决定是否显示扫描内容为空的状态图
    property bool thumbEmpty: false//决定是否显示扫描内容为空的状态图
    property int item_height: 30
    property int mode: 0//扫描模式：0表示两者都扫描，1表示只选中了apt，2表示只选中了soft，3表示只选中了thumbnails, 4表示只选中了apt和soft，5表示只选中了apt和thumbnails, 6表示只选中了thumbnails和soft
    ListModel { id: aptmainModel }
    ListModel { id: aptsubModel }
    ListModel { id: softmainModel }
    ListModel { id: softsubModel }
    ListModel { id: thumbmainModel }
    ListModel { id: thumbsubModel }

    Connections
    {
        target: sessiondispatcher
        onAppendContentToCacheModel: {
            //QString flag, QString path, QString fileFlag, QString sizeValue
            if(flag == "apt") {//Apt缓存
                aptsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue, "index": cachepage.aptNum, "checked": true});
                cachepage.aptNum += 1;
            }
            else if(flag == "software-center") {//软件中心缓存
                softsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue, "index": cachepage.softNum, "checked": true});
                cachepage.softNum += 1;
            }
            else if(flag == "thumbnails") {//缩略图缓存
                thumbsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue, "index": cachepage.thumbNum, "checked": true});
                cachepage.thumbNum += 1;
            }
        }
        onTellQMLCaheOver: {
            if(flag == "cache") {
                aptmainModel.clear();
                softmainModel.clear();
                thumbmainModel.clear();
                //"detailstr": qsTr("Apt Cache Path: /var/cache/apt/archives"
                //sessiondispatcher.getHomePath() + "/.cache/software-center"
                //"detailstr": qsTr("Thumbnails Cache Path: ") + sessiondispatcher.getHomePath() + "/.cache/thumbnails"
                doingImage.visible = false;
                //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup Package Cache"),
                                 "picture": "../../img/toolWidget/apt-min.png"})
                //软件中心缓存清理       软件中心缓存路径：
                softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup Software Center Cache"),
                                 "picture": "../../img/toolWidget/software-min.png"})
                //缩略图缓存清理       缩略图缓存路径：
                thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                 "picture": "../../img/toolWidget/thumbnails.png"})
                if(cachepage.aptNum != 0) {
                    cachepage.aptresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(cachepage.mode == 0 || cachepage.mode == 1 || cachepage.mode == 4 || cachepage.mode == 5) {
                        cachepage.aptEmpty = true;
                    }
                    cachepage.aptresultFlag = false;//扫描的实际有效内容不存在
                }
                if(cachepage.softNum != 0) {
                    cachepage.softresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(cachepage.mode == 0 || cachepage.mode == 2  || cachepage.mode == 4 || cachepage.mode == 6) {
                        cachepage.softEmpty = true;
                    }
                    cachepage.softresultFlag = false;//扫描的实际有效内容不存在
                }
                if(cachepage.thumbNum != 0) {
                    cachepage.thumbresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(cachepage.mode == 0 || cachepage.mode == 3 || cachepage.mode == 5 || cachepage.mode == 6) {
                        cachepage.thumbEmpty = true;
                    }
                    cachepage.thumbresultFlag = false;//扫描的实际有效内容不存在
                }

                if(cachepage.aptresultFlag == false) {
                    cachepage.apt_showNum = false;
                    cachepage.apt_expanded = false;//伸缩箭头不扩展
                    cachepage.apt_arrow_show = 0;//伸缩箭头不显示
                }
                else if(cachepage.aptresultFlag == true) {
                    cachepage.apt_showNum = true;
                    cachepage.apt_expanded = true;//伸缩箭头扩展
                    cachepage.apt_arrow_show = 1;//伸缩箭头显示
                }
                if(cachepage.softresultFlag == false) {
                    cachepage.soft_showNum = false;
                    cachepage.soft_expanded = false;//伸缩箭头不扩展
                    cachepage.soft_arrow_show = 0;//伸缩箭头不显示
                }
                else if(cachepage.softresultFlag == true) {
                    cachepage.soft_showNum = true;
                    cachepage.soft_expanded = true;//伸缩箭头扩展
                    cachepage.soft_arrow_show = 1;//伸缩箭头显示
                }
                if(cachepage.thumbresultFlag == false) {
                    cachepage.thumb_showNum = false;
                    cachepage.thumb_expanded = false;//伸缩箭头不扩展
                    cachepage.thumb_arrow_show = 0;//伸缩箭头不显示
                }
                else if(cachepage.thumbresultFlag == true) {
                    cachepage.thumb_showNum = true;
                    cachepage.thumb_expanded = true;//伸缩箭头扩展
                    cachepage.thumb_arrow_show = 1;//伸缩箭头显示
                }

                if(cachepage.aptresultFlag == false && cachepage.softresultFlag == false && cachepage.thumbresultFlag == false) {
                    cachepage.state = "AptWorkEmpty";
                    if(cachepage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        //友情提示：      扫描内容为空，无需清理！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                    }
                    else {//清理apt后的重新获取数据，此时不需要显示对话框
                        cachepage.flag = false;
                    }
                }
                else {
                    if(cachepage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                    }
                    else {//清理software后的重新获取数据，此时不需要显示对话框
                        cachepage.flag = false;
                    }
                    cachepage.state = "AptWork";
                    actionBtn.text = qsTr("Begin cleanup");//开始清理
                    cachepage.btnFlag = "cache_work";
                    backBtn.visible = true;
    //                rescanBtn.visible = true;
                }
                scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 1) * cachepage.item_height + cachepage.spaceValue*6;
                //扫描完成后恢复按钮的使能
                actionBtn.enabled = true;
            }
        }
    }

    Component.onCompleted: {
        //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
        aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                         "itemTitle": qsTr("Cleanup Package Cache"),
                         "picture": "../../img/toolWidget/apt-min.png"})
        //软件中心缓存清理       软件中心缓存：
        softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                         "itemTitle": qsTr("Cleanup Software Center Cache"),
                         "picture": "../../img/toolWidget/software-min.png"})
        //缩略图缓存清理       缩略图缓存路径：
        thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                         "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                         "picture": "../../img/toolWidget/thumbnails.png"})
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (btnFlag == "cache_work") {
                if (msg == "cache") {
                    doingImage.visible = false;
                    cachepage.state = "AptWorkError";
                    //清理过程中发生错误，解禁按钮
                    actionBtn.enabled = true;
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (cachepage.btnFlag == "cache_work") {
                doingImage.visible = false;
                if (msg == "") {
                    //清理取消，解禁按钮
                    actionBtn.enabled = true;
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
                }
                else if (msg == "cache") {
                    cachepage.state = "AptWorkFinish";
                    toolkits.alertMSG(qsTr("Cleared!"));//清理完毕！
                    //清理完毕后重新获取数据
                    cachepage.flag = true;
                    if(cachepage.apt_maincheck && cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                        aptmainModel.clear();
                        softmainModel.clear();
                        thumbmainModel.clear();
                        //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                        aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Package cache cleanup"),
                                         "picture": "../../img/toolWidget/apt-min.png"})
                        //软件中心缓存清理       软件中心缓存：
                        softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Software Center buffer cleaning"),
                                         "picture": "../../img/toolWidget/software-min.png"})
                        //缩略图缓存清理       缩略图缓存路径：
                        thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                         "picture": "../../img/toolWidget/thumbnails.png"})
                        aptsubModel.clear();//内容清空
                        softsubModel.clear();//内容清空
                        thumbsubModel.clear();//内容清空
                        cachepage.aptNum = 0;//隐藏滑动条
                        cachepage.softNum = 0;//隐藏滑动条
                        cachepage.thumbNum = 0;//隐藏滑动条
                        cachepage.mode = 0;
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(0), 'cache');
                    }
                    else {
                        if(cachepage.apt_maincheck && !cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            aptmainModel.clear();
                            //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                            aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Package cache cleanup"),
                                             "picture": "../../img/toolWidget/apt-min.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 1;
                            sessiondispatcher.cache_scan_function_qt("apt", 'cache');
                        }
                        else if(!cachepage.apt_maincheck && cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            softmainModel.clear();
                            //软件中心缓存清理       软件中心缓存：
                            softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Software Center buffer cleaning"),
                                             "picture": "../../img/toolWidget/software-min.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 2;
                            sessiondispatcher.cache_scan_function_qt("software-center", 'cache');
                        }
                        else if(!cachepage.apt_maincheck && !cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            thumbmainModel.clear();
                            //缩略图缓存清理       缩略图缓存路径：
                            thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                             "picture": "../../img/toolWidget/thumbnails.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 3;
                            sessiondispatcher.cache_scan_function_qt("thumbnails", 'cache');
                        }
                        else if(cachepage.apt_maincheck && cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            aptmainModel.clear();
                            //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                            aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Package cache cleanup"),
                                             "picture": "../../img/toolWidget/apt-min.png"})
                            softmainModel.clear();
                            //软件中心缓存清理       软件中心缓存：
                            softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Software Center buffer cleaning"),
                                             "picture": "../../img/toolWidget/software-min.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 4;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(4), 'cache');
                        }
                        else if(cachepage.apt_maincheck && !cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            aptmainModel.clear();
                            //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                            aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Package cache cleanup"),
                                             "picture": "../../img/toolWidget/apt-min.png"})
                            thumbmainModel.clear();
                            //缩略图缓存清理       缩略图缓存路径：
                            thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                             "picture": "../../img/toolWidget/thumbnails.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 5;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(5), 'cache');
                        }
                        else if(!cachepage.apt_maincheck && cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            softmainModel.clear();
                            //软件中心缓存清理       软件中心缓存：
                            softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Software Center buffer cleaning"),
                                             "picture": "../../img/toolWidget/software-min.png"})
                            thumbmainModel.clear();
                            //缩略图缓存清理       缩略图缓存路径：
                            thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                             "picture": "../../img/toolWidget/thumbnails.png"})
                            aptsubModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            thumbsubModel.clear();//内容清空
                            cachepage.aptNum = 0;//隐藏滑动条
                            cachepage.softNum = 0;//隐藏滑动条
                            cachepage.thumbNum = 0;//隐藏滑动条
                            cachepage.mode = 6;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(6), 'cache');
                        }
                    }
                    //清理成功完成，解禁按钮
                    actionBtn.enabled = true;
                }
            }
        }
    }

    //背景
//    Image {
//        source: "../../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }

    //titlebar
    Row {
        id: titlebar
        spacing: 20
        width: parent.width
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
        Image {
            id: apt_refreshArrow
            source: "../../img/toolWidget/cache.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: cachepage.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: cachepage.description
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
                    cachepage.aptEmpty = false;
                    cachepage.softEmpty = false;
                    cachepage.thumbEmpty = false;
                    if(cachepage.apt_maincheck == false) {
                        cachepage.apt_maincheck = true;
                    }
                    if(cachepage.soft_maincheck == false) {
                        cachepage.soft_maincheck = true;
                    }
                    if(cachepage.thumb_maincheck == false) {
                        cachepage.thumb_maincheck = true;
                    }
                    cachepage.apt_showNum = false;
                    cachepage.soft_showNum = false;
                    cachepage.thumb_showNum = false;
                    aptmainModel.clear();
                    softmainModel.clear();
                    thumbmainModel.clear();
                    //软件包缓存清理           Apt缓存路径：/var/cache/apt/archives
                    aptmainModel.append({"mstatus": cachepage.apt_maincheck ? "true": "false",
                                     "itemTitle": qsTr("Package cache cleanup"),
                                     "picture": "../../img/toolWidget/apt-min.png"})
                    //软件中心缓存清理       软件中心缓存：
                    softmainModel.append({"mstatus": cachepage.soft_maincheck ? "true": "false",
                                     "itemTitle": qsTr("Software Center buffer cleaning"),
                                     "picture": "../../img/toolWidget/software-min.png"})
                    //缩略图缓存清理       缩略图缓存路径：
                    thumbmainModel.append({"mstatus": cachepage.thumb_maincheck ? "true": "false",
                                     "itemTitle": qsTr("Cleanup Thumbnails Cache"),
                                     "picture": "../../img/toolWidget/thumbnails.png"})
                    aptsubModel.clear();//内容清空
                    cachepage.aptNum = 0;//隐藏滑动条
                    cachepage.apt_arrow_show = 0;//伸缩图标隐藏
                    softsubModel.clear();//内容清空
                    cachepage.softNum = 0;//隐藏滑动条
                    cachepage.soft_arrow_show = 0;//伸缩图标隐藏
                    thumbsubModel.clear();//内容清空
                    cachepage.thumbNum = 0;//隐藏滑动条
                    cachepage.thumb_arrow_show = 0;//伸缩图标隐藏
                    scrollItem.height = 3 * cachepage.item_height + cachepage.spaceValue*6;
                    cachepage.state = "AptWorkAGAIN";//按钮的状态恢复初始值
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
                //扫描过程中禁用按钮
                actionBtn.enabled = false;
                cachepage.aptEmpty = false;
                cachepage.softEmpty = false;
                cachepage.thumbEmpty = false;
//                console.log("-----------");
//                console.log(cachepage.apt_maincheck);
//                console.log(cachepage.soft_maincheck);

                if (cachepage.btnFlag == "cache_scan") {//扫描
                    cachepage.flag = false;
                    if(cachepage.apt_maincheck && cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                        doingImage.visible = true;
                        cachepage.mode = 0;
                        cachepage.aptNum = 0;
                        cachepage.softNum = 0;
                        cachepage.thumbNum = 0;
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(0), 'cache');
                    }
                    else {
                        if(cachepage.apt_maincheck && !cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 1;
                            cachepage.aptNum = 0;
                            sessiondispatcher.cache_scan_function_qt("apt", 'cache');
                        }
                        else if(!cachepage.apt_maincheck && cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 2;
                            cachepage.softNum = 0;
                            sessiondispatcher.cache_scan_function_qt("software-center", 'cache');
                        }
                        else if(!cachepage.apt_maincheck && !cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 3;
                            cachepage.thumbNum = 0;
                            sessiondispatcher.cache_scan_function_qt("thumbnails", 'cache');
                        }
                        else if(cachepage.apt_maincheck && cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 4;
                            cachepage.aptNum = 0;
                            cachepage.softNum = 0;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(4), 'cache');
                        }
                        else if(cachepage.apt_maincheck && !cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 5;
                            cachepage.aptNum = 0;
                            cachepage.thumbNum = 0;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(5), 'cache');
                        }
                        else if(!cachepage.apt_maincheck && cachepage.soft_maincheck && cachepage.thumb_maincheck) {
                            doingImage.visible = true;
                            cachepage.mode = 6;
                            cachepage.softNum = 0;
                            cachepage.thumbNum = 0;
                            sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist(6), 'cache');
                        }
                        else{
                            doingImage.visible = false;
                            actionBtn.enabled = true;
                            //友情提示：        对不起，您没有选择需要扫描的内容，请确认！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be scanned, please confirm!"));
                        }
                    }
                }
                else if (cachepage.btnFlag == "cache_work") {//清理
                    if(cachepage.aptresultFlag || cachepage.softresultFlag || cachepage.thumbresultFlag) {//扫描得到的实际内容存在时
                        if(!cachepage.apt_maincheck && !cachepage.soft_maincheck && !cachepage.thumb_maincheck) {
                            //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"));
                        }
                        else {
                            //test 0410
                            var filelist = new Array();
                            for(var i=0; i<aptsubModel.count; i++) {
                                if(aptsubModel.get(i).checked) {
                                    console.log("111");
                                    console.log(i);
                                    filelist.push(aptsubModel.get(i).itemTitle);
                                }
                            }
                            for(var j=0; j<softsubModel.count; j++) {
                                if(softsubModel.get(j).checked) {
                                    console.log("222");
                                    console.log(j);
                                    filelist.push(softsubModel.get(j).itemTitle);
                                }
                            }
                            for(var k=0; k<thumbsubModel.count; k++) {
                                if(thumbsubModel.get(k).checked) {
                                    console.log("333");
                                    console.log(k);
                                    filelist.push(thumbsubModel.get(k).itemTitle);
                                }
                            }
                            doingImage.visible = true;
                            //开始清理时，禁用按钮，等到清理完成后解禁
                            actionBtn.enabled = false;
                            systemdispatcher.clean_file_cruft_qt(filelist, "cache");
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
//        anchors.leftMargin: 27
        height: cachepage.height - titlebar.height - 47
        width: parent.width -2//parent.width - 27 -2
        Item {
            id: scrollItem
            width: parent.width
            height: cachepage.item_height*3 + cachepage.spaceValue*3*2
            Column {
                spacing: cachepage.spaceValue * 2
                //垃圾清理显示内容
                ListView {
                    id: aptListView
                    width: parent.width
                    height: cachepage.apt_expanded ? (cachepage.aptNum + 1) * cachepage.item_height : cachepage.item_height
                    model: aptmainModel
                    delegate: CacheDelegate{
                        sub_num: cachepage.aptNum//cachepage.aptsubNum//1212
                        sub_model: aptsubModel
                        btn_flag: cachepage.btnFlag
                        arrowFlag: "apt"
                        showNum: cachepage.apt_showNum
                        arrow_display: cachepage.apt_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: cachepage.apt_expanded//apt_expanded为true时，箭头向下，内容展开;apt_expanded为false时，箭头向上，内容收缩
                        delegate_flag: cachepage.splitFlag
                        emptyTip: cachepage.aptEmpty

                        //test 0410
                        onTransmitCacheItemMainCheckBoxStatus: {
                            if(flag == "apt") {
                                if(status) {
                                    for(var i=0; i<aptsubModel.count; i++) {
                                        aptsubModel.setProperty(i, "checked", true);
                                    }
                                }
                                else {
                                    for(var j=0; j<aptsubModel.count; j++) {
                                        aptsubModel.setProperty(j, "checked", false);
                                    }
                                }
                            }
                        }

                        //test 0410
                        onTransmitCacheItemCheckBoxStatus: {
                            if(flag == "apt") {
                                if(status) {
                                    aptsubModel.setProperty(index, "checked", true);
                                }
                                else {
                                    aptsubModel.setProperty(index, "checked", false);
                                }
                            }
                        }


                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
//                            cachepage.aptresultFlag = checkchange;
                            cachepage.apt_maincheck = checkchange;
                        }
                        onTellModelToOpenFolder: {
                            if(category == "apt") {
                                sessiondispatcher.open_folder_qt(path);
                            }
                        }
                        onArrowClicked: {
                            if(cacheFlag == "apt") {//1212
                                if(expand_flag == true) {
                                    cachepage.apt_expanded = true;
                                    if((cachepage.soft_expanded == true) && (cachepage.thumb_expanded == true)) {
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 1) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.soft_expanded == true) && (cachepage.thumb_expanded == false)){
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.soft_expanded == false) && (cachepage.thumb_expanded == true)){
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.thumbNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = (cachepage.aptNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                                else {
                                    cachepage.apt_expanded = false;
                                    if((cachepage.soft_expanded == true) && (cachepage.thumb_expanded == true)) {
                                        scrollItem.height = (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.soft_expanded == true) && (cachepage.thumb_expanded == false)){
                                        scrollItem.height = (cachepage.softNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.soft_expanded == false) && (cachepage.thumb_expanded == true)){
                                        scrollItem.height = (cachepage.thumbNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = 3 * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                            }
                        }
                    }
                    cacheBuffer: 1000
                    opacity: 1
//                    spacing: 10
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
                    height: cachepage.soft_expanded ? (cachepage.softNum + 1) * cachepage.item_height : cachepage.item_height
                    model: softmainModel
                    delegate: CacheDelegate{
                        sub_num: cachepage.softNum
                        sub_model: softsubModel
                        btn_flag: cachepage.btnFlag
                        showNum: cachepage.soft_showNum
                        arrowFlag: "soft"
                        arrow_display: cachepage.soft_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: cachepage.soft_expanded//soft_expanded为true时，箭头向下，内容展开;soft_expanded为false时，箭头向上，内容收缩
                        delegate_flag: cachepage.splitFlag
                        emptyTip: cachepage.softEmpty

                        //test 0410
                        onTransmitCacheItemMainCheckBoxStatus: {
                            if(flag == "soft") {
                                if(status) {
                                    for(var i=0; i<softsubModel.count; i++) {
                                        softsubModel.setProperty(i, "checked", true);
                                    }
                                }
                                else {
                                    for(var j=0; j<softsubModel.count; j++) {
                                        softsubModel.setProperty(j, "checked", false);
                                    }
                                }
                            }
                        }

                        //test 0410
                        onTransmitCacheItemCheckBoxStatus: {
                            if(flag == "soft") {
                                if(status) {
                                    softsubModel.setProperty(index, "checked", true);
                                }
                                else {
                                    softsubModel.setProperty(index, "checked", false);
                                }
                            }
                        }


                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
//                            cachepage.softresultFlag = checkchange;
                            cachepage.soft_maincheck = checkchange;
                        }
                        onTellModelToOpenFolder: {
                            if(category == "soft") {
                                sessiondispatcher.open_folder_qt(path);
                            }
                        }
                        onArrowClicked: {
                            if(cacheFlag == "soft") {//1212
                                if(expand_flag == true) {
                                    cachepage.soft_expanded = true;
                                    if((cachepage.apt_expanded == true) && (cachepage.thumb_expanded == true)) {
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 1) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == true) && (cachepage.thumb_expanded == false)){
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == false) && (cachepage.thumb_expanded == true)){
                                        scrollItem.height = (cachepage.thumbNum + 1) * cachepage.item_height + (cachepage.softNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = (cachepage.softNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                                else {
                                    cachepage.soft_expanded = false;
                                    if((cachepage.apt_expanded == true) && (cachepage.thumb_expanded == true)) {
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.thumbNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == true) && (cachepage.thumb_expanded == false)){
                                        scrollItem.height = (cachepage.aptNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == false) && (cachepage.thumb_expanded == true)){
                                        scrollItem.height = (cachepage.thumbNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = 3 * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                            }
                        }
                    }
                    cacheBuffer: 1000
                    opacity: 1
//                    spacing: 10
                    snapMode: ListView.NoSnap
                    boundsBehavior: Flickable.DragOverBounds
                    currentIndex: 0
                    preferredHighlightBegin: 0
                    preferredHighlightEnd: preferredHighlightBegin
                    highlightRangeMode: ListView.StrictlyEnforceRange
                }
                //垃圾清理显示内容
                ListView {
                    id: thumbListView
                    width: parent.width
                    height: cachepage.thumb_expanded ? (cachepage.thumbNum + 1) * cachepage.item_height : cachepage.item_height
                    model: thumbmainModel
                    delegate: CacheDelegate{
                        sub_num: cachepage.thumbNum
                        sub_model: thumbsubModel
                        btn_flag: cachepage.btnFlag
                        showNum: cachepage.thumb_showNum
                        arrowFlag: "thumb"
                        arrow_display: cachepage.thumb_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: cachepage.thumb_expanded//soft_expanded为true时，箭头向下，内容展开;soft_expanded为false时，箭头向上，内容收缩
                        delegate_flag: cachepage.splitFlag
                        emptyTip: cachepage.thumbEmpty

                        //test 0410
                        onTransmitCacheItemMainCheckBoxStatus: {
                            if(flag == "thumb") {
                                if(status) {
                                    for(var i=0; i<thumbsubModel.count; i++) {
                                        thumbsubModel.setProperty(i, "checked", true);
                                    }
                                }
                                else {
                                    for(var j=0; j<thumbsubModel.count; j++) {
                                        thumbsubModel.setProperty(j, "checked", false);
                                    }
                                }
                            }
                        }

                        //test 0410
                        onTransmitCacheItemCheckBoxStatus: {
                            if(flag == "thumb") {
                                if(status) {
                                    thumbsubModel.setProperty(index, "checked", true);
                                }
                                else {
                                    thumbsubModel.setProperty(index, "checked", false);
                                }
                            }
                        }


                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
//                            cachepage.softresultFlag = checkchange;
                            cachepage.thumb_maincheck = checkchange;
                        }
                        onTellModelToOpenFolder: {
                            if(category == "thumb") {
                                sessiondispatcher.open_folder_qt(path);
                            }
                        }
                        onArrowClicked: {
                            if(cacheFlag == "thumb") {//1212
                                if(expand_flag == true) {
                                    cachepage.thumb_expanded = true;
                                    if((cachepage.apt_expanded == true) && (cachepage.soft_expanded == true)) {
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 1) * cachepage.item_height + cachepage.spaceValue*6;
//                                        scrollItem.height = (cachepage.aptNum + 1) * 40 + (cachepage.softNum + 1) * 40 + cachepage.spaceValue*2;
                                    }
                                    else if((cachepage.apt_expanded == true) && (cachepage.soft_expanded == false)){
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.thumbNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == false) && (cachepage.soft_expanded == true)){
                                        scrollItem.height = (cachepage.softNum + 1) * cachepage.item_height + (cachepage.thumbNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = (cachepage.thumbNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                                else {
                                    cachepage.thumb_expanded = false;
                                    if((cachepage.apt_expanded == true) && (cachepage.soft_expanded == true)) {
                                        scrollItem.height = (cachepage.aptNum + 1) * cachepage.item_height + (cachepage.softNum + 2) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == true) && (cachepage.soft_expanded == false)){
                                        scrollItem.height = (cachepage.aptNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else if((cachepage.apt_expanded == false) && (cachepage.soft_expanded == true)){
                                        scrollItem.height = (cachepage.softNum + 3) * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                    else {
                                        scrollItem.height = 3 * cachepage.item_height + cachepage.spaceValue*6;
                                    }
                                }
                            }
                        }
                    }
                    cacheBuffer: 1000
                    opacity: 1
//                    spacing: 10
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
            PropertyChanges { target: actionBtn; text:qsTr("Begin cleanup")}//开始清理
            PropertyChanges { target: cachepage; btnFlag: "cache_work" }
            PropertyChanges { target: backBtn; visible: true}
        },
        State {
            name: "AptWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: cachepage; btnFlag: "cache_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "AptWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: cachepage; btnFlag: "cache_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "AptWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: cachepage; btnFlag: "cache_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "AptWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: cachepage; btnFlag: "cache_scan" }
            PropertyChanges { target: backBtn; visible: false}
        }
    ]
}
