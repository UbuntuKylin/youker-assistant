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
import SystemType 0.1
import "common" as Common

Rectangle {
    id: scaleMe
    scale: 0.0
    Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
    //竖列高度和宽度
    width: 78
    height: 82
    //横列高度和宽度
//    width: 120
//    height: 78
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    function iconClicked() {
        scaleMe.state = "Details";
        settigsDetails.setTitle = flag;
//        console.log(settigsDetails.setTitle);
    }

    //竖列
    Column {
        anchors.fill: parent
        anchors.topMargin: 7
        spacing: 5
        Image {
            id: seticon
            source: icon
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: btnText
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            text: qsTr(name)
        }
    }
    //横列
//    Row {
//        anchors.fill: parent
//        anchors.topMargin: 7
//        Image {
//            id: seticon
//            source: icon
//            //横列
//            anchors.verticalCenter: parent.verticalCenter
//            //竖列
////            anchors.horizontalCenter: parent.horizontalCenter
//        }
//        Text {
//            id: btnText
//            //横列
//            anchors.verticalCenter: parent.verticalCenter
//            //竖列
////            anchors.horizontalCenter: parent.horizontalCenter
//            color: "green"
//            text: qsTr(name)
//        }
//    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }


    Connections {
        target: toolBar
        //按下返回按钮
        onQuitBtnClicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Original'
        //按下确定按钮
//        onButton2Clicked: {
//            console.log("111111111111");
//            console.log(settigsDetails.setTitle);
//            console.log("222222222222");
//        }
    }

    states: [
        State {
            name: "Original"; when: seticon.status == Image.Ready
            PropertyChanges { target: scaleMe; scale: 1 }
        },
        State {
            name: "Details"
            PropertyChanges { target: scaleMe; scale: 1 }
            PropertyChanges { target: setting_widget; state: "DetailedView" }//展示细节页面,出现工具栏
        }
    ]
    transitions: [
        Transition {
            from: "Original"; to: "Details"
            ParentAnimation {
                via: foreground
                NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
            }
        },
        Transition {
            from: "Details"; to: "Original"
            ParentAnimation {
                via: foreground
                NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
            }
        }
    ]

    MouseArea {
        id: signaltest
        hoverEnabled: true
        anchors.fill: parent
        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""
        onClicked: {
            //屏幕坏点检测
            if (flag == "CheckScreen")
                sessiondispatcher.send_checkscreen_dialog();
            else
                iconClicked();
            //kobe:选中项深色块移动
            scaleMe.GridView.view.currentIndex = index;
        }
    }
}



//Item {
//    id: wrapper; width: GridView.view.cellWidth; height: GridView.view.cellHeight
//    function iconClicked() {
//        scaleMe.state = "Details";
//        settigsDetails.setTitle = flag;
//        console.log(settigsDetails.setTitle);
//    }
//    Item {
//        anchors.centerIn: parent
//        scale: 0.0
//        Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
//        id: scaleMe
//        Item {
//            width: 70
//            height: 77
//            anchors.centerIn: parent
//            Column {
//                Image {
//                    id: seticon
//                    source: icon
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }
//                Text {
//                    id: btnText
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    color: "green"
//                    text: qsTr(name)
//                }
//            }
//            Image {
//                id: btnImg
//                anchors.fill: parent
////                anchors.horizontalCenter: parent.horizontalCenter
//                source: ""
//            }
//        }

//        Connections {
//            target: toolBar
//            //按下返回按钮
//            onButton1Clicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Original'
//        }

//        states: [
//            State {
//                name: "Original"; when: seticon.status == Image.Ready
//                PropertyChanges { target: scaleMe; scale: 1 }
//            },
//            State {
//                name: "Details"
//                PropertyChanges { target: scaleMe; scale: 1 }
//                PropertyChanges { target: setting_widget; state: "DetailedView" }//展示细节页面,出现工具栏
//            }
//        ]
//        transitions: [
//            Transition {
//                from: "Original"; to: "Details"
//                ParentAnimation {
//                    via: foreground
//                    NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                }
//            },
//            Transition {
//                from: "Details"; to: "Original"
//                ParentAnimation {
//                    via: foreground
//                    NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                }
//            }
//        ]
//    }
//    MouseArea {
//        anchors.fill: wrapper
//        hoverEnabled: true
//        onEntered: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "../img/toolWidget/menu_press.png"
//        onReleased: btnImg.source = "../img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""
//        onClicked: {
//            iconClicked();
//            //kobe:选中项深色块移动
//            wrapper.GridView.view.currentIndex = index;
//        }
//    }
//}














