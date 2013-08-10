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
import SessionType 0.1
import SystemType 0.1
import "common" as Common
import "bars" as Bars
/*
{'desktopenvironment': 'Unity', 'update_time': 'The package information was last updated 4 hours ago.',
'hostname': 'kobe-3570R-370R-470R-450R-510R', 'language': 'zh_CN.UTF-8', 'platform': 'i686',
'cache_packages': '346 cache packages can be cleaned.', 'ram': '1.8 GB', 'currrent_user': 'kobe',
'cache_flag': True, 'shell': '/bin/bash', 'cache_size': '33.4 MB thumbnails cache can be cleaned.',
'distribution': 'Ubuntu 13.04 raring',
'home_path': '/home/kobe', 'cpu': 'Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz'}
*/
Rectangle {
    id: screen; width: parent.width; height: 475
    property SessionDispatcher dis1: sessiondispatcher
    property SystemDispatcher dis2: systemdispatcher
    signal dialogmsg()
    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component:", component.errorString());
     }
//    Common.Border {
//        id: leftborder
//        width: 2
//        height: parent.height
//    }
//    Common.Border {
//        id: rightborder
//        width: 2
//        height: parent.height
//        anchors.right: parent.right
//    }

    Rectangle {
        id: tools_widget
        anchors {
            fill: parent
            left: parent.right
            leftMargin: 2
            right: parent.left
            rightMargin: 2
        }
//        color: "white"

        Item {
            id: views
            width: parent.width
            height: parent.height

            //--------------------左边隐藏说明栏---------------------
//            BorderImage {
//                id: sidebar
//                source: "../img/icons/unselect.png"
//                anchors.left: parent.left
////                anchors.right: parent.right
//                anchors.top: parent.top
//                width: show ? 140 : 10
//                height:parent.height
//                Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
//                property bool show: false
//                border.left: 0;
//                border.right: 26;
////                border.left: 26;
////                border.right: 0;
//                MouseArea {
//                    id:mouseArea
//                    anchors.fill: parent
//                    onClicked: sidebar.show = !sidebar.show
//                }
//                Column {
//                    id: panel1
//                    opacity: sidebar.show ? 1 : 0
//                    Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }
//                    scale: sidebar.show ? 1 : 0
//                    Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
//                    transformOrigin: Item.Top
//                    anchors.top: parent.top
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    anchors.margins: 12
//                    spacing:12
//                    Image {
//                        width: 47
//                        height: 47
//                        source: "../img/icons/kysoft.png"
//                    }
//                    Label {
//                        text: "UbuntuKylin Team"
//                        width: parent.width - 12
//                    }
//                    Label {
//                        text: qsTr("Youker Assistant")
//                        width: parent.width - 12
//                    }
//                    Label {
//                        text: qsTr("第一期工程 20130601")
//                        width: parent.width - 12
//                    }
//                    Button {
//                        id: mybtn
//                        text: qsTr("测试")
//                        onClicked: {
//                            //method 1
//        //                     var component = Qt.createComponent("MyDialog.qml");
//        //                     if (component.status == Component.Ready) {
//        ////                         var button = component.createObject(home);
//        ////                         button.color = "red";
//        //                         component.createObject(home);
//        //                     }

//                            //method 2
//        //                    pageLoader.source = "MyDialog.qml"

//                            //method 3
//        //                    mydialog.open();

//                            //method 4
//        //                    home.openFile("MyDialog.qml");
//        //                    sessiondispatcher.send_dialog_msg("modeless");
//                            sessiondispatcher.send_dialog_msg("modal");
//                        }
//                    }
//                }
//            }
            //--------------------左边隐藏说明栏---------------------


//            ListModel {
//                id: clearModel
//                ListElement {
//                    icon: "../img/icons/themeset.png"
//                    name: "主题"
//                    flag: "theme"
//                }
//                ListElement {
//                    icon: "../img/icons/iconbeauty.png"
//                    name: "桌面图标"
//                    flag: "desktopicon"
//                }
//                ListElement {
//                    icon: "../img/icons/bootanimation.png"
//                    name: "开机动画"
//                    flag: "touchpad"
////                    flag: "bootanimation"
//                }
//                ListElement {
//                    icon: "../img/icons/systemsound.png"
//                    name: "系统声音"
//                    flag: "sound"
//                }
//                ListElement {
//                    icon: "../img/icons/deepclear.png"
//                    name: "深度清理"
//                    flag: "fonts"
//                }

//                ListElement {
//                    icon: "../img/icons/systemreduce.png"
//                    name: "系统瘦身"
//                    flag: "unity"
//                }

//            }

            //左右布局
            Row {
                anchors.fill: parent
                spacing: 0
                //坐边栏
                LeftPage {
                    id: leftbar
                    anchors.left: parent.left
                    anchors.leftMargin: -2
                    width: 600; height: screen.height
                }
               RightPage {
                    id: rightbar
                    anchors.left: leftbar.right
                    anchors.leftMargin: 0
                    width: screen.width - 600; height: screen.height
                }

//                Rectangle {
//                    id: leftbar
//                    width: 600; height: screen.height
////                    color: "blue"
//                    Image {
//                        source: "../img/skin/leftbackground.png"
//                        anchors.fill: parent
//                    }

//                    Row {
//                        spacing: 10
//                        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//                        Image {
//                            id: refreshArrow
//                            source: "../img/toolWidget/hardware.png"
//        //                    anchors { top: parent.top; topMargin: 10; left: parent.left; leftMargin: 45 }
//                            width: 120; height: 120
//        //                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                        }
//                        Column {
//                            spacing: 10
////                            anchors.fill: parent
//                            id: mycolumn
//                            Text {
//                                id: text0
//                                width: 69
//                                text: qsTr("您的电脑已经有1天没有清理垃圾,建议立即清理!")
//                                font.bold: true
//                                font.pointSize: 13
//                                font.pixelSize: 12
//        //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                            }
//                            Text {
//                                id: text1
//                                width: 69
//                                text: qsTr("定期清理垃圾可以提升电脑的运行速率.")
//        //                        font.bold: true
//                                font.pointSize: 13
//                                font.pixelSize: 12
//        //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                            }
//                            SetBtn {
//                                iconName: "onekeyBtn.png"
////                                anchors.horizontalCenter: mycolumn.horizontalCenter
//                                anchors {
//                                    top: text1.bottom; topMargin: 30
//                                    left: parent.left; leftMargin: 80
//                                }
//                                width: 186
//                                height: 45
//                            }
//                        }
//                        Label {
//                            id: itemtip
//                            text: qsTr("<h1>安全项目</h1>")
//                            font.family: "楷体"
//                            color: "green"
//                            anchors { top: refreshArrow.bottom; topMargin: 10; left: parent.left; leftMargin: 5 }
//                        }
//                        ScrollArea {
//                            frame:false
//        //                    anchors.fill: parent
//                            width:560
//                            height: screen.height - refreshArrow.height - itemtip.height - 40
//                            anchors.top: itemtip.bottom
//                            anchors.topMargin: 10
//                            anchors.left: parent.left
//                            Item {
//                                width:parent.width
//                                height:330
//                                Component {
//                                    id: statusDelegate
//                                    Row {
//                                        Text {
//                                            text: title
//                                        }
//                                    }
//                                }
//                                ListModel {
//                                    id: streamModel
//                                    ListElement {
//                                        title: "清理垃圾1"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾2"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾3"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾4"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾5"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾6"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾7"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾8"
//                                    }

//                                }

//                                //垃圾清理显示内容
//                                ListView {
//                                    id: listView
//                                    height: parent.height
//                                    width: parent.width
//                                    model: streamModel
//                                    delegate: statusDelegate
//                                    cacheBuffer: 1000
//                                    opacity: 1
//                                    spacing: 10
//                                    snapMode: ListView.NoSnap
//        //                            cacheBuffer: parent.height
//                                    boundsBehavior: Flickable.DragOverBounds
//                                    currentIndex: 0
//                                    preferredHighlightBegin: 0
//                                    preferredHighlightEnd: preferredHighlightBegin
//                                    highlightRangeMode: ListView.StrictlyEnforceRange
//                                }
//                            }//Item
//                        }//ScrollArea
//                    }
//                }//坐边栏Rectangle

                //右边栏
//                Rectangle {
//                    id: rightbar
//                    width: screen.width - 600; height: screen.height
//                    //背景
//                    Image {
//                        source: "../img/skin/rightbackground.png"
//                        anchors.fill: parent
//                    }

//                    //-------------------
//                    Column {
//                        anchors.fill: parent
//                        spacing: 10
//                        Image {
//                            id: logoimage
//                            anchors {
//                                top: parent.top
//                                topMargin: 20
//                                horizontalCenter: parent.horizontalCenter
//                            }
//                            source: "../img/icons/admin.png"
//                        }
//                        Row {
//                            id: setrow
//                            anchors {
//                                horizontalCenter: parent.horizontalCenter
//                                top: logoimage.bottom
//                                topMargin: 1
//                            }
//                            SetBtn {iconName: "set.png"}
//                            SetBtn {iconName: "message.png"}
//                        }
//                        Column {
//                            anchors {
//                                left: parent.left; leftMargin: 10
//                                top: setrow.bottom
//                            }
//                            Label {
//                                id: hareware
//                                text: qsTr("<h1>硬件信息</h1>")
//                                font.family: "楷体"
//                            }
//                            Text {
//                                text: qsTr("CPU:" + systemdispatcher.get_value("cpu") + "; "+ "内存:" + systemdispatcher.get_value("ram"))
//                            }
//                        }
//                    }
//                    //上下分割条
//                    Rectangle {id: splitbar; y: 270; width: parent.width; height: 1; color: "#cccccc" }
//                    //-------------------


//                    GridView {
//                        id: gridView
//                        height: parent.height
//                        width: parent.width
//                        anchors {
//                            top: splitbar.bottom
//                            topMargin: 5
//                            left: parent.left
//                            leftMargin: 5
//                        }
//                        model: clearModel
//                        delegate: ToolsDelegate {}
//                        cellWidth: (parent.width-2)/3; cellHeight: cellWidth
////                        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
//                        focus: true
//                    }

//                    Row {
//                        spacing: 40
//                        anchors {
//                            bottom: parent.bottom
//                            left: parent.left
//                            leftMargin: 10
//                        }
//                        Label {
//                            text: "论坛求助"
//                            color: "green"
//                        }
//                        Label {
//                            text: "新版本特性"
//                            color: "green"
//                        }
//                    }

//                    //颜色渐变
////                    gradient: Gradient{
////                           GradientStop{
////                               position: 0.0
////                               color: "purple"
////                           }
////                           GradientStop{
////                               position: 1.0
////                               color: "white"
////                           }
////                       }
//                }//右边栏Rectangle
            }//左右布局Row
//            SettingsDetails {
//                id: settigsDetails
//                width: parent.width
//                anchors.left: views.right
//                height: parent.height
//            }
            Item { id: foreground; anchors.fill: parent }
            //左右分割条
            Rectangle {id: midsplitbar1; x: 600; height: screen.height; width: 1; color: "#b9c5cc" }
            Rectangle {id: midsplitbar2; x: 602; height: screen.height; width: 1; color: "#fafcfe" }

        }//Item:views


        //顶层工具栏
//        Bars.TopBar {
//            id: topBar
//            visible: false
//            width: 28
//            height: 26
//            anchors.top: parent.top
//            anchors.topMargin: 40
//            anchors.left: parent.left
//            anchors.leftMargin: 40
//            opacity: 0.9
//            onButtonClicked: {}
//        }

//        //工具栏
//        Bars.ToolBar {
//            id: toolBar
//            visible: false
//            height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
////            button1Label: qsTr("返回")
////            button2Label: qsTr("确定")
//            onQuitBtnClicked: {}
//            onOkBtnClicked: {}
//        }

//        states: State {
//            name: "DetailedView"
//            PropertyChanges { target: views; x: -parent.width }
//            PropertyChanges { target: toolBar; visible: true }
//            PropertyChanges { target: topBar; visible: true }
//        }

//        transitions: Transition {
//            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//        }
    }//Rectangle:tools_widget
}//Rectangle:screen




















