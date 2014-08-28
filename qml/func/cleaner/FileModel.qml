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

Rectangle {
    id:filepage
    width: parent.width; height: 437
//    color: "#e4f2fc"

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


    Connections
    {
        target: sessiondispatcher
        onTellQMLLargeFileList: {
            subModel.clear();
            var largestfile_data = filelist;
            if (largestfile_data.length === 0) {
                filepage.null_flag = true;
                filepage.deleget_arrow =0;
                if(statusImage.visible == true)
                    statusImage.visible = false;
                filepage.resultFlag = false;//扫描内容不存在
            }
            else
            {
                filepage.null_flag = false;
                filepage.deleget_arrow =1;
                statusImage.visible = true;
                filepage.resultFlag = true;//扫描内容存在
            }
            filepage.sub_num = largestfile_data.length;
            var num = 0;
            for (var i=0; i< largestfile_data.length; i++) {
                var splitlist = largestfile_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": "", "index": i, "checked": true});
                }
            }
            filepage.sub_num -= num;
            filepage.lar_num = filepage.sub_num;
            filepage.check_num = filepage.sub_num;
            if(check_num != 0) {
                filepage.check_flag = true;
            }
            mainModel.clear();
            //清理路径为：   清理用户指定目录下的最大文件，节省磁盘空间。
            mainModel.append({"mstatus": filepage.check_flag ? "true": "false",
                              "itemTitle": qsTr("Cleanup path is:")  + filepage.directory,
                             "picture": "../../img/toolWidget/deb-min.png",
                             "detailstr": qsTr("cleaning up the maximum files in user-specified directory, to save disk space.")})
            if (filepage.resultFlag == false) {
                toolkits.alertMSG(qsTr("Nothing found!"));// 没有该大小的文件！
            }
        }
    }

    //获取数据
    function refresh_page() {
        filepage.sub_num=0;
        filepage.check_num=0
        sessiondispatcher.scan_of_large_qt(filepage.directory, filepage.size);
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (msg == "largestfile") {
                filepage.state = "LargestFileWorkError";
            }
         }
        onFinishCleanWork: {
            if (msg == "") {
                filepage.state = "LargestFileWorkAgain";
            }
            else if (msg == "largestfile") {
                filepage.state = "LargestFileWorkFinish";
                toolkits.alertMSG(qsTr("Cleared!"));//清理完毕！
                refresh_page();
            }
        }
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
                text: filepage.title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: filepage.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
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
            text: qsTr("Browse...")//浏览...
            picNormal: "../../img/icons/button12-lightblue.png"
            picHover: "../../img/icons/button12-lightblue-hover.png"
            picPressed: "../../img/icons/button12-lightblue-hover.png"
            fontcolor:"#ffffff"
            fontsize: 12
            width: 100; height: 28
            onClicked: {
                if (size_text.text == 0) {
                    //对不起，您没有设置扫描文件大小或者设置值为0,请重新输入文件大小！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you haven't set the file size or the value is 0, please input the file size!"));
                }
                else {
                    filepage.size = size_text.text;
                    filepage.directory = sessiondispatcher.show_folder_dialog();
                    if (filepage.directory != "") {
                        filepage.refresh_page();
                        filepage.state = "LargestFileWorkAgain";
                    }
                }
            }
        }

        Common.Button {
            id: bitButton
            picNormal: "../../img/icons/button16.png"
            picHover: "../../img/icons/button16-hover.png"
            picPressed: "../../img/icons/button16-hover.png"
            fontcolor:"#ffffff"
            fontsize: 16
            width: 120; height: 36
            visible: ((filepage.lar_num > 0) && (size_text.text != "") && (size_text.text != 0) && (filepage.directory != "") && (filepage.null_flag == false)) ? true : false
            text: qsTr("Begin cleanup")//开始清理
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(filepage.lar_num > 0) {
                    if(size_text.text == "" || size_text.text == 0)
                        //友情提示：        对不起，您没有设置扫描文件的大小或者设置值为 0，请重新输入文件大小！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You haven't set the file size or the value is 0, please input the file sizes !"));
                    else if (filepage.directory == "")
                    {
                        //友情提示：        对不起，您没有选择扫描路径，请点击＂浏览＂按钮选择！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You did not choose the scan path, please click the 'Browse' button to continue!"));
                        filepage.deleget_arrow =0;
                    }
                    else {
                        if(filepage.null_flag == true) {
                           filepage.state = "LargestFileWorkEmpty";
                            //友情提示：         扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("The scan reslut is empty, nothing has been done!"));
                        }
                        else if(filepage.null_flag == false) {
                            //test 0410
                            var filelist = new Array();
                            for(var i=0; i<subModel.count; i++) {
                                if(subModel.get(i).checked) {
                                    filelist.push(subModel.get(i).desc);
                                }
                            }
                            if (filelist == "") {
                                //友情提示：         对不起，您没有选择需要清理的项，请确认！
                                sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"));
                            }
                            else {
                            systemdispatcher.clean_file_cruft_qt(filelist, "largestfile");
                            }
                        }
                    }
                }
                else {
                    //友情提示：         对不起，您没有选择需要清理的项，请确认！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"),qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"));
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
        height: filepage.height -titlebar.height - 37
        width: parent.width -2
        Item {
            width: parent.width
            height: (filepage.sub_num + 1) * 30 + 30
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: FileDelegate{
                    sub_num: filepage.lar_num
                    sub_model:subModel
                    btn_flag: filepage.btnFlag
                    arrow_display: filepage.deleget_arrow
                    delegate_flag: false
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
                        filepage.sub_num = hMark;
                    }
                    onCheckchanged: {
                        filepage.check_flag = checkchange;
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