//Component {
//    Item {
//        id: clearDelegate
//        width: parent.width//clearDelegate.ListView.view.width
//        height: 65

//        Item {
//            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
//            id: scaleMe

//            Item {
//                width: 77; height: 77; anchors.centerIn: parent

//                Column {
//                    id: whiteRect; width: 77; height: 77
//                    Image {
//                        id: thumb; source: icon
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                    Text {
//                        id: btnText
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        color: "green"
//                        text: qsTr(name)
//                    }
//                }
//            }

//        }

//    }
//}









//Item {
//    id: wrapper; width: GridView.view.cellWidth; height: GridView.view.cellHeight

//    function photoClicked() {
//        scaleMe.state = "Details";
//    }

//    Item {
//        anchors.centerIn: parent
//        scale: 0.0
//        Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
//        id: scaleMe

//        Item {
//            width: 77; height: 77; anchors.centerIn: parent

//            Column {
//                id: whiteRect; width: 77; height: 77
//                Image {
//                    id: thumb; source: icon
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }
//                Text {
//                    id: btnText
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    color: "green"
//                    text: qsTr(name)
//                }
//            }
//        }

//        Connections {
//            target: toolBar
//            onButton2Clicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Show'
//        }

//        states: [
//            State {
//                name: "Show"; when: thumb.status == Image.Ready
//                PropertyChanges { target: scaleMe; scale: 1 }
//            },
//            State {
//                name: "Details"
//                PropertyChanges { target: scaleMe; scale: 1 }
//                ParentChange { target: whiteRect; x: 10; y: 20; parent: imageDetails.frontContainer }
//                PropertyChanges { target: background; state: "DetailedView" }
//            }
//        ]
//        transitions: [
//            Transition {
//                from: "Show"; to: "Details"
//                ParentAnimation {
//                    via: foreground
//                    NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                }
//            },
//            Transition {
//                from: "Details"; to: "Show"
//                ParentAnimation {
//                    via: foreground
//                    NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                }
//            }
//        ]
//    }
//    MouseArea { anchors.fill: wrapper; onClicked: photoClicked() }
//}





//Item {
//    id: mysettings
//    signal senditemset(string itemset)
//    Column {
//        anchors.fill: parent
//        //---------------------Unity设置start---------------------
////            Common.SetTitle {
////                id: unity_title
////            }

//        Row {
//            Image {
//                id: refreshArrow0
//                source: "../img/icons/settings.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text0
////                    x: 30
////                    y: 11
//                width: 69
//                height: 20
//                text: qsTr("Unity")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "Launcher"; text: "launcher"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Search"; text: "search"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Panel"; text: "panel"}
//            SetBtn {iconName: "searchtrojan.png"; method: "Switcher"; text: "switcher"}
//            SetBtn {iconName: "computerclinic.png"; method: "WebApps"; text: "webapps"}
//            SetBtn {iconName: "fixbug.png"; method: "Additonal_uinty"; text: "additonal_uinty"}
//        }
//        //---------------------Unity设置end---------------------


//        //---------------------窗体设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow1
//                source: "../img/icons/about.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text1
//                width: 69
//                height: 20
//                text: qsTr("Window Manager")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "General"; text: "general"}
//            SetBtn {iconName: "clearrubbish.png"; method: "WorkspaceSettings"; text: "workspacesettings"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "WindowSpread"; text: "windowspread"}
//            SetBtn {iconName: "searchtrojan.png"; method: "WindowSnapping"; text: "windowsnapping"}
//            SetBtn {iconName: "computerclinic.png"; method: "Hotcorners"; text: "hotcorners"}
//            SetBtn {iconName: "fixbug.png"; method: "Additional_window"; text: "Additional_window"}
//        }
//        //---------------------窗体设置end---------------------

