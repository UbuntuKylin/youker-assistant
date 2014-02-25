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
import "../bars" as Bars

Rectangle {
    id: widgetthemepage
    width: parent.width
    height: 475
    property string actiontitle: qsTr("Theme settings")//GTK主题设置
    property string actiontext: qsTr("Choose the theme what you want.")//选择您想设置的主题。
    property string selected_theme: ""
    property int themeIndex: 0//序号
    property string init_theme: ""
    property string path: "../../img/en/title/"
    property int gredview_num: 0 //记录listmodel中的子项数

    property int current_index//当前主题的索引
    property int default_index//系统默认主题的索引
    property string uk_default

    Component.onCompleted: {
        var windowlist = sessiondispatcher.get_window_themes_qt();
        var current_window_theme = sessiondispatcher.get_current_window_theme_qt();
        var default_window_theme = sessiondispatcher.get_default_theme_sring_qt("windowtheme");
        //系统默认值为Adwaita，但是目前均无法设置该值
        choices.clear();
        if(current_window_theme == default_window_theme) {
            for(var i=0; i < windowlist.length; i++) {
                choices.append({"text": windowlist[i]});
                if (windowlist[i] == current_window_theme) {
                    widgetthemepage.current_index = i;
                    widgetthemepage.default_index = i;
                }
            }
        }
        else {
            for(var j=0; j < windowlist.length; j++) {
                choices.append({"text": windowlist[j]});
                if (windowlist[j] == current_window_theme) {
                    widgetthemepage.current_index = j;
                }
                else if (windowlist[j] == default_window_theme) {
                    widgetthemepage.default_index = j;
                }
            }
        }
        windowcombo.selectedIndex = widgetthemepage.current_index;




        if(sessiondispatcher.get_locale_version() == "zh_CN") {
            widgetthemepage.path = "../../img/zh_CN/";
        }
        else {
            widgetthemepage.path = "../../img/en/";
        }

        statusImage.visible = false;
        var syslist = sessiondispatcher.get_themes_qt();
        widgetthemepage.init_theme = sessiondispatcher.get_theme_qt();
//        showText.text = qsTr("[ Current Theme is: ") + widgetthemepage.init_theme + " ]";//[ 当前主题是：
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

    ListModel { id: themeModel }
    ListModel { id: choices }

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row{
            spacing: 50
            Text {
                 text: widgetthemepage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            Text {
                id: showText
                text: ""
                font.pixelSize: 14
                color: "#318d11"
            }
            //status picture
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            text: widgetthemepage.actiontext
            font.pixelSize: 12
            color: "#7a7a7a"
        }
    }

    Row {
        id: settitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 105

        }
        Text{
            id: themetitle
            text: qsTr("Window theme settings")//窗口主题设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: widgetthemepage.width - themetitle.width - 40 * 2
        }
    }
    Row {
        id: themeline
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10

        }
        spacing: 200
        Row {
            spacing: 20
            Text {
                id: iconthemelabel
                width: 170 - 50
                text: qsTr("Window theme:")//窗口主题：
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.ComboBox {
                id: windowcombo
                model: choices
                width: 170 + 50
                onSelectedTextChanged: {
                    sessiondispatcher.set_window_theme_qt(windowcombo.selectedText);
                }
            }
        }
        Common.Button {
            hoverimage: "blue.png"
            text: qsTr("Restore")//恢复默认
            width: 94
            height: 29
            fontsize: 13
            onClicked: {
                var mylist = sessiondispatcher.get_window_themes_qt();
                var mytheme = sessiondispatcher.get_default_theme_sring_qt("windowtheme");
                //系统默认值为Adwaita，但是目前均无法设置该值
                var flag = false;
                for(var k=0; k < mylist.length; k++) {
                    if(mylist[k] == mytheme) {
                        flag = true;
                        break;
                    }
                }
                if(flag) {//系统默认值存在于列表中
                    sessiondispatcher.set_default_theme_qt("windowtheme");
                    windowcombo.selectedIndex = widgetthemepage.default_index;
                }
                else {//系统默认值不存在于列表中
                    flag = false;
                    var q;
                    for(q=0; q < mylist.length; q++) {
                        if(mylist[q] == "ubuntukylin-theme") {
                            flag = true;
                            break;
                        }
                    }
                    if(flag) {//ubuntukylin-theme存在于列表中
                        sessiondispatcher.set_window_theme_qt("ubuntukylin-theme");
                        windowcombo.selectedIndex = q;
                    }
                    else {//ubuntukylin-theme不存在于列表中
                        sessiondispatcher.set_window_theme_qt(mylist[0]);
                        windowcombo.selectedIndex = 0;
                    }
                }
            }
        }
    }
    Row {
        id: icontitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: themeline.bottom
            topMargin: 15
        }
        Text{
            id: showtitle
            text: qsTr("Gtk theme settings")//Gtk主题设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: desktopiconsetpage.width - showtitle.width - 40 * 2
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
                id: themeindex
                anchors{
                    top: parent.top
                    left: parent.left
                    leftMargin: 15
//                    right: parent.right
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
//                    console.log(index);
                    console.log(widgetthemepage.gredview_num);
                    widgetthemepage.themeIndex = index;
                    widgetthemepage.selected_theme = name;
                    sessiondispatcher.set_theme_qt(name);
                    statusImage.visible = true;
//                    showText.text = qsTr("[ Current Theme is: ") + name + " ]";//[ 当前主题是：
                }
            }
        }
    }

    Item {  //gredview外框架
        id:item
        width: parent.width - 60*2
        height: parent.height - 170
        anchors {
//            top: parent.top
            top: icontitle.bottom
            topMargin: 10
//            topMargin: 100
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
//                height: 2 * 156     //列表长度,前面的数字为列表行数
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
            if (num == 0) {
                pageStack.push(homepage);
            }
            else if (num == 3) {
                pageStack.push(systemset);
            }
            else if (num == 4) {
                pageStack.push(functioncollection);
            }
        }
    }

    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        showok: false
        showrestore: false
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0) {
                pageStack.push(homepage);
            }
            else if (num == 3) {
                pageStack.push(systemset);
            }
            else if (num == 4) {
                pageStack.push(functioncollection);
            }
        }
        Timer {
            interval: 5000; running: true; repeat: true
            onTriggered: statusImage.visible = false
        }
    }
}







