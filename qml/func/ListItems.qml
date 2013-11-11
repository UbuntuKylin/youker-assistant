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
Item {
    id: container
    property string fontName: "Helvetica"
    property int fontSize: 10
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""
    property string bgImage: '../img/icons/list_item.png'
    property string bgImageSelected: '../img/icons/list_item_selected.png'
    property string bgImagePressed: '../img/icons/list_item_pressed.png'
    property bool selected: false
    property bool selectable: false
    property bool checkbox_status: true
    property bool split_status: false
    property string btn_flag: "cookies_scan"
    property string browserFlag//浏览器标记
    signal clicked

    width: 850
    height: 30
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''
    onCheckbox_statusChanged: {checkbox.checked=checkbox_status}  //当父项传进来的check值改变时，强制改变全部子项的check值以进行统一控制


    Connections
    {
        target: systemdispatcher
        onFinishCleanWork: {
//            if (btnFlag == "cookies_work") {
                if (msg == "") {
                    console.log("clean failed....");
                }
                else if (msg == "cookies") {
                    console.log("clean success....");
                    container.clicked();
                }
        }
    }

    function get_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    BorderImage {
        id: background
        border { top: 9; bottom: 36; left: 35; right: 35; }
        source: bgImage
        anchors.fill: parent
    }
    Text {
        id: itemText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        font {
            family: container.fontName
            pointSize: container.fontSize
            bold: container.fontBold
        }
        color: container.fontColor
        elide: Text.ElideRight
        text: container.split_status ? get_last_name(container.text) : container.text
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        text: container.size_num
        anchors {
            right: bitButton.left
            top: parent.top
            rightMargin: 40
            verticalCenter: container.verticalCenter
        }
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }
    Common.Button {
        id: bitButton
        anchors {
            right: parent.right
            rightMargin: 100
            verticalCenter: parent.verticalCenter
        }
        hoverimage: "blue1.png"
        text: "删除"
        fontcolor: "#086794"
        width: 60
        height: 20
        onClicked: {
            console.log(itemText.text);
            console.log(container.browserFlag);
            systemdispatcher.set_user_homedir_qt();
            systemdispatcher.cookies_clean_record_function_qt(container.browserFlag, itemText.text);

        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: itemText
//        onClicked: container.clicked();
        onReleased: selectable && !selected ? selected = true : selected = false
    }

    states: [
        State {
            name: 'pressed'; when: mouseArea.pressed
            PropertyChanges { target: background; source: bgImagePressed; border { left: 35; top: 35; right: 35; bottom: 10 } }
        },
        State {
            name: 'selected'
            PropertyChanges { target: background; source: bgImageSelected; border { left: 35; top: 35; right: 35; bottom: 10 } }
        }
    ]
}
