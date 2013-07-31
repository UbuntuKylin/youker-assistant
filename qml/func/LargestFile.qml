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
import QtDesktop 0.1
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435//475
    property string btn_text: "开始扫描"
    property string title: "快速找出最占用磁盘空间的大文件"
    property string description: "删除占用磁盘空间的无用大文件，释放更多磁盘空间。"
    property string btn_flag: "largestfile_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""
    //箭头图标
    property string arrow: '../img/icons/arrow.png'
    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"
    //子项字体
    property string subItemFontName: "Helvetica"
    property int subItemFontSize: headerItemFontSize-2
    property color subItemFontColor: "black"
    property bool check_flag: true
    property int itemHeight: 40
//    property alias expandedItemCount: subItemRepeater.count
    property bool expanded: true //kobe:子项扩展默认打开

    property string directory: ""

    signal largestfile_signal(string largestfile_msg);
    onLargestfile_signal: {
        if (largestfile_msg == "LargestFileWork") {
            //get data of largestfile
//            var largestfile_data = systemdispatcher.scan_of_large_qt("/home/kobe");
            var largestfile_data = systemdispatcher.scan_of_large_qt(root.directory);
            root.sub_num = largestfile_data.length;
            systemdispatcher.clear_largestfile_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< largestfile_data.length; i++) {
//                console.log(unneed_data[i]);//linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
                var splitlist = largestfile_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0] + "字节", "desc": splitlist[1]});
                    systemdispatcher.set_largestfile_args(splitlist[1]);
                }
            }
            root.sub_num -= num;
            mainModel.clear();
            console.log(systemdispatcher.get_largestfile_args());
            mainModel.append({"itemTitle": "清理最大文件",
                             "picture": "../img/toolWidget/deb-min.png",
                             "detailstr": "清理用户指定目录下的最大文件，节省磁盘空间",
                             "flags": "clear_largestfile",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })
        }
    }



    ListModel {
        id: mainModel
        ListElement {
            itemTitle: "清理最大文件"
            picture: "../img/toolWidget/deb-min.png"
            detailstr: "清理用户指定目录下的最大文件，节省磁盘空间"
            flags: "clear_largestfile"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }

    }

    ListModel {
        id: subModel
        ListElement {itemTitle: ""; desc: ""}
    }



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
        //             if (btn_flag == "package_scan") {
        //                 console.log("******package_scan Signal handler received  Start******");
        ////                 console.log("33333333333333");
        ////                 console.log(msg);
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "UnneedWork";
        //             }

//         }
        onFinishCleanWork: {
//            console.log("33333333333333");
//            console.log(msg);//apt software   package   history   cookies
//            console.log(btn_flag);
            if (btn_flag == "largestfile_work") {
                if (msg == "largestfile") {
                    console.log("******Clear Signal handler received  Start package_work******");
    //                 console.log(msg);
                    root.work_result = msg;
                    root.state = "LargestFileWorkFinish";
                }
            }
        }
    }

