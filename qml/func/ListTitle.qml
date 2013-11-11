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

Item {
    id: itemtitle
    signal clicked
    signal resetclicked
    width: parent.width
    height: 40
    property bool expanded: false
    property string imageSource: ""
    property string itemTitle: ""
    property string detailstr: ""
    property string arrowSource: "../img/icons/arrow.png"


    property int heightMark: sub_num
    property int sub_num
    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量
    property int check_num: sub_num   //记录子项个数，在确定总checkbox状态时需要的变量
    property string btnFlag//存放主按钮标记：扫描或者清理
    property bool nullFlag//存放扫描到的内容是否为空的标记
//    property bool flag: false//根据nullFlag来设置值，为true时不显示后面的状态

//    signal sendScanOrCleanFlag(string flag);
    signal sendBrowserType(string flag, string status);//flag判断是firefox还是chromium，status判断是扫描还是清理

    property string flag //判断是firefox还是chromium

    onNullFlagChanged: {
//        console.log("00000000");
//        console.log(itemtitle.nullFlag);
        if (itemtitle.nullFlag === true) {
            if(itemtitle.flag == "firefox") {//firefox扫描内容为空
                itemtitle.state = "CookiesWorkEmpty";
            }
            else if (itemtitle.flag == "chromium") {//chromium扫描内容为空
                itemtitle.state = "CookiesWorkEmptyC";
            }
        }
        else if (itemtitle.nullFlag === false) {
//            console.log("kkkkkkkkkkkk");
//            console.log(itemtitle.flag);
            if(itemtitle.flag == "firefox") {//firefox扫描内容不为空
//                console.log("111111111111111");
                itemtitle.state = "CookiesWork";
            }
            else if (itemtitle.flag == "chromium") {//chromium扫描内容不为空
//                console.log("22222222222");
                itemtitle.state = "CookiesWorkC";
            }
        }
    }

//    Connections {
//        target: sessiondispatcher
//        //子chechbox改变后，得到信号，改变主checkbox的状态
//        onStartChangeMaincheckboxStatus: {
//            check.checked = status;
//        }
//    }

//    Connections
//    {
//        target: sessiondispatcher
//        onGetNullFlag: {
//            console.log("&&&&&&&&&");
//            console.log(emptyFlag);
//            console.log(status);
//            if(emptyFlag == "firefox") {
//                if(status) {//firefox扫描内容为空
//                    itemtitle.state = "CookiesWorkEmpty";
//                }
//                else {//firefox扫描内容不为空
//                    console.log("666666666");
//                    itemtitle.state = "CookiesWork";
//                }
//            }
//            else if (emptyFlag == "chromium") {
//                if(status) {//chromium扫描内容为空
//                    itemtitle.state = "CookiesWorkEmptyC";
//                }
//                else {//chromium扫描内容不为空
//                    console.log("777777777777");
//                    itemtitle.state = "CookiesWorkC";
//                }
//            }
//        }
//    }
    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (btnFlag == "cookies_work") {
                if (msg == "cookies") {
//                    root.work_result = msg;
                    itemtitle.state = "CookiesWorkError";
                    toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
                }
            }
         }
        onFinishCleanWork: {
            if (btnFlag == "cookies_work") {
                if (msg == "") {
                    resetBtn.visible = true;
                    toolkits.alertMSG("清理中断了！", mainwindow.pos.x, mainwindow.pos.y);
                }
                else if (msg == "cookies") {
//                    root.work_result = msg;
                    itemtitle.state = "CookiesWorkFinish";
                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
                    //清理完毕后重新获取cookies
//                    root.cookies_signal("CookiesWork");
                }
            }
        }
    }
    Row {
        id: chromium
        width: parent.width
        spacing: 15
//        Common.CheckBox {
//            id: checkbox
//            checked: true
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                itemtitle.sendMainStatus(checkbox.checked, itemtitle.flag);
//            }
//        }
        Image {
            id: chrominmImage
            fillMode: "PreserveAspectFit"
            height: parent.height*0.9
            source: itemtitle.imageSource
            smooth: true
        }

        Column {
            id: chromiumColumn
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                text: itemtitle.itemTitle
                font.pointSize: 11
                color: "black"
            }
            Text {
                text: itemtitle.detailstr
                font.family: "URW Bookman L"
                font.pointSize: 9
                color: "gray"
            }
        }
    }

    Row {
        anchors {
            right: chromiumarrow.left
            rightMargin: 50
            verticalCenter: parent.verticalCenter
        }
        spacing: 15
        //=========================
//        Common.StatusImage {
//            id: statusImage
//            visible: false
//            iconName: "yellow.png"
//            anchors.verticalCenter: parent.verticalCenter
//            text: "未完成"
//        }
        Common.Button {
            id: scanBtn
            width: 95
            height: 30
            hoverimage: "green2.png"
            text: "开始扫描"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(itemtitle.btnFlag == "cookies_scan") {
//                    itemtitle.state = "CookiesWork";
//                    resetBtn.visible = true;
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scan");

                }
                else if(itemtitle.btnFlag == "cookies_scanc") {
//                    itemtitle.state = "CookiesWorkC";
//                    resetBtn.visible = true;
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scanc");

                }
                else if(itemtitle.btnFlag == "cookies_work") {
//                    itemtitle.expanded = false;
//                    resetBtn.visible = false;
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_work");
//                    itemtitle.state = "CookiesWorkFinish";
//                    itemtitle.arrow_display = 0;//清理完毕后隐藏箭头图标
//                    itemtitle.expanded = false;
                }
                else if(itemtitle.btnFlag == "cookies_workc") {
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_workc");
//                    itemtitle.state = "CookiesWorkFinishC";
                }
            }
        }
        SetBtn {
            id: resetBtn
            width: 12
            height: 15
            iconName: "revoke.png"
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                itemtitle.expanded = false;
                resetBtn.visible = false;
                itemtitle.sendBrowserType(itemtitle.flag, "reset");
                if(itemtitle.flag == "firefox") {
                    itemtitle.state = "BrowserWorkAGAIN";
                }
                else if(itemtitle.flag == "chromium") {
                    itemtitle.state = "BrowserWorkAGAINC";
                }
            }
        }
        //=========================
    }
    Image {
        id: chromiumarrow
        fillMode: "PreserveAspectFit"
        anchors {
            left: parent.left
            leftMargin: 750
            verticalCenter: parent.verticalCenter
        }
        height: 28
        width: 26
        source: itemtitle.arrowSource
        opacity: itemtitle.arrow_display//这里初始为0,可以初始时将箭头隐藏,以后根据扫描内容确定其值
        rotation: itemtitle.expanded ? 0 : -180
//        rotation: itemtitle.expanded ? -180 : 0
        smooth: true
        MouseArea {
            anchors.fill: parent
            onClicked: {
                itemtitle.clicked();
                itemtitle.expanded = !itemtitle.expanded;//扫描出的子项是否下拉显示的控制变量
            }
        }
    }
    states: [
        State {
            name: "CookiesWork"
            PropertyChanges { target: scanBtn; text:"全部清理"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_work" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
            PropertyChanges { target: resetBtn; visible: true }
        },
        State {
            name: "CookiesWorkC"
            PropertyChanges { target: scanBtn; text:"全部清理"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_workc" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
            PropertyChanges { target: resetBtn; visible: true }
        },
        State {
            name: "CookiesWorkAGAIN"
            PropertyChanges { target: scanBtn; text:"开始扫描" }
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false }
        },
        State {
            name: "CookiesWorkAGAINC"
            PropertyChanges { target: scanBtn; text:"开始扫描" }
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: statusImage; visible: false }
        },
        State {
            name: "CookiesWorkError"
            PropertyChanges { target: scanBtn; text:"开始扫描" }
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
        },
        State {
            name: "CookiesWorkErrorC"
            PropertyChanges { target: scanBtn; text:"开始扫描" }
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
        },
        State {
            name: "CookiesWorkFinish"
            PropertyChanges { target: scanBtn; text:"开始扫描"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "CookiesWorkFinishC"
            PropertyChanges { target: scanBtn; text:"开始扫描"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "CookiesWorkEmpty"
            PropertyChanges { target: scanBtn; text:"开始扫描"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false}
            PropertyChanges { target: resetBtn; visible: false}
        },
        State {
            name: "CookiesWorkEmptyC"
            PropertyChanges { target: scanBtn; text:"开始扫描"}
            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: statusImage; visible: false}
            PropertyChanges { target: resetBtn; visible: false}
        }
    ]
}












