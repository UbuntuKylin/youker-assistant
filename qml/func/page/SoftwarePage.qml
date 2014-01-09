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

//http://www.longene.org/download/linux-2.6.34.tar.bz2

Item {
    id: root
    width: parent.width
    height: 475
    property string source_status_text: ""
    Connections
    {
        target: systemdispatcher
        onNotifySourceStatusToQML: {
            root.source_status_text = qsTr("Progress: ") + total_items + qsTr(" itmes need to be updated,  the number of completed updates is: ") + download_items;//进度：//个项目需要更新，已完成个数：
        }
        //下载完成
        onFinishSoftwareFetch: {
            if(type == "down_stop" && root.source_status_text != "") {
                //软件源更新完成后，重新获取所有软件的状态
                systemdispatcher.check_pkgs_status_qt(systemdispatcher.getAllSoftwareExecNameList());
                //软件源更新完成后，重新该软件的单个状态
                actionBtn.text = software.reset_text(systemdispatcher.check_pkg_status_qt(software.software_name));
                root.source_status_text = "";
                root.state = "SofeWareState";
            }
//            else if(type == "down_fail") {
//                console.log("down_fail.....");
//            }
        }
        onCallMasklayer: {
            root.state = "MaskLayerState";
        }
    }

    Rectangle {
        id: masklayer
        width: parent.width
        height: parent.height
        x: (parent.width * 1.5)
        Connections
        {
            target: systemdispatcher
            //得到数据，显示在进度条上
            onSendDynamicSoftwareProgressQML: {
                if(type == "down_start") {
                    progressTitle.text = qsTr("Download");//开始下载
                    progress.value = 0;
                }
                else if(type == "down_pulse"){
                    progressTitle.text = qsTr("Downloading...");//正在下载安装包...
                    progress.value = ratio_sus;
                }
                else if(type == "down_stop") {
                    progressTitle.text = qsTr("Downloaded");//下载完成
                    progress.value = 100;
                }
                else if(type == "apt_start"){
                    progressTitle.text = qsTr("Start");//开始
                    progress.value = 0;
                }
                else if(type == "apt_pulse"){
                    progressTitle.text = qsTr("In progress: ") + info;//正在进行：
                    progress.value = ratio_sus;
                }
                else if(type == "apt_stop") {
//                    progressTitle.text = "完成";
                    progress.value = 0;
                }
            }
        }

        //背景
        Image {
            source: "../../img/skin/bg-middle.png"
            anchors.fill: parent
        }

        Text {
            id: title1
            anchors.centerIn: parent
            text: qsTr("If it takes too long to update,  there may be network problems,  you can click the ‘back’ button in the upper left hand corner to exit the interface.")//如果太长时间没有更新完毕，这可能是网络问题，您可以点击左上角的“返回”按钮退出该界面。
            wrapMode: Text.WordWrap
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
            text: qsTr("Updating software source,  please be patient,  there will pop-up prompt information automatically after the update completed.")//正在更新软件源，请耐心等待，软件源更新完成后会自动弹出提示信息。
            wrapMode: Text.WordWrap
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
            source: "../../img/icons/move.gif"
        }

        Common.SetBtn {
            id: resetBtn
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
                root.state = "SofeWareState";
            }
        }
    }


    Rectangle {
        id: masklayer2
        width: parent.width
        height: parent.height
        x: (parent.width * 1.5)
        //背景
        Image {
            source: "../../img/skin/bg-middle.png"
            anchors.fill: parent
        }

        Column {
            anchors.centerIn: parent
            spacing: 5
            AnimatedImage {
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
                root.state = "SofeWareState";
            }
        }
    }

    Rectangle {
        id: software
//        property bool checkFlag: false
        property string useinfo: qsTr("If the software is installed successfully, you can search the Chinese or English keywords in Dash and start it .")//如果软件安装成功，则可以通过软件的中文/英文名关键字在Dash中搜索并启动软件。
        property string software_name: ""
        property string installed_status: "n"
        property string tm_status: "n"
        property string path: "../../img/en/"
//        x: (parent.width * 1.5)
        width: parent.width
        height: parent.height

        Component.onCompleted: {
            if(sessiondispatcher.get_locale_version() == "zh_CN") {
                software.path = "../../img/zh_CN/";
            }
            else {
                software.path = "../../img/en/";
            }
        }

        function reset_text(showtext) {
            if(showtext == "i") {
                statusImage.source = software.path + "installed.png"
                return qsTr("Uninstall");//立即卸载
            }
            else if(showtext == "n") {
                statusImage.source = software.path + "noinstalled.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Access web");//进入网页
                }
                else {
                    return qsTr("Install");//立即安装
                }
            }
            else if(showtext == "u") {
                statusImage.source = software.path + "installed.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Download");//下载地址
                }
                else {
                    return qsTr("Upgrade");//立即升级
                }
            }
            else {
                statusImage.source = software.path + "noinstalled.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Download");//下载地址
                }
                else {
                    return qsTr("N/A");//未发现
                }
            }
        }
        function show_text(showtext) {
            if(showtext == "i") {
                statusImage.source = software.path + "installed.png"
                return qsTr("Uninstall");//立即卸载
            }
            else if(showtext == "n") {
                statusImage.source = software.path + "noinstalled.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Download");//下载地址
                }
                else {
                    return qsTr("Install");//立即安装
                }
            }
            else if(showtext == "u") {
                statusImage.source = software.path + "installed.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Download");//下载地址
                }
                else {
                    return qsTr("Upgrade");//立即升级
                }
            }
            else {
                statusImage.source = software.path + "noinstalled.png"
                if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                    return qsTr("Download");//下载地址
                }
                else {
                    return qsTr("N/A");//未发现
                }
            }
        }
        Connections
        {
            target: systemdispatcher
            //收到app的信号，开始显示对应app的页面信息
            onSendAppInfo: {
                systemdispatcher.getAppInfo(flag);
                //得到app在源里面的名字
                software.software_name = systemdispatcher.getSingleInfo("name");
                //得到该软件的初始状态
                software.installed_status = systemdispatcher.getSoftwareStatus(software.software_name);
                //根据得到的初始状态来设置按钮的文字显示
                actionBtn.text = software.reset_text(software.installed_status);
                //页面赋值
                softwarename.text = systemdispatcher.getSingleInfo("title");
                softwareintroduction.text = systemdispatcher.getSingleInfo("description");
                imageId.source = systemdispatcher.getSingleInfo("logo");
                introductionimage1.source = systemdispatcher.getSingleInfo("image1");
                introductionimage2.source = systemdispatcher.getSingleInfo("image2");
            }

            //操作完成
            onFinishSoftwareApt: {
                if(type == "apt_stop") {
                    //获取软件操作后的新状态
                    software.tm_status = systemdispatcher.check_pkg_status_qt(software.software_name);
                    //如果软件操作后的新状态和进入该页面时的初始状态相同，说明此时操作是没有成功的，提醒用户更新源
                    if(software.tm_status == software.installed_status) {
                        systemdispatcher.showUpdateSourceDialog(mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {//如果软件操作后的新状态和进入该页面时的初始状态不同，说明操作是成功的，把当前状态赋值给初始状态的变量
                        software.installed_status = software.tm_status;
                        if(software.installed_status == "i") {
                            actionBtn.text = qsTr("Uninstall");//立即卸载
                            statusImage.source = software.path + "installed.png"
                        }
                        else if(software.installed_status == "n") {
                            if(software.software_name == "wine-qq2012-longeneteam" || software.software_name == "wine-thunder") {
                                actionBtn.text = qsTr("Download");//下载地址
                            }
                            else {
                                actionBtn.text = qsTr("Install");//立即安装
                            }
                            statusImage.source = software.path + "noinstalled.png"
                        }
                        else if(software.installed_status == "u") {
                            actionBtn.text = qsTr("Upgrade");//立即升级
                            statusImage.source = software.path + "installed.png"
                        }
                        root.state = "SofeWareState";
                        toolkits.alertMSG(qsTr("Operation completed!"), mainwindow.pos.x, mainwindow.pos.y);//软件操作完成！
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
            source: "../../img/skin/bg-bottom-tab.png"
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
                text: qsTr("Back")//返回
                fontcolor: "grey"
                fontsize: 14
                onClicked: {
                    //返回软件主页面时重新获取所有软件的状态
                    systemdispatcher.check_pkgs_status_qt(systemdispatcher.getAllSoftwareExecNameList());
                    pageStack.push(softwarerecommend);
                }
            }
            Text {
                anchors.centerIn: parent
                text:qsTr("Detailed Info")//详细信息
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
            Image {
                id: imageId
                source: ""
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
                    text: ""
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Text {
                    width: 455
                    text: software.useinfo
                    wrapMode: Text.WordWrap
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
                    software.installed_status = systemdispatcher.check_pkg_status_qt(software.software_name);

                    if(software.installed_status == "n") {
                        if(software.software_name == "wine-qq2012-longeneteam") {
                            Qt.openUrlExternally("http://www.longene.org/forum/viewtopic.php?t=4700");
                        }
                        else if(software.software_name == "wine-thunder") {
                            Qt.openUrlExternally("http://code.google.com/p/wine-packages/downloads/list");
                        }
                        else {
                            root.state = "MaskLayerStateApt";
                            systemdispatcher.install_pkg_qt(software.software_name);
                        }
                    }
                    else if(software.installed_status == "i") {
                        root.state = "MaskLayerStateApt";
                        systemdispatcher.uninstall_pkg_qt(software.software_name);
                    }
                    else if(software.installed_status == "u") {
                        if(software.software_name == "wine-qq2012-longeneteam") {
                            Qt.openUrlExternally("http://www.longene.org/forum/viewtopic.php?t=4700");
                        }
                        else if(software.software_name == "wine-thunder") {
                            Qt.openUrlExternally("http://code.google.com/p/wine-packages/downloads/list");
                        }
                        else {
                            root.state = "MaskLayerStateApt";
                            systemdispatcher.update_pkg_qt(software.software_name);
                        }
                    }
                    else{
                        if(software.software_name == "wine-qq2012-longeneteam") {
                            Qt.openUrlExternally("http://www.longene.org/forum/viewtopic.php?t=4700");
                        }
                        else if(software.software_name == "wine-thunder") {
                            Qt.openUrlExternally("http://code.google.com/p/wine-packages/downloads/list");
                        }
                        else {
                            systemdispatcher.showUpdateSourceDialog(mainwindow.pos.x, mainwindow.pos.y);
                        }
                    }
                }
            }
            Image {
                id: statusImage
                source: ""//software.path + "noinstalled.png"
                anchors{
                    right:parent.right
                    top: parent.top
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
                    text:qsTr("Software introduction")//软件介绍
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
                text: ""
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
                    source: ""
                }
                Image {
                    id: introductionimage2
                    source: ""
                }
            }
        }
    }


    states: [
        State {
            name: "SofeWareState"
            PropertyChanges { target: software; x: 0 }
            PropertyChanges { target: masklayer; x: (parent.width * 1.5) }
            PropertyChanges { target: masklayer2; x: (parent.width * 1.5) }
        },
        State {
            name: "MaskLayerState"
            PropertyChanges { target: masklayer; x: 0 }
            PropertyChanges { target: software; x: (parent.width * 1.5) }
            PropertyChanges { target: masklayer2; x: (parent.width * 1.5) }
        },
        State {
            name: "MaskLayerStateApt"
            PropertyChanges { target: masklayer2; x: 0 }
            PropertyChanges { target: progressTitle; text: qsTr("Software operation schedule") }//软件操作进度
            PropertyChanges { target: progress; value: 0 }
            PropertyChanges { target: masklayer; x: (parent.width * 1.5) }
            PropertyChanges { target: software; x: (parent.width * 1.5) }
        }
    ]
//    transitions: Transition {
//        NumberAnimation { properties: "x"; duration: 1000; easing.type: Easing.InOutQuad }
//    }
}
