import QtQuick 1.1
//import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1

import "common" as Common
Item {
    id: screen; width: parent.width; height: 420
//    frame:false
    property SystemDispatcher dis: systemdispatcher
    property bool inListView : false

    Rectangle {
        id: background
        anchors.fill: parent
//        color: "white"
        Item {
            id: views
            width: parent.width
            height: parent.height - titlebar.height

            ListModel {
                id: clearModel
                ListElement {
                    title: "清理垃圾"
                    picture: "../img/icons/user.png"
                    detailstr: "清理系统垃圾，让系统运行跟流畅"
                    flag: "rubbish"
                }
                ListElement {
                    title: "清理历史记录"
                    picture: "../img/icons/at.png"
                    detailstr: "清理使用计算机时留下的历史记录，保护个人隐私"
                    flag: "history"
                }
                ListElement {
                    title: "清理Cookies"
                    picture: "../img/icons/at.png"
                    detailstr: "清理使用计算机时留下的Cookies，保护个人隐私"
                    flag: "cookie"
                }
                ListElement {
                    title: "清理插件"
                    picture: "../img/icons/pen.png"
                    detailstr: "清理电脑日常使用中下载的插件，提高系统性能"
                    flag: "plugin"
                }
            }

            ListView {
                id: listView
                height: parent.height - titlebar.height
                width: parent.width
                anchors.top: parent.top
                anchors.topMargin: titlebar.height + 45
                model: clearModel
                delegate: FastDelegate {}
                cacheBuffer: 1000
            }
        }

        //垃圾清理自定义标题栏
        Common.MyTitleBar {
            id: titlebar; width: parent.width; height: 45; opacity: 0.9
            btn_flag: "one_key_scan"
        }
    }
}




//import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import RegisterMyType 0.1

//import "common" as Common

//Item {
//    id: screen; width: 320; height: 480
//    property Dispatcher dis: mydispather
//    property bool inListView : false

//    Rectangle {
//        id: background
//        anchors.fill: parent; color: "white"
//        Item {
//            id: views
//            width: parent.width
//            anchors.top: parent.top
//            anchors.topMargin: titleBar.height + 110
//            anchors.bottom: toolBar.top
//            ListModel {
//                id: clearModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                }
//                ListElement {
//                    title: "清理痕迹"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                }
//                ListElement {
//                    title: "清理注册表"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                }
//            }
//            ListModel {
//                id: scanModel
//                ListElement {
//                    title: "清理垃圾scan"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                }
//                ListElement {
//                    title: "清理痕迹scan"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                }
//                ListElement {
//                    title: "清理注册表scan"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                }
//            }

//            //默认情况下显示这个ListView:垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height - titlebar.height
//                width: parent.width
//                model: clearModel
//                delegate: FastDelegate {}
//                cacheBuffer: 1000
//            }

//            //当screen.inListView == true时，显示这个listview
//            ListView {
//                id: scanlistView
//                height: parent.height - titlebar.height
//                width: parent.width
//                x: -(parent.width * 1.5)
//                model: scanModel
//                delegate: FastDelegate {}
//                cacheBuffer: 1000
//            }

//            Scrollbar {
//                flickableItem: listView
//                align: Qt.AlignTrailing
//            }

//            //页面变化，当screen.inListView == true时，用scanlistView替换listView页面
//            states: State {
//                name: "ListView"; when: screen.inListView == true
//                PropertyChanges { target: scanlistView; x: 0 }
//                PropertyChanges { target: listView; x: -(parent.width * 1.5) }
//            }

//            //动画效果
//            transitions: Transition {
//                NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//            }

//            Common.RotateDetails { id: rotateDetails; width: parent.width; anchors.left: views.right; height: parent.height }

//            Item { id: foreground; anchors.fill: parent }
//        }

//        //标题栏
////        Common.RotateTitleBar { id: titleBar; width: parent.width; height: 40; y: 80; opacity: 0.9 }
//        //垃圾清理自定义标题栏
//        Common.MyTitleBar {
//            id: titleBar; width: parent.width; height: 45; y: 80; opacity: 0.9}

//        //工具栏
//        Common.ToolBar {
//            id: toolBar
//            height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("无效")
//            button2Label: qsTr("页面切换测试")
//            onButton1Clicked: {

//            }
//            onButton2Clicked: {
//                if (screen.inListView == true) screen.inListView = false; else screen.inListView = true
//            }
//        }