//Rectangle {
//    id: widgetthemepage
//    width: parent.width
//    height: 475
//    property string actiontitle: qsTr("GTK Theme settings")//GTK主题设置
//    property string actiontext: qsTr("Choose the theme what you want. The first is the theme of the currently used.")//选择您想设置的主题。第一个主题为系统当前使用的主题。
//    property string selected_theme: ""
//    property int themeIndex: 0//序号
//    property string init_theme: ""
//    property string path: "../../img/en/title/"
//    property int gredview_num: 0 //记录listmodel中的子项数

//    Component.onCompleted: {
//        if(sessiondispatcher.get_locale_version() == "zh_CN") {
//            widgetthemepage.path = "../../img/zh_CN/";
//        }
//        else {
//            widgetthemepage.path = "../../img/en/";
//        }

//        statusImage.visible = false;
//        var syslist = sessiondispatcher.get_themes_qt();
//        widgetthemepage.init_theme = sessiondispatcher.get_theme_qt();
////        showText.text = qsTr("[ Current Theme is: ") + widgetthemepage.init_theme + " ]";//[ 当前主题是：
//        syslist.unshift(widgetthemepage.init_theme);
//        themeModel.clear();
//        for(var i=0; i < syslist.length; i++) {
//            if(syslist[i] == "Ambiance" || syslist[i] == "HighContrast" || syslist[i] == "Radiance" || syslist[i] == "ubuntukylin-theme"){
//                themeModel.append({"icon": "../../img/skin/" + syslist[i] + ".png", "name": syslist[i]});
//            }
//            //非系统默认的4个gtk主题时使用定义的通用图片
//            else{
//                themeModel.append({"icon": widgetthemepage.path + "disappear.png", "name": syslist[i]});
//            }
//            widgetthemepage.gredview_num += 1;
//            if (i!=0 && syslist[i] == widgetthemepage.init_theme){
//                widgetthemepage.gredview_num -= 1;
//                themeModel.remove(i);
//            }
//        }
//        //将系统初始的标题栏字体写入QSetting配置文件
////        sessiondispatcher.write_default_configure_to_qsetting_file("theme", "widgettheme", widgetthemepage.init_theme);
//    }

//    ListModel { id: themeModel }

//    //背景
//    Image {
//        source: "../../img/skin/bg-middle.png"
//        anchors.fill: parent
//    }

