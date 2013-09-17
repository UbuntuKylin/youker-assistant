/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SystemType 0.1
import "./common" as Common
import "./bars" as Bars
import "../func" as Func
Item {
    id: root
    width: parent.width
    height: 475
    property string source_status_text: ""
    Connections
    {
        target: sudodispatcher
        onFinishGetSourceStatus: {
            root.source_status_text = "进度: " + cur_status;
        }
        onFinishSoftwareFetch: {
            if(type == "down_stop" && root.source_status_text != "") {
                root.source_status_text = "";
                root.state = "SofeWareState";
//                sudodispatcher.check_pkgs_status_qt(sudodispatcher.get_args());
                toolkits.alertMSG("软件源更新完成！", mainwindow.pos.x, mainwindow.pos.y);
            }
        }
        onCallMasklayer: {
            root.state = "MaskLayerState";
        }
    }

    Rectangle {
        id: masklayer
        width: parent.width
        height: parent.height
        x: (parent.width * 1.5);
//        color: "gray"
        //背景
        Image {
            source: "../img/skin/bg-middle.png"
            anchors.fill: parent
        }

        Text {
            id: title1
            anchors.centerIn: parent
            text: "如果太长时间没有更新完毕，可能是网络问题，可以点击左上角的返回按钮退出该界面。"
            font.pixelSize: 12
            color: "#7a7a7a"
            font.family: "Arial"
            style: Text.Sunken
            styleColor: "#AAAAAA"
        }
        Text {
            id: title2
            anchors {
                bottom: title1.top
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            text: "正在更新软件源，请耐心等待，软件源更新完成后会自动弹出提示信息"
            font.pixelSize: 14
            color: "#383838"
            font.family: "Arial"
            style: Text.Sunken
            styleColor: "#AAAAAA"
        }
        Text {
            anchors {
                bottom: title2.top
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: 14
            color: "#383838"
            text: root.source_status_text
        }
        AnimatedImage {
            anchors {
                top: title1.bottom
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            width: 16
            height: 16
            source: "../img/icons/move.gif"
//            anchors.centerIn: parent
        }

        SetBtn {
            id: resetBtn
            width: 12
            height: 15
            iconName: "revoke.png"
            anchors {
                left: parent.left
                leftMargin: 10
                top: parent.top
                topMargin: 10
//                verticalCenter: parent.verticalCenter
            }
            onClicked: {
                root.state = "SofeWareState";
            }
        }
    }
    Rectangle {
        id: software
        property bool in_no: false
        //需要时常变动的变量
        property string software_name: content.delegate_name
        property string software_appname: content.delegate_appname
//        property string software_information: content.delegate_information
        property string software_image: content.delegate_image
        property string software_introduction: content.delegate_introduction
        property string introduction_image1: content.introduction_image1
        property string introduction_image2: content.introduction_image2
        property string installed_status: content.soft_status
        property string tm_status: "n"
        width: parent.width
        height: parent.height
        function reset_text(showtext) {
            if(showtext == "i") {
                statusImage.source = "../img/icons/installed.png"
                return "立即卸载";
            }
            else if(showtext == "n") {
                statusImage.source = "../img/icons/noinstalled.png"
                return "立即安装";
            }
            else if(showtext == "u") {
                statusImage.source = "../img/icons/installed.png"
                return "立即升级";
            }
            else {
                statusImage.source = "../img/icons/noinstalled.png"
                return "未发现";
            }
        }
        function show_text(showtext) {
            if(showtext == "i") {
                statusImage.source = "../img/icons/installed.png"
                return "立即卸载";
            }
            else if(showtext == "n") {
                statusImage.source = "../img/icons/noinstalled.png"
                return "立即安装";
            }
            else if(showtext == "u") {
                statusImage.source = "../img/icons/installed.png"
                return "立即升级";
            }
            else {
                statusImage.source = "../img/icons/noinstalled.png"
                return "未发现";
            }
        }
        Connections
        {
            target: sudodispatcher
            onFinishSoftwareStatus: {
                software.installed_status = content.soft_status;
//                console.log("3333333333333");
//                console.log(software.installed_status);
//                console.log(content.soft_status);
                actionBtn.text = software.reset_text(software.installed_status);
            }

            onFinishSoftwareApt: {
                if(type == "apt_stop") {
//                    console.log("000000000000");
                    sudodispatcher.check_pkgs_status_qt(sudodispatcher.get_args());
                    software.tm_status = sudodispatcher.check_pkg_status_qt(software.software_name);

                    if(software.in_no) {
                        //delete software source
                        console.log("start to delete.....");
                        software.in_no = false;
                    }

                    if(software.tm_status == software.installed_status) {
//                        console.log("111111111111111111");
//                        console.log(software.software_name);
//                        console.log(software.tm_status);
//                        console.log(software.installed_status);

                        //start to add software source
                        sudodispatcher.show_update_dialog(mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {
                        software.installed_status = software.tm_status;
                        if(software.installed_status == "i") {
                            actionBtn.text = "立即卸载";
                            statusImage.source = "../img/icons/installed.png"
                        }
                        else if(software.installed_status == "n") {
                            actionBtn.text = "立即安装";
                            statusImage.source = "../img/icons/noinstalled.png"
                        }
                        else if(software.installed_status == "u") {
                            actionBtn.text = "立即升级";
                            statusImage.source = "../img/icons/installed.png"
                        }
                        toolkits.alertMSG("软件操作完成！", mainwindow.pos.x, mainwindow.pos.y);
                    }
                }
            }
        }
    //    function split_string(statusdata) {
    //        var splitlist = statusdata.split(":");
    //        software.appname = splitlist[0];
    //        software.installed_status = splitlist[1];
    //    }

        //背景
        Image {
            source: "../img/skin/bg-bottom-tab.png"
            anchors.fill: parent
        }
        Rectangle{
            width: parent.width-2;height: 36
            gradient: Gradient{
                GradientStop{position: 0.0; color: "#e2e2e2"}
                GradientStop{position: 1.0; color: "#dedede"}
            }
            anchors{
                top:parent.top
                left: parent.left
                leftMargin: 1
            }
            Common.Button{
                width: 80;height: 28
                anchors{
                    left: parent.left
                    leftMargin: 8
                    verticalCenter: parent.verticalCenter
                }
                hoverimage: "blue1.png"
                text:"返回"
                fontcolor: "grey"
                fontsize: 14
                onClicked: {
                    pageStack.push(softwarerecommend);
                }
            }
            Text {
                anchors.centerIn: parent
                text:"详细信息"
                color:"grey"
                font.bold: true
                font.pixelSize: 14
            }
        }
        Rectangle{
            width: parent.width-50;height: 110
            anchors{
                top:parent.top
                topMargin: 47
                left: parent.left
                leftMargin: 25
            }
            border.color: "lightgrey"
//            color: "#e6ebfe"
            Image {
                source: software.software_image
                anchors{
                    left: parent.left
                    leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }
            }
            Column{
                anchors{
                    left: parent.left
                    leftMargin: 105
                    verticalCenter: parent.verticalCenter
                }
                spacing: 10
                Text{
                    id:softwarename
                    text:software.software_appname
    //                font.pixelSize: 18
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
//                Text {
//                    id: softwareinformation
//                    text: software.software_information
//                    font.pixelSize: 12
//                    color: "#7a7a7a"
//                }
                Text {
                    text: content.delegate_useinfo
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Common.Button{
                id: actionBtn
                width:145;height: 43
                anchors{
                    right:parent.right
                    rightMargin: 80
                    verticalCenter: parent.verticalCenter
                }
                text: software.show_text(software.installed_status)
                fontsize: 20
                onClicked: {
                    software.installed_status = sudodispatcher.check_pkg_status_qt(software.software_name);
                    if(software.installed_status == "n") {
                        if(content.delegate_name == "wine-qq2012-longeneteam") {
//                            console.log("test qq");
                        }
                        else {
                            var softwarelist = sudodispatcher.getUKSoftwareList();
                            console.log("111111111");
                            console.log(softwarelist);
                            for (var i=0; i< softwarelist.length; i++) {
                                if(softwarelist[i] == software.software_name) {
                                    console.log("is mine......");
                                    software.in_no = true;
                                    break;
                                }
                            }
                            sudodispatcher.show_progress_dialog(mainwindow.pos.x, mainwindow.pos.y);
                            sudodispatcher.install_pkg_qt(software.software_name);
                        }
                    }
                    else if(software.installed_status == "i") {
                        //add software source
                        software.in_no = false;
                        sudodispatcher.show_progress_dialog(mainwindow.pos.x, mainwindow.pos.y);
                        sudodispatcher.uninstall_pkg_qt(software.software_name);
                    }
                    else if(software.installed_status == "u") {
                        if(content.delegate_name == "wine-qq2012-longeneteam") {
//                            console.log("test qq222222222");
                        }
                        else {
                            var softwareList = sudodispatcher.getUKSoftwareList();
                            console.log("111111111");
                            console.log(softwareList);
                            for (var j=0; i< softwareList.length; j++) {
                                if(softwareList[j] == software.software_name) {
                                    console.log("is mine 2......");
                                    software.in_no = true;
                                    break;
                                }
                            }
//                            software.in_no = true;
                            sudodispatcher.show_progress_dialog(mainwindow.pos.x, mainwindow.pos.y);
                            sudodispatcher.update_pkg_qt(software.software_name);
                        }
                    }
                    else{
                        if(content.delegate_name == "wine-qq2012-longeneteam") {
                            Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php");
                        }
                        else if(content.delegate_name == "wine-thunder") {
                            Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php");
                        }
                        else {
//                            console.log("222222222222");
                            sudodispatcher.show_update_dialog(mainwindow.pos.x, mainwindow.pos.y);
                        }
                    }
                }
            }
            Image {
                id: statusImage
                source: "../img/icons/noinstalled.png"
                anchors{
                    right:parent.right
                    top: parent.top
//                    verticalCenter: parent.verticalCenter
                }
            }

        }
        Rectangle {
            id: views
            width: parent.width-50
            height: 276
            anchors{
                bottom:parent.bottom
                bottomMargin: 17
                left: parent.left
                leftMargin: 25
            }
            clip:true
            border.color: "#9aa2af"
            color: "#e6ebfe"
            Rectangle{
                id:rec
                width: parent.width-1;height: 31
                anchors{
                    top:parent.top
                    topMargin: 1
                    left: parent.left
                    leftMargin: 1
                }
                gradient: Gradient{
                    GradientStop{position: 0.0; color: "#e2e2e2"}
                    GradientStop{position: 1.0; color: "#dedede"}
                }
                Text {
                    anchors.centerIn: parent
                    text:"软件介绍"
                    color:"grey"
                    font.bold: true
                    font.pixelSize: 14
                }
            }
            Rectangle{id: splitbar1; anchors{top:rec.bottom;left: parent.left;leftMargin: 1 }width:parent.width-1 ; height:1; color:"#b8bdc3"}
            Rectangle{id: splitbar2; anchors{top:splitbar1.bottom;left: parent.left;leftMargin: 1  }width:parent.width-1 ; height:1; color:"#ebf0f6"}
            Text {
                id: softwareintroduction
                width: parent.width-30
                anchors{
                    left:parent.left
                    leftMargin: 15
                    top:parent.top
                    topMargin: 46
                }
                font.pixelSize: 13
                text: software.software_introduction
    //            text:softwaredelegate.delegate_introduction
                wrapMode: Text.WrapAnywhere
            }
            Row{
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    bottom: parent.bottom
                    bottomMargin: 20
                }
                spacing: 80
                Image {
                    id: introductionimage1
                    source: introduction_image1
    //                source: softwaredelegate.introduction_image1
                }
                Image {
                    id: introductionimage2
                    source: introduction_image2
    //                source: softwaredelegate.introduction_image2
                }
            }
        }
    }


    states: [
        State {
            name: "SofeWareState"
            PropertyChanges { target: software; x: 0 }
            PropertyChanges { target: masklayer; x: (parent.width * 1.5) }
        },
        State {
            name: "MaskLayerState"
            PropertyChanges { target: masklayer; x: 0 }
            PropertyChanges { target: software; x: (parent.width * 1.5) }
        }
    ]
//    transitions: Transition {
//        NumberAnimation { properties: "x"; duration: 1000; easing.type: Easing.InOutQuad }
//    }
}