//Rectangle {
//    id: screen; width: parent.width; height: 460
//    property SessionDispatcher dis1: sessiondispatcher
//    property SystemDispatcher dis2: systemdispatcher
//    signal dialogmsg()
//    function openFile(file) {
//         var component = Qt.createComponent(file)
//         if (component.status == Component.Ready)
//             pageStack.push(component);
//         else
//             console.log("Error loading component:", component.errorString());
//     }
//    Common.Border {
//        id: leftborder
//        width: 2
//        height: parent.height
//    }
//    Common.Border {
//        id: rightborder
//        width: 2
//        height: parent.height
//        anchors.right: parent.right
//    }

//    Rectangle {
//        id: tools_widget
//        anchors {
//            fill: parent
//            left: leftborder.right
//            leftMargin: 2
//            right: rightborder.left
//            rightMargin: 2
//        }
////        color: "white"

//        Item {
//            id: views
//            width: parent.width
//            height: parent.height

//            //--------------------左边隐藏说明栏---------------------
////            BorderImage {
////                id: sidebar
////                source: "../img/icons/unselect.png"
////                anchors.left: parent.left
//////                anchors.right: parent.right
////                anchors.top: parent.top
////                width: show ? 140 : 10
////                height:parent.height
////                Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
////                property bool show: false
////                border.left: 0;
////                border.right: 26;
//////                border.left: 26;
//////                border.right: 0;
////                MouseArea {
////                    id:mouseArea
////                    anchors.fill: parent
////                    onClicked: sidebar.show = !sidebar.show
////                }
////                Column {
////                    id: panel1
////                    opacity: sidebar.show ? 1 : 0
////                    Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }
////                    scale: sidebar.show ? 1 : 0
////                    Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
////                    transformOrigin: Item.Top
////                    anchors.top: parent.top
////                    anchors.left: parent.left
////                    anchors.right: parent.right
////                    anchors.margins: 12
////                    spacing:12
////                    Image {
////                        width: 47
////                        height: 47
////                        source: "../img/icons/kysoft.png"
////                    }
////                    Label {
////                        text: "UbuntuKylin Team"
////                        width: parent.width - 12
////                    }
////                    Label {
////                        text: qsTr("Youker Assistant")
////                        width: parent.width - 12
////                    }
////                    Label {
////                        text: qsTr("第一期工程 20130601")
////                        width: parent.width - 12
////                    }
////                    Button {
////                        id: mybtn
////                        text: qsTr("测试")
////                        onClicked: {
////                            //method 1
////        //                     var component = Qt.createComponent("MyDialog.qml");
////        //                     if (component.status == Component.Ready) {
////        ////                         var button = component.createObject(home);
////        ////                         button.color = "red";
////        //                         component.createObject(home);
////        //                     }

