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
import SessionType 0.1
//import SystemType 0.1
import "common" as Common
Rectangle {
    id: home
    width: parent.width
    height: 475
    property SessionDispatcher dis: sessiondispatcher
//    property SystemDispatcher dis2: systemdispatcher
    signal dialogmsg()

    Component.onCompleted: {
        console.log("start to get system message................");
        sessiondispatcher.get_system_message_qt();
    }

    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component:", component.errorString());
     }

    //背景
    Image {
        source: "../img/skin/bg-left.png"
        anchors.fill: parent
    }
    //desktop logo
    Image {
        source: "../img/toolWidget/ubuntukylin.png"
        anchors {
            top: parent.top
            topMargin: 230
            right: parent.right
            rightMargin: 70
        }
    }

    Image {
        id: titleimage
        anchors {
            left: parent.left
            leftMargin: 2
        }
        source: "../img/skin/note-bg.png"
    }
    Text {
        anchors {
            left: parent.left
            leftMargin: 50
            top: parent.top
            topMargin: titleimage.height/2 - 7
        }
        text: "您可以查看相关信息，随时了解系统情况。"
        font.pixelSize: 12
        color: "#383838"
    }

    Common.Border {
        id: leftborder
//        width: 2
//        height: parent.height
    }
    Common.Border {
        id: roightborder
//        width: 2
//        height: parent.height
        anchors.right: parent.right
    }

//    Image {
//        id: leftborder
//        source: "../img/icons/tab.png"
//        width: 2
//        height: parent.height
//        anchors {
//            top: parent.top
//            left: parent.left
//            bottom: parent.bottom
//        }
//    }
//    Image {
//        id: rightborder
//        source: "../img/icons/tab.png"
//        width: 2
//        height: parent.height
//        anchors {
//            top: parent.top
//            right: parent.right
//            bottom: parent.bottom
//        }
//    }



    //--------------------右边隐藏说明栏---------------------
//    BorderImage {
//        id: sidebar
//        source: "../img/icons/unselect.png"
////        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.top: parent.top
//        width: show ? 140 : 10
//        height:parent.height
//        Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
//        property bool show: false
////        border.left: 0;
////        border.right: 26;
//        border.left: 26;
//        border.right: 0;
//        MouseArea {
//            id:mouseArea
//            anchors.fill: parent
//            onClicked: sidebar.show = !sidebar.show
//        }
//        Column {
//            id: panel1
//            opacity: sidebar.show ? 1 : 0
//            Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }

//            scale: sidebar.show ? 1 : 0
//            Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
//            transformOrigin: Item.Top

//            anchors.top: parent.top
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.margins: 12
//            spacing:12

//            Image {
//                width: 47
//                height: 47
//                source: "../img/icons/kysoft.png"
//            }
//            Label {
//                text: "UbuntuKylin Team"
//                width: parent.width - 12
//            }
//            Label {
//                text: qsTr("Youker Assistant")
//                width: parent.width - 12
//            }
//            Label {
//                text: qsTr("第一期工程 20130601")
//                width: parent.width - 12
//            }
//            Button {
//                id: mybtn
//                text: qsTr("测试")
//                onClicked: {

//                    //method 1
////                     var component = Qt.createComponent("MyDialog.qml");
////                     if (component.status == Component.Ready) {
//////                         var button = component.createObject(home);
//////                         button.color = "red";
////                         component.createObject(home);
////                     }

//                    //method 2
////                    pageLoader.source = "MyDialog.qml"

//                    //method 3
////                    mydialog.open();

//                    //method 4
////                    home.openFile("MyDialog.qml");
////                    sessiondispatcher.send_dialog_msg("modeless");
//                    sessiondispatcher.send_dialog_msg("modal");
//                }
//            }
//        }


