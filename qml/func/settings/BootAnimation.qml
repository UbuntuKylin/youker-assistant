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
    id: bootimagepage
    width: parent.width
    height: 476
    color: "#eeedf0"

    property int scrollbar_z:0
    property int lisv_height: 250
    property string image_path: ""
    property string actiontitle: qsTr("Boot animation settings")//开机动画设置
    property string actiontext: qsTr("Click the \"Custom Picture\" button to select the picture you want to add, click the picture you want to set and push the \"OK\" button to complete.")//单击＂自定义图片＂按钮选择需要添加的图片，选中列表中要设置的图片名称，单击＂确定＂按钮完成设置。
    property int num: 0
    property string selectedimage: ""

    ListModel { id: mainModel }

    Component.onCompleted: {
        systemdispatcher.plymouth_init_check_qt();
        var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
        bootimagepage.num = plymouth_list.length;
        mainModel.clear();
        for(var i=0; i < plymouth_list.length; i++) {
            if(systemdispatcher.get_image_path_qt(plymouth_list[i]) != "False"){
                mainModel.append({"itemTitle": plymouth_list[i]});
            }
        }
        if(30*plymouth_list.length<=lisv_height) {
            scrollbar_z = -1
        }
        else {
            scrollbar_z = 1;
        }

    }
    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishAddBootImage: {
            systemdispatcher.plymouth_init_check_qt();
            var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
            bootimagepage.num = plymouth_list.length;
            mainModel.clear();
            for(var i=0; i < plymouth_list.length; i++) {
                if(systemdispatcher.get_image_path_qt(plymouth_list[i]) != "False"){
                    mainModel.append({"itemTitle": plymouth_list[i]});
                }
            }
            bootimagepage.selectedimage = plymouth_list[0];
        }
    }

    Row {
        spacing: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 20
        }
        Common.Button {
            id: backBtn
            anchors.verticalCenter: parent.verticalCenter
            picNormal: "../../img/icons/button12-gray.png"
            picHover: "../../img/icons/button12-gray-hover.png"
            picPressed: "../../img/icons/button12-gray-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 70; height: 28
            text: qsTr("Back")//返回
            onClicked: {
                pageStack.pop();
            }
        }
        Column {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Row {
                spacing: 50
                Text {
                     text: bootimagepage.actiontitle
                     font.bold: true
                     font.pixelSize: 14
                     color: "#383838"
                 }
                //status picture
                Common.StatusImage {
                    id: statusImage
                    visible: false
                    iconName: "green.png"
                    text: qsTr("Completed!")//已完成！
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Text {
                width: bootimagepage.width - 80 - 20
                text: bootimagepage.actiontext
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    //分割条
    Common.Separator {
        id: top_splitbar
        y: 70
        anchors {
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
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
            picNormal: "../../img/icons/button12-gray-long.png"
            picHover: "../../img/icons/button12-gray-long-hover.png"
            picPressed: "../../img/icons/button12-gray-long-hover.png"
            fontcolor:"#707070"
            fontsize: 12
            width: 100; height: 28
            text: qsTr("Custom Picture")//自定义图片
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bootimagepage.image_path = systemdispatcher.showSelectFileDialog("bootanimation");
                bootimage.source = bootimagepage.image_path;
                var imagename = bootimagepage.image_path;
                imagename = imagename.substr(imagename.lastIndexOf("/") + 1, imagename.length - imagename.lastIndexOf("/"));
                systemdispatcher.add_new_plymouth_qt(bootimagepage.image_path, imagename);
                systemdispatcher.readyAddBootImageToList();
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
        text: qsTr("Optional BootAnimation")//可选的开机动画
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
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
                width: 460; height: 30
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
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                        if(systemdispatcher.get_image_path_qt(itemTitle) != "False"){
                            bootimagepage.selectedimage = itemTitle;
                            bootimage.source = systemdispatcher.get_image_path_qt(itemTitle);
                        }
                        else{
                            //待添加原图片路径不存在时的说明图
                        }
                    }
                }
                Rectangle{
                    width: revoke.width;height: revoke.height; color: "transparent"
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: 35
                    }
                    opacity: wrapper.ListView.isCurrentItem? 1:0
                    Image {id:revoke;source: "../../img/icons/revoke.png"}
                    Image {
                        id: btnImg
                        anchors.fill: parent
                        source: ""
                    }
                    Text {
                        id: showText
                        anchors {
                            left: btnImg.right
                            verticalCenter: parent.verticalCenter
                        }
                        visible: false
                        text: qsTr("Delete")
                        font.pixelSize: 10
                        color: "#dd291c"
                    }
                    MouseArea{
                        anchors.fill:parent
                        hoverEnabled: true
                        onEntered: {
                            btnImg.source = "../../img/icons/revoke_hover.png";
                            showText.visible = true;
                        }
                        onPressed: {
                            btnImg.source = "../../img/icons/revoke_hover.png";
                        }
                        //要判断松开是鼠标位置
                        onReleased: {
                            btnImg.source = "";
                        }
                        onExited: {
                            btnImg.source = "";
                            showText.visible = false;
                        }
                        enabled:wrapper.ListView.isCurrentItem? true:false
                        onClicked: {
                            var result = systemdispatcher.delete_plymouth_qt(itemTitle);
                            if (result === "ok") {
                                toolkits.alertMSG(qsTr("Deleted successfully!"));//删除成功！
                                systemdispatcher.readyAddBootImageToList();
                            }
                            else if (result === "use") {
                                toolkits.alertMSG(qsTr("This is the using animation!"));//该动画为当前使用动画！
                            }
                            else if (result === "sys") {
                                toolkits.alertMSG(qsTr("This is the default animation!"));//该动画为系统默认动画！
                            }
                            else {
                                toolkits.alertMSG(qsTr("An unknown error occurred!"));//发生未知错误！
                            }
                        }
                    }
                }
            }
        }
        Common.ScrollArea {
            frame:false
            anchors{
                top:parent.top
                topMargin: 1
                left:parent.left
                leftMargin: 1
            }
            height: parent.height-1
            width: parent.width-1
            Item {
                width: parent.width
                height: bootimagepage.num * 30 //列表长度
                //垃圾清理显示内容
                ListView{
                    id:lisv
                    anchors.fill: parent
                    model: mainModel
                    delegate: cdelegat
                    highlight: Rectangle{width: parent.width /*440*/;height: 30 ; color: "lightsteelblue"}
                    focus:true
                }
            }//Item
        }//ScrollArea
    }

    Common.Button {
        id: okBtn
        anchors {
            right: parent.right
            rightMargin: 42
            bottom: parent.bottom
            bottomMargin: 30
        }
        picNormal: "../../img/icons/button12-gray.png"
        picHover: "../../img/icons/button12-gray-hover.png"
        picPressed: "../../img/icons/button12-gray-hover.png"
        fontcolor:"#707070"
        fontsize: 12
        width: 70; height: 28
        text: qsTr("OK")//确定
        onClicked: {
            systemdispatcher.custom_plymouth_bg_qt(bootimagepage.selectedimage);
            statusImage.visible = true;
        }
    }
    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: statusImage.visible = false
    }
}