////                            //method 2
////        //                    pageLoader.source = "MyDialog.qml"

////                            //method 3
////        //                    mydialog.open();

////                            //method 4
////        //                    home.openFile("MyDialog.qml");
////        //                    sessiondispatcher.send_dialog_msg("modeless");
////                            sessiondispatcher.send_dialog_msg("modal");
////                        }
////                    }
////                }
////            }
//            //--------------------左边隐藏说明栏---------------------


//            ListModel {
//                id: clearModel
//                ListElement {
//                    icon: "../img/icons/themeset.png"
//                    name: "主题"
//                    flag: "theme"
//                }
//                ListElement {
//                    icon: "../img/icons/iconbeauty.png"
//                    name: "桌面图标"
//                    flag: "desktopicon"
//                }
//                ListElement {
//                    icon: "../img/icons/bootanimation.png"
//                    name: "开机动画"
//                    flag: "touchpad"
////                    flag: "bootanimation"
//                }
//                ListElement {
//                    icon: "../img/icons/systemsound.png"
//                    name: "系统声音"
//                    flag: "sound"
//                }
//                ListElement {
//                    icon: "../img/icons/deepclear.png"
//                    name: "深度清理"
//                    flag: "fonts"
//                }

//                ListElement {
//                    icon: "../img/icons/systemreduce.png"
//                    name: "系统瘦身"
//                    flag: "unity"
//                }