//    //背景
    Image {
        source: "../img/skin/bg-onekey.png"
        anchors.fill: parent
    }


    //titlebar
    Row {
        id: titlebar
        spacing: 20
        width: parent.width
//        height: 50
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/find.gif"
////            width: 50; height: 50
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
        AnimatedImage {
            id: refreshArrow
            source: "../img/toolWidget/find.gif"
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.leftMargin: 30
            spacing: 10
            Text {
                text: root.title
                font.bold: true
                font.pixelSize: 14
            }
            Text {
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }

        //status picture
        Image {
            id: statusImage
            source: "../img/toolWidget/unfinish.png"
            fillMode: "PreserveAspectFit"
            smooth: true
            anchors {
                right: label.left
                rightMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }

        Label {
            id: label
            visible: false
            text: ""
            anchors.right: bitButton.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Button {
            id: bitButton
            width: 120
            height: 39
            hoverimage: "scan-start.png"
//            text: root.btn_text
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                 if (btn_flag == "largestfile_scan") {
                     console.log("largestfile_scan---------------");
                     if (root.directory == "")
                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击‘选择路径’按钮选择！");
                     else {
                         root.state = "LargestFileWork";
                         largestfile_signal("LargestFileWork");
                     }
                 }
                 else if (btn_flag == "largestfile_work") {
                     console.log("largestfile_work---------------");
                     console.log(systemdispatcher.get_largestfile_args());
                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
                 }
            }
        }
    }
    //分割条
    Rectangle {
        id: splitbar
        anchors.top: titlebar.bottom
        anchors.topMargin: 18
        width: parent.width-2
        height: 1
        color: "#b9c5cc"
    }

//    ItemListModel {
//        id: pluginlist
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 20
//        height: parent.height -titlebar.height - 40
//        listmodel: root.listmodel
//        submodel: root.submodel
//        num: root.sub_num
//        btn_flag: root.btn_flag
//    }
    //----------------------------
    Component {
        id: listViewDelegate
        Item {
            id: delegate
            property alias expandedItemCount: subItemRepeater.count
            x: 5; y: 2
            width: root.width
            height: headerItemRect.height + subItemsRect.height

            //母项
            //checkbox, picture and words
            Row {
                id: headerItemRect
                x: 5; y: 2
                width: root.width
                height: root.itemHeight
                spacing: 10
                Image {
                    id: clearImage
                    fillMode: "PreserveAspectFit"
                    height: parent.height*0.9
                    source: picture
                    smooth: true
                }

                Column {
                    id: status_update_content
                    spacing: 5
                    anchors {
                        left: clearImage.right; leftMargin: 15
                        verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: itemTitle
                        font.pointSize: 11
                        color: "black"
                    }
                    Text {
                        text: detailstr
                        font.pointSize: 9
                        color: "gray"
                    }
                }


//                Button {
//                    id: selectBtn
//                    text: "选择路径"
//                    anchors {
//                        left: clearImage.right
//                        verticalCenter: parent.verticalCenter
//                        leftMargin: 650
//                    }
//                    onClicked: {
//                        console.log("select path.....");
//                        root.directory = sessiondispatcher.show_folder_dialog();
//                        console.log("the path is.....");
//                        console.log(root.directory);
//                    }
//                }


                Common.Button {
                    id: selectBtn
                    anchors {
                        left: clearImage.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: 600
                    }
                    hoverimage: "browser-green.png"
                    width: 95
                    height: 30
                    onClicked: {
                        console.log("select path.....");
                        root.directory = sessiondispatcher.show_folder_dialog();
                        console.log("the path is.....");
                        console.log(root.directory);
                    }
                }

                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
                    height: 28
                    width: 26
                    source: root.arrow
                    //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
                    rotation: expanded ? 0 : -180
                    smooth: true
                    anchors {
                        left: clearImage.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: 750
                    }
                }

                MouseArea {
                    id: mouseRegion
                    anchors.fill: status_update_content
                    onPressed: {
//                        console.log(root.width)
                        expanded = !expanded
                    }
                }
            }//母项Row

            //子项
            Item {
                id: subItemsRect
                property int itemHeight: root.itemHeight
                y: headerItemRect.height
                width: root.width
                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
                height: expanded ? delegate.expandedItemCount * itemHeight : 0
                clip: true
                opacity: 1
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Column {
                    width: root.width
                    Repeater {
                        id: subItemRepeater
//                        model: attributes
                        model: subModel
//                        model: mysubmodel
                        width: subItemsRect.width
                        /*Common.*/ListItem {
                            id: subListItem
                            width: root.width
                            height: subItemsRect.itemHeight
//                            text: subItemTitle
                            text: itemTitle
                            descript: desc
//                            size_num: number
                            checkbox_status: root.check_flag
//                            bgImage: "../../img/icons/list_subitem.png"
                            bgImage: ""
                            fontName: root.subItemFontName
                            fontSize: root.subItemFontSize
                            fontColor: root.subItemFontColor
                            textIndent: 20

                            btn_flag: root.btn_flag

                            onClicked: {/*console.log(number)*/}
                        }

                    }//Repeater
                }//Column
            }//子项Item
        }
    }//Component


    ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 30
        height: root.height -titlebar.height - 50
        width: parent.width
        Item {
            width: parent.width
            height: (root.sub_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: listViewDelegate
                cacheBuffer: 1000
                opacity: 1
                spacing: 10
                snapMode: ListView.NoSnap
                boundsBehavior: Flickable.DragOverBounds
                currentIndex: 0
                preferredHighlightBegin: 0
                preferredHighlightEnd: preferredHighlightBegin
                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }//Item
    }//ScrollArea
    //----------------------------

//    //status picture
//    Image {
//        id: statusImage
//        source: "../img/toolWidget/unfinish.png"
//        fillMode: "PreserveAspectFit"
//        smooth: true
//        anchors {
//            top: parent.top; topMargin: 120
//            left: parent.left; leftMargin: 650
//        }
//    }

    states: [
        State {
            name: "LargestFileWork"
            PropertyChanges { target: label; visible: true; text: "largestfile扫描完成"}
//            PropertyChanges { target: bitButton; text: "开始清理" }
            PropertyChanges { target: bitButton; hoverimage: "clear-start.png" }
            PropertyChanges { target: root; btn_flag: "largestfile_work" }
        },
        State {
            name: "LargestFileWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "largestfile_scan" }
            PropertyChanges { target: statusImage; source: "../img/toolWidget/finish.png"}
        }
    ]
}














//Item {
//    id:root
//    width: parent.width
//    height: 435//420//340

//    property string btn_text: "开始扫描"
//    property string title: "卸载不必要的安装程序"
//    property string description: "清理软件安装过程中安装的依赖程序，提高系统性能"
//    property string btn_flag: "package_scan"
//    property SystemDispatcher dis: systemdispatcher
//    property ListModel listmodel: mainModel
//    property ListModel submodel: subModel
//    property int sub_num: 0
//    property string work_result: ""

