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

//右边栏
Rectangle {
    id: rightbar

    //更新登录状态
    Connections
    {
        target: sessiondispatcher
        onShowLoginAnimatedImage: {//正在登录过程中显示动态图片
            rightbar.state = "Logining";
        }
        onLoginFailedStatus: {//登录失败
            if(status == 99) {
                toolkits.alertMSG(qsTr("Network Error!"));//网络错误！
            }
            else if(status == -1) {
                toolkits.alertMSG(qsTr("No User!"));//没有该用户！
            }
            else if(status == -2) {
                toolkits.alertMSG(qsTr("Password Wrong!"));//密码错误！
            }
            else {
                toolkits.alertMSG(qsTr("Login Failed!"));//登录失败！
            }
            rightbar.state = "OffLine";
        }
        onUpdateLoginStatus: {//登录成功
            logo.source = "../../img/icons/logo.png"
            userText.text = username;
            levelText.text = "Lv" + level;
            scoreText.text = score;
            rightbar.state = "OnLine";
        }
        onRefreshUserInfo: {//刷新成功
            levelText.text = "Lv" + level;
            scoreText.text = score;
        }
    }

    //更新列表
    function updateList() {
        clearModel.clear();//清空
        clearModel.append({"icon": "../../img/icons/checkscreen.png", "name": qsTr("DeadpixelTest"), "flag": "CheckScreen"});//坏点检测
        clearModel.append({"icon": "../../img/icons/iconbeauty.png", "name": qsTr("DesktopIcon"), "flag": "Desktopicon"});//桌面图标
        clearModel.append({"icon": "../../img/icons/bootanimation.png", "name": qsTr("BootAnimation"), "flag": "BootAnimation"});//开机动画
        clearModel.append({"icon": "../../img/icons/camera.png", "name": qsTr("Camera"), "flag": "CameraCapture"});//摄像头
        clearModel.append({"icon": "../../img/icons/mouse.png", "name": qsTr("MousePointer"), "flag": "MousePointer"});//鼠标指针
        clearModel.append({"icon": "../../img/icons/touchpad.png", "name": qsTr("Touchpad"), "flag": "TouchpadSet"});//触摸板
    }

    ListModel {
        id: clearModel
        Component.onCompleted: {
            rightbar.updateList();
        }
    }
    //背景
    //    Image {
    //        source: "../../img/skin/bg-right.png"
    //        anchors.fill: parent
    //    }

    Rectangle {
        id: offline
        width: parent.width
        property string path: "../../img/en/"
        Component.onCompleted: {
            if(sessiondispatcher.get_locale_version() == "zh_CN") {
                offline.path = "../../img/zh_CN/";
            }
            else {
                offline.path = "../../img/en/";
            }
            login.showImage = offline.path + "login.png";
        }
        Common.KButton {
            id: login
            kflag: "login"
            showImage: ""
            anchors {
                top: parent.top; topMargin: 25
                horizontalCenter: parent.horizontalCenter
            }
            width: 216
            height: 67
            onClicked: {
                sessiondispatcher.popup_login_dialog();
            }
        }
    }

    Rectangle {
        id: logining
        width: parent.width
        x: (parent.width * 1.5)
        Column {
            spacing: 5
            anchors {
                top: parent.top; topMargin: 40
                horizontalCenter: parent.horizontalCenter
            }
            AnimatedImage {
                width: 16
                height: 16
                anchors.horizontalCenter: parent.horizontalCenter
                source: "../../img/icons/move.gif"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 14
                color: "#383838"
                text: qsTr("Logging...") //正在登录...
            }
        }
    }

    //------------------login
    Rectangle {
        id: online
        width: parent.width
        x: (parent.width * 1.5)
        Column {
            id: logcolumn
            spacing: 5
            anchors{
                left: parent.left
                leftMargin: 15
                top:parent.top
                topMargin: 10
            }
            Image {
                id: logo
                width: 56; height: 56
                source: ""
            }
            Common.Button {
                id: logout
                picNormal: "../../img/icons/button12-gray.png"
                picHover: "../../img/icons/button12-gray-hover.png"
                picPressed: "../../img/icons/button12-gray-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 56; height: 24
                text: qsTr("Logout")//注销
                onClicked: {
                    sessiondispatcher.logout_ubuntukylin_account();
                    userText.text = "";
                    levelText.text = "";
                    scoreText.text = "";
                    logo.source = "";
                    rightbar.state = "OffLine";
                }
            }
        }
        Column {
            spacing: 10
            anchors{
                left: logcolumn.right
                leftMargin: 10
                top:parent.top
                topMargin: 10
            }
            Text {
                id: userText
                text: ""
                font.bold: true
                font.pixelSize: 20
                color: "#383838"
                width: 160
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Level:")//当前等级：
                    width: 60
                }
                Text {
                    id: levelText
                    text: ""
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Score:")//当前积分：
                    width: 60
                }
                Text {
                    id: scoreText
                    text: ""
                }
            }
        }
        Common.Separator {
            anchors {
                left: parent.left
                leftMargin: 2
                top: parent.top
                topMargin: 100
            }
            width: parent.width - 4
        }
    }

    WeatherZone {
        id: weatherZone
        width: 208;height: 147
        anchors {
            top: parent.top
            topMargin: 110
            horizontalCenter: parent.horizontalCenter
        }
    }

    Common.Separator {
        id: splitbar
        x: 2; y: 270;
        width: parent.width - 4
    }

    Column {
        width: parent.width
        height: 200
        anchors {
            top: splitbar.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }
        Item {
            id: views
            width: parent.width


//            ListView {
//                focus: true
//                id: distrowatch
//                anchors.fill: parent
//                model: listModel
//                delegate: Others.InfoDelegate {}

            GridView {
                id: gridView
                anchors.fill: parent
                model: clearModel
                delegate: ToolsDelegate {}
                cellWidth: (parent.width-20)/3; cellHeight: cellWidth
                cacheBuffer: 1000
                focus: true
            }
        }
    }

    Row {
        id: versionrow
        spacing: 25
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            left: parent.left
            leftMargin: 20
        }

        Common.StyleButton {
            id: helplabel
            wordname: qsTr("Forum Help")//论坛求助
            width: 50
            height: 25
            onClicked: {
                Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php");
            }
        }
