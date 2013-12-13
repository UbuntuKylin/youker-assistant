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
    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量
    property string btnFlag//存放主按钮标记：扫描或者清理
    property string title//扫描按钮的显示文字
    property bool resetStatus//重置按钮是显示还是隐藏

    signal sendBrowserType(string flag, string status);//flag判断是firefox还是chromium，status判断是扫描还是清理

    property string flag //判断是firefox还是chromium

    Row {
        id: chromium
        width: parent.width
        spacing: 15
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
                width: 500
                text: itemtitle.itemTitle
                wrapMode: Text.WordWrap
                font.pointSize: 11
                color: "black"
            }
            Text {
                width: 500
                text: itemtitle.detailstr
                wrapMode: Text.WordWrap
                font.family: "URW Bookman L"
                font.pointSize: 9
                color: "gray"
            }
        }
    }


    //--------------------------------------
    Row {
        anchors {
            right: chromiumarrow.left
            rightMargin: 50
            verticalCenter: parent.verticalCenter
        }
        spacing: 15
        Row {
            spacing: 20
            Item {
                id: resetBtn
                visible: itemtitle.resetStatus//false
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
                        itemtitle.sendBrowserType(itemtitle.flag, "reset");
                    }
                }
            }
//            Item {
//                id: rescanBtn
//                visible: itemtitle.resetStatus//false
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
//                        itemtitle.sendBrowserType(itemtitle.flag, "rescan");
////                        actionBtn.text = qsTr("Start scanning");//开始扫描
////                        root.btnFlag = "apt_scan";
////                        backBtn.visible = false;
////                        rescanBtn.visible = false;
////                        subModel.clear();//内容清空
////                        root.arrowShow = 0;//伸缩图标隐藏
////                        root.flag = false;
////                        root.getData();//获取数据
//                    }
//                }
//            }
        }
        Common.Button {
            id: scanBtn
            width: 95
            height: 30
            hoverimage: "green2.png"
            text: itemtitle.title//qsTr("Start scanning")//开始扫描
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(itemtitle.btnFlag == "cookies_scan") {
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scan");
                }
                else if(itemtitle.btnFlag == "cookies_scanc") {
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scanc");
                }
                else if(itemtitle.btnFlag == "cookies_work") {
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_work");
                }
                else if(itemtitle.btnFlag == "cookies_workc") {
                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_workc");
                }
            }
        }
    }
    //--------------------------------------





//    Row {
//        anchors {
//            right: chromiumarrow.left
//            rightMargin: 50
//            verticalCenter: parent.verticalCenter
//        }
//        spacing: 15
//        Common.Button {
//            id: scanBtn
//            width: 95
//            height: 30
//            hoverimage: "green2.png"
//            text: itemtitle.title//qsTr("Start scanning")//开始扫描
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if(itemtitle.btnFlag == "cookies_scan") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scan");
//                }
//                else if(itemtitle.btnFlag == "cookies_scanc") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scanc");
//                }
//                else if(itemtitle.btnFlag == "cookies_work") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_work");
//                }
//                else if(itemtitle.btnFlag == "cookies_workc") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_workc");
//                }
//            }
//        }
//        SetBtn {
//            id: resetBtn
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            visible: itemtitle.resetStatus//false
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                itemtitle.sendBrowserType(itemtitle.flag, "reset");
//            }
//        }
//    }
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
        rotation: itemtitle.expanded ? -180 : 0
        smooth: true
        MouseArea {
            anchors.fill: parent
            onClicked: {
                itemtitle.clicked();
                itemtitle.expanded = !itemtitle.expanded;//扫描出的子项是否下拉显示的控制变量
            }
        }
    }
}

















//Item {
//    id: itemtitle
//    signal clicked
//    signal resetclicked
//    width: parent.width
//    height: 40
//    property bool expanded: false
//    property string imageSource: ""
//    property string itemTitle: ""
//    property string detailstr: ""
//    property string arrowSource: "../img/icons/arrow.png"

//    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量
//    property string btnFlag//存放主按钮标记：扫描或者清理
//    property bool nullFlag//存放扫描到的内容是否为空的标记

//    signal sendBrowserType(string flag, string status);//flag判断是firefox还是chromium，status判断是扫描还是清理

//    property string flag //判断是firefox还是chromium

//    onNullFlagChanged: {
//        if (itemtitle.nullFlag === true) {
//            if(itemtitle.flag == "firefox") {//firefox扫描内容为空
//                itemtitle.state = "CookiesWorkEmpty";
//            }
//            else if (itemtitle.flag == "chromium") {//chromium扫描内容为空
//                itemtitle.state = "CookiesWorkEmptyC";
//            }
//        }
//        else if (itemtitle.nullFlag === false) {
//            if(itemtitle.flag == "firefox") {//firefox扫描内容不为空
//                itemtitle.state = "CookiesWork";
//            }
//            else if (itemtitle.flag == "chromium") {//chromium扫描内容不为空
//                itemtitle.state = "CookiesWorkC";
//            }
//        }
//    }

