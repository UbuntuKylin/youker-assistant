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
import SystemType 0.1
import "../common" as Common
import "../bars" as Bars
Rectangle {
    id: bootimagepage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int scrollbar_z:0
    property int lisv_height: 250
    property int fontSize: 12
    property color fontColor: "black"
    property SystemDispatcher dis: systemdispatcher
    property string image_path: ""
    property string actiontitle: "开机动画设置(目前仅支持png图片格式，不支持以中文命名的图片)"
    property string actiontext: "点击“自定义图片”按钮选择您需要添加到列表中的图片，在列表中选中您要设置的图片名称，点击“确定”按钮完成设置。"
    property int num: 0
    property string selectedimage: ""

    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        systemdispatcher.plymouth_init_check_qt();
        var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
        bootimagepage.num = plymouth_list.length;
        mainModel.clear();
        for(var i=0; i < plymouth_list.length; i++) {
            mainModel.append({"itemTitle": plymouth_list[i]});
        }
//        bootimagepage.selectedimage = plymouth_list[0];
        if(30*plymouth_list.length<=lisv_height)
        {
            scrollbar_z=-1
        }
        else scrollbar_z=1
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onAddBootImage: {
            systemdispatcher.plymouth_init_check_qt();
            var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
            bootimagepage.num = plymouth_list.length;
            mainModel.clear();
            for(var i=0; i < plymouth_list.length; i++) {
                mainModel.append({"itemTitle": plymouth_list[i]});
            }
            bootimagepage.selectedimage = plymouth_list[0];
        }
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row {
            spacing: 50
            Text {
                 text: bootimagepage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            //status picture
            Image {
                id: statusImage
                visible: false
                source: "../../img/toolWidget/finish.png"
                fillMode: "PreserveAspectFit"
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             text: bootimagepage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    Column {
        anchors {
            top: parent.top
            topMargin: 120
            left: parent.left
            leftMargin: 60
        }
        spacing: 30
        Image {
            id: previewzone
            source: "../../img/icons/previewzone.png"
        }

        Common.Button {
            width: 134
            height: 35
            hoverimage: "blue3.png"
            text: "自定义图片"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bootimagepage.image_path = systemdispatcher.show_file_dialog("bootanimation");
                bootimage.source = bootimagepage.image_path;
                var imagename = bootimagepage.image_path;
                imagename = imagename.substr(imagename.lastIndexOf("/") + 1, imagename.length - imagename.lastIndexOf("/"));
                systemdispatcher.add_new_plymouth_qt(bootimagepage.image_path, imagename);
                systemdispatcher.send_boot_signal();
            }
        }
    }

    Image {
        id: bootimage
        width: 165
        height: 114
        anchors {
            top: parent.top
            topMargin: 140
            left: parent.left
            leftMargin: 80
        }
//        fillMode: Image.TileHorizontally
        source: ""
        smooth: true
    }

    Text {
        id: chooselabel
        anchors {
            top: parent.top
            topMargin: 120
            left: bootimage.right
            leftMargin: 100
        }
        text: "可选开机动画"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
    }

    ListModel {
        id: mainModel
        ListElement {
            itemTitle: ""
        }
    }


    Rectangle{
        border.color: "#b9c5cc"
        width: 460; height: 250
        clip:true
        anchors {
            top: chooselabel.bottom
            topMargin: 5
            left: bootimage.right
            leftMargin: 100
        }
        Component{
            id:cdelegat
            Item{
                id:wrapper
                width: 440; height: 30
                Text{
                    id:listtext
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text:itemTitle
                }
                Image {
                    id: btnImg
                    anchors.fill: parent
                    source: ""
                }
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                        bootimagepage.selectedimage = itemTitle;
                    }
                }

            }
        }
        ListView{
            id:lisv
            anchors.fill: parent
            model: mainModel
            delegate: cdelegat
            highlight: Rectangle{width: 440;height: 30 ; color: "lightsteelblue"}
            focus:true
        }

        Rectangle{
            id:scrollbar
            anchors.right: parent.right
            anchors.rightMargin: 8
            height: parent.height
            z:scrollbar_z
            width:4
            color: "lightgrey"
        }
        Rectangle{
            id: button
            anchors.right: parent.right
            anchors.rightMargin: 5
            width: 10
            z:scrollbar_z
            y: lisv.visibleArea.yPosition * scrollbar.height
            height: lisv.visibleArea.heightRatio * scrollbar.height;
            radius: 3
            smooth: true
            color: "white"
            border.color: "lightgrey"
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
            }
            MouseArea {
                id: mousearea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height - button.height
                onMouseYChanged: {
                    lisv.contentY = button.y / scrollbar.height * lisv.contentHeight
                }
            }
        }
    }

    //顶层工具栏
    Bars.TopBar {
        id: topBar
        width: 28
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        opacity: 0.9
        onButtonClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {
            systemdispatcher.custom_plymouth_bg_qt(bootimagepage.selectedimage);
            statusImage.visible = true;
        }
        Timer {
                 interval: 5000; running: true; repeat: true
                 onTriggered: statusImage.visible = false
             }
    }
}
