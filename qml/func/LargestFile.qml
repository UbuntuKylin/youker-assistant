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
Item {
    id:root
    width: parent.width
    height: 435//475
    property string btn_text: "开始清理"
    property string title: "快速找出最占用磁盘空间的大文件"
    property string description: "删除占用磁盘空间的无用大文件，释放更多磁盘空间。"
    property string scope_desc: "文件的大小范围为1M--20480M，暂不支持中文路径。"
    property string btn_flag: "largestfile_work"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""
    property int lar_num: sub_num
    property int check_num:sub_num
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
    property bool null_flag: false

    property string directory: ""
    property int size: 0
    property int deleget_arrow :0


    function refresh_page() {
        sub_num=0;
        check_num=0
        var largestfile_data = sessiondispatcher.scan_of_large_qt(root.size, root.directory);
        if (largestfile_data == "")
        {
            root.null_flag = true;
            deleget_arrow =0;
        }
        else
        {
            root.null_flag = false;
            deleget_arrow =1;
        }
        root.sub_num = largestfile_data.length;
        systemdispatcher.clear_largestfile_args();
        subModel.clear();
        var num = 0;
        for (var i=0; i< largestfile_data.length; i++) {
            var splitlist = largestfile_data[i].split("<2_2>");
            if (splitlist[0] == "") {
                num++;
            }
            else {
                subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": ""});
                systemdispatcher.set_largestfile_args(splitlist[1]);
            }
        }
        root.sub_num -= num;
        lar_num=sub_num;
        check_num=sub_num;
        if(check_num!=0)
            check_flag=true;

        mainModel.clear();
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
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (btn_flag == "largestfile_work") {
                if (msg == "largestfile") {
                    root.work_result = msg;
                    root.state = "LargestFileWorkError";
                }
            }
         }
        onFinishCleanWork: {
            if (btn_flag == "largestfile_work") {
                if (msg == "largestfile") {
                    root.work_result = msg;
                    root.state = "LargestFileWorkFinish";
                    refresh_page();
                }
            }
        }
    }

