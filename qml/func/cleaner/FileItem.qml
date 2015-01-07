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
    property int fontSize: 10
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
    property string itemFlag//1210 apt/soft标记 //1212 cache
    property string browserFlag//浏览器标记
    signal change_num(bool check_status, string browser_flag)   //作为子项checkbox，当状态改变时需要通过信号传给父项以进行个数统计
    signal clicked

    signal getFileItemCheckBoxStatus(bool status, int index); //test

    width: 850 - 2
    height: 30
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''
    onCheckbox_statusChanged: {checkbox.checked=checkbox_status}  //当父项传进来的check值改变时，强制改变全部子项的check值以进行统一控制

    function get_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: (container.item_index%2 == 0) ? "#d7ecfb" : "transparent"
     }
    Common.CheckBox {
        id: checkbox
//        width: 30
        checked: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30

        onClicked: {
            container.getFileItemCheckBoxStatus(checkbox.checked, item_index);
        }

        onCheckedChanged: {
            //单个checkbox状态改变时，先将状态通过信号change_num()传递给BrowserCookies.qml
            container.change_num(checkbox.checked, container.browserFlag);
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
            width: 12
            height: 12
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
    //        text: get_last_name(container.text)
            text: container.split_status ? get_last_name(container.text) : container.text
            verticalAlignment: Text.AlignVCenter
        }

    }

    Text {
        text: {
            if(btn_flag == "largestfile_work") {
                container.descript
            }
            else {
                ""
            }
        }
        visible: (btn_flag == "largestfile_work") ? true : false
        anchors {
            left: itemText.right
            top: parent.top
            leftMargin: 20
            verticalCenter: container.verticalCenter
        }
        wrapMode: Text.WordWrap
        width: 700
        font.pixelSize: container.fontSize
        font.family: container.fontName
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
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
}