//            }

//            //左右布局
//            Row {
////                anchors.fill: parent
//                //坐边栏
//                Rectangle {
//                    id: leftbar
//                    width: 600; height: screen.height
////                    color: "blue"
//                    Image {
//                        source: "../img/skin/leftbackground.png"
//                        anchors.fill: parent
//                    }

//                    Row {
//                        spacing: 10
//                        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//                        Image {
//                            id: refreshArrow
//                            source: "../img/toolWidget/hardware.png"
//        //                    anchors { top: parent.top; topMargin: 10; left: parent.left; leftMargin: 45 }
//                            width: 120; height: 120
//        //                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                        }
//                        Column {
//                            spacing: 10
////                            anchors.fill: parent
//                            id: mycolumn
//                            Text {
//                                id: text0
//                                width: 69
//                                text: qsTr("您的电脑已经有1天没有清理垃圾,建议立即清理!")
//                                font.bold: true
//                                font.pointSize: 13
//                                font.pixelSize: 12
//        //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                            }
//                            Text {
//                                id: text1
//                                width: 69
//                                text: qsTr("定期清理垃圾可以提升电脑的运行速率.")
//        //                        font.bold: true
//                                font.pointSize: 13
//                                font.pixelSize: 12
//        //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                            }
//                            SetBtn {
//                                iconName: "onekeyBtn.png"
////                                anchors.horizontalCenter: mycolumn.horizontalCenter
//                                anchors {
//                                    top: text1.bottom; topMargin: 30
//                                    left: parent.left; leftMargin: 80
//                                }
//                                width: 186
//                                height: 45
//                            }
//                        }
//                        Label {
//                            id: itemtip
//                            text: qsTr("<h1>安全项目</h1>")
//                            font.family: "楷体"
//                            color: "green"
//                            anchors { top: refreshArrow.bottom; topMargin: 10; left: parent.left; leftMargin: 5 }
//                        }
//                        ScrollArea {
//                            frame:false
//        //                    anchors.fill: parent
//                            width:560
//                            height: screen.height - refreshArrow.height - itemtip.height - 40
//                            anchors.top: itemtip.bottom
//                            anchors.topMargin: 10
//                            anchors.left: parent.left
//                            Item {
//                                width:parent.width
//                                height:330
//                                Component {
//                                    id: statusDelegate
//                                    Row {
//                                        Text {
//                                            text: title
//                                        }
//                                    }
//                                }
//                                ListModel {
//                                    id: streamModel
//                                    ListElement {
//                                        title: "清理垃圾1"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾2"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾3"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾4"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾5"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾6"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾7"
//                                    }
//                                    ListElement {
//                                        title: "清理垃圾8"
//                                    }