//        states: State {
//            name: "DetailedView"
//            PropertyChanges { target: views; x: -parent.width }
//            PropertyChanges { target: toolBar; button1Label: qsTr("开始翻转") }
//            PropertyChanges {
//                target: toolBar
//                onButton1Clicked: if (rotateDetails.state=='') rotateDetails.state='Back'; else rotateDetails.state=''
//            }
//            PropertyChanges { target: toolBar; button2Label: qsTr("返回列表") }
//            PropertyChanges { target: toolBar; onButton2Clicked: rotateDetails.closed() }
//        }

//        transitions: Transition {
//            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//        }
//    }
//}




//Item {
//    id: fastitem
//    property Dispatcher dis: mydispather
//    ListModel {
//        id: clearModel
//        ListElement {
//            title: "清理垃圾"
//            picture: "../img/icons/user.png"
//            detailstr: "清理系统垃圾，让系统运行跟流畅"
//        }
//        ListElement {
//            title: "清理痕迹"
//            picture: "../img/icons/at.png"
//            detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//        }
//        ListElement {
//            title: "清理注册表"
//            picture: "../img/icons/pen.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//        }
//    }

//    Column {
//        anchors.fill: parent
//        //垃圾清理自定义标题栏
//        Common.TitleBar {
//            id: titlebar
//            anchors.top: parent.top
//            anchors.topMargin: 80
//            width: parent.width
//            height: 45
//            opacity: 0.9
//        }

//        //垃圾清理显示内容
//        ListView {
//            id: listView
//            height: fastitem.height - titlebar.height
//            width: fastitem.width
////            focus: true
//            anchors.fill: parent
//            anchors.top: titlebar.bottom
//            anchors.topMargin: 130
////            highlight: Rectangle { color: "white" }
//            model: clearModel
//            delegate: FastDelegate {}
//        }
//        Scrollbar {
//            flickableItem: listView
//            align: Qt.AlignTrailing
//        }
////        ScrollBar {
////            scrollArea: listView; height: listView.height; width: 8
////            anchors.right: listView.right
////        }
//    }
//}












//Item {
//    id: fastitem
//    property Dispatcher dis: mydispather

//    Column {
//        anchors.fill: parent

//        //垃圾清理自定义标题栏
//        TitleBar {
//            id: titlebar
//            anchors.top: parent.top
//            anchors.topMargin: 80
//            width: parent.width
//            height: 45
//            opacity: 0.9
//        }

//        //垃圾清理显示内容
//        Rectangle {
//            anchors {fill: parent; top: parent.top; topMargin: 133}
//            Component {
//                id: clearDelegate
//                Item {
//                    width: listView.width
//                    height: 65
//                    //checkbox, picture and words
//                    Rectangle {
//                        id: lineLayout
//                        anchors {
//                            fill: parent
//                            left: parent.left
//                            leftMargin: 50
//                        }
//                        height: clearImage.height; width: parent.width
////                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: lineLayout.top; topMargin: 15 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }

//                        Image {
//                            id: clearImage
//                            anchors { top: lineLayout.top; topMargin: 8 }
//                            width: 47; height: 47
//                            source: picture
//                            anchors { left: parent.left; leftMargin: 45}

//                        }

//                        Column {
//                            spacing: 5
//                            anchors {
//                                top: parent.top; topMargin: 15
//                                left: clearImage.right; leftMargin: 15}
//                            Text {
//                                text: title
//                                font.pointSize: 11
//                                color: "black"
//                            }
//                            Text {
//                                text: detailstr
//                                font.pointSize: 9
//                                color: "gray"
//                            }
//                        }
//                    }
//                    ListItem.ThinDivider {} //分割条  can be used as header for list
//                }
//            }
//            ListModel {
//                id: clearModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                }
//                ListElement {
//                    title: "清理痕迹"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                }
//                ListElement {
//                    title: "清理注册表"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                }
//            }
//            ListView {
//                id: listView
//                anchors.fill: parent
//                model: clearModel
//                delegate: clearDelegate
//            }
//        }
//    }
//}

//Rectangle {
//    height: 460
//    property Dispatcher dis: mydispather
//    Page {
//        Item {
//            Column {
//                spacing: 5

//                TitleBar { id: titleBar; width: parent.width; height: 45; opacity: 0.9 }

//                Rectangle {
//                    anchors {fill: parent; top: parent.top; topMargin: 52}
//                    Component {
//                        id: clearDelegate
//                        Item {
//                            width: listView.width
//                            height: 65
//                            //checkbox, picture and words
//                            Rectangle {
//                                id: lineLayout
//                                anchors {
//                                    fill: parent
//                                    left: parent.left
//                                    leftMargin: 50
//                                }
//                                height: clearImage.height; width: parent.width
//        //                        spacing: 10

