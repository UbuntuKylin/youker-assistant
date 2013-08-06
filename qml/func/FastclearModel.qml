import QtQuick 1.1
//import SessionType 0.1
import SystemType 0.1
import "common" as Common
Rectangle {
    id: fastmode
//    width: 650; height: 435
    width: parent.width
    height: 435
    property string onekeypage: "second"


    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkSecond: {
            console.log("begin LeftPage Second onOneKeyFinishCleanWork..............");
            console.log(msg);
            if (msg == "") {
                onekeybtn.enabled=true;
            }
            else if (msg == "h") {
                historystatus.state = "StatusH";
                onekeybtn.enabled=true;
            }
            else if (msg == "k") {
               cookiestatus.state = "StatusK";
                onekeybtn.enabled=true;
            }
            else if (msg == "u") {
                unneedstatus.state = "StatusU";
                onekeybtn.enabled=true;
            }
            else if (msg == "c") {
                cachestatus.state = "StatusC";
                onekeybtn.enabled=true;
            }

            else if (msg == "he") {
                historystatus.state = "StatusH1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ke") {
                cookiestatus.state = "StatusK1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ue") {
                unneedstatus.state = "StatusU1";
                onekeybtn.enabled=true;
            }
            else if (msg == "ce") {
                cachestatus.state = "StatusC1";
                onekeybtn.enabled=true;
            }
        }
    }


    //背景
    Image {
        source: "../img/skin/bg-onekey.png"
        anchors.fill: parent
    }

    //上下分割条
    Rectangle {id: splitbar1; x: 2; y: 80; width: 650-2; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar2; x: 2; y: 82; width: 650-2; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar3; x: 2; y: 140; width: 650-2; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar4; x: 2; y: 142; width: 650-2; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar5; x: 2; y: 204; width: 650-2; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar6; x: 2; y: 206; width: 650-2; height: 1; color: "#fafcfe" }

    Rectangle {id: splitbar7; x: 2; y: 268; width: 650-2; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar8; x: 2; y: 270; width: 650-2; height: 1; color: "#fafcfe" }

    Rectangle {x: 652; y: 140; width: 200-8; height: 1; color: "#b9c5cc" }
    Rectangle {x: 654; y: 142; width: 200-8; height: 1; color: "#fafcfe" }
    //-------------------

    //左右分割条
    Rectangle {x: 650; height: parent.height; width: 1; color: "#b9c5cc" }
    Rectangle {x: 652; height: parent.height; width: 1; color: "#fafcfe" }

    Row {

        Column {
//            anchors.fill: parent
            width: 650
            Row {
                id: myrow
                spacing: 10
                anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//                Image {
//                    id: refreshArrow
//                    source: "../img/toolWidget/ubuntukylin.png"
//                    width: 50; height: 50
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
                AnimatedImage {
                    id: refreshArrow
                    source: "../img/toolWidget/clear-movie.gif"
                }
                Column {
                    spacing: 10
                    id: mycolumn
                    Text {
                        id: text0
                        width: 69
                        text: qsTr("全面清理电脑中的垃圾、缓存和痕迹，只需要一个按键！")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Text {
                        id: text
                        width: 69
    //                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
                        text: qsTr("一键帮您节省磁盘空间，清理电脑中的垃圾，让系统运行更加快速。")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                SetBtn {
                    id: onekeybtn
                    iconName: "onekey.png"
                    setbtn_flag: "smallonekey"
                    anchors {
                        left: parent.left; leftMargin: 480
                    }
                    width: 120
                    height: 39
                }

            }//Row


            Column {
                anchors.top: parent.top
                anchors.topMargin: 110
                Item {
                    id: views
                    width: parent.width ////ListView不会随鼠标上下移动
        //                width:fastmode.width -10 //ListView会随鼠标上下移动
                    height: fastmode.height - refreshArrow.height - 10*2 - 20 -10
//                    anchors.top: parent.top
//                    anchors.topMargin: 110

                    ListModel {
                        id: clearModel
                        ListElement {
                            titlename: "清理垃圾"
                            picturename: "../img/toolWidget/brush.png"
                            detailstr: "清理系统中的垃圾文件，释放磁盘空间"
                            clearflag: "cache"
                        }
                        ListElement {
                            titlename: "清理历史记录"
                            picturename: "../img/toolWidget/eraser.png"
                            detailstr: "清理上网时留下的历史记录，保护您的个人隐私"
                            clearflag: "history"
                        }
                        ListElement {
                            titlename: "清理Cookies"
                            picturename: "../img/toolWidget/firefox.png"
                            detailstr: "清理上网时产生的Cookies，还浏览器一片天空"
                            clearflag: "cookies"
                        }
                        ListElement {
                            titlename: "卸载不必要的程序"
                            picturename: "../img/toolWidget/deb.png"
                            detailstr: "清理软件安装过程中安装的依赖程序，提高系统性能"
                            clearflag: "unneed"
                        }
                    }

                    ListView {
                        id: listView
                        height: parent.height
                        width: parent.width
                        anchors.top: parent.top
        //                    anchors.topMargin: titlebar.height + 45
                        model: clearModel
                        delegate: FastDelegate {pagenum: fastmode.onekeypage}//"second"
                        cacheBuffer: 1000
                    }
                }
            }

        }//Column


        Rectangle {
            width: parent.width - 650
            anchors {
               left: parent.left
               leftMargin: 650
            }
//            Image {
//                id: titleimage
//                anchors {
//                    left: parent.left
//                    leftMargin: 2
//                }
//                source: "../img/skin/note-bg.png"
//            }
//            Text {
//                anchors {
//                    left: parent.left
//                    leftMargin: 50
//                    top: parent.top
//                    topMargin: titleimage.height/2 - 7
//                }
//                text: "正在研发测试中..."
//                font.pixelSize: 12
//                color: "#383838"
//            }

            Row {
                spacing: 20
                Column {
                    spacing: 15
                    anchors {
                        top: parent.top
                        topMargin: 30
                        left: parent.left
                        leftMargin: 10
                    }
                    Image {
                        id: clearpic
                        source: "../img/toolWidget/clear-pic.png"
                    }
                    Image {
                        id: startpic
                        source: "../img/toolWidget/open.png"
                    }
                }

                Column {
                    spacing: 5
                    anchors {
                        top: parent.top
                        topMargin: 30
//                        left: parent.left
//                        leftMargin: 10
                    }
                    Text {
                        id: titletext
                        text: "定时清理"
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Text {
                        id: text1
                        text: "定时清理帮您清理电脑"
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                    Text {
                        id: text2
                        text: "中的垃圾和痕迹,让您的"
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                    Text {
                        id: text3
                        text: "系统运行更加流畅!"
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }



//                Text {
//                    id: nextclear
//                    text: "距离下次清理"
//                    font.bold: true
//                    font.pixelSize: 14
//                    color: "#383838"
//                }


                Image {
                    id: titleimage
                    anchors {
                        top: parent.top
                        topMargin: 145
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
                        topMargin: 158//titleimage.height/2 - 7
                    }
                    text: "正在研发测试中..."
                    font.pixelSize: 12
                    color: "#383838"
                }
            }


        }



        Image {
            id: cachestatus
            source: "../img/toolWidget/unfinish.png"
            anchors {
                top: parent.top; topMargin: 100
                left: parent.left; leftMargin: 550
            }
            states: [
                    State {
                    name: "StatusC"
                    PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
                },

                    State {
                    name: "StatusC1"
                    PropertyChanges { target: cachestatus; source: "../img/toolWidget/open.png"}
                }
            ]
        }
        Image {
            id: historystatus
            source: "../img/toolWidget/unfinish.png"
            anchors {
                top: parent.top; topMargin: 164
                left: parent.left; leftMargin: 550
            }
            states: [
                    State {
                    name: "StatusH"
                    PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
                },

                    State {
                    name: "StatusH1"
                    PropertyChanges { target: historystatus; source: "../img/toolWidget/open.png"}
                }
            ]
        }
        Image {
            id: cookiestatus
            source: "../img/toolWidget/unfinish.png"
            anchors {
                top: parent.top; topMargin: 228
                left: parent.left; leftMargin: 550
            }
            states: [
                    State {
                    name: "StatusK"
                    PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
                },

                    State {
                    name: "StatusK1"
                    PropertyChanges { target: cookiestatus; source: "../img/toolWidget/open.png"}
                }
            ]
        }
        Image {
            id: unneedstatus
            source: "../img/toolWidget/unfinish.png"
            anchors {
                top: parent.top; topMargin: 290
                left: parent.left; leftMargin: 550
            }
            states: [
                    State {
                    name: "StatusU"
                    PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
                },

                    State {
                    name: "StatusU1"
                    PropertyChanges { target: unneedstatus; source: "../img/toolWidget/open.png"}
                }

            ]
        }


    }//Row


//    states: [
//        State {
//            name: "StatusEmpty"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/unfinish.png"}
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/unfinish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/unfinish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/unfinish.png"}
//        },
//        State {
//            name: "StatusH"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusK"
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusU"
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}

//        },
//        State {
//            name: "StatusC"
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHK"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHU"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHC"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusKU"
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusKC"
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusUC"
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHKU"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHKC"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusHUC"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusKUC"
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        },
//        State {
//            name: "StatusOver"
//            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cookiestatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: unneedstatus; source: "../img/toolWidget/finish.png"}
//            PropertyChanges { target: cachestatus; source: "../img/toolWidget/finish.png"}
//        }
//    ]



}//坐边栏Rectangle



//Item {
//    id: screen; width: parent.width; height: 435
////    frame:false
//    property SystemDispatcher dis: systemdispatcher
//    property bool inListView : false

//    Rectangle {
//        id: background
//        anchors.fill: parent
//        Item {
//            id: views
//            width: parent.width
//            height: parent.height - titlebar.height

//            ListModel {
//                id: clearModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                    flag: "cache"
//                }
//                ListElement {
//                    title: "清理历史记录"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理浏览器的历史记录，还浏览器一片天空"
//                    flag: "history"
//                }
//                ListElement {
//                    title: "清理Cookies"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的Cookies，保护个人隐私"
//                    flag: "cookies"
//                }
//                ListElement {
//                    title: "卸载不必要的安装程序"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理软件安装过程中安装的依赖程序，提高系统性能"
//                    flag: "unneed"
//                }
//            }

//            ListView {
//                id: listView
//                height: parent.height// - titlebar.height
//                width: parent.width
//                anchors.top: parent.top
//                anchors.topMargin: titlebar.height + 45
//                model: clearModel
//                delegate: FastDelegate {}
//                cacheBuffer: 1000
//            }
//        }


//        Row {
//            id: myrow
//            spacing: 10
//            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//            Image {
//                id: refreshArrow
//                source: "../img/toolWidget/ubuntukylin.png"
////                width: 120; height: 120
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
//            Column {
//                spacing: 10
//                id: mycolumn
//                Text {
//                    id: text0
//                    width: 69
//                    text: qsTr("一键清理系统垃圾，有效提高系统运行效率")
//                    font.bold: true
//                    font.pixelSize: 14
//                    color: "#383838"
////                    font.pointSize: 13
////                    font.pixelSize: 12
//    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                }
//                Text {
//                    id: text1
//                    width: 69
////                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
//                    text: qsTr("       一键清理将会直接清理掉下面四个勾选项的内容,如果您不想直接清理掉某项")
//                    font.pixelSize: 12
//                    color: "#7a7a7a"
////                    font.pointSize: 13
////                    font.pixelSize: 12
//    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                }
//                Text {
//                    id: text2
//                    width: 69
////                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
//                    text: qsTr("内容,请去掉该项的勾选框,进入系统清理页面进行更细致地选择性清理。")
//                    font.pixelSize: 12
//                    color: "#7a7a7a"
////                    font.pointSize: 13
////                    font.pixelSize: 12
//    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//                }
//                SetBtn {
//                    iconName: "onekeyBtn.png"
//                    setbtn_flag: "onekey"
//                    anchors {
//                        top: text2.bottom; topMargin: 10
//                        left: parent.left; leftMargin: 100
//                    }
//                    width: 186
//                    height: 45
//                }
//            }
//        }//Row

////        //垃圾清理自定义标题栏
////        Common.TitleBar {
////            id: titlebar; width: parent.width; height: 45; opacity: 0.9
////            btn_flag: "one_key_scan"
////        }
//    }
//}




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
//        Common.TitleBar {
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
