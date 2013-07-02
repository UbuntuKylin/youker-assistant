import QtQuick 1.1
import RegisterMyType 0.1
import "common" as Common
Item {
    id: traceitem
    width: parent.width; height: 420
    property Dispatcher dis: mydispather
    Component {
        id: statusDelegate
        RubbishStatus {
            id: content
            width: listView.width//  - units.gu(1)
            height: childrenRect.height + 40
        }
    }
    ListModel {
        id: streamModel
        ListElement {
            title: "上网浏览痕迹"
            picture: "../img/icons/user.png"
            detailstr: "上网时留下的浏览痕迹，支持各种主流浏览器"
            flags: "net_scan"
        }
        ListElement {
            title: "系统使用痕迹"
            picture: "../img/icons/at.png"
            detailstr: "系统运行痕迹，打开文档痕迹等"
            flags: "system_use"
        }
        ListElement {
            title: "常用软件的使用痕迹"
            picture: "../img/icons/pen.png"
            detailstr: "清理系统第三方软件产生的垃圾文件，节约磁盘空间"
            flags: "software_use"
        }
        ListElement {
            title: "USB设备使用痕迹"
            picture: "../img/icons/pen.png"
            detailstr: "U盘、智能手机、数码相机、Mp3等USB设备的使用痕迹"
            flags: "usb_use"
        }
        ListElement {
            title: "办公软件的使用痕迹"
            picture: "../img/icons/pen.png"
            detailstr: "常用办公软件的使用痕迹"
            flags: "office_use"
        }
        ListElement {
            title: "搜索引擎跟踪cookies清理"
            picture: "../img/icons/pen.png"
            detailstr: "防止搜索引擎记录您的搜索行为，避免这些缓存泄漏隐私"
            flags: "cookie_use"
        }
    }

    //垃圾清理显示内容
    ListView {
        id: listView
//            objectName: "listView"
        height: parent.height//traceitem.height - titlebar.height// - units.gu(2)
        width: traceitem.width
//            focus: true
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: titleBar.height + 10

//        opacity: 1
//        spacing: units.gu(1)
        model: streamModel
//        snapMode: ListView.NoSnap
//        cacheBuffer: parent.height
//        boundsBehavior: Flickable.DragOverBounds
//        currentIndex: 0
        delegate: statusDelegate
//        preferredHighlightBegin: 0
//        preferredHighlightEnd: preferredHighlightBegin
//        highlightRangeMode: ListView.StrictlyEnforceRange
    }
//    Scrollbar {
//        flickableItem: listView
//        align: Qt.AlignTrailing
//    }

    //垃圾清理自定义标题栏
    Common.MyTitleBar {
        id: titleBar; width: parent.width; height: 45; opacity: 0.9
        btn_text: "开始扫描"
        title: "清理电脑的痕迹"
        description:  "清理痕迹可以保障电脑的安全和访问速度"
        btn_flag: "traces"
    }

}//Item





//Item {
//    id: rubbishitem
//    property Dispatcher dis: mydispather
//    Component {
//        id: statusDelegate
//        RubbishStatus {
//            id: content
//            width: listView.width//  - units.gu(1)
//            height: childrenRect.height
//        }
//    }
//    ListModel {
//        id: streamModel
//        ListElement {
//            title: "上网浏览痕迹"
//            picture: "../img/icons/user.png"
//            detailstr: "上网时留下的浏览痕迹，支持各种主流浏览器"
//            flags: "net_scan"
//        }
//        ListElement {
//            title: "系统使用痕迹"
//            picture: "../img/icons/at.png"
//            detailstr: "系统运行痕迹，打开文档痕迹等"
//            flags: "system_use"
//        }
//        ListElement {
//            title: "常用软件的使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "清理系统第三方软件产生的垃圾文件，节约磁盘空间"
//            flags: "software_use"
//        }
//        ListElement {
//            title: "USB设备使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "U盘、智能手机、数码相机、Mp3等USB设备的使用痕迹"
//            flags: "usb_use"
//        }
//        ListElement {
//            title: "办公软件的使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "常用办公软件的使用痕迹"
//            flags: "office_use"
//        }
//        ListElement {
//            title: "搜索引擎跟踪cookies清理"
//            picture: "../img/icons/pen.png"
//            detailstr: "防止搜索引擎记录您的搜索行为，避免这些缓存泄漏隐私"
//            flags: "cookie_use"
//        }
//    }

//    //垃圾清理显示内容
//    ListView {
//        id: listView
////            objectName: "listView"
//        height: rubbishitem.height - titlebar.height// - units.gu(2)
//        width: rubbishitem.width
////            focus: true
//        anchors.fill: parent
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 133
////            highlight: Rectangle { color: "white" }
////            anchors {
////                top: updatesBanner.bottom
////                topMargin: 100//units.gu(1)
////            }
//        opacity: 1
//        spacing: units.gu(1)
//        model: streamModel
//        snapMode: ListView.NoSnap
//        cacheBuffer: parent.height
//        boundsBehavior: Flickable.DragOverBounds
//        currentIndex: 0
//        delegate: statusDelegate
//        preferredHighlightBegin: 0
//        preferredHighlightEnd: preferredHighlightBegin
//        highlightRangeMode: ListView.StrictlyEnforceRange
//    }
//    Scrollbar {
//        flickableItem: listView
//        align: Qt.AlignTrailing
//    }

//    //垃圾清理自定义标题栏
//    Common.MyTitleBar {
//        id: titleBar; width: parent.width; height: 45; y: 80; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "清理电脑的痕迹"
//        description:  "清理痕迹可以保障电脑的安全和访问速度"
//        btn_flag: "traces"
//    }