//                                CheckBox {
//                                    checked: true
//                                    anchors { top: lineLayout.top; topMargin: 15 }
//                                    onCheckedChanged: {
//                                        //kobe: wait for adding function
//                                    }
//                                }

//                                Image {
//                                    id: clearImage
//                                    anchors { top: lineLayout.top; topMargin: 8 }
//                                    width: 47; height: 47
//                                    source: picture
//                                    anchors { left: parent.left; leftMargin: 45}

//                                }

//                                Column {
//                                    spacing: 5
//                                    anchors {
//                                        top: parent.top; topMargin: 15
//                                        left: clearImage.right; leftMargin: 15}
//                                    Text {
//                                        text: title
//                                        font.pointSize: 11
//                                        color: "black"
//                                    }
//                                    Text {
//                                        text: detailstr
//                                        font.pointSize: 9
//                                        color: "gray"
//                                    }
//                                }
//                            }
//                            ListItem.ThinDivider {} //分割条  can be used as header for list
//                        }
//                    }
//                    ListModel {
//                        id: clearModel
//                        ListElement {
//                            title: "清理垃圾"
//                            picture: "../img/icons/user.png"
//                            detailstr: "清理系统垃圾，让系统运行跟流畅"
//                        }
//                        ListElement {
//                            title: "清理痕迹"
//                            picture: "../img/icons/at.png"
//                            detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                        }
//                        ListElement {
//                            title: "清理注册表"
//                            picture: "../img/icons/pen.png"
//                            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                        }
//                    }
//                    ListView {
//                        id: listView
//                        anchors.fill: parent
//                        model: clearModel
//                        delegate: clearDelegate
//                    }
//                }
//            }
//        }



//    }
//}




//Rectangle {
//    height: 460
//    property Dispatcher dis: mydispather
//    Page {
//        Common.TitleBar { id: titleBar; width: parent.width; height: 45; opacity: 0.9 }
////        Rectangle {
////            anchors {fill: parent; top: parent.top; topMargin: 10; left: parent.left; leftMargin: 30}
////            Column {
////                Text {
////                    text: "一键清理系统垃圾，有效提高系统运行效率"
////                    font.pointSize: 11
////                    color: "black"
////                }
////                Text {
////                    text:  "全面清理垃圾、痕迹、注册表，高效率解决系统清理问题"
////                    font.pointSize: 9
////                    color: "gray"
////                }
////            }
////            Button {
////                id: pluginBtn
////                width: 90
////                color: "gray"
////                anchors {
////                    left: parent.left
////                    leftMargin: 700
////                }
////                text: "一键清理"
////                onClicked: {
////                    //kobe: wait for adding function
////                    mydispather.send_btn_msg("clearfast")
////                    pageStack.pop()
////                    pageStack.push(clearprogress)
////                }
////            }
////        }
////        Rectangle {  //分割条
////            width: parent.width; height: 1
////            anchors { top: parent.top; topMargin: 50}
////            color: "gray"
////        }
////        ListItem.ThinDivider {} //can be used as header for list

//        Rectangle {
//            anchors {fill: parent; top: parent.top; topMargin: 52}
//            Component {
//                id: clearDelegate
//                Item {
//                    width: listView.width
//                    height: 65
//                    //checkbox, picture and words
//                    Rectangle {
//                        id: lineLayout
//                        anchors {
//                            fill: parent
//                            left: parent.left
//                            leftMargin: 50
//                        }
//                        height: clearImage.height; width: parent.width
////                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: lineLayout.top; topMargin: 15 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }

//                        Image {
//                            id: clearImage
//                            anchors { top: lineLayout.top; topMargin: 8 }
//                            width: 47; height: 47
//                            source: picture
//                            anchors { left: parent.left; leftMargin: 45}

//                        }

//                        Column {
//                            spacing: 5
//                            anchors {
//                                top: parent.top; topMargin: 15
//                                left: clearImage.right; leftMargin: 15}
//                            Text {
//                                text: title
//                                font.pointSize: 11
//                                color: "black"
//                            }
//                            Text {
//                                text: detailstr
//                                font.pointSize: 9
//                                color: "gray"
//                            }
//                        }
//                    }
//                    ListItem.ThinDivider {} //分割条  can be used as header for list
//                }
//            }
//            ListModel {
//                id: clearModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                }
//                ListElement {
//                    title: "清理痕迹"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                }
//                ListElement {
//                    title: "清理注册表"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                }
//            }
//            ListView {
//                id: listView
//                anchors.fill: parent
//                model: clearModel
//                delegate: clearDelegate
//            }
//        }
//    }
//}
