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

//右边栏
Rectangle {
    id: rightbar

    //推荐软件的三张图片
    property string image1: "../../img/skin/qq0.png"
    property string image2: "../../img/skin/qt0.png"
    property string image3: "../../img/skin/wps0.png"
    property string mage_source: image1

    //更新列表
    function updateList() {
        clearModel.clear();//清空
        clearModel.append({"icon": "../../img/icons/checkscreen.png", "name": qsTr("DeadpixelTest"), "flag": "CheckScreen"});//坏点检测
        clearModel.append({"icon": "../../img/icons/iconbeauty.png", "name": qsTr("DesktopIcon"), "flag": "Desktopicon"});//桌面图标
        clearModel.append({"icon": "../../img/icons/bootanimation.png", "name": qsTr("BootAnimation"), "flag": "BootAnimation"});//开机动画
        clearModel.append({"icon": "../../img/icons/systemsound.png", "name": qsTr("SysSounds"), "flag": "SoundEffects"});//系统声音
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
    Image {
        source: "../../img/skin/bg-right.png"
        anchors.fill: parent
    }

    Common.SetBtn {
        id: setBtn
        iconName: "set.png"
        setbtn_flag: "set"
        anchors{
            left: parent.left
            leftMargin: 26
            top:parent.top
            topMargin: 30
        }
    }
    Image {
        id: adminImage
        source: "../../img/icons/admin.png"
        anchors{
            left: parent.left
            leftMargin: 26 + 39
            top:parent.top
            topMargin: 15
        }
    }
    Common.SetBtn {
        iconName: "message.png"
        setbtn_flag: "message"
        anchors{
            left: adminImage.right
            top:parent.top
            topMargin: 30
        }
    }

    WeatherZone {
        id: weatherZone
        width: 208;height: 147
        anchors {
            top: parent.top
            topMargin: 105
            horizontalCenter: parent.horizontalCenter
        }
    }

    //上下分割条
    Rectangle {id: splitbar1; x: 2; y: 270; width: parent.width; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar2; x: 2; y: 272; width: parent.width; height: 1; color: "#fafcfe" }

    Column {
        width: parent.width
        height: 200
        anchors {
            top: splitbar2.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }
        Item {
            id: views
            width: parent.width
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
            height: 20
//            flag: "BBS"
            onClicked: {
                Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php");
            }
        }
        Common.StyleButton {
            id: versionlabel
            wordname: qsTr("Features")//新版本特性
            width: 60
            height: 20
//            flag: "VersionFeature"
            onClicked: {
                sessiondispatcher.showFeatureDialog(mainwindow.pos.x, mainwindow.pos.y);
            }
        }
        Common.StyleButton {
            id: buglabel
            wordname: qsTr("Report Bugs")//Bug提交
            width: 40
            height: 20
//            flag: "BUG"
            onClicked: {
                Qt.openUrlExternally("https://bugs.launchpad.net/youker-assistant");
            }
        }
    }
}