//    signal unneed_signal(string unneed_msg);
//    onUnneed_signal: {
//        if (unneed_msg == "UnneedWork") {
//            //get data of unneed
//            var unneed_data = systemdispatcher.scan_unneed_packages_qt();

//            root.sub_num = unneed_data.length;
//            systemdispatcher.clear_package_args();
//            subModel.clear();
//            var num = 0;
//            for (var i=0; i< unneed_data.length; i++) {
////                console.log(unneed_data[i]);//linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//                var splitlist = unneed_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2] + "字节"});
//                    systemdispatcher.set_package_args(splitlist[0]);
//                }
//            }
//            root.sub_num -= num;
//            mainModel.clear();
//            console.log("unneed........................");
//            console.log(systemdispatcher.get_package_args());
//            mainModel.append({"itemTitle": "卸载不必要的安装程序",
//                             "picture": "../img/icons/user.png",
//                             "detailstr": "卸载不再需要的安装程序,让系统更瘦",
//                             "flags": "clear_cookies",
//                            "attributes":
//                                 [{"subItemTitle": "Cookies1"},
//                                 {"subItemTitle": "Cookies2"},
//                                 {"subItemTitle": "Cookies3"},
//                                 {"subItemTitle": "Cookies4"}]
//                             })
//        }
//    }



//    ListModel {
//        id: mainModel
//        ListElement {
//            itemTitle: "清理不再需要的安装包"
//            picture: "../img/icons/user.png"
//            detailstr: "不再需要的安装包,让系统更瘦"
//            flags: "clear_package"
//            attributes: [
//                ListElement { subItemTitle: "" }
////                ListElement { subItemTitle: "kobe 2/1" }
//            ]
//        }
////        ListElement {
////            itemTitle: "Item title 2"
////            picture: "../img/icons/user.png"
////            detailstr: "清理deb，让系统更瘦2"
////            flags: "clear_package"
////            attributes: [
////                ListElement { subItemTitle: "kobe 1/3" },
////                ListElement { subItemTitle: "kobe 2/3" },
////                ListElement { subItemTitle: "kobe 3/3" }
////            ]
////        }
////        ListElement {
////            itemTitle: "Item title 3"
////            picture: "../img/icons/user.png"
////            detailstr: "清理deb，让系统更瘦3"
////            flags: "clear_package"
////            attributes: [
////                ListElement { subItemTitle: "kobe 1/4" },
////                ListElement { subItemTitle: "kobe 2/4" },
////                ListElement { subItemTitle: "kobe 3/4" },
////                ListElement { subItemTitle: "kobe 4/4" }
////            ]
////        }
//    }

//    ListModel {
//        id: subModel
//        ListElement {itemTitle: ""; desc: ""; number: ""}
//    }



//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
//        //             if (btn_flag == "package_scan") {
//        //                 console.log("******package_scan Signal handler received  Start******");
//        ////                 console.log("33333333333333");
//        ////                 console.log(msg);
//        //                 titleBar.work_result = msg;
//        //                 titleBar.state = "UnneedWork";
//        //             }

////         }
//        onFinishCleanWork: {
////            console.log("33333333333333");
////            console.log(msg);//apt software   package   history   cookies
////            console.log(btn_flag);
//            if (btn_flag == "package_work") {
//                if (msg == "package") {
//                    console.log("******Clear Signal handler received  Start package_work******");
//    //                 console.log(msg);
//                    root.work_result = msg;
//                    root.state = "UnneedWorkFinish";
//                }
//            }
//        }
//    }


//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 50
//        width: parent.width
//        height: 50
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.leftMargin: 30
////                width: parent.width - 150
//            spacing: 2
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//        Label {
//            id: label
//            visible: false
//            text: ""
//            anchors.right: bitButton.left
//            anchors.rightMargin: 20
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Button {
//            id: bitButton
//            width: 95
//            height: 32
//            text: root.btn_text
//            anchors.right: parent.right
//            anchors.rightMargin: 50
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                 //package cruft
//                  if (btn_flag == "package_scan") {
//                      console.log("package_scan---------------");
//                      root.state = "UnneedWork";
//                      unneed_signal("UnneedWork");
//                  }
//                  else if (btn_flag == "package_work") {
//                      console.log("package_work---------------");
//                      console.log(systemdispatcher.get_package_args());
//                      systemdispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args());
//                  }
//            }
//        }
//    }

//    ItemListModel {
//        id: pluginlist
//        anchors.top: titlebar.bottom
//        height: parent.height -titlebar.height
//        listmodel: root.listmodel
//        submodel: root.submodel
//        num: root.sub_num
//        btn_flag: root.btn_flag
//    }


//    states: [
//        State {
//            name: "UnneedWork"
//            PropertyChanges { target: label; visible: true; text: "unneed扫描完成"}
//            PropertyChanges { target: bitButton; text: "开始清理" }
//            PropertyChanges { target: root; btn_flag: "package_work" }
//        },
//        State {
//            name: "UnneedWorkFinish"
//            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; text: "开始扫描" }
//            PropertyChanges { target: root; btn_flag: "package_scan" }
//        }
//    ]
//}