//                                }

//                                //垃圾清理显示内容
//                                ListView {
//                                    id: listView
//                                    height: parent.height
//                                    width: parent.width
//                                    model: streamModel
//                                    delegate: statusDelegate
//                                    cacheBuffer: 1000
//                                    opacity: 1
//                                    spacing: 10
//                                    snapMode: ListView.NoSnap
//        //                            cacheBuffer: parent.height
//                                    boundsBehavior: Flickable.DragOverBounds
//                                    currentIndex: 0
//                                    preferredHighlightBegin: 0
//                                    preferredHighlightEnd: preferredHighlightBegin
//                                    highlightRangeMode: ListView.StrictlyEnforceRange
//                                }
//                            }//Item
//                        }//ScrollArea
//                    }
//                }//坐边栏Rectangle

//                //右边栏
//                Rectangle {
//                    id: rightbar
//                    width: screen.width - 600; height: screen.height
//                    //背景
//                    Image {
//                        source: "../img/skin/rightbackground.png"
//                        anchors.fill: parent
//                    }

//                    //-------------------
//                    Column {
//                        anchors.fill: parent
//                        spacing: 10
//                        Image {
//                            id: logoimage
//                            anchors {
//                                top: parent.top
//                                topMargin: 20
//                                horizontalCenter: parent.horizontalCenter
//                            }
//                            source: "../img/icons/admin.png"
//                        }
//                        Row {
//                            id: setrow
//                            anchors {
//                                horizontalCenter: parent.horizontalCenter
//                                top: logoimage.bottom
//                                topMargin: 1
//                            }
//                            SetBtn {iconName: "set.png"}
//                            SetBtn {iconName: "message.png"}
//                        }
//                        Column {
//                            anchors {
//                                left: parent.left; leftMargin: 10
//                                top: setrow.bottom
//                            }
//                            Label {
//                                id: hareware
//                                text: qsTr("<h1>硬件信息</h1>")
//                                font.family: "楷体"
//                            }
//                            Text {
//                                text: qsTr("CPU:" + systemdispatcher.get_value("cpu") + "; "+ "内存:" + systemdispatcher.get_value("ram"))
//                            }
//                        }
//                    }
//                    //上下分割条
//                    Rectangle {id: splitbar; y: 270; width: parent.width; height: 1; color: "#cccccc" }
//                    //-------------------