//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWorkError: {
//            if (msg == "firefox") {
//                if (btnFlag == "cookies_work") {
//                    itemtitle.state = "CookiesWorkError";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//            else if (msg == "chromium") {
//                if (btnFlag == "cookies_workc") {
//                    itemtitle.state = "CookiesWorkErrorC";
//                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
//                }
//            }
//        }
//        onFinishCleanWork: {
//            if (msg == "") {
//                resetBtn.visible = true;
//                toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
//            }
//            else if (msg == "firefox") {
//                if (btnFlag == "cookies_work") {
//                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    itemtitle.state = "CookiesWorkFinish";
//                }
//            }
//            else if (msg == "chromium") {
//                if (btnFlag == "cookies_workc") {
//                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
//                    itemtitle.state = "CookiesWorkFinishC";
//                }
//            }
//        }
//    }
//    Row {
//        id: chromium
//        width: parent.width
//        spacing: 15
//        Image {
//            id: chrominmImage
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
//                width: 500
//                text: itemtitle.itemTitle
//                wrapMode: Text.WordWrap
//                font.pointSize: 11
//                color: "black"
//            }
//            Text {
//                width: 500
//                text: itemtitle.detailstr
//                wrapMode: Text.WordWrap
//                font.family: "URW Bookman L"
//                font.pointSize: 9
//                color: "gray"
//            }
//        }
//    }

//    Row {
//        anchors {
//            right: chromiumarrow.left
//            rightMargin: 50
//            verticalCenter: parent.verticalCenter
//        }
//        spacing: 15
//        Common.Button {
//            id: scanBtn
//            width: 95
//            height: 30
//            hoverimage: "green2.png"
//            text: qsTr("Start scanning")//开始扫描
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if(itemtitle.btnFlag == "cookies_scan") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scan");
//                }
//                else if(itemtitle.btnFlag == "cookies_scanc") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_scanc");
//                }
//                else if(itemtitle.btnFlag == "cookies_work") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_work");
//                }
//                else if(itemtitle.btnFlag == "cookies_workc") {
//                    itemtitle.sendBrowserType(itemtitle.flag, "cookies_workc");
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
//                itemtitle.sendBrowserType(itemtitle.flag, "reset");
//                if(itemtitle.flag == "firefox") {
//                    itemtitle.state = "BrowserWorkAGAIN";
//                }
//                else if(itemtitle.flag == "chromium") {
//                    itemtitle.state = "BrowserWorkAGAINC";
//                }
//            }
//        }
//    }
//    Image {
//        id: chromiumarrow
//        fillMode: "PreserveAspectFit"
//        anchors {
//            left: parent.left
//            leftMargin: 750
//            verticalCenter: parent.verticalCenter
//        }
//        height: 28
//        width: 26
//        source: itemtitle.arrowSource
//        opacity: itemtitle.arrow_display//这里初始为0,可以初始时将箭头隐藏,以后根据扫描内容确定其值
//        rotation: itemtitle.expanded ? -180 : 0
//        smooth: true
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                itemtitle.clicked();
//                itemtitle.expanded = !itemtitle.expanded;//扫描出的子项是否下拉显示的控制变量
//            }
//        }
//    }
//    states: [
//        State {
//            name: "CookiesWork"
//            PropertyChanges { target: scanBtn; text:qsTr("All clean")}//全部清理
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_work" }
//            PropertyChanges { target: resetBtn; visible: true }
//        },
//        State {
//            name: "CookiesWorkC"
//            PropertyChanges { target: scanBtn; text:qsTr("All clean")}//全部清理
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_workc" }
//            PropertyChanges { target: resetBtn; visible: true }
//        },
//        State {
//            name: "CookiesWorkAGAIN"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//        },
//        State {
//            name: "CookiesWorkAGAINC"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//        },
//        State {
//            name: "CookiesWorkError"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//        },
//        State {
//            name: "CookiesWorkErrorC"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning") }//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//        },
//        State {
//            name: "CookiesWorkFinish"
//            PropertyChanges { target: scanBtn; text:"Start scanning"}//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: resetBtn; visible: false}
//        },
//        State {
//            name: "CookiesWorkFinishC"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: resetBtn; visible: false}
//        },
//        State {
//            name: "CookiesWorkEmpty"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scan" }
//            PropertyChanges { target: resetBtn; visible: false}
//        },
//        State {
//            name: "CookiesWorkEmptyC"
//            PropertyChanges { target: scanBtn; text:qsTr("Start scanning")}//开始扫描
//            PropertyChanges { target: itemtitle; btnFlag: "cookies_scanc" }
//            PropertyChanges { target: resetBtn; visible: false}
//        }
//    ]
//}
