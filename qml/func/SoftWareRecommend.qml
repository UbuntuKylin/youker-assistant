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
import "common" as Common
import "bars" as Bars

Item {
    id: screen; width: parent.width; height: 475
    //需要时常变动的变量
    property string image_flag:"wps"
    property string recommendone_image: "../img/skin/wps-small.png"
    property string recommendtwo_image: "../img/skin/qq-small.png"
    property string recommendthree_image: "../img/skin/qt-small.png"
    property string recommendoneimage_image: "../img/skin/wps.png"
    property string recommendimage_text: qsTr("WPS For Ubuntu Kylin, the best office software of Linux system.")//WPS For Ubuntu Kylin，Linux系统上最好用的办公软件。
    property string status_value: "n"
    property string status_value2: "n"

    Component.onCompleted: {
    }

    //背景
    Image {
        source: "../img/skin/bg-middle.png"
        anchors.fill: parent
    }
    Item {
        id: recommendimage
        width: 560
        height: 210
        anchors{
            left: parent.left
            leftMargin: 25
            top:parent.top
            topMargin: 25
        }
        Image {
            anchors.fill:parent
            source: recommendoneimage_image
        }
        Image {
            id: statusImage
            source: "../img/icons/recommend.png"
            anchors{
                right:parent.right
                top: parent.top
            }
        }
        Image{
            anchors.fill:parent
            source: "../img/skin/linecolor.png"
        }
        Rectangle{
            width: parent.width;height: 30
            anchors.bottom: parent.bottom
            color: "transparent"
            Text{
                id: desc_text
                visible: (screen.image_flag == "qt") ? false : true
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                text:recommendimage_text
            }
            Common.Button{
                id: ecliseBtn
                visible: (screen.image_flag == "qt") ? true : false
                width: 80;height: 26
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                text: qsTr("Details")//详情
                onClicked: {
                    sudodispatcher.ready_show_app_page("eclipse");
                    pageStack.push(softwarepage);
                }
            }
            Common.Button{
                width: 80;height: 26
                anchors{
                    verticalCenter:parent.verticalCenter
                    right:parent.right
                    rightMargin: 15
                }
                text: qsTr("Details")//详情
                onClicked: {
                    if(screen.image_flag == "wps") {
                        sudodispatcher.ready_show_app_page("wps");
                    }
                    else if(screen.image_flag == "qq") {
                        sudodispatcher.ready_show_app_page("wineqq");
                    }
                    else if(screen.image_flag == "qt") {
                        sudodispatcher.ready_show_app_page("qtcreator");
                    }
                    pageStack.push(softwarepage);
                }
            }
        }
    }
    Column{
        id:colum
        anchors{
            top:parent.top
            topMargin: 25
            right: parent.right
            rightMargin: 25
        }
        spacing: 5
        Item{
            id: recommendone
            width:imageone.width;height: imageone.height
            Image {
                id:imageone
                source: recommendone_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.image_flag = "wps";
                    screen.recommendimage_text = qsTr("WPS For Ubuntu Kylin, the best office software of Linux system.")//WPS For Ubuntu Kylin，Linux系统上最好用的办公软件。
                    imagframe.y=colum.y+recommendone.y;
                    recommendoneimage_image="../img/skin/wps.png";
                }
            }
        }
        Item {
            id: recommendtwo
            width:imagetwo.width;height: imagetwo.height
            Image {
                id:imagetwo
                source: recommendtwo_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.image_flag = "qq";
                    screen.recommendimage_text = qsTr("WineQQ, with the best version of Linux system.");//WineQQ，Linux系统上最好用的QQ版本。
                    imagframe.y=colum.y+recommendtwo.y;
                    recommendoneimage_image="../img/skin/qq.png";
                }
            }
        }
        Item{
            id: recommendthree
            width:imagethree.width;height: imagethree.height
            Image {
                id:imagethree
                source: recommendthree_image
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    screen.image_flag = "qt";
                    imagframe.y=colum.y+recommendthree.y;
                    recommendoneimage_image="../img/skin/qt.png";
                }
            }
        }
    }

    Image {
        id: imagframe
        source: "../img/skin/frame.png"
        x:colum.x-13;y:colum.y
        opacity: 0.8
    }

    Rectangle {
        id: views
        width: parent.width-50
        height: 227
        anchors{
            bottom:parent.bottom
            left: parent.left
            leftMargin: 25
        }

        //收到软件列表信息后添加到QML界面上
        Connections
        {
            target: sudodispatcher
            onSendAppListToQML: {
                funcmodel.clear();
                var num = 0;
                for (var i=0; i< appList.length; i++) {
                    funcmodel.append({"icon": "../img/icons/" + appList[i] + ".png", "flag": appList[i]});
                }
            }
        }

        clip:true
        border.color: "#9aa2af"
        color: "#e6ebfe"
        Rectangle{
            id:rec
            width: parent.width-1;height: 31
            anchors{
                top:parent.top
                topMargin: 1
                left: parent.left
                leftMargin: 1
            }
            gradient: Gradient{
                GradientStop{position: 0.0; color: "#e2e2e2"}
                GradientStop{position: 1.0; color: "#dedede"}
            }
            Row{
                anchors.centerIn: parent
                spacing: 50
                Text {
                    text:qsTr("Recommendations")//推荐金榜单
                    color: "#6b6f70"
                    font.pixelSize: 14
                }
            }
        }
        Rectangle{id: splitbar1; anchors{top:rec.bottom;left: parent.left;leftMargin: 1 }width:parent.width-1 ; height:1; color:"#b8bdc3"}
        Rectangle{id: splitbar2; anchors{top:splitbar1.bottom;left: parent.left;leftMargin: 1  }width:parent.width-1 ; height:1; color:"#ebf0f6"}
        Item {
            width: views.width
            height: 194
            anchors.bottom: parent.bottom
            clip:true

            ListModel {
                id: funcmodel
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
                    width: views.width-20   //列表宽度
                    height: 4 * 95     //列表长度,前面的数字为列表行数
                    GridView {
                        id: gridView
                        height: parent.height-12
                        width: parent.width
                        anchors {
                            top: parent.top
                            topMargin: 12
                            left: parent.left
                            leftMargin: 20
                        }
                        model: funcmodel
                        delegate: SoftwareDelegate {}
                        cacheBuffer: 1000
                        cellWidth: 190; cellHeight: 90
                        focus: true
                    }
                }//Item
            }//ScrollArea
        }
    }
}