//Item {
//    id: itemtitle
//    signal clicked
//    width: parent.width
//    height: 40
//    property bool expanded: true
//    property string imageSource: ""
//    property string itemTitle: ""
//    property string detailstr: ""
//    property string arrowSource: "../img/icons/arrow.png"


//    property int heightMark: sub_num
//    property int sub_num
//    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量
//    property int check_num: sub_num   //记录子项个数，在确定总checkbox状态时需要的变量

//    property bool checkboxStatus: true//主checkbox的状态
//    signal subpressed(int hMark);

//    Connections {
//        target: sessiondispatcher
//        //得到信号，改变主checkbox的状态
//        onStartChangeMaincheckboxStatus: {
//            check.checked = status;
//        }
//    }

//    Row {
//        id: chromium
//        width: parent.width
//        spacing: 15
//        Common.MainCheckBox{
//            id: check
//            checked: "true"
//            anchors.verticalCenter: parent.verticalCenter
//            onCheckedChanged: {
//                itemtitle.checkboxStatus = check.checkedbool;
//            }
//        }
//        Image {
//            id: chromiumImage
//            fillMode: "PreserveAspectFit"
//            height: parent.height*0.9
//            source: itemtitle.imageSource
//            smooth: true
//        }

//        Column {
//            id: chromiumColumn
//            spacing: 5
//            anchors.verticalCenter: parent.verticalCenter
//            Text {
//                text: itemtitle.itemTitle
//                font.pointSize: 11
//                color: "black"
//            }
//            Text {
//                text: itemtitle.detailstr
//                font.family: "URW Bookman L"
//                font.pointSize: 9
//                color: "gray"
//            }
//        }

