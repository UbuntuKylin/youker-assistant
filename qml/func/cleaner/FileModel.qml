/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
Item {
    id:root
    width: parent.width
    height: 435
    property string title: qsTr("Quickly find large files")//快速找出大文件
    property string description: qsTr("Range:1M-20480M; 1GB = 1024MB")//大小范围为1M-20480M；1GB = 1024MB
//    property string scope_desc: qsTr("Tips: No support the path contains Chinese.")//提示：暂不支持中文路径。
    property string btnFlag: "largestfile_work"//清理的标记：largestfile_work
    property int sub_num: 0
    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int lar_num: sub_num
    property int check_num:sub_num
    property bool check_flag: false//true
    property bool null_flag: false
//    property string yesOrno: "false"
    property string directory: ""
    property int size: 0
    property int deleget_arrow :0

    ListModel { id: mainModel }
    ListModel { id: subModel }

    //获取数据
    function refresh_page() {
        root.sub_num=0;
        root.check_num=0
        var largestfile_data = sessiondispatcher.scan_of_large_qt(root.size, root.directory);
        if (largestfile_data.length === 0) {
            root.null_flag = true;
            root.deleget_arrow =0;
            if(statusImage.visible == true)
                statusImage.visible = false;
            root.resultFlag = false;//扫描内容不存在
        }
        else
        {
            root.null_flag = false;
            root.deleget_arrow =1;
            statusImage.visible = true;
        }
        root.sub_num = largestfile_data.length;
//        systemdispatcher.clear_largestfile_args();
        subModel.clear();
        var num = 0;
        for (var i=0; i< largestfile_data.length; i++) {
            var splitlist = largestfile_data[i].split("<2_2>");
            if (splitlist[0] == "") {
                num++;
            }
            else {
                subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": "", "index": i, "checked": true});
//                systemdispatcher.set_largestfile_args(splitlist[1]);


//                if(root.yesOrno == "true") {
//                    console.log("is yes...........");
//                    systemdispatcher.set_largestfile_args(splitlist[1]);
//                }
//                else {
//                    console.log("is no...........");
//                }
            }
        }
        root.sub_num -= num;
        root.lar_num = root.sub_num;
        root.check_num = root.sub_num;
        if(check_num != 0) {
            check_flag = true;
        }
        mainModel.clear();
        //清理路径为：   清理用户指定目录下的最大文件，节省磁盘空间。
        mainModel.append({"mstatus": root.check_flag ? "true": "false",
                          "itemTitle": qsTr("Cleanup path is:")  + root.directory,
                         "picture": "../../img/toolWidget/deb-min.png",
                         "detailstr": qsTr("cleaning up the maximum files in user-specified directory, to save disk space.")})
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (msg == "largestfile") {
                root.state = "LargestFileWorkError";
            }
         }
        onFinishCleanWork: {
            if (msg == "") {
                root.state = "LargestFileWorkAgain";
            }
            else if (msg == "largestfile") {
                root.state = "LargestFileWorkFinish";
                toolkits.alertMSG(qsTr("Cleared!"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                refresh_page();
            }
        }
    }

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    //titlebar
    Row {
        id: titlebar
        spacing: 10
        width: parent.width
        anchors { top: parent.top; topMargin: 10; left: parent.left; leftMargin: 10}
        Image {
            id: refreshArrow
            visible: true
            source: "../../img/toolWidget/searchfile.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
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
//            Text {
//                text: root.scope_desc
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
        }

    }
    Row{
        anchors { top: parent.top; topMargin: 20;right: parent.right ; rightMargin: 40 }
        spacing: 20
        Text {
            text: qsTr("Please input the file size (M) : ")//请输入文件大小 (M)：
            font.pixelSize: 12
            color: "#383838"
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 50; height: 20
            Image {
                source: "../../img/toolWidget/green.png"
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
        Common.Button {
            id: selectBtn
            anchors.verticalCenter: parent.verticalCenter
            hoverimage: "skyblue.png"
            text: qsTr("Browse...")//浏览...
            fontcolor: "#086794"
            width: 94
            height: 29
            fontsize: 13
            onClicked: {
                root.size = size_text.text;
                root.directory = sessiondispatcher.show_folder_dialog();
                if (root.directory != "") {
                    root.refresh_page();
                    root.state = "LargestFileWorkAgain";
                }
            }
        }

        Common.Button {
            id: bitButton
            width: 94
            height: 29
            fontsize: 13
            hoverimage: "green.png"
            text: qsTr("Begin cleanup")//开始清理
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
//                if(root.check_flag) {
                if(root.lar_num > 0) {
                    if(size_text.text == "" || size_text.text == 0)
                        //友情提示：        对不起，您没有设置扫描文件的大小或者设置值为 0，请重新输入文件大小！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You haven't set the file size or the value is 0, please input the file sizes !"), mainwindow.pos.x, mainwindow.pos.y);
                    else if (root.directory == "")
                    {
//                        if(root.sub_num != 0 && root.null_flag == false) {
//                            systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
//                        }
//                        else {
                        //友情提示：        对不起，您没有选择扫描路径，请点击＂浏览＂按钮选择！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You did not choose the scan path, please click the 'Browse' button to continue!"), mainwindow.pos.x, mainwindow.pos.y);
                        root.deleget_arrow =0;
//                        }
                    }
                    else {
                        if(root.null_flag == true) {
                           root.state = "LargestFileWorkEmpty";
                            //友情提示：         扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("The scan results are empty, no need to clean up !"), mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else if(root.null_flag == false) {
                            //test 0410
                            var filelist = new Array();
                            for(var i=0; i<subModel.count; i++) {
                                if(subModel.get(i).checked) {
                                    filelist.push(subModel.get(i).desc);
                                }
                            }
//                            console.log("yyyy", filelist);
                            systemdispatcher.clean_file_cruft_qt(filelist, "largestfile");
//                            systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_largestfile_args(), "largestfile");
                        }
                    }
                }
                else {
                    //友情提示：         对不起，您没有选择需要清理的项，请确认！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"), mainwindow.pos.x, mainwindow.pos.y)
                }
            }
        }
    }

    //分割条
    Common.Separator {
        id: splitbar
        anchors {
            top: titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
    }

    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 30
        anchors.left:parent.left
//        anchors.leftMargin: 27
        height: root.height -titlebar.height - 37
        width: parent.width -2
//        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.sub_num + 1) * 30 + 30
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: FileDelegate{
                    sub_num: root.lar_num
                    sub_model:subModel
                    btn_flag: root.btnFlag
                    arrow_display: root.deleget_arrow
                    delegate_flag: false
//                    main_check_value: root.yesOrno


                    //test 0410
                    onTransmitFileItemMainCheckBoxStatus: {
                        if(status) {
                            for(var i=0; i<subModel.count; i++) {
                                subModel.setProperty(i, "checked", true);
                            }
                        }
                        else {
                            for(var j=0; j<subModel.count; j++) {
                                subModel.setProperty(j, "checked", false);
                            }
                        }
                    }

                    //test 0410
                    onTransmitFileItemCheckBoxStatus: {
                        if(status) {
                            subModel.setProperty(index, "checked", true);
                        }
                        else {
                            subModel.setProperty(index, "checked", false);
                        }
                    }


                    onSubpressed: {
                        root.sub_num = hMark;
                    }
                    onCheckchanged: {
                        root.check_flag = checkchange;
                    }
                }
                cacheBuffer: 1000
                opacity: 1
//                spacing: 10
                snapMode: ListView.NoSnap
                boundsBehavior: Flickable.DragOverBounds
                currentIndex: 0
                preferredHighlightBegin: 0
                preferredHighlightEnd: preferredHighlightBegin
                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }
        Common.StatusImage {
            id: statusImage
            anchors{
                top:parent.top
                topMargin: 15
                left: parent.left
                leftMargin:610
            }
            visible: false
            iconName: "yellow.png"
            text: qsTr("Unfinished")//未完成
        }
    }

    states: [
        State {
            name: "LargestFileWorkAgain"
            PropertyChanges { target: statusImage; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
        },
        State {
            name: "LargestFileWorkError"
            PropertyChanges { target: statusImage; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
        },
        State {
            name: "LargestFileWorkFinish"
            PropertyChanges { target: statusImage; iconName: "green.png"; text: qsTr("Completed")}//已完成
        },
        State {
            name: "LargestFileWorkEmpty"
            PropertyChanges { target: statusImage; iconName: "green.png"; text: qsTr("Completed")}//已完成
        }
    ]
}