//        //---------------------皮肤设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow2
//                source: "../img/icons/history.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text2
//                width: 69
//                height: 20
//                text: qsTr("Apprearance")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "Theme"; text: "homepage"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Icons"; text: "clearrubbish"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Cursor"}
//            SetBtn {iconName: "searchtrojan.png"; method: "Font"; text: "searchtrojan"}
//            SetBtn {iconName: "computerclinic.png"; method: "WindowControls"; text: "computerclinic"}
//        }
//        //---------------------皮肤设置end---------------------


//        //---------------------系统设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow3
//                source: "../img/icons/about.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text3
//                width: 69
//                height: 20
//                text: qsTr("System")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "DesktopIcons"; text: "desktopIcons"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Security"; text: "security"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Scrolling"; text: "scrolling"}
//        }
//        //---------------------系统设置end---------------------
//    }//Column

//}//Item




//Item {
//    id: mysettings
//    signal senditemset(string itemset)
//    Column {
//        anchors.fill: parent
//        //---------------------Unity设置start---------------------
////            Common.SetTitle {
////                id: unity_title
////            }

//        Row {
//            Image {
//                id: refreshArrow0
//                source: "../img/icons/settings.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text0
////                    x: 30
////                    y: 11
//                width: 69
//                height: 20
//                text: qsTr("Unity")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "Launcher"; text: "launcher"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Search"; text: "search"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Panel"; text: "panel"}
//            SetBtn {iconName: "searchtrojan.png"; method: "Switcher"; text: "switcher"}
//            SetBtn {iconName: "computerclinic.png"; method: "WebApps"; text: "webapps"}
//            SetBtn {iconName: "fixbug.png"; method: "Additonal_uinty"; text: "additonal_uinty"}
//        }
//        //---------------------Unity设置end---------------------


//        //---------------------窗体设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow1
//                source: "../img/icons/about.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text1
//                width: 69
//                height: 20
//                text: qsTr("Window Manager")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "General"; text: "general"}
//            SetBtn {iconName: "clearrubbish.png"; method: "WorkspaceSettings"; text: "workspacesettings"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "WindowSpread"; text: "windowspread"}
//            SetBtn {iconName: "searchtrojan.png"; method: "WindowSnapping"; text: "windowsnapping"}
//            SetBtn {iconName: "computerclinic.png"; method: "Hotcorners"; text: "hotcorners"}
//            SetBtn {iconName: "fixbug.png"; method: "Additional_window"; text: "Additional_window"}
//        }
//        //---------------------窗体设置end---------------------

//        //---------------------皮肤设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow2
//                source: "../img/icons/history.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text2
//                width: 69
//                height: 20
//                text: qsTr("Apprearance")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "Theme"; text: "homepage"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Icons"; text: "clearrubbish"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Cursor"}
//            SetBtn {iconName: "searchtrojan.png"; method: "Font"; text: "searchtrojan"}
//            SetBtn {iconName: "computerclinic.png"; method: "WindowControls"; text: "computerclinic"}
//        }
//        //---------------------皮肤设置end---------------------


//        //---------------------系统设置start---------------------
//        Row {
//            Image {
//                id: refreshArrow3
//                source: "../img/icons/about.png"
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Text {
//                id: text3
//                width: 69
//                height: 20
//                text: qsTr("System")
//                font.bold: true
//                font.pointSize: 13
//                font.pixelSize: 12
//            }
//        }
//        Row {
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            spacing: 25
//            SetBtn {iconName: "homepage.png"; method: "DesktopIcons"; text: "desktopIcons"}
//            SetBtn {iconName: "clearrubbish.png"; method: "Security"; text: "security"}
//            SetBtn {iconName: "optimalacceleration.png"; method: "Scrolling"; text: "scrolling"}
//        }
//        //---------------------系统设置end---------------------
//    }//Column

//}//Item