//        Image {
//            id: chromiumarrow
//            fillMode: "PreserveAspectFit"
//            height: 28
//            width: 26
//            source: itemtitle.arrowSource
//            opacity: itemtitle.arrow_display//这里初始为0,可以初始时将箭头隐藏,以后根据扫描内容确定其值
//            rotation: itemtitle.expanded ? 0 : -180
//            smooth: true
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    itemtitle.clicked();
//                    itemtitle.expanded = !itemtitle.expanded;//扫描出的子项是否下拉显示的控制变量



//                    if(itemtitle.heightMark == itemtitle.sub_num){//通过对heightMark的赋值来实现子项的下拉显示与收缩不显示
//                        check.checkedbool=false;//子项收缩时,将总checkbox回到勾选状态
//                        check.checked="true";
//                        itemtitle.heightMark=0;
//                    }
//                    else if(itemtitle.heightMark==0) {
//                        if(itemtitle.sub_num>0){//子项下拉显示时，根据总checkbox状态进行赋值控制
//                            if(check.checked=="true") {
//                                check.checkedbool = true;
//                                itemtitle.check_num = itemtitle.sub_num;
//                                check.checked = "true"
//                            }
//                            else if(check.checked=="false") {
//                                itemtitle.check_num = itemtitle.sub_num-1;
//                                check.checkedbool = false;
//                                check.checked = "false"
//                            }
//                        }
//                        itemtitle.heightMark=itemtitle.sub_num;
//                    }
//                    itemtitle.subpressed(itemtitle.heightMark); //将heightMark的值传给清理界面实现对是否下拉显示子项的控制
//                }
//            }
//        }
//    }
//}