//        Text {
//            id: helplabel
//            width: 50
//            height: 25
//            textFormat: Text.RichText
//            text:  qsTr("<a href=\"http://www.ubuntukylin.com/ukylin/forum.php\">Forum Help</a>")
//            onLinkActivated: { Qt.openUrlExternally(link); }
//        }
        Common.StyleButton {
            id: versionlabel
            wordname: qsTr("Features")//新版本特性
            width: 60
            height: 25
            onClicked: {
                sessiondispatcher.showFeatureDialog();
            }
        }
        Common.StyleButton {
            id: buglabel
            wordname: qsTr("Feedback")//问题反馈
            width: 40
            height: 25
            onClicked: {
                Qt.openUrlExternally("https://bugs.launchpad.net/youker-assistant");
            }
        }
    }

    states: [
        State {
            name: "OnLine"
            PropertyChanges { target: online; x: 0 }
            PropertyChanges { target: offline; x: (parent.width * 1.5) }
            PropertyChanges { target: logining; x: (parent.width * 1.5) }
        },
        State {
            name: "Logining"
            PropertyChanges { target: logining; x: 0 }
            PropertyChanges { target: online; x: (parent.width * 1.5) }
            PropertyChanges { target: offline; x: (parent.width * 1.5) }
        },
        State {
            name: "OffLine"
            PropertyChanges { target: offline; x: 0 }
            PropertyChanges { target: online; x: (parent.width * 1.5) }
            PropertyChanges { target: logining; x: (parent.width * 1.5) }
        }
    ]
}