//}//Item








//Item {
//    id: rubbishitem
//    property Dispatcher dis: mydispather
//    Component {
//        id: statusDelegate
//        RubbishStatus {
//            id: content
//            width: listView.width//  - units.gu(1)
//            height: childrenRect.height
//        }
//    }
//    ListModel {
//        id: streamModel
//        ListElement {
//            title: "上网浏览痕迹"
//            picture: "../img/icons/user.png"
//            detailstr: "上网时留下的浏览痕迹，支持各种主流浏览器"
//            flags: "net_scan"
//        }
//        ListElement {
//            title: "系统使用痕迹"
//            picture: "../img/icons/at.png"
//            detailstr: "系统运行痕迹，打开文档痕迹等"
//            flags: "system_use"
//        }
//        ListElement {
//            title: "常用软件的使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "清理系统第三方软件产生的垃圾文件，节约磁盘空间"
//            flags: "software_use"
//        }
//        ListElement {
//            title: "USB设备使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "U盘、智能手机、数码相机、Mp3等USB设备的使用痕迹"
//            flags: "usb_use"
//        }
//        ListElement {
//            title: "办公软件的使用痕迹"
//            picture: "../img/icons/pen.png"
//            detailstr: "常用办公软件的使用痕迹"
//            flags: "office_use"
//        }
//        ListElement {
//            title: "搜索引擎跟踪cookies清理"
//            picture: "../img/icons/pen.png"
//            detailstr: "防止搜索引擎记录您的搜索行为，避免这些缓存泄漏隐私"
//            flags: "cookie_use"
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
//            btn_text: "开始扫描"
//            title: "清理电脑的痕迹"
//            description:  "清理痕迹可以保障电脑的安全和访问速度"
//            btn_flag: "traces"
//        }
//        //垃圾清理显示内容
//        ListView {
//            id: listView
////            objectName: "listView"
//            height: rubbishitem.height - titlebar.height// - units.gu(2)
//            width: rubbishitem.width
////            focus: true
//            anchors.fill: parent
//            anchors.top: titlebar.bottom
//            anchors.topMargin: 133
////            highlight: Rectangle { color: "white" }
////            anchors {
////                top: updatesBanner.bottom
////                topMargin: 100//units.gu(1)
////            }
//            opacity: 1
//            spacing: units.gu(1)
//            model: streamModel
//            snapMode: ListView.NoSnap
//            cacheBuffer: parent.height
//            boundsBehavior: Flickable.DragOverBounds
//            currentIndex: 0
//            delegate: statusDelegate
//            preferredHighlightBegin: 0
//            preferredHighlightEnd: preferredHighlightBegin
//            highlightRangeMode: ListView.StrictlyEnforceRange
//        }
//        Scrollbar {
//            flickableItem: listView
//            align: Qt.AlignTrailing
//        }

//        Item {
//            id: updatesBanner
//            anchors {
//                top: parent.top
//                left: parent.left
//                right: parent.right
//            }
//            visible: true
//            height: visible ? units.gu(3) : 0
//            Text {
//                id: updatesText
//                anchors {
//                    centerIn: parent
//                    bottom: parent.bottom
//                }
//                text: ""
//                font.family: "Ubuntu"
//                font.bold: true
//                font.pointSize: 12
//                color: "gray"
//            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {

//                }
//            }
//        }//Item
//    }//Column
//}//Item







//Rectangle {
//    height: 460
//    property Dispatcher dis: mydispather
//    Page {

//        TitleBar {
//            id: titleBar
//            width: parent.width
//            height: 45
//            opacity: 0.9
//            btn_text: "开始扫描"
//            title: "清理电脑的痕迹"
//            description:  "清理痕迹可以保障电脑的安全和访问速度"
//        }

//        Column {
//            anchors {fill: parent; top: parent.top; topMargin: 52}

//            /*------------上网浏览痕迹-----------*/
//            ListItem.Standard {
//                id: nettraces
//                progression: true
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/settings.png")
////                text: i18n.tr("上网浏览产生的缓存垃圾")
//                Column {
//                    spacing: 5
//                    anchors {
//                        top: parent.top; topMargin: 10
//                        left: parent.left; leftMargin: 80}
//                    Text {
//                        text: "上网浏览痕迹"
//                        font.pointSize: 9
//                        color: "black"
//                    }
//                    Text {
//                        text: "上网时留下的浏览痕迹，支持各种主流浏览器"
//                        font.pointSize: 7
//                        color: "gray"
//                    }
//                }
//                onClicked: netListView.visible = !netListView.visible
//            }
//            Component {
//                id: netDelegate
//                ListItem.Standard {
////                    text: i18n.tr(title)
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/clinic.png")
////                        onClicked: {
////                            netListView.visible = false
////                        }
////                    }
//                    Row {
//                        id: netLayout
//                        anchors {fill: parent; left: parent.left; leftMargin: 50}
//                        height: 38; width: parent.width
//                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: netLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }
//                        Text {
//                            text: title
//                            anchors { top: netLayout.top; topMargin: 8 }
//                            font.pointSize: 9
//                            color: "black"
//                        }
//                    }
//                    iconFrame: true
//                }
//            }

//            ListModel {
//                id: netModel
//                ListElement {
//                    title: "浏览器缓存文件清理"
//                }
//                ListElement {
//                    title: "浏览器自动保存的密码和登录信息（Cookie）"
//                }
//            }

//            ListView {
//                id: netListView
//                width: parent.width
//                height: 38 *2
//                model: netModel
//                delegate: netDelegate
//                visible: false
//            }



//        }
//    }
//}
