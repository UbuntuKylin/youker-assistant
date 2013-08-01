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
import SessionType 0.1
//import SystemType 0.1
import QtDesktop 0.1
import "../common" as Common

Rectangle {
    id: widgetthemepage
    width: parent.width
    height: 475
    property string actiontitle: "窗口主题设置"
    property string actiontext: "选中您想设置的主题，点击确定按钮更换主题。"
    property string init_theme: ""
    property string selected_theme: ""
    property SessionDispatcher dis: sessiondispatcher
    property bool listorgrid: false
    property int num: 0

    Component.onCompleted: {
        var syslist = sessiondispatcher.get_themes_qt();
        widgetthemepage.num = syslist.length;
        widgetthemepage.init_theme = sessiondispatcher.get_theme_qt();
        syslist.unshift(widgetthemepage.init_theme);
        themeModel.clear();
        for(var i=0; i < syslist.length; i++) {
            themeModel.append({"icon": "../../img/skin/" + syslist[i] + ".png", "name": syslist[i]});
            if (i!=0 && syslist[i] == widgetthemepage.init_theme)
                themeModel.remove(i);
        }
    }


    Connections {
        target: toolBar
        //按下确定按钮
        onOkBtnClicked: {
            if (settigsDetails.setTitle == "WidgetTheme") {
//                console.log("-----------------");
//                console.log(widgetthemepage.selected_theme);
//                console.log(widgetthemepage.init_theme);
                if (widgetthemepage.selected_theme == "")
                    sessiondispatcher.set_theme_qt(widgetthemepage.init_theme);
                else
                    sessiondispatcher.set_theme_qt(widgetthemepage.selected_theme);
            }
        }
    }

    ListModel {
        id: themeModel
        ListElement {
            icon: ""
            name: ""
            flag: ""
        }
    }

    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

     Component {
         id: themegridDelegate
         Item {
             id: griditem
             width: themegrid.cellWidth; height: themegrid.cellHeight

//             function iconClicked() {
//                 widgetthemepage.init_theme = name;
//             }

             Column {
                 anchors.fill: parent
                 spacing: 10
                 Image {
                     id: seticon
                     source: icon
                     anchors.top: parent.top
                     anchors.topMargin: 5
//                     width: griditem.width - 20
//                     height: griditem.height - 30
                     width: 120
                     height: 120
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
                     //kobe:选中项深色块移动
//                     iconClicked();
                     griditem.GridView.view.currentIndex = index;
                     widgetthemepage.selected_theme = name;
//                     console.log(name);
//                     sessiondispatcher.set_theme_qt(name);
                 }
             }
         }
     }


//     Component {
//         id: themelistDelegate
//         Item {
//             id: listitem
////             width: themegrid.cellWidth; height: themegrid.cellHeight
//             width: 120; height: 120

//             function listiconClicked() {
//                 widgetthemepage.cur_theme = name;
//             }

//             Column {
//                 anchors.fill: parent
//                 spacing: 5
//                 Image {
//                     id: listseticon
//                     source: icon
//                     anchors.top: parent.top
//                     anchors.topMargin: 5
//                     width: listitem.width - 20
//                     height: listitem.height - 30
//                     anchors.horizontalCenter: parent.horizontalCenter
//                 }
//                 Text {
//                     id: listbtnText
//                     height: 20
//                     anchors.horizontalCenter: parent.horizontalCenter
//                     color: "green"
//                     text: qsTr(name)
//                 }
//             }
//             Image {
//                 id: listbtnImg
//                 anchors.fill: parent
//                 source: ""
//             }
//             MouseArea {
//                 id: listsignaltest
//                 hoverEnabled: true
//                 anchors.fill: parent
//                 onEntered: listbtnImg.source = "../../img/toolWidget/menu_hover.png"
//                 onPressed: listbtnImg.source = "../../img/toolWidget/menu_press.png"
//                 //要判断松开是鼠标位置
//                 onReleased: listbtnImg.source = "../../img/toolWidget/menu_hover.png"
//                 onExited: listbtnImg.source = ""
//                 onClicked: {
//                     listiconClicked();
//                 }
//             }
//         }
//     }


//     Row {
//         id: titlerow
//         spacing: 80
//         anchors {
//            top: parent.top
//            topMargin: 44
//            left: parent.left
//            leftMargin: 80
//         }
//         width: parent.width
//         Column {
//             id: titlecolumn
////             width: parent.width
//             Text {
//                  text: widgetthemepage.actiontitle
//                  font.bold: true
//                  font.pixelSize: 14
//                  color: "#383838"
//              }
//              Text {
//                  text: widgetthemepage.actiontext
//                  font.pixelSize: 12
//                  color: "#7a7a7a"
//              }
//         }
//        Common.Button {
//            width: 23
//            height: 23
//            hoverimage: "sort.png"
////            anchors {
////               left: titlecolumn.right
////               leftMargin: 200
////            }
//            onClicked: {
//                if (widgetthemepage.listorgrid == true) {
//                    console.log("111");
//                    widgetthemepage.listorgrid = false;
//                }
//                else {
//                    widgetthemepage.listorgrid = true;
//                    console.log("222");
//                }
//            }
//        }
//     }

     Column {
         id: titlecolumn
         anchors {
            top: parent.top
            topMargin: 44
            left: parent.left
            leftMargin: 80
         }
//             width: parent.width
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



     GridView {
         id: themegrid
//         visible: true
         anchors {
             fill: parent
             top: parent.top
             topMargin: 100
             left: parent.left
             leftMargin: 60
         }
         cellWidth: 120; cellHeight: 120
         model: themeModel
         delegate: themegridDelegate
         focus: true
         cacheBuffer: 1000
         highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
     }

//     ScrollArea {
//         id: scroolarea
//         visible: false
//         frame:false
//         width: parent.width - 60 //因为左边移位了60
//         height: 320
//         anchors {
//             top: titlerow.bottom
//             topMargin: 10
//             left: parent.left
//             leftMargin: 60
//         }
//         Item {
//             width:parent.width
//             height: widgetthemepage.num * 120
//             ListView {
//                 id: themelist
//                 width: parent.width
//                 height: parent.height
//                 model: themeModel
//                 delegate: themelistDelegate
//                 focus: true
//                 cacheBuffer: 1000
//        //         x: -(parent.width * 1.5)
////                 visible: false
//                 opacity: 1
//                 spacing: 10
//                 snapMode: ListView.NoSnap
//                 boundsBehavior: Flickable.DragOverBounds
//                 currentIndex: 0
//                 preferredHighlightBegin: 0
//                 preferredHighlightEnd: preferredHighlightBegin
//                 highlightRangeMode: ListView.StrictlyEnforceRange
//             }
//         }//Item
//     }//ScrollArea
//     states: [
//         State {
//             name: "ListView"; when: widgetthemepage.listorgrid == true
////             PropertyChanges { target: themelist; x: 0 }
////             PropertyChanges { target: themelist; visible: true }
//             PropertyChanges { target: scroolarea; visible: true }
////             PropertyChanges { target: themegrid; x: -(parent.width * 1.5) }
//             PropertyChanges { target: themegrid; visible: false}
//         }
//     ]
//     transitions: [
//         Transition {
//             NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//         }
//     ]
//     Item { id: foreground; anchors.fill: parent }
 }




//Item {
//    id: screen

//    width: parent.width
//    height: 475
//    property bool listorgrid: false

//    Rectangle {
//        id: widgetthemepage
//        anchors.fill: parent
////        width: parent.width
////        height: 475
//        property string actiontitle: "窗口主题设置"
//        property string actiontext: "单击某个主题立即更改 窗口主题，您可以点击右侧按钮选择想要的排序方式。"
//        property string cur_theme: ""
//        property SessionDispatcher dis: sessiondispatcher

//        Component.onCompleted: {
//            var syslist = sessiondispatcher.get_themes_qt();
//            widgetthemepage.cur_theme = sessiondispatcher.get_theme_qt();
//            syslist.unshift(widgetthemepage.cur_theme);
//    //        var current_theme = sessiondispatcher.get_theme_qt();
//    //        syslist.unshift(current_theme);
//            themeModel.clear();
//            for(var i=0; i < syslist.length; i++) {
//                themeModel.append({"icon": "../../img/icons/systemsound.png", "name": syslist[i]});
//                if (i!=0 && syslist[i] == widgetthemepage.cur_theme)
//                    themeModel.remove(i);
//    //            if (i!=0 && syslist[i] == current_theme)
//    //                themeModel.remove(i);
//            }
//        }


//        Connections {
//            target: toolBar
//            //按下确定按钮
//            onOkBtnClicked: {
//                if (settigsDetails.setTitle == "WidgetTheme") {
//    //                console.log("-----------------");
//    //                console.log(widgetthemepage.cur_theme);
//                    sessiondispatcher.set_theme_qt(syscombo.selectedText);
//                }
//            }
//        }

//        ListModel {
//            id: themeModel
//            ListElement {
//                icon: ""
//                name: ""
//                flag: ""
//            }
//        }

//        //背景
//        Image {
//            source: "../../img/skin/bg-left.png"
//            anchors.fill: parent
//        }

//         Component {
//             id: themegridDelegate
//             Item {
//                 id: griditem
//                 width: themegrid.cellWidth; height: themegrid.cellHeight

//                 function iconClicked() {
//                     widgetthemepage.cur_theme = name;
//                 }

//                 Column {
//                     anchors.fill: parent
//                     spacing: 5
//                     Image {
//                         id: seticon
//                         source: icon
//                         anchors.top: parent.top
//                         anchors.topMargin: 5
//                         width: griditem.width - 20
//                         height: griditem.height - 30
//                         anchors.horizontalCenter: parent.horizontalCenter
//                     }
//                     Text {
//                         id: btnText
//                         height: 20
//                         anchors.horizontalCenter: parent.horizontalCenter
//                         color: "green"
//                         text: qsTr(name)
//                     }
//                 }


//                 Image {
//                     id: btnImg
//                     anchors.fill: parent
//                     source: ""
//                 }

//                 MouseArea {
//                     id: signaltest
//                     hoverEnabled: true
//                     anchors.fill: parent
//                     onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                     onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//                     //要判断松开是鼠标位置
//                     onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//                     onExited: btnImg.source = ""
//                     onClicked: {
//                         //kobe:选中项深色块移动
//                         iconClicked();
//                         griditem.GridView.view.currentIndex = index;
//                     }
//                 }
//             }
//         }


//         Component {
//             id: themelistDelegate
//             Item {
//                 id: listitem
//    //             width: themegrid.cellWidth; height: themegrid.cellHeight

//                 function listiconClicked() {
//                     widgetthemepage.cur_theme = name;
//                 }

//                 Column {
//                     anchors.fill: parent
//                     spacing: 5
//                     Image {
//                         id: listseticon
//                         source: icon
//                         anchors.top: parent.top
//                         anchors.topMargin: 5
//                         width: listitem.width - 20
//                         height: listitem.height - 30
//                         anchors.horizontalCenter: parent.horizontalCenter
//                     }
//                     Text {
//                         id: listbtnText
//                         height: 20
//                         anchors.horizontalCenter: parent.horizontalCenter
//                         color: "green"
//                         text: qsTr(name)
//                     }
//                 }
//                 Image {
//                     id: listbtnImg
//                     anchors.fill: parent
//                     source: ""
//                 }
//                 MouseArea {
//                     id: listsignaltest
//                     hoverEnabled: true
//                     anchors.fill: parent
//                     onEntered: listbtnImg.source = "../../img/toolWidget/menu_hover.png"
//                     onPressed: listbtnImg.source = "../../img/toolWidget/menu_press.png"
//                     //要判断松开是鼠标位置
//                     onReleased: listbtnImg.source = "../../img/toolWidget/menu_hover.png"
//                     onExited: listbtnImg.source = ""
//                     onClicked: {
//                         listiconClicked();
//                     }
//                 }
//             }
//         }


//         Column {
//             spacing: 10
//             anchors {
//                top: parent.top
//                topMargin: 44
//                left: parent.left
//                leftMargin: 80
//             }
//             Text {
//                  text: widgetthemepage.actiontitle
//                  font.bold: true
//                  font.pixelSize: 14
//                  color: "#383838"
//              }
//              Text {
//                  text: widgetthemepage.actiontext
//                  font.pixelSize: 12
//                  color: "#7a7a7a"
//              }
//         }

//         Common.Button {
//             anchors.top: parent.top
//             anchors.right: parent.right
//             width: 120
//             height: 39
//             hoverimage: "scan-start.png"
//             onClicked: {
//                 if (screen.listorgrid == true) {
//                     console.log("111");
//                     screen.listorgrid = false;
//                 }
//                 else {
//                     screen.listorgrid = true;
//                     console.log("222");
//                 }
//             }
//         }


//         Item {
//             id: views
//             width: parent.width

//             GridView {
//                 id: themegrid
//                 anchors {
//                     fill: parent
//                     top: parent.top
//                     topMargin: 120
//                     left: parent.left
//                     leftMargin: 60
//                 }
//                 cellWidth: 120; cellHeight: 120
//                 model: themeModel
//                 delegate: themegridDelegate
//                 focus: true
//                 cacheBuffer: 1000
//                 highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
//             }

//             ListView {
//                 id: themelist
//                 anchors {
//                     fill: parent
//                     top: parent.top
//                     topMargin: 120
//                     left: parent.left
//                     leftMargin: 60
//                 }
//                 width: parent.width
//                 height: parent.height
//                 model: themeModel
//                 delegate: themelistDelegate
//        //         focus: true
//                 cacheBuffer: 1000
//                 x: -(parent.width * 1.5)
//             }


//             states: [
//                 State {
//                     name: "ListView"; when: screen.listorgrid == true
//                     PropertyChanges { target: themelist; x: 0 }
//                     PropertyChanges { target: themegrid; x: -(parent.width * 1.5) }
//                 }
//             ]
//             transitions: [
//                 Transition {
//                     NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                 }
//             ]
//             Item { id: foreground; anchors.fill: parent }
//         }
//     }
//}




//Rectangle {
//    id: widgetthemepage
//    property bool on: true
//    width: parent.width
//    height: 475
//    property string fontName: "Helvetica"
//    property int fontSize: 12
//    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
//    property int cursor_size: 24
//    property string default_theme: ""
//    property string default_icon_theme: ""
//    property string default_cursor_theme: ""

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    //OK工具栏
////    Common.OkToolBar {
////        id: oktoolBar
//////        visible: idenfer ? true : false
////        visible: false
////        height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
////        buttonLabel: qsTr("确定")
////        onButtonClicked: {
////            console.log("oktoolbar clicked...");
////        }
////    }


//    Component.onCompleted: {
////        console.log("------55555---------");
//        widgetthemepage.cursor_size = themespinbox.value;
//        widgetthemepage.default_theme = sessiondispatcher.get_theme_qt();
//        widgetthemepage.default_icon_theme = sessiondispatcher.get_icon_theme_qt();
//        widgetthemepage.default_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
////        console.log(widgetthemepage.default_theme);
////        console.log(widgetthemepage.default_icon_theme);
////        console.log(widgetthemepage.default_cursor_theme);
////        console.log(widgetthemepage.cursor_size);


////        var syslist = sessiondispatcher.get_themes_qt();
////        syslist.unshift(widgetthemepage.default_theme);
////        choices1.clear();
////        for(var i=0; i < syslist.length; i++) {
////            choices1.append({"text": syslist[i]});
////            if (i!=0 && syslist[i] == widgetthemepage.default_theme)
////                choices1.remove(i);
////        }

////        var iconlist = sessiondispatcher.get_icon_themes_qt();
////        iconlist.unshift(widgetthemepage.default_icon_themeg);
////        choices2.clear();
////        for(var j=0; j < iconlist.length; j++) {
////            choices2.append({"text": iconlist[j]});
////            if (j!=0 && iconlist[j] == widgetthemepage.default_icon_theme)
////                choices2.remove(j);
////        }

////        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
////        cursorlist.unshift(widgetthemepage.default_cursor_theme);
////        choices3.clear();
////        for(var k=0; k < cursorlist.length; k++) {
////            choices3.append({"text": cursorlist[k]});
////            if (k!=0 && cursorlist[k] == widgetthemepage.default_cursor_theme)
////                choices3.remove(k);
////        }

//        var syslist = sessiondispatcher.get_themes_qt();
//        var current_theme = sessiondispatcher.get_theme_qt();
//        syslist.unshift(current_theme);
//        choices1.clear();
//        for(var i=0; i < syslist.length; i++) {
//            choices1.append({"text": syslist[i]});
//            if (i!=0 && syslist[i] == current_theme)
//                choices1.remove(i);
//        }

//        var iconlist = sessiondispatcher.get_icon_themes_qt();
//        var current_icon_theme = sessiondispatcher.get_icon_theme_qt();
//        iconlist.unshift(current_icon_theme);
//        choices2.clear();
//        for(var j=0; j < iconlist.length; j++) {
//            choices2.append({"text": iconlist[j]});
//            if (j!=0 && iconlist[j] == current_icon_theme)
//                choices2.remove(j);
//        }

//        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
//        var current_cursor_theme = sessiondispatcher.get_cursor_theme_qt();
//        cursorlist.unshift(current_cursor_theme);
//        choices3.clear();
//        for(var k=0; k < cursorlist.length; k++) {
//            choices3.append({"text": cursorlist[k]});
//            if (k!=0 && cursorlist[k] == current_cursor_theme)
//                choices3.remove(k);
//        }

//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onOkBtnClicked: {
//            if (settigsDetails.setTitle == "theme") {
//                console.log("-----------------");
////                sessiondispatcher.set_theme_qt(syscombo.selectedText);
////                sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
////                sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
////                console.log(current_theme.text);
////                console.log(syscombo.selectedText);
////                console.log(current_icon_theme.text);
////                console.log(iconcombo.selectedText);
////                console.log(current_cursor_theme.text);
////                console.log(cursorcombo.selectedText);
//                //default:ubuntukylin-theme
//                if (widgetthemepage.default_theme != syscombo.selectedText) {
//                    console.log("111");
//                    widgetthemepage.default_theme = syscombo.selectedText;
//                    sessiondispatcher.set_theme_qt(syscombo.selectedText);
//                }
//                else
//                    console.log("222");
//                //default:ubuntukylin-icon-theme
//                if (widgetthemepage.default_icon_theme != iconcombo.selectedText) {
//                    console.log("333");
//                    widgetthemepage.default_icon_theme = iconcombo.selectedText;
//                    sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                }
//                else
//                    console.log("444");
//                //default:DMZ-White
//                if (widgetthemepage.default_cursor_theme != cursorcombo.selectedText) {
//                    console.log("555");
//                    widgetthemepage.default_cursor_theme = cursorcombo.selectedText;
//                    sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
//                }
//                else
//                    console.log("666");
//                //default:24
//                if (widgetthemepage.cursor_size != themespinbox.value) {
//                    widgetthemepage.cursor_size = themespinbox.value;
//                    sessiondispatcher.set_cursor_size_qt(themespinbox.value);
//                }
////                console.log("*********************88");
////                console.log(current_theme.text);
////                console.log(syscombo.selectedText);
////                console.log(current_icon_theme.text);
////                console.log(iconcombo.selectedText);
////                console.log(current_cursor_theme.text);
////                console.log(cursorcombo.selectedText);
////                console.log(widgetthemepage.cursor_size);
////                console.log(themespinbox.value);

//            }

////                console.log(themespinbox.value);
////                console.log(themelabel.text);
//        }
//    }
//    ListModel {
//        id: choices0
//        ListElement { text: "" }
//    }
//    ListModel {
//        id: choices1
//        ListElement { text: "kobe999" }
//    }
//    ListModel {
//        id: choices2
//        ListElement { text: "kobe888" }
//    }
//    ListModel {
//        id: choices3
//        ListElement { text: "kobe777" }
//    }


//    Label {
//        id: theme
//        text: qsTr("主题设置>")
//        height: 30
//        font.bold: true
//        font.family: "Ubuntu"
//        elide: Text.ElideRight
//        font.pointSize: 20
//        anchors {
//            top: parent.top
//            topMargin: 10
//            left: parent.left
//            leftMargin: 15
//        }
//    }

//    Column {
//        spacing: 20
//        anchors {
////            top: parent.top
////            topMargin: 20
//            top: theme.bottom
//            topMargin: 20
//            horizontalCenter: parent.horizontalCenter
//        }

////        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            anchors.horizontalCenter: parent.horizontalCenter
//            Label {
//                id: systhemelabel
//                width: 110
//                text: qsTr("系统主题:")
//                font {
//                    family: widgetthemepage.fontName
//                    pointSize: widgetthemepage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: syscombo
//                model: choices1
//                width: cursorthemelabel.width

//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_theme
////                text: sessiondispatcher.get_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: iconthemelabel
//                width: 110
//                text: qsTr("图标主题:")
//                font {
//                    family: widgetthemepage.fontName
//                    pointSize: widgetthemepage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: iconcombo
//                model: choices2
//                width: cursorthemelabel.width
//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_icon_theme
////                text: sessiondispatcher.get_icon_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: cursorthemelabel
//                width: 110
//                text: qsTr("cursor主题:")
//                font {
//                    family: widgetthemepage.fontName
//                    pointSize: widgetthemepage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            ComboBox {
//                id: cursorcombo
//                model: choices3
//                width: cursorthemelabel.width
//                onSelectedTextChanged: console.log(selectedText)
//            }
////            Label {
////                id: current_cursor_theme
////                text: sessiondispatcher.get_cursor_theme_qt()
////                width: cursorthemelabel.width
////                anchors.verticalCenter: parent.verticalCenter
////            }
//        }

//        Row {
//            Label {
//                id: trashlabel
//                width: 110
//                text: qsTr("cursor大小:")
//                font {
//                    family: widgetthemepage.fontName
//                    pointSize: widgetthemepage.fontSize
//                }
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            SpinBox {
//                id: themespinbox
//                width: trashlabel.width
////                width: 97
//                minimumValue: 0//32
//                maximumValue: 64
//                value: sessiondispatcher.get_cursor_size_qt()
////                value: 48
//            }
//        }
//    }//Column

//}










//import QtQuick 1.1
////import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
//import QtDesktop 0.1
//import "../common" as Common
//import "../common" as Common
//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
////    property Dispatcher dis: mydispather

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    Component.onCompleted: {
////        choices.clear();
////        choices.append({"text": mydispather.get_themes()[0]});
////        choices.append({"text": mydispather.get_themes()[1]});
////        choices.append({"text": mydispather.get_themes()[2]});
////        choices.append({"text": mydispather.get_themes()[3]});

////        streamModel.sync();
//    }

//    ListModel {
//        id: choices
//        ListElement { text: "theme" }
//        ListElement { text: "lixiang" }
//        ListElement { text: "ps" }
//        ListElement { text: "baby" }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onButton2Clicked: {
////            console.log("111111111111");
////            console.log(settigsDetails.setTitle);
//            if (settigsDetails.setTitle == "theme")
//                console.log(themelabel.text);
////            console.log("222222222222");
//        }
//    }

//    Column {
//        spacing: 20
//        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            Label {
//                id:themelabel
//                width: 110
//                text: qsTr("ps1-model")
//            }
//            ComboBox {
//                id: combobox
//                model: choices;
//                width: parent.width;
////                KeyNavigation.tab: t1
////                KeyNavigation.backtab: button2
////                onSelectedIndexChanged: console.log(selectedText)
//            }
//            Button {
//                id: button1
//                text: qsTr("确定")
//                width: 96
//                tooltip:"This is an interesting tool tip"
//                //                KeyNavigation.tab: button2
//                //                KeyNavigation.backtab: frame.tabBar
//                onClicked: {

//                }
//            }
//        }
//        Row {
//            Label {
//                id: modelabel1
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox2
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel3
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox4
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel5
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox6
//                x: 110
//            }
//        }


//    }//Column

//}





//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Column {
//        spacing: 20
//        anchors.top: parent.top
//        anchors.topMargin: 30
//        anchors.left: parent.left
//        anchors.leftMargin: 30

//        Row {
//            Label {
//                id: hidelabel
//                width: 110
//                text: qsTr("自动隐藏:")
//            }
//            CheckBox {
//                id: enabledCheck
//                text: qsTr("开启")
//                checked: false
//                onCheckedChanged: {}
//                onClicked: {
////                    enabledCheck.checked = !enabledCheck.checked;
////                    if (enabledCheck.checked == true) {
//////                        enabledCheck.checked = false;
////                        enabledCheck.text = qsTr("关闭");
////                    }
////                    else if (enabledCheck.checked == false){
//////                        enabledCheck.checked = true;
////                        enabledCheck.text = qsTr("开启");
////                    }
//                }
//            }

////            Common.Switch {
////                id: themeSwitch
////                anchors.right: parent.right
////                height: parent.height
////                spacing: 8
////                textOn: qsTr("On")
////                textOff: qsTr("Off")
////                fontColor: "#666666"
////                onSwitched: lancherpage.on = position
//////                id: switchLauncher
////////                checked: false
//////                x: 130
////////                onClicked: {
////////                    //kobe: wait for adding function
////////                    mydispather.set_launcher(switchLauncher.checked)
////////                }
////            }
//        }

//        Row {
//            Label {
//                id: sizelabel
//                width: 110
//                text: qsTr("图标大小:")
//            }
//            Slider {
//                id: slider
//                x: 130
////                function formatValue(v) { return v.toFixed(2) }
//                minimumValue: 0
//                maximumValue: 100
//                value: 0
////                live: true
////                onTouched: {
////                    console.log(slider.value)
////                }
//            }
//        }

//        Row {
//            Label {
//                id: locationlabel
//                width: 110
//                text: qsTr("位置:")
//            }
//            RadioButton {
//                id: radioleft
//                x: 130
////                text: "靠左"
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel1
//                width: 110
//                text: qsTr("输入用户名:")
//            }
//            TextField {
//                id: textfield1
//                placeholderText: qsTr("put your username")
//                echoMode: TextInput.Normal
////                hasClearButton: true
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield1.text)
//                }
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel2
//                width: 110
//                text: qsTr("输入密码:")
//            }
//            TextField {
//                id: textfield2
//                placeholderText: qsTr("put your password")
////                hasClearButton: true
//                echoMode: TextInput.Password
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield2.text)
//                }

//            }
//        }

//        Row {
//            Label {
//                id: progresslabel
//                width: 110
//                text: qsTr("进度显示:")
//            }
//            ProgressBar {
//                id: progressbar
////                indeterminate: true
//                value: 24
//                minimumValue: 0
//                maximumValue: 100

//            }
//        }

//        Row {
//            Label {
//                id: modelabel
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox
//                x: 110
////                titel1: "111111111"
////                titel2: "222222222"
////                titel3: "333333333"
////                flags: "launcher"
//            }

//        }
//    }
//}