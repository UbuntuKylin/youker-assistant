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

Rectangle {
    id:container
//    property SessionDispatcher dis: sessiondispatcher
    width: parent.width
    height: 420

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

    Component.onCompleted: {
    }

    //垃圾清理自定义标题栏
    Common.MyTitleBar {
        id: titleBar; width: parent.width; height: 45; opacity: 0.9
        btn_text: "开始扫描"
        title: "test"
        description:  "kobe lee"
        btn_flag: "history_scan"
    }

    PluginListModel {
        id: mainModel
    }

    Component {
        id: listViewDelegate
        Item {
            id: delegate
            property int itemHeight: 40
            property alias expandedItemCount: subItemRepeater.count
            property bool expanded: false
            x: 0; y: 0;
            width: container.width
            height: headerItemRect.height + subItemsRect.height

            //母项
            Row {
                id: headerItemRect
                x: 0; y: 0
                width: parent.width
                height: parent.itemHeight
                Image {
                    id: logo
                    fillMode: "PreserveAspectFit"
                    height: parent.height*0.9
                    source: "../img/icons/kysoft.png"
                    smooth: true
                    anchors {
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 10
                    }
                }

                Text {
                    id: itemtext
                    text: itemTitle
                    anchors {
                        left: logo.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: 10
                    }
                }

                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
                    height: parent.height*0.3
                    source: container.arrow
                    //当鼠标点击后,箭头图片旋转90度
                    rotation: expanded ? 90 : 0
                    smooth: true
                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                        rightMargin: 30
                    }
                }

                MouseArea {
                      id: mouseRegion
                      anchors.fill: parent
                      hoverEnabled: true
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
                        model: attributes
                        width: subItemsRect.width
                        MyListItem {
                            id: subListItem
                            width: delegate.width
                            height: subItemsRect.itemHeight
                            text: subItemTitle
                            bgImage: "../img/icons/list_subitem.png"
                            fontName: container.subItemFontName
                            fontSize: container.subItemFontSize
                            fontColor: container.subItemFontColor
                            textIndent: 20
                            onClicked: {}
                        }//MyListItem

                    }//Repeater
                }//Column
            }//子项Item
        }
    }//Component


    ScrollArea {
        frame:false
        anchors.fill: parent
        anchors.top: titleBar.bottom
        anchors.topMargin: 50
        Item {
            width:parent.width
            height:450 //this height must be higher than root.height, then the slidebar can display
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
}



//Item {
//    id: container
//    width: parent.width
//    height: 420

//    property string bgImage: '../img/icons/list_item.png'
//    property string bgImagePressed: '../img/icons/list_item_pressed.png'
//    property string bgImageActive: '../img/icons/list_item_active.png'
//    property string bgImageSubItem: "../img/icons/list_subitem.png"
//    property string arrow: '../img/icons/arrow.png'
//    property string headerItemFontName: "Helvetica"
//    property int headerItemFontSize: 12
//    property color headerItemFontColor: "black"
//    // Font properties for  subitems
//    property string subItemFontName: "Helvetica"
//    property int subItemFontSize: headerItemFontSize-2
//    property color subItemFontColor: "black"

//    //垃圾清理自定义标题栏
//    Common.MyTitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "测试"
//        description:  "test"
//        btn_flag: "plugin"
//    }

//    PluginListModel {
//        id: mainModel
//    }

//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom

//        Item {
//            width:parent.width
//            height:450

//            ListView {
//                id: listView
//                height: parent.height - titleBar.height
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    top: parent.top
//                    topMargin: titleBar.height
//                }
//                model: mainModel
//                delegate: listViewDelegate
//                focus: true
//                spacing: 0
//            }
//        }
//    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            // Modify appearance from these properties
//            property int itemHeight: 40
//            property alias expandedItemCount: subItemRepeater.count

//            // Flag to indicate if this delegate is expanded
//            property bool expanded: false

//            x: 0; y: 0;
//            width: container.width
//            height: headerItemRect.height + subItemsRect.height

//            // Top level list item.
//            Row {
//                id: headerItemRect
//                x: 0; y: 0
//                width: parent.width
//                height: parent.itemHeight
////                text: itemTitle
////                onClicked: expanded = !expanded
////                bgImage: container.bgImage
////                bgImagePressed: container.bgImagePressed
////                bgImageActive: container.bgImageActive
////                fontName: container.headerItemFontName
////                fontSize: container.headerItemFontSize
////                fontColor: container.headerItemFontColor
////                fontBold: true
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
//                      anchors.fill: parent;

//                      onPressed: {
//                          expanded = !expanded
//                      }
//                  }
//            }
////            ListItem {
////                id: headerItemRect
////                x: 0; y: 0
////                width: parent.width
////                height: parent.itemHeight
////                text: itemTitle
////                onClicked: expanded = !expanded
////                bgImage: container.bgImage
////                bgImagePressed: container.bgImagePressed
////                bgImageActive: container.bgImageActive
////                fontName: container.headerItemFontName
////                fontSize: container.headerItemFontSize
////                fontColor: container.headerItemFontColor
////                fontBold: true
//////                Image {
//////                    id: logo
//////                    fillMode: "PreserveAspectFit"
//////                    height: parent.height*0.9
//////                    source: "../img/icons/kysoft1.png"
//////                    smooth: true
//////                    anchors {
//////                        left: parent.left
//////                        verticalCenter: parent.verticalCenter
//////                        leftMargin: 10
//////                    }
//////                }
////                Image {
////                    id: arrow
////                    fillMode: "PreserveAspectFit"
////                    height: parent.height*0.3
////                    source: container.arrow
////                    //当鼠标点击后,箭头图片旋转90度
////                    rotation: expanded ? 90 : 0
////                    smooth: true
////                    anchors {
////                        right: parent.right
////                        verticalCenter: parent.verticalCenter
////                        rightMargin: 30
////                    }
////                }
////            }

//            // Subitems are in a column whose height depends
//            // on the expanded status. When not expandend, it is zero.
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
//                    // Animate subitem expansion. After the final height is reached,
//                    // ensure that it is visible to the user.
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: parent.width

//                    // Repeater creates each sub-ListItem using attributes
//                    // from the model.
//                    Repeater {
//                        id: subItemRepeater
//                        model: attributes
//                        width: subItemsRect.width

//                        MyListItem {
//                            id: subListItem
//                            width: delegate.width
//                            height: subItemsRect.itemHeight
//                            text: subItemTitle
//                            bgImage: container.bgImageSubItem
//                            fontName: container.subItemFontName
//                            fontSize: container.subItemFontSize
//                            fontColor: container.subItemFontColor
//                            textIndent: 20
//                            onClicked: {
//                            }
//                        }
//                    }
//                }
//            }




//        }
//    }
//}




//Item {
//    id: container
//    width: parent.width
//    height: 420

//    property string bgImage: '../img/icons/list_item.png'
//    property string bgImagePressed: '../img/icons/list_item_pressed.png'
//    property string bgImageActive: '../img/icons/list_item_active.png'
//    property string bgImageSubItem: "../img/icons/list_subitem.png"
//    property string arrow: '../img/icons/arrow.png'
//    property string headerItemFontName: "Helvetica"
//    property int headerItemFontSize: 12
//    property color headerItemFontColor: "black"
//    // Font properties for  subitems
//    property string subItemFontName: "Helvetica"
//    property int subItemFontSize: headerItemFontSize-2
//    property color subItemFontColor: "black"

//    //垃圾清理自定义标题栏
//    Common.MyTitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "测试"
//        description:  "test"
//        btn_flag: "plugin"
//    }

//    PluginListModel {
//        id: mainModel
//    }

//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        Item {
//            width:parent.width
//            height:450

//            ListView {
//                id: listView
//                height: parent.height - titleBar.height
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    top: parent.top
//                    topMargin: titleBar.height
//                }
//                model: mainModel
//                delegate: listViewDelegate
//                focus: true
//                spacing: 0
//            }
//        }
//    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            // Modify appearance from these properties
//            property int itemHeight: 40
//            property alias expandedItemCount: subItemRepeater.count

//            // Flag to indicate if this delegate is expanded
//            property bool expanded: false

//            x: 0; y: 0;
//            width: container.width
//            height: headerItemRect.height + subItemsRect.height

//            // Top level list item.
//            ListItem {
//                id: headerItemRect
//                x: 0; y: 0
//                width: parent.width
//                height: parent.itemHeight
//                text: itemTitle
//                onClicked: expanded = !expanded
//                bgImage: container.bgImage
//                bgImagePressed: container.bgImagePressed
//                bgImageActive: container.bgImageActive
//                fontName: container.headerItemFontName
//                fontSize: container.headerItemFontSize
//                fontColor: container.headerItemFontColor
//                fontBold: true
////                Image {
////                    id: logo
////                    fillMode: "PreserveAspectFit"
////                    height: parent.height*0.9
////                    source: "../img/icons/kysoft1.png"
////                    smooth: true
////                    anchors {
////                        left: parent.left
////                        verticalCenter: parent.verticalCenter
////                        leftMargin: 10
////                    }
////                }
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
//            }

//            // Subitems are in a column whose height depends
//            // on the expanded status. When not expandend, it is zero.
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
//                    // Animate subitem expansion. After the final height is reached,
//                    // ensure that it is visible to the user.
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: parent.width

//                    // Repeater creates each sub-ListItem using attributes
//                    // from the model.
//                    Repeater {
//                        id: subItemRepeater
//                        model: attributes
//                        width: subItemsRect.width

//                        MyListItem {
//                            id: subListItem
//                            width: delegate.width
//                            height: subItemsRect.itemHeight
//                            text: subItemTitle
//                            bgImage: container.bgImageSubItem
//                            fontName: container.subItemFontName
//                            fontSize: container.subItemFontSize
//                            fontColor: container.subItemFontColor
//                            textIndent: 20
//                            onClicked: {
//                            }
//                        }
//                    }
//                }
//            }




//        }
//    }
//}