//                    GridView {
//                        id: gridView
//                        height: parent.height
//                        width: parent.width
//                        anchors {
//                            top: splitbar.bottom
//                            topMargin: 5
//                            left: parent.left
//                            leftMargin: 5
//                        }
//                        model: clearModel
//                        delegate: ToolsDelegate {}
//                        cellWidth: (parent.width-2)/3; cellHeight: cellWidth
////                        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
//                        focus: true
//                    }

//                    Row {
//                        spacing: 40
//                        anchors {
//                            bottom: parent.bottom
//                            left: parent.left
//                            leftMargin: 10
//                        }
//                        Label {
//                            text: "论坛求助"
//                            color: "green"
//                        }
//                        Label {
//                            text: "新版本特性"
//                            color: "green"
//                        }
//                    }

//                    //颜色渐变
////                    gradient: Gradient{
////                           GradientStop{
////                               position: 0.0
////                               color: "purple"
////                           }
////                           GradientStop{
////                               position: 1.0
////                               color: "white"
////                           }
////                       }
//                }//右边栏Rectangle
//            }//左右布局Row
//            SettingsDetails {
//                id: settigsDetails
//                width: parent.width
//                anchors.left: views.right
//                height: parent.height
//            }
//            Item { id: foreground; anchors.fill: parent }
//            //左右分割条
//            Rectangle {id: midsplitbar; x: 600; height: screen.height; width: 1; color: "#cccccc" }

//        }//Item:views


//        //工具栏
//        Common.ToolBar {
//            id: toolBar
//            visible: false
//            height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("返回")
//            button2Label: qsTr("确定")
//            onButton1Clicked: {}
//            onButton2Clicked: {}
//        }

//        states: State {
//            name: "DetailedView"
//            PropertyChanges { target: views; x: -parent.width }
//            PropertyChanges { target: toolBar; visible: true }
//        }

//        transitions: Transition {
//            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//        }
//    }//Rectangle:tools_widget
//}//Rectangle:screen
