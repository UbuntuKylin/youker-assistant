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
    id: widgetthemepage
    width: parent.width
    height: 476
//    color: "#eeedf0"

    property string actiontitle: qsTr("Theme settings")//GTK主题设置
    property string actiontext: qsTr("Choose the theme what you want.")//选择您想设置的主题。
    property int themeIndex: 0//序号
    property string init_theme: ""
    property string path: "../../img/en/title/"
    property int gredview_num: 0 //记录listmodel中的子项数
//    property int current_index//当前主题的索引
//    property int default_index//系统默认主题的索引

    ListModel { id: themeModel }

    Component.onCompleted: {
        //gtk theme
        if(sessiondispatcher.get_locale_version() == "zh_CN") {
            widgetthemepage.path = "../../img/zh_CN/";
        }
        else {
            widgetthemepage.path = "../../img/en/";
        }
        var syslist = sessiondispatcher.get_themes_qt();
        widgetthemepage.init_theme = sessiondispatcher.get_theme_qt();
        syslist.unshift(widgetthemepage.init_theme);
        themeModel.clear();
        for(var i=0; i < syslist.length; i++) {
            if(syslist[i] == "Ambiance" || syslist[i] == "HighContrast" || syslist[i] == "Radiance" || syslist[i] == "ubuntukylin-theme"){
                themeModel.append({"icon": "../../img/skin/" + syslist[i] + ".png", "name": syslist[i]});
            }
            //非系统默认的4个gtk主题时使用定义的通用图片
            else{
                themeModel.append({"icon": widgetthemepage.path + "disappear.png", "name": syslist[i]});
            }
            widgetthemepage.gredview_num += 1;
            if (i!=0 && syslist[i] == widgetthemepage.init_theme){
                widgetthemepage.gredview_num -= 1;
                themeModel.remove(i);
            }
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
            Text {
                 text: widgetthemepage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            Text {
                text: widgetthemepage.actiontext
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

    Row {
        id: icontitle
        anchors{
            left: parent.left
            leftMargin: 60
            top: top_splitbar.bottom
            topMargin: 40
        }
        z: 11
        spacing: 285 - 16 - 20
        Row {
            spacing: 20
            Image {
                source: "../../img/icons/dot.png"
                width: 14; height: 14
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.TipLabel {
                anchors.verticalCenter: parent.verticalCenter
                kflag: "no"
                showImage: "../../img/icons/cloud-gray.png"
            }
            Text {
                id: showtitle
                width: 130
                text: qsTr("Window theme settings:")//窗口装饰主题：         Gtk theme settings:
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component {
        id: themegridDelegate
        Item {
            id: griditem
            width: 125; height: 125
            Column {
                 anchors.fill: parent
                 spacing: 10
                 Image {
                    id: seticon
                    source: icon
                    width: 125
                    height: 125
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: btnText
                    height: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: name
                    font.bold: true
                    font.pixelSize: 12
                    color: "#383838"
                }
            }
            Image {
//                id: themeindex
                anchors{
                    top: parent.top
                    left: parent.left
                    leftMargin: 15
                }
                source: widgetthemepage.path + "using.png"
                opacity: griditem.GridView.isCurrentItem? 1:0
                rotation: -90
            }

            Image {
                id: btnImg
                anchors.fill: parent
                source: ""
            }
            MouseArea {
                id: signaltest
                hoverEnabled: true
                anchors.fill: parent
                onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
                onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
                //要判断松开是鼠标位置
                onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
                onExited: btnImg.source = ""
                onClicked: {
                    griditem.GridView.view.currentIndex = index;
                    widgetthemepage.themeIndex = index;
                    sessiondispatcher.set_theme_qt(name);
                }
            }
        }
    }

    Item {  //gredview外框架
        id:item
        width: parent.width - 60*2
        height: 350
        anchors {
            top: icontitle.bottom
            topMargin: 10
            left: parent.left
            leftMargin: 85
        }
        Common.ScrollArea { //gredview滚动条
            frame:false
            anchors{
                top:parent.top
                topMargin: 1
                left:parent.left
                leftMargin: 1
            }
            height: parent.height-1
            width: parent.width-1
            Item {  //gredview列表大小
                width: item.width - 15   //列表宽度
                height: (widgetthemepage.gredview_num/4 + (widgetthemepage.gredview_num % 4 ? 1: 0)) * 150 //自动计算列表行数
                GridView {
                    id: themegrid
                    anchors.fill: parent
                    cellWidth: 175; cellHeight: 156
                    model: themeModel
                    delegate: themegridDelegate
                    focus: true
                    cacheBuffer: 1000
        //            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
                }
            }
        }
    }
}