//    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }


    //titlebar
    Row {
        id: titlebar
        spacing: 10
        width: parent.width
//        height: 50
        anchors { top: parent.top; topMargin: 10; left: parent.left; leftMargin: 27}
        Image {
            id: refreshArrow
            visible: true
            source: "../img/toolWidget/find.gif"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        AnimatedImage {
            id: refreshArrow_active
            visible: false
            source: "../img/toolWidget/find.gif"
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                text: root.title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                text: root.scope_desc
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
        Text {
            text: "请输入文件大小(M):"
            font.pixelSize: 12
            color: "#383838"
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 50; height: 20
            Image {
                source: "../img/toolWidget/green.png"
                anchors.fill: parent
            }
            TextInput{
                id: size_text
                color: "white"
                anchors.fill: parent
                selectByMouse: true
                selectedTextColor: "gray"
                focus: true
                IntValidator{
                    id: intval
                    bottom: 1
                    top: 20480
                }
                text: "1"
                validator: intval
            }
        }
        Common.StatusImage {
            id: statusImage
            visible: false
            iconName: "yellow.png"
            text: "未完成"
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Button {
            id: selectBtn
            anchors.verticalCenter: parent.verticalCenter
            hoverimage: "blue1.png"
            text: "浏览..."
            width: 95
            height: 30
            onClicked: {
                root.size = size_text.text;
                root.directory = sessiondispatcher.show_folder_dialog();
                if (root.directory != "") {
                    refresh_page();
                    root.state = "LargestFileWorkAgain";
//                    arrow.visible = true;
                }
            }
        }

        Common.Button {
            id: bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                console.log(root.check_flag);
                if(root.check_flag) {
                    if(size_text.text == "")
                        sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有设置扫描文件的大小，请在绿色框中输入数字！", mainwindow.pos.x, mainwindow.pos.y);
                    else if (root.directory == "")
                    {
                        sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击“浏览”按钮选择！", mainwindow.pos.x, mainwindow.pos.y);
                        deleget_arrow =0;
                    }
                    else {
                        if(root.null_flag == true) {
                           root.state = "LargestFileWorkEmpty";
                            sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else if(root.null_flag == false) {
                            systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
                            root.state = "LargestFileWorkFinish";
//                            refresh_page();
                        }
                    }
                }
                else
                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！", mainwindow.pos.x, mainwindow.pos.y)
            }
        }
    }

    //分割条
    Rectangle {
        id: splitbar
        anchors {
            top: titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        height: 1
        color: "#d8e0e6"
    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            property alias expandedItemCount: subItemRepeater.count
//            x: 5; y: 2
//            width: root.width
//            height: headerItemRect.height + subItemsRect.height

//            //母项
//            //checkbox, picture and words
//            Row {
//                id: headerItemRect
//                x: 5; y: 2
//                width: root.width
//                height: root.itemHeight
//                spacing: 300
//                Row{
//                    spacing: 15
//                    Common.MainCheckBox{
//                        id:check
//                        checked:"true"
//                        anchors.verticalCenter: parent.verticalCenter
//                        onCheckedChanged: {
//                        }
//                    }
//                    Image {
//                        id: clearImage
//                        fillMode: "PreserveAspectFit"
//                        height: parent.height*0.9
//                        source: picture
//                        smooth: true
//                    }

//                    Column {
//                        id: status_update_content
//                        spacing: 5
//                        anchors.verticalCenter: parent.verticalCenter
//                        Text {
//                            text: itemTitle
//                            font.pointSize: 11
//                            color: "black"
//                        }
//                        Text {
//                            text: detailstr
//                            font.pointSize: 9
//                            color: "gray"
//                        }
//                    }
//                }
//                Row{
//                    spacing: 40
//                    anchors.verticalCenter: parent.verticalCenter
//                    Common.Button {
//                        id: bitButton
//                        width: 120
//                        height: 39
//                        hoverimage: "green1.png"
//                        text: root.btn_text
//                        anchors.verticalCenter: parent.verticalCenter
//                        onClicked: {
//                            console.log(check.checked);
//                            if(size_text.text == "")
//                                sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有设置扫描文件的大小，请在绿色框中输入数字！");
//                            else if (root.directory == "")
//                                sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击“浏览”按钮选择！");
//                            else if (check.checked == "false")
//                                sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！")
//                            else {
//                                if(root.null_flag == true) {
//                                   root.state = "LargestFileWorkEmpty";
//                                    sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                                }
//                                else if(root.null_flag == false) {
//                                    console.log("cccccccccc");
//                                    console.log(systemdispatcher.get_largestfile_args());
//                                    systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//            //                        sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//                                    root.state = "LargestFileWorkFinish";
//                                }
//                            }
//                        }
//                    }


//                    Image {
//                        id: arrow
//                        fillMode: "PreserveAspectFit"
//    //                    height: parent.height*0.3
//                        height: 28
//                        width: 26
////                        visible: false
//                        source: root.arrow
//                        //当鼠标点击后,箭头图片旋转90度
//    //                    rotation: expanded ? 90 : 0
//                        rotation: expanded ? 0 : -180
//                        smooth: true
//                        anchors.verticalCenter: parent.verticalCenter
//                        MouseArea {
//                            id: mouseRegion
//                            anchors.fill: parent
//                            onPressed: {
//                                expanded = !expanded
//                                if(lar_num==sub_num)
//                                    lar_num=0;
//                                else
//                                    lar_num=sub_num;
//                            }
//                        }
//                    }
//                }

//            }//母项Row

//            //子项
//            Item {
//                id: subItemsRect
//                property int itemHeight: root.itemHeight
//                y: headerItemRect.height
//                width: root.width
//                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
//                height: expanded ? delegate.expandedItemCount * itemHeight : 0
//                clip: true
//                opacity: 1
//                Behavior on height {
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: root.width
//                    Repeater {
//                        id: subItemRepeater
////                        model: attributes
//                        model: subModel
////                        model: mysubmodel
//                        width: subItemsRect.width
//                        ListItem {
//                            id: subListItem
//                            width: root.width
//                            height: subItemsRect.itemHeight
////                            text: subItemTitle
////                            text: desc
////                            descript: itemTitle
//                            text: itemTitle
//                            descript: desc
////                            size_num: number
//                            checkbox_status: check.checkedbool
////                            bgImage: "../../img/icons/list_subitem.png"
//                            bgImage: ""
//                            fontName: root.subItemFontName
//                            fontSize: root.subItemFontSize
//                            fontColor: root.subItemFontColor
//                            textIndent: 20

//                            btn_flag: root.btn_flag

//                            onClicked: {}
//                            onChange_num: {
//                                if(sub_num!=0)
//                                {
//                                    if(check_status==true)
//                                        check_num=check_num+1;
//                                    else
//                                        check_num=check_num-1;
//                                    if(check_num ==0&&check.checked!="false")
//                                        check.checked="false";
//                                    else if(check_num ==sub_num&&check.checked!= "true")
//                                        check.checked="true";
//                                    else
//                                        check.checked="mid";
//                                }
//                                if(check.checked=="true"||check_num>0)
//                                    check_flag=true;
//                                else
//                                    check_flag=false;
//                            }
//                        }

//                    }//Repeater
//                }//Column
//            }//子项Item
//        }
//    }//Component


//    Common.ScrollArea {
//        frame:false
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 30
//        height: root.height -titlebar.height - 50
//        width: parent.width
//        Item {
//            width: parent.width
//            height: (root.lar_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height
//                model: mainModel
//                delegate: listViewDelegate
//                cacheBuffer: 1000
//                opacity: 1
//                spacing: 10
//                snapMode: ListView.NoSnap
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
//            }
//        }//Item
//    }//ScrollArea

    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 30
        anchors.left:parent.left
        anchors.leftMargin: 27
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
                delegate: Cleardelegate{
                    sub_num:root.lar_num;sub_model:subModel;btn_flag:root.btn_flag;arrow_display:deleget_arrow;
                    delegate_flag: false
                    onSubpressed: {root.sub_num=hMark}
                    onCheckchanged: {root.check_flag=checkchange}
                }
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

//    Common.Button {
//        id: bitButton
//        width: 120
//        height: 39
//        hoverimage: "green1.png"
//        text: root.btn_text
////        anchors.verticalCenter: parent.verticalCenter
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 30
//        anchors.right: parent.right
//        anchors.rightMargin: 100
//        onClicked: {
//            console.log(root.check_flag);
//            if(root.check_flag) {
//                if(size_text.text == "")
//                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有设置扫描文件的大小，请在绿色框中输入数字！");
//                else if (root.directory == "")
//                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击“浏览”按钮选择！");
//                else {
//                    if(root.null_flag == true) {
//                       root.state = "LargestFileWorkEmpty";
//                        sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                    }
//                    else if(root.null_flag == false) {
//                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//    //                        sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//                        root.state = "LargestFileWorkFinish";
//                    }
//                }
//            }
//            else
//                sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！")
//        }
//    }


    states: [
        State {
            name: "LargestFileWorkAgain"
            PropertyChanges { target: statusImage; iconName: "yellow.png"; text: "未完成"}
        },
        State {
            name: "LargestFileWorkError"
            PropertyChanges { target: statusImage; iconName: "red.png"; text: "出现异常"}
        },
        State {
            name: "LargestFileWorkFinish"
            PropertyChanges { target: statusImage; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "LargestFileWorkEmpty"
            PropertyChanges { target: statusImage; iconName: "green.png"; text: "已完成"}
        }
    ]
}




//Item {
//    id:root
//    width: parent.width
//    height: 435//475
//    property string btn_text: "开始清理"
//    property string title: "快速找出最占用磁盘空间的大文件"
//    property string description: "删除占用磁盘空间的无用大文件，释放更多磁盘空间。"
//    property string btn_flag: "largestfile_work"
//    property SystemDispatcher dis: systemdispatcher
//    property ListModel listmodel: mainModel
//    property ListModel submodel: subModel
//    property int sub_num: 0
//    property string work_result: ""
//    property int lar_num: sub_num
//    property int check_num:sub_num
//    //箭头图标
//    property string arrow: '../img/icons/arrow.png'
//    //母项字体
//    property string headerItemFontName: "Helvetica"
//    property int headerItemFontSize: 12
//    property color headerItemFontColor: "black"
//    //子项字体
//    property string subItemFontName: "Helvetica"
//    property int subItemFontSize: headerItemFontSize-2
//    property color subItemFontColor: "black"
//    property bool check_flag: true
//    property int itemHeight: 40
////    property alias expandedItemCount: subItemRepeater.count
//    property bool expanded: true //kobe:子项扩展默认打开
//    property bool null_flag: false

//    property string directory: ""


//    function refresh_page() {
//        sub_num=0;
//        check_num=0
////        var largestfile_data = systemdispatcher.scan_of_large_qt(root.directory);
//        var largestfile_data = sessiondispatcher.scan_of_large_qt(root.directory);
//        if (largestfile_data == "")
//            root.null_flag = true;
//        else
//            root.null_flag = false;
//        root.sub_num = largestfile_data.length;
//        systemdispatcher.clear_largestfile_args();
//        subModel.clear();
//        var num = 0;
//        for (var i=0; i< largestfile_data.length; i++) {
//        //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//            var splitlist = largestfile_data[i].split("<2_2>");
//            if (splitlist[0] == "") {
//                num++;
//            }
//            else {
//                subModel.append({"itemTitle": splitlist[0] + "字节", "desc": splitlist[1]});
//                systemdispatcher.set_largestfile_args(splitlist[1]);
//            }
//        }
//        root.sub_num -= num;
//        lar_num=sub_num;
//        check_num=sub_num;
//        if(check_num!=0)
//            check_flag=true;

//        mainModel.clear();
//        mainModel.append({"itemTitle": "清理最大文件",
//                         "picture": "../img/toolWidget/deb-min.png",
//                         "detailstr": "清理用户指定目录下的最大文件，节省磁盘空间",
//                         "flags": "clear_largestfile",
//                        "attributes":
//                             [{"subItemTitle": "Cookies1"},
//                             {"subItemTitle": "Cookies2"},
//                             {"subItemTitle": "Cookies3"},
//                             {"subItemTitle": "Cookies4"}]
//                         })
//    }


//    ListModel {
//        id: mainModel
//        ListElement {
//            itemTitle: "清理最大文件"
//            picture: "../img/toolWidget/deb-min.png"
//            detailstr: "清理用户指定目录下的最大文件，节省磁盘空间"
//            flags: "clear_largestfile"
//            attributes: [
//                ListElement { subItemTitle: "" }
//            ]
//        }

//    }

//    ListModel {
//        id: subModel
//        ListElement {itemTitle: ""; desc: ""}
//    }



//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
//        //             if (btn_flag == "package_scan") {
//        //                 titleBar.work_result = msg;
//        //                 titleBar.state = "UnneedWork";
//        //             }

////         }
//        onFinishCleanWork: {
//            if (btn_flag == "largestfile_work") {
//                if (msg == "largestfile") {
//                    root.work_result = msg;
//                    root.state = "LargestFileWorkFinish";
//                }
//            }
//        }
//    }

////    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }


//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 20
//        width: parent.width
////        height: 50
//        anchors { top: parent.top; topMargin: 10; left: parent.left; leftMargin: 20 }
////        Image {
////            id: refreshArrow
////            source: "../img/toolWidget/find.gif"
//////            width: 50; height: 50
////            Behavior on rotation { NumberAnimation { duration: 200 } }
////        }
//        AnimatedImage {
//            id: refreshArrow
//            source: "../img/toolWidget/find.gif"
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }

//        //status picture
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20
////        Image {
////            id: statusImage
////            source: "../img/toolWidget/unfinish.png"
////            fillMode: "PreserveAspectFit"
////            smooth: true
////            anchors.verticalCenter: parent.verticalCenter
////        }
//        Common.StatusImage {
//            id: statusImage
//            iconName: "yellow.png"
//            text: "未完成"
//            anchors.verticalCenter: parent.verticalCenter
//        }

//        Common.Label {
//            id: label
//            visible: false
//            text: ""
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
//            hoverimage: "green1.png"
//            text: root.btn_text
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if (root.directory == "")
//                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击“浏览”按钮选择！");
//                else {
//                    if(root.null_flag == true) {
//                       root.state = "LargestFileWorkEmpty";
//                        sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                    }
//                    else if(root.null_flag == false) {
//                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
////                        sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//                        root.state = "LargestFileWorkFinish";
//                    }
//                }
//            }
//        }

////        Common.Button {
////            id: bitButton
////            width: 120
////            height: 39
//////            hoverimage: "clear-start.png"
////            text:"开始清理"
////            textsize: 12
////            bold:true
////            anchors.verticalCenter: parent.verticalCenter
////            onClicked: {
////                if(root.check_flag)
////                {
////                    if (root.directory == "")
////                        sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择扫描路径，请点击“浏览”按钮选择！");
////                    else {
////                        if(root.null_flag == true) {
////                           root.state = "LargestFileWorkEmpty";
////                            sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
////                        }
////                        else if(root.null_flag == false) {
////                            systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
////    //                        sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
////                            root.state = "LargestFileWorkFinish";
////                        }
////                    }
////                }
////                else
////                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！");
////            }
////        }
//    }
//    //分割条
//    Rectangle {
//        id: splitbar
//        anchors {
//            top: titlebar.bottom
//            topMargin: 18
//            left: parent.left
//            leftMargin: 2
//        }
//        width: parent.width - 4
//        height: 1
//        color: "#b9c5cc"
//    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            property alias expandedItemCount: subItemRepeater.count
//            x: 5; y: 2
//            width: root.width
//            height: headerItemRect.height + subItemsRect.height

//            //母项
//            //checkbox, picture and words
//            Row {
//                id: headerItemRect
//                x: 5; y: 2
//                width: root.width
//                height: root.itemHeight
//                spacing: 335
//                Row{
//                    spacing: 15
//                    Common.MainCheckBox{
//                        id:check
//                        checked:"true"
//                        anchors.verticalCenter: parent.verticalCenter
//                        onCheckedChanged: {
//                        }
//                    }
//                    Image {
//                        id: clearImage
//                        fillMode: "PreserveAspectFit"
//                        height: parent.height*0.9
//                        source: picture
//                        smooth: true
//                    }

//                    Column {
//                        id: status_update_content
//                        spacing: 5
//                        anchors.verticalCenter: parent.verticalCenter
//                        Text {
//                            text: itemTitle
//                            font.pointSize: 11
//                            color: "black"
//                        }
//                        Text {
//                            text: detailstr
//                            font.pointSize: 9
//                            color: "gray"
//                        }
//                    }
//                }
//                Row{
//                    spacing: 40
//                    anchors.verticalCenter: parent.verticalCenter
//                    Common.Button {
//                        id: selectBtn
//                        anchors.verticalCenter: parent.verticalCenter
//                        hoverimage: "blue1.png"
//                        text: "浏览..."
//                        width: 95
//                        height: 30
//                        onClicked: {
//                            root.directory = sessiondispatcher.show_folder_dialog();
//                            if (root.directory != "") {
//                                refresh_page();
//                                root.state = "LargestFileWorkAgain";
//                            }
//                        }
//                    }

////                    Common.Button {
////                        id: selectBtn
////                        anchors.verticalCenter: parent.verticalCenter
//////                        hoverimage: "browser-green.png"
////                        text:"浏览"
////                        color1: "#acdbf9"
////                        color2: "#7cb9e5"
////                        bordercolor: "#89b5d0"
////                        textsize: 11
////                        width: 95
////                        height: 30
////                        onClicked: {
////                            if(root.check_flag)
////                            {
////                                root.directory = sessiondispatcher.show_folder_dialog();
////                                if (root.directory != "") {
////                                    refresh_page();
////                                    root.state = "LargestFileWorkAgain";
////                                }
////                            }
////                            else
////                                sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要浏览的项，请确认！");
////                        }
////                    }

//                    Image {
//                        id: arrow
//                        fillMode: "PreserveAspectFit"
//    //                    height: parent.height*0.3
//                        height: 28
//                        width: 26
//                        source: root.arrow
//                        //当鼠标点击后,箭头图片旋转90度
//    //                    rotation: expanded ? 90 : 0
//                        rotation: expanded ? 0 : -180
//                        smooth: true
//                        anchors.verticalCenter: parent.verticalCenter
//                        MouseArea {
//                            id: mouseRegion
//                            anchors.fill: parent
//                            onPressed: {
//                                expanded = !expanded
//                                if(lar_num==sub_num)
//                                    lar_num=0;
//                                else
//                                    lar_num=sub_num;
//                            }
//                        }
//                    }
//                }

//            }//母项Row

//            //子项
//            Item {
//                id: subItemsRect
//                property int itemHeight: root.itemHeight
//                y: headerItemRect.height
//                width: root.width
//                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
//                height: expanded ? delegate.expandedItemCount * itemHeight : 0
//                clip: true
//                opacity: 1
//                Behavior on height {
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: root.width
//                    Repeater {
//                        id: subItemRepeater
////                        model: attributes
//                        model: subModel
////                        model: mysubmodel
//                        width: subItemsRect.width
//                        ListItem {
//                            id: subListItem
//                            width: root.width
//                            height: subItemsRect.itemHeight
////                            text: subItemTitle
////                            text: desc
////                            descript: itemTitle
//                            text: itemTitle
//                            descript: desc
////                            size_num: number
//                            checkbox_status: check.checkedbool
////                            bgImage: "../../img/icons/list_subitem.png"
//                            bgImage: ""
//                            fontName: root.subItemFontName
//                            fontSize: root.subItemFontSize
//                            fontColor: root.subItemFontColor
//                            textIndent: 20

//                            btn_flag: root.btn_flag

//                            onClicked: {}
//                            onChange_num: {
//                                if(sub_num!=0)
//                                {
//                                    if(check_status==true)
//                                        check_num=check_num+1;
//                                    else
//                                        check_num=check_num-1;
//                                    if(check_num ==0&&check.checked!="false")
//                                        check.checked="false";
//                                    else if(check_num ==sub_num&&check.checked!= "true")
//                                        check.checked="true";
//                                    else
//                                        check.checked="mid";
//                                }
//                                if(check.checked=="true"||check_num>0)
//                                    check_flag=true;
//                                else
//                                    check_flag=false;
//                            }
//                        }

//                    }//Repeater
//                }//Column
//            }//子项Item
//        }
//    }//Component


//    Common.ScrollArea {
//        frame:false
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 30
//        height: root.height -titlebar.height - 50
//        width: parent.width
//        Item {
//            width: parent.width
//            height: (root.lar_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height
//                model: mainModel
//                delegate: listViewDelegate
//                cacheBuffer: 1000
//                opacity: 1
//                spacing: 10
//                snapMode: ListView.NoSnap
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
//            }
//        }//Item
//    }//ScrollArea


//    states: [
//        State {
//            name: "LargestFileWorkAgain"
//            PropertyChanges { target: statusImage; iconName: "yellow.png"; text: "未完成"}
//        },
//        State {
//            name: "LargestFileWorkFinish"
//            PropertyChanges { target: statusImage; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "LargestFileWorkEmpty"
//            PropertyChanges { target: statusImage; iconName: "green.png"; text: "已完成"}
//        }
//    ]
//}
