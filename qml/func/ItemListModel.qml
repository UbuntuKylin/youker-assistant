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
import "common" as Common

import SessionType 0.1

Rectangle {
    id:container
    property SessionDispatcher dis: sessiondispatcher
    width: parent.width
    height: 435

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


    property ListModel listmodel: mymodel
    property ListModel submodel: mysubmodel
    property int num: 0 //number of subitem
    property string btn_flag: ""
    property bool check_flag: true


    //背景
    Image {
        source: "../img/skin/bg-onekey.png"
        anchors.fill: parent
    }


    ListModel {
        id: mymodel
    }
    ListModel {
        id: mysubmodel
    }

    Component {
        id: listViewDelegate
        Item {
            id: delegate
            property int itemHeight: 40
            property alias expandedItemCount: subItemRepeater.count
            property bool expanded: true //kobe:子项扩展默认打开
//            property bool expanded: subItemTitle="" ? false : true//kobe:子项扩展默认打开
            //subListItem
//            x: 0; y: 0;
            x: 5; y: 2
            width: container.width
            height: headerItemRect.height + subItemsRect.height


            //'flags' comes from ListModel in BrowserHistory.qml or BrowserCookies.qml
            Component.onCompleted: {
//                if (flags == "clear_rubbish") {
//                    var rubbish_str = sessiondispatcher.get_str();
//                    if (rubbish_str.indexOf("r") < 0)
//                        sessiondispatcher.set_str("r");
//                }
//                else if (flags == "clear_apt") {
//                    var apt_str = sessiondispatcher.get_str();
//                    if (apt_str.indexOf("a") < 0)
//                        sessiondispatcher.set_str("a");
//                }
//                else if (flags == "clear_software") {
//                    var software_str = sessiondispatcher.get_str();
//                    if (software_str.indexOf("s") < 0)
//                        sessiondispatcher.set_str("s");
//                }
//                else if (flags == "clear_history") {
//                    var history_str = sessiondispatcher.get_str();
//                    if (history_str.indexOf("h") < 0)
//                        sessiondispatcher.set_str("h");
//                }
//                else if (flags == "clear_cookies") {
//                    var cookie_str = sessiondispatcher.get_str();
//                    if (cookie_str.indexOf("c") < 0)
//                        sessiondispatcher.set_str("c");
//                }
//                else if (flags == "clear_package") {
//                    var plugin_str = sessiondispatcher.get_str();
//                    if (plugin_str.indexOf("p") < 0)
//                        sessiondispatcher.set_str("p");
//                }


//                if (checkbox.checked) {
//        //            console.log("2222222222222");
//                    if (flags == "clear_rubbish") {
//                        var rubbish_str = sessiondispatcher.get_str();
//                        if (rubbish_str.indexOf("r") < 0)
//                            sessiondispatcher.set_str("r");
//                    }
//                    else if (flags == "clear_apt") {
//                        var apt_str = sessiondispatcher.get_str();
//                        if (apt_str.indexOf("a") < 0)
//                            sessiondispatcher.set_str("a");
//                    }
//                    else if (flags == "clear_software") {
//                        var software_str = sessiondispatcher.get_str();
//                        if (software_str.indexOf("s") < 0)
//                            sessiondispatcher.set_str("s");
//                    }
//                    else if (flags == "clear_history") {
////                        console.log("aaaaaaaaa");
//                        var history_str = sessiondispatcher.get_str();
////                        console.log(history_str)
//                        if (history_str.indexOf("h") < 0)
//                            sessiondispatcher.set_str("h");
////                        console.log('bbbbbbbbbbb');
//                    }
//                    else if (flags == "clear_cookies") {
//                        var cookie_str = sessiondispatcher.get_str();
//                        if (cookie_str.indexOf("c") < 0)
//                            sessiondispatcher.set_str("c");
//                    }
//                    else if (flags == "clear_package") {
//                        var plugin_str = sessiondispatcher.get_str();
//                        if (plugin_str.indexOf("p") < 0)
//                            sessiondispatcher.set_str("p");
//                    }
//                }
            }

            //母项
            //checkbox, picture and words
            Row {
                id: headerItemRect
//                x: 0; y: 0
                x: 5; y: 2
                width: parent.width
                height: parent.itemHeight
                spacing: 10
//                CheckBox {
//                    id: checkbox
//                    checked: true
//                    width: 30
//                    anchors.verticalCenter: parent.verticalCenter
//                    onCheckedChanged: {
//                        //kobe: wait for adding function
//                        if (checkbox.checked) {
//                            container.check_flag = true;
//                            console.log(container.check_flag);
//                            console.log(container.num);

//                            if (flags == "clear_rubbish") {
////                                clearDelegate.check_flag = "clear_rubbish";
//                                var rubbish_str = sessiondispatcher.get_str();
//                                if (rubbish_str.indexOf("r") < 0)
//                                    sessiondispatcher.set_str("r");
//                            }
//                            else if (flags == "clear_history") {
////                                clearDelegate.check_flag = "clear_history";
//                                var history_str = sessiondispatcher.get_str();
//                                if (history_str.indexOf("h") < 0)
//                                    sessiondispatcher.set_str("h");
//                            }
//                            else if (flags == "clear_cookies") {
////                                clearDelegate.check_flag = "clear_cookies";
//                                var cook_str = sessiondispatcher.get_str();
//                                if (cook_str.indexOf("c") < 0)
//                                    sessiondispatcher.set_str("c");
//                            }
//                            else if (flags == "clear_package") {
////                                clearDelegate.check_flag = "clear_package";
//                                var plugin_str = sessiondispatcher.get_str();
//                                if (plugin_str.indexOf("p") < 0)
//                                    sessiondispatcher.set_str("p");
//                            }
//                        }
//                        else if (!checkbox.checked) {

//                            container.check_flag = false;
//                            console.log(container.check_flag);
//                            console.log(container.num);
////                            clearDelegate.check_flag = "";
//                            if (flags == "clear_rubbish") {
//                                var rubbish_str1 = sessiondispatcher.get_str();
//                                if (rubbish_str1.indexOf("r") > -1) {
//                                    sessiondispatcher.del_str("r");
//                                }
//                            }
//                            else if (flags == "clear_history") {
//                                var history_str1 = sessiondispatcher.get_str();
//                                console.log(history_str1);
//                                if (history_str1.indexOf("h") > -1) {
//                                    sessiondispatcher.del_str("h");
//                                }
//                            }
//                            else if (flags == "clear_cookies") {
//                                var cook_str1 = sessiondispatcher.get_str();
//                                if (cook_str1.indexOf("c") > -1)
//                                    sessiondispatcher.del_str("c");
//                            }
//                            else if (flags == "clear_package") {
//                                var plugin_str1 = sessiondispatcher.get_str();
//                                if (plugin_str1.indexOf("p") > -1)
//                                    sessiondispatcher.del_str("p");
//                            }
//                        }
//                    }
//                }
                Image {
                    id: clearImage
//                    width: 47; height: 47
                    fillMode: "PreserveAspectFit"
                    height: parent.height*0.9
                    source: picture
                    smooth: true
                    anchors {
//                        left: checkbox.right; leftMargin: 15
                        left: parent.left; leftMargin: 15
                        verticalCenter: parent.verticalCenter
                    }

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

                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
                    height: 28
                    width: 26
                    source: container.arrow
                    //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
                    rotation: expanded ? 0 : -180
                    smooth: true
                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                        rightMargin: 30
                    }
                }

                MouseArea {
                    id: mouseRegion
                    anchors.fill: status_update_content
                    onPressed: {
                        expanded = !expanded
                    }
                }
            }//母项Row

            //子项
            Item {
                id: subItemsRect
                property int itemHeight: delegate.itemHeight
                y: headerItemRect.height
                width: parent.width
                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
                height: expanded ? expandedItemCount * itemHeight : 0
                clip: true
                opacity: 1
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Column {
                    width: parent.width
                    Repeater {
                        id: subItemRepeater
//                        model: attributes
                        model: container.submodel
//                        model: mysubmodel
                        width: subItemsRect.width
                        /*Common.*/ListItem {
                            id: subListItem
                            width: delegate.width
                            height: subItemsRect.itemHeight
//                            text: subItemTitle
                            text: itemTitle
                            descript: desc
                            size_num: number
                            checkbox_status: container.check_flag
//                            bgImage: "../../img/icons/list_subitem.png"
                            bgImage: ""
                            fontName: container.subItemFontName
                            fontSize: container.subItemFontSize
                            fontColor: container.subItemFontColor
                            textIndent: 20

                            btn_flag: container.btn_flag

                            onClicked: {/*console.log(number)*/}
                        }

                    }//Repeater
                }//Column
            }//子项Item
        }
    }//Component


    ScrollArea {
        frame:false
        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        anchors.topMargin: 50
        Item {
            width:parent.width
            height:(container.num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: container.listmodel
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
}




//Rectangle {
//    id:container
////    property SessionDispatcher dis: sessiondispatcher
//    width: parent.width
//    height: 420

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


//    Component.onCompleted: {
//    }

//    //垃圾清理自定义标题栏
//    Common.TitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "test"
//        description:  "kobe lee"
//        btn_flag: "history_scan"
//    }

//    PluginListModel {
//        id: mainModel
//    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            property int itemHeight: 40
//            property alias expandedItemCount: subItemRepeater.count
//            property bool expanded: false
//            x: 0; y: 0;
//            width: container.width
//            height: headerItemRect.height + subItemsRect.height

//            //母项
//            Row {
//                id: headerItemRect
//                x: 0; y: 0
//                width: parent.width
//                height: parent.itemHeight
//                Image {
//                    id: logo
//                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.9
//                    source: "../img/icons/kysoft.png"
//                    smooth: true
//                    anchors {
//                        left: parent.left
//                        verticalCenter: parent.verticalCenter
//                        leftMargin: 10
//                    }
//                }

//                Text {
//                    id: itemtext
//                    text: itemTitle
//                    anchors {
//                        left: logo.right
//                        verticalCenter: parent.verticalCenter
//                        leftMargin: 10
//                    }
//                }

//                Image {
//                    id: arrow
//                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
//                    source: container.arrow
//                    //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
//                    smooth: true
//                    anchors {
//                        right: parent.right
//                        verticalCenter: parent.verticalCenter
//                        rightMargin: 30
//                    }
//                }

//                MouseArea {
//                      id: mouseRegion
//                      anchors.fill: parent
//                      hoverEnabled: true
//                      onPressed: {
//                          expanded = !expanded
//                      }
//                  }
//            }//母项Row

//            //子项
//            Item {
//                id: subItemsRect
//                property int itemHeight: delegate.itemHeight
//                y: headerItemRect.height
//                width: parent.width
//                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
//                height: expanded ? expandedItemCount * itemHeight : 0
//                clip: true
//                opacity: 1
//                Behavior on height {
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: parent.width
//                    Repeater {
//                        id: subItemRepeater
//                        model: attributes
//                        width: subItemsRect.width
//                        MyListItem {
//                            id: subListItem
//                            width: delegate.width
//                            height: subItemsRect.itemHeight
//                            text: subItemTitle
//                            bgImage: "../img/icons/list_subitem.png"
//                            fontName: container.subItemFontName
//                            fontSize: container.subItemFontSize
//                            fontColor: container.subItemFontColor
//                            textIndent: 20
//                            onClicked: {}
//                        }//MyListItem

//                    }//Repeater
//                }//Column
//            }//子项Item
//        }
//    }//Component


//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        anchors.topMargin: 50
//        Item {
//            width:parent.width
//            height:450 //this height must be higher than root.height, then the slidebar can display
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
//}