//    Component {
//        id: themegridDelegate
//        Item {
//            id: griditem
//            width: 125; height: 125
//            Column {
//                 anchors.fill: parent
//                 spacing: 10
//                 Image {
//                    id: seticon
//                    source: icon
//                    width: 125
//                    height: 125
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }
//                Text {
//                    id: btnText
//                    height: 20
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    text: name
//                    font.bold: true
//                    font.pixelSize: 12
//                    color: "#383838"
//                }
//            }
//            Image {
//                id: themeindex
//                anchors{
//                    top: parent.top
//                    left: parent.left
//                    leftMargin: 15
////                    right: parent.right
//                }
//                source: widgetthemepage.path + "using.png"
//                opacity: griditem.GridView.isCurrentItem? 1:0
//                rotation: -90
//            }

//            Image {
//                id: btnImg
//                anchors.fill: parent
//                source: ""
//            }
//            MouseArea {
//                id: signaltest
//                hoverEnabled: true
//                anchors.fill: parent
//                onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//                //要判断松开是鼠标位置
//                onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                onExited: btnImg.source = ""
//                onClicked: {
//                    griditem.GridView.view.currentIndex = index;
////                    console.log(index);
//                    console.log(widgetthemepage.gredview_num);
//                    widgetthemepage.themeIndex = index;
//                    widgetthemepage.selected_theme = name;
//                    sessiondispatcher.set_theme_qt(name);
//                    statusImage.visible = true;
////                    showText.text = qsTr("[ Current Theme is: ") + name + " ]";//[ 当前主题是：
//                }
//            }
//        }
//    }

////    function restoreTheme() {
////        griditem.GridView.view.currentIndex = 0;
////        widgetthemepage.themeIndex = 0;
////    }

//    Column {
//        id: titlecolumn
//        spacing: 10
//        anchors {
//            top: parent.top
//            topMargin: 44
//            left: parent.left
//            leftMargin: 80
//        }
//        Row {
//            spacing: 50
//            Text {
//                text: widgetthemepage.actiontitle
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
////            Text {
////                id: showText
////                text: ""
////                font.pixelSize: 14
////                color: "#318d11"
////            }
//            //status picture
//            Common.StatusImage {
//                id: statusImage
//                visible: false
//                iconName: "green.png"
//                text: qsTr("Completed")//已完成
//                anchors.verticalCenter: parent.verticalCenter
//            }
//         }
//        Text {
//            text: widgetthemepage.actiontext
//            font.pixelSize: 12
//            color: "#7a7a7a"
//        }
//    }
//    Item {  //gredview外框架
//        id:item
//        width: parent.width - 60*2
//        height: parent.height - 170
//        anchors {
//            top: parent.top
//            topMargin: 100
//            left: parent.left
//            leftMargin: 85
//        }
//        Common.ScrollArea { //gredview滚动条
//            frame:false
//            anchors{
//                top:parent.top
//                topMargin: 1
//                left:parent.left
//                leftMargin: 1
//            }
//            height: parent.height-1
//            width: parent.width-1
//            Item {  //gredview列表大小
//                width: item.width - 15   //列表宽度
////                height: 2 * 156     //列表长度,前面的数字为列表行数
//                height: (widgetthemepage.gredview_num/4 + (widgetthemepage.gredview_num % 4 ? 1: 0)) * 150 //自动计算列表行数
//                GridView {
//                    id: themegrid
//                    anchors.fill: parent
//                    cellWidth: 175; cellHeight: 156
//                    model: themeModel
//                    delegate: themegridDelegate
//                    focus: true
//                    cacheBuffer: 1000
//        //            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
//                }
//            }
//        }
//    }



//    //顶层工具栏
//    Bars.TopBar {
//        id: topBar
//        width: 28
//        height: 26
//        anchors.top: parent.top
//        anchors.topMargin: 40
//        anchors.left: parent.left
//        anchors.leftMargin: 40
//        opacity: 0.9
//        onButtonClicked: {
//            var num = sessiondispatcher.get_page_num();
//            if (num == 0) {
//                pageStack.push(homepage);
//            }
//            else if (num == 3) {
//                pageStack.push(systemset);
//            }
//            else if (num == 4) {
//                pageStack.push(functioncollection);
//            }
//        }
//    }

//    //底层工具栏
//    Bars.ToolBar {
//        id: toolBar
//        showok: false
//        showrestore: false
//        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//        onQuitBtnClicked: {
//            var num = sessiondispatcher.get_page_num();
//            if (num == 0) {
//                pageStack.push(homepage);
//            }
//            else if (num == 3) {
//                pageStack.push(systemset);
//            }
//            else if (num == 4) {
//                pageStack.push(functioncollection);
//            }
//        }
//        Timer {
//            interval: 5000; running: true; repeat: true
//            onTriggered: statusImage.visible = false
//        }
//    }
//}
