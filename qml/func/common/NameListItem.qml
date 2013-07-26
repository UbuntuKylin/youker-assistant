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
Item {
    id: container
    property string fontName: "Helvetica"
    property int fontSize: 10
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""
    property string bgImage: '../../img/icons/list_item.png'
    property string bgImageSelected: '../../img/icons/list_item_selected.png'
    property string bgImagePressed: '../../img/icons/list_item_pressed.png'
    property bool selected: false
    property bool selectable: false
    property int textIndent: 0
    property bool checkbox_status: true

    property string btn_flag: "one_key_scan"

    signal clicked

    width: 360
    height: 64
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''

    BorderImage {
        id: background
        border { top: 9; bottom: 36; left: 35; right: 35; }
        source: bgImage
        anchors.fill: parent
    }

    Image {
        id: btnImg
        anchors.fill: parent
    }
    Text {
        id: itemText
        anchors {
            left: parent.left
            top: parent.top
            topMargin: 4
            bottomMargin: 4
            leftMargin: 10// + textIndent
            verticalCenter: container.verticalCenter
        }
        font {
            family: container.fontName
            pointSize: container.fontSize
            bold: container.fontBold
        }
        color: container.fontColor
        elide: Text.ElideRight
        text: container.text
        verticalAlignment: Text.AlignVCenter
    }


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
//        onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""
        //鼠标放上时
        onEntered: {
            btnImg.source = "../../img/toolWidget/menu_hover.png"
//            if (text == "homepage") {
//                btnImg.source = "./img/toolWidget/homepage-hover.png"
//            }

        }
        //鼠标按下时
        onPressed: {
//            if (text == "homepage") {
//                btnImg.source = "./img/toolWidget/homepage-hover.png"
//            }

        }
        //要判断松开是鼠标位置
        //鼠标按下松开时
        onReleased: {
            selectable && !selected ? selected = true : selected = false
//            if (text == "homepage") {
//                btnImg.source = "./img/toolWidget/homepage.png"
//            }

        }
        //鼠标按下松开再移开时
        onExited: btnImg.source = ""

        onClicked: container.clicked();
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
