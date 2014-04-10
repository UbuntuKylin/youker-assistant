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
    id: container

    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""
    property int item_index
    property string bgImage: "../../img/icons/green.png"
    property string bgImage2: "../../img/icons/blue.png"
    property string bgImageSelected: '../../img/icons/list_item_selected.png'
    property string bgImagePressed: '../../img/icons/list_item_pressed.png'
    property bool selected: false
    property bool selectable: false
//    property int textIndent: 0
    property bool checkbox_status: true
    property bool split_status: false

    property string btn_flag: "one_key_scan"
    property string itemFlag//cache标记

    property string browserFlag//浏览器标记
    signal change_num(bool check_status, string browser_flag)   //作为子项checkbox，当状态改变时需要通过信号传给父项以进行个数统计
    signal clicked(string path);

    signal getCacheItemCheckBoxStatus(string flag, bool status, int index); //test

    width: 800//850
    height: 30
    clip: true
    onSelectedChanged: {
        selected ? state = 'selected' : state = '';
    }
    onCheckbox_statusChanged: {
        checkbox.checked=checkbox_status;
    }  //当父项传进来的check值改变时，强制改变全部子项的check值以进行统一控制

    function get_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

//    BorderImage {
//        id: background
//        anchors {
//            left: parent.left
//            leftMargin: 20
//        }

////        border { top: 9; bottom: 36; left: 35; right: 35; }
////        source: bgImage
//        border {left: 35; right: 35; }
//        source: (container.item_index%2 == 0) ? bgImage : bgImage2
//        anchors.fill: parent

//    }
    Rectangle {
        id: background
        anchors.fill: parent
        color: (container.item_index%2 == 0) ? "#d7ecfb" : "transparent"
//        color: (container.item_index%2 == 0) ? "#d0eafb" : "#d7eefd"
//         border.color: "black"
//         border.width: 5
//         radius: 10
     }

    Common.CheckBox {
        id: checkbox
//        width: 30
        checked: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30

        onClicked: {
            container.getCacheItemCheckBoxStatus(itemFlag, checkbox.checked, item_index);
        }

        onCheckedChanged: {
            //单个checkbox状态改变时，先将状态通过信号change_num()传递给BrowserCookies.qml
            container.change_num(checkbox.checked, container.browserFlag);
//            if (checkbox.checked) {
//                if (btn_flag == "cache_work") {
////                if(container.itemFlag == "apt") {
//                    var aptlist = systemdispatcher.get_cache_args();
//                    var word_flag = "false";
//                    for (var i=0; i<aptlist.length; i++) {
//                        if (aptlist[i] == container.text) {
//                            word_flag = "true";
//                            break;
//                        }
//                    }
//                    if (word_flag == "false") {
//                        systemdispatcher.set_cache_args(container.text);
//                    }
//                }
//                else if (btn_flag == "package_work") {
//                    var mylist = systemdispatcher.get_package_args();
//                    var word_flag3 = "false";
//                    for (var q=0; q<mylist.length; q++) {
//                        if (mylist[q] == container.text) {
//                            word_flag3 = "true";
//                            break;
//                        }
//                    }
//                    if (word_flag3 == "false") {
//                        systemdispatcher.set_package_args(container.text);
//                    }
//                }
//                else if (btn_flag == "browser_work") {
//                    var browserlist = systemdispatcher.get_browser_args();
//                    var word_flag4 = "false";
//                    for (var p=0; q<browserlist.length; p++) {
//                        if (browserlist[p] == container.text) {
//                            word_flag4 = "true";
//                            break;
//                        }
//                    }
//                    if (word_flag4 == "false") {
//                        systemdispatcher.set_browser_args(container.text);
//                    }
//                }
//            }
//            else if (!checkbox.checked) {
////                if(container.itemFlag == "apt") {
//                if (btn_flag == "cache_work") {
//                    systemdispatcher.del_cache_args(container.text);
//                }
//                else if (btn_flag == "package_work") {
//                    systemdispatcher.del_package_args(container.text);
//                }
//                else if (btn_flag == "browser_work") {
//                    systemdispatcher.del_browser_args(container.text);
//                }
//                else if (btn_flag == "largestfile_work") {
//                    systemdispatcher.del_largestfile_args(container.descript);
//                }
//            }

        }
        visible: itemText.text=="" ? false : true
    }

    Row {
        id: itemText
        spacing: 10
        anchors {
            left: checkbox.right
            top: parent.top
            topMargin: 4
            bottomMargin: 4
            leftMargin: 10// + textIndent
            verticalCenter: container.verticalCenter
        }
        Image {
            width: 16
            height: 16
            anchors.verticalCenter: parent.verticalCenter
            source: {
                if(container.descript == "True") {//文件夹
                    "../../img/icons/folder.png"
                }
                else if(container.descript == "False") {//文件
                    "../../img/icons/book.png"
                }
                else {
                    ""
                }
            }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: container.fontSize
            font.family: container.fontName
            color: container.fontColor
            elide: Text.ElideRight
            text: container.split_status ? get_last_name(container.text) : container.text
            verticalAlignment: Text.AlignVCenter
        }

    }

    Row {
        spacing: 10
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 80
            verticalCenter: container.verticalCenter
        }
        Text {
            text: container.size_num
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: container.fontSize
            font.family: container.fontName
            color: container.fontColor
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: itemText
//        onClicked: container.clicked();
        onDoubleClicked: {//双击浏览器缓存栏目时，可以打开文件夹
            if((btn_flag == "browser_work") || (btn_flag == "cache_work" && container.descript == "True")) {
                container.clicked(container.text);
            }
        }

        onExited: container.state = ''
        onReleased: container.state = ''//selectable && !selected ? selected = true : selected = false
        onHoveredChanged:  {
            !selected ? selected = true : selected = false
        }
    }
    states: [
        State {
            name: 'pressed'; when: mouseArea.pressed
            PropertyChanges { target: background; color: "#cae7fa" }
        },
        State {
            name: 'selected'
            PropertyChanges { target: background; color: "#cae7fa" }
        }
    ]

//    states: [
//        State {
//            name: 'pressed'; when: mouseArea.pressed
//            PropertyChanges { target: background; source: bgImagePressed; border { left: 35; top: 35; right: 35; bottom: 10 } }
//        },
//        State {
//            name: 'selected'
//            PropertyChanges { target: background; source: bgImageSelected; border { left: 35; top: 35; right: 35; bottom: 10 } }
//        }
//    ]
}
