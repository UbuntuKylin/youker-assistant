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
//import Ubuntu.Components 0.1
import RegisterMyType 0.1
import QtDesktop 0.1
import "common" as Common
/*
{'desktopenvironment': 'Unity', 'update_time': 'The package information was last updated 4 hours ago.',
'hostname': 'kobe-3570R-370R-470R-450R-510R', 'language': 'zh_CN.UTF-8', 'platform': 'i686',
'cache_packages': '346 cache packages can be cleaned.', 'ram': '1.8 GB', 'currrent_user': 'kobe',
'cache_flag': True, 'shell': '/bin/bash', 'cache_size': '33.4 MB thumbnails cache can be cleaned.',
'distribution': 'Ubuntu 13.04 raring',
'home_path': '/home/kobe', 'cpu': 'Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz'}
*/
Rectangle {
    id: home
    width: parent.width
    height: 460
    property Dispatcher dis: mydispather

    function openFile(file) {
         var component = Qt.createComponent(file)
         if (component.status == Component.Ready)
             pageStack.push(component);
         else
             console.log("Error loading component:", component.errorString());
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
    BorderImage {
        id: sidebar
        source: "../img/icons/unselect.png"
//        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        width: show ? 140 : 10
        height:parent.height
        Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
        property bool show: false
//        border.left: 0;
//        border.right: 26;
        border.left: 26;
        border.right: 0;
        MouseArea {
            id:mouseArea
            anchors.fill: parent
            onClicked: sidebar.show = !sidebar.show
        }
        Column {
            id: panel1
            opacity: sidebar.show ? 1 : 0
            Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }

            scale: sidebar.show ? 1 : 0
            Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
            transformOrigin: Item.Top

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 12
            spacing:12

            Image {
                width: 47
                height: 47
                source: "../img/icons/kysoft.png"
            }
            Label {
                text: "UbuntuKylin Team"
                width: parent.width - 12
            }
            Label {
                text: qsTr("Youker Assistant")
                width: parent.width - 12
            }
            Label {
                text: qsTr("第一期工程 20130601")
                width: parent.width - 12
            }
            Button {
                id: mybtn
                text: qsTr("测试")
                onClicked: {

                    //method 1
//                     var component = Qt.createComponent("MyDialog.qml");
//                     if (component.status == Component.Ready) {
////                         var button = component.createObject(home);
////                         button.color = "red";
//                         component.createObject(home);
//                     }


                    ////method 2
//                    pageLoader.source = "MyDialog.qml"

                    //method 3
//                    mydialog.open();

                    //method 4
                    home.openFile("MyDialog.qml");
                }
            }
        }


    }
    //------------------------------------------------

    //Loader { id: pageLoader }
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




    Column {
        anchors.fill: parent
        Rectangle {
            id: lineLayout
            Image {
                id: refreshArrow
                source: "../img/toolWidget/hardware.png"
                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 }
                width: 47; height: 47
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text0
                width: 69
                text: qsTr("硬件信息:")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
                anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
            }
            Column {
                anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 + refreshArrow.width + text0.width }
                spacing: 10
                Text {
                    text: qsTr("CPU: "+ mydispather.get_value("cpu"))
                }
                Text {
                    text: qsTr("内存: " + mydispather.get_value("ram"))
                }
            }
        }

        Rectangle {
            id: lineLayout1
            y: 110
            Image {
                id: refreshArrow1
                anchors { left: parent.left; leftMargin: 45}
                width: 47; height: 47
                source: "../img/toolWidget/desktop.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text1
                width: 69
                anchors { top: lineLayout1.top; topMargin: 15; left: parent.left; leftMargin: 45 + refreshArrow1.width }
                text: qsTr("桌面信息:")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
            }
            Column {
                anchors { top: lineLayout1.top; topMargin: -20; left: parent.left; leftMargin: 45 + refreshArrow1.width + text1.width }
                spacing: 10
                Text {
                    text: qsTr("主机名: " + mydispather.get_value("hostname"))
                }
                Text {
                    text: qsTr("平台: " + mydispather.get_value("platform"))
                }
                Text {
                    text: qsTr("发行版: " + mydispather.get_value("distribution"))
                }
                Text {
                    text: qsTr("桌面环境: " + mydispather.get_value("desktopenvironment"))
                }
            }

        }

        Rectangle {
            id: lineLayout2
            y: 220
            Image {
                id: refreshArrow2
                anchors { left: parent.left; leftMargin: 45}
                width: 47; height: 47
                source: "../img/toolWidget/cache.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text2
                width: 69
                text: qsTr("缓存信息:")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
                anchors { top: lineLayout2.top; topMargin: 15; left: parent.left; leftMargin: 45 + refreshArrow2.width }
            }
            Column {
                anchors { top: lineLayout2.top; topMargin: -10; left: parent.left; leftMargin: 45 + refreshArrow2.width + text2.width }
                spacing: 10
                Text {
                    text: qsTr("可以清除一些缓存以便释放您的磁盘空间")
                }
                Text {
                    text: qsTr(mydispather.get_value("cache_packages"))
                }
                Text {
                    text: qsTr(mydispather.get_value("cache_size"))
                }
            }
        }

        Rectangle {
            id: lineLayout3
            y: 330
            Image {
                id: refreshArrow3
                anchors { left: parent.left; leftMargin: 45}
                width: 47; height: 47
                source: "../img/toolWidget/softpackage.png"
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Text {
                id: text3
                width: 69
                text: qsTr("软件包信息:")
                font.bold: true
                font.pointSize: 13
                font.pixelSize: 12
                anchors { top: lineLayout3.top; topMargin: 15; left: parent.left; leftMargin: 45 + refreshArrow3.width }
            }
            Column {
                anchors { top: lineLayout3.top; topMargin: 5; left: parent.left; leftMargin: 45 + refreshArrow3.width + text3.width }
                spacing: 10
                Text {
                    text: qsTr("您的系统已经为最新")
                }
                Text {
                    text: qsTr("更新时间: "+ mydispather.get_value("update_time"))
                }
            }
        }
    }
}