//    }



    //上下分割条
    Rectangle {x: 100; y: 90; width: parent.width - 150; height: 1; color: "#b9c5cc" }
    Rectangle {x: 100; y: 92; width: parent.width - 150; height: 1; color: "#fafcfe" }
    //-------------------

    //上下分割条
    Rectangle {x: 100; y: 190; width: parent.width - 150; height: 1; color: "#b9c5cc" }
    Rectangle {x: 100; y: 192; width: parent.width - 150; height: 1; color: "#fafcfe" }
    //-------------------

    //上下分割条
    Rectangle {x: 100; y: 370; width: parent.width - 150; height: 1; color: "#b9c5cc" }
    Rectangle {x: 100; y: 372; width: parent.width - 150; height: 1; color: "#fafcfe" }
    //-------------------

    Column {
        anchors {
//            fill: parent
            top: titleimage.bottom
            topMargin: 40
            left: parent.left
            leftMargin: 30
        }
        spacing: 20

        Text {
            id: hardwaretitle
            text: qsTr("硬件信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
//            font.pointSize: 13
//            font.pixelSize: 12
//            anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("处理器:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("cpu")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("内存:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("ram")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }


        Text {
            id: desktoptitle
//            anchors { top: lineLayout1.top; topMargin: 15; left: parent.left; leftMargin: 45 + refreshArrow1.width }
            text: qsTr("桌面信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("主机名:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("hostname")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("平台:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("platform")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("发行版:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("distribution")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("桌面环境:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("desktopenvironment")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("语言:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("language")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }

        Text {
            id: usertitle
            text: qsTr("用户信息")
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
//            font.pointSize: 13
//            font.pixelSize: 12
//            anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("当前用户:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("currrent_user")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("用户主目录:")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 60
                }
                Text {
                    text: sessiondispatcher.get_value("home_path")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }




//        Rectangle {
//            id: lineLayout
//            Image {
//                id: refreshArrow
//                source: "../img/toolWidget/hardware.png"
//                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 }
//                width: 47; height: 47
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }

//            Column {
//                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 + refreshArrow.width + text0.width }
//                spacing: 10

//            }
//        }

//        Rectangle {
//            id: lineLayout1
//            y: 110
//            Image {
//                id: refreshArrow1
//                anchors { left: parent.left; leftMargin: 45}
//                width: 47; height: 47
//                source: "../img/toolWidget/desktop.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }

//            Column {
//                anchors { top: lineLayout1.top; topMargin: -20; left: parent.left; leftMargin: 45 + refreshArrow1.width + text1.width }
//                spacing: 10

//            }
//        }
    }




    //------------------------------------------------
    //method 2
//    Loader { id: pageLoader }
    //对话框 //method 3
//    MyDialog {
//        id: mydialog
//        content:
//            Column {
//                anchors.centerIn: parent
//                spacing: 10
//                Label {
//                    id: lable
//                    text: qsTr("点击鼠标左键开始,右键结束")
//                    color: "white"
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }
//                Row {
//                    spacing: 10
//                    Button {
//                        id: quitbtn
//                        text: qsTr("取消")
//                        onClicked: {
//                            mydialog.close();
//                            mydialog.rejected();
//                        }
//                    }
//                    Button {
//                        id: okbtn
//                        text: qsTr("确定")
//                        onClicked: {
//                            mydispather.new_object_test();
//                        }
//                    }
//                }
//        }
//        onRejected: console.log("Dialog closed.")
//    }





//    MyDialog {
//        id: mydialog

//        property alias titleText: titleText.text
//        property alias message: message.text

//        signal accepted();

//        Text{
//            id: titleText
//            anchors.bottom: message.top
//            anchors.margins: 20
//            width: parent.width
//            color: "white"
//            font.pointSize: 40
//            font.bold: true
//            horizontalAlignment: Text.AlignHCenter
//            wrapMode: Text.Wrap
//        }

//        Text{
//            id:message
//            anchors.centerIn: parent
//            width: parent.width
//            color: "white"
//            font.pointSize: 25
//            horizontalAlignment: Text.AlignHCenter
//            wrapMode: Text.Wrap
//        }

//        Button{
//            id: acceptButton
//            text: "OK"
//            anchors.top: message.bottom
//            anchors.topMargin: 20
//            anchors.horizontalCenter: parent.horizontalCenter
//            width: parent.width * 0.5
//            onClicked: {
//                close()
//                accepted()
//            }
//        }

//        Button{
//            id: rejectButton
//            text: "Cancel"
//            anchors.top: acceptButton.bottom
//            anchors.topMargin: 10
//            anchors.horizontalCenter: parent.horizontalCenter
//            width: parent.width * 0.5
//            onClicked: {
//                close()
//                rejected()
//            }
//        }
//    }




//    Column {
//        anchors.fill: parent
//        Rectangle {
//            id: lineLayout
//            Image {
//                id: refreshArrow
//                source: "../img/toolWidget/hardware.png"
//                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 }
//                width: 47; height: 47
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text0
//                width: 69
//                text: qsTr("硬件信息:")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//                anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//            }
//            Column {
//                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 + refreshArrow.width + text0.width }
//                spacing: 10
//                Text {
//                    text: qsTr("CPU: "+ systemdispatcher.get_value("cpu"))
//                }
//                Text {
//                    text: qsTr("内存: " + systemdispatcher.get_value("ram"))
//                }
//            }
//        }

//        Rectangle {
//            id: lineLayout1
//            y: 110
//            Image {
//                id: refreshArrow1
//                anchors { left: parent.left; leftMargin: 45}
//                width: 47; height: 47
//                source: "../img/toolWidget/desktop.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text1
//                width: 69
//                anchors { top: lineLayout1.top; topMargin: 15; left: parent.left; leftMargin: 45 + refreshArrow1.width }
//                text: qsTr("桌面信息:")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//            Column {
//                anchors { top: lineLayout1.top; topMargin: -20; left: parent.left; leftMargin: 45 + refreshArrow1.width + text1.width }
//                spacing: 10
//                Text {
//                    text: qsTr("主机名: " + systemdispatcher.get_value("hostname"))
//                }
//                Text {
//                    text: qsTr("平台: " + systemdispatcher.get_value("platform"))
//                }
//                Text {
//                    text: qsTr("发行版: " + systemdispatcher.get_value("distribution"))
//                }
//                Text {
//                    text: qsTr("桌面环境: " + systemdispatcher.get_value("desktopenvironment"))
//                }
//            }
//        }
//    }


//    gradient: Gradient{
//           GradientStop{
//               position: 0.0
//               color: "purple"
//           }
//           GradientStop{
//               position: 1.0
//               color: "white"
//           }
//       }

}

//import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import RegisterMyType 0.1

//Rectangle {
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather

//    Column {
//        width: parent.width
//        ListItem.ValueSelector {
//            text: "Standard"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//        }
//        ListItem.ValueSelector {
//            text: "Disabled"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            enabled: false
//        }
//        ListItem.ValueSelector {
//            text: "Expanded"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            expanded: true
//        }
//        ListItem.ValueSelector {
//            text: "Icon"
////            icon: Qt.resolvedUrl("icon.png")
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            selectedIndex: 2
//        }
//    }
//}
